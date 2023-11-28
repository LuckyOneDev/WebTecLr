#pragma once
#include <iostream>
#include <tuple>
#include <mpirxx.h>

using namespace std;
// Function to generate a random prime number of given bit length
mpz_class generate_prime(int bit_length) {
    mpz_class random_number;
    // Initialize a random number generator
    gmp_randclass r(gmp_randinit_default);
    r.seed(time(NULL));
    // Generate a random number of the given bit length
    random_number = r.get_z_bits(bit_length);
    // Find the next prime number
    mpz_nextprime(random_number.get_mpz_t(), random_number.get_mpz_t());
    // Clear the random number if it's not prime
    while (!mpz_probab_prime_p(random_number.get_mpz_t(), 25)) {
        random_number = r.get_z_bits(bit_length);
        mpz_nextprime(random_number.get_mpz_t(), random_number.get_mpz_t());
    }
    return random_number;
}

struct key_struct {
    mpz_class e;
    mpz_class n;
    mpz_class d;
};

// Function to calculate the public key for RSA encryption
key_struct get_keys(mpz_class p, mpz_class q) {
    key_struct keys;
    mpz_class n = p * q;
    // Calculate ϕ(n) = (p - 1) * (q - 1)
    mpz_class phi_n = (p - 1) * (q - 1);
        
    // Calculate e such that 1 < e < ϕ(n) and gcd(e, ϕ(n)) = 1
    gmp_randclass r(gmp_randinit_default);
    mpz_class e, gcd;
    do {
        e = r.get_z_range(phi_n - 1) + 1;
        mpz_gcd(gcd.get_mpz_t(), e.get_mpz_t(), phi_n.get_mpz_t());
    } while (gcd != 1);

    mpz_class d;
    mpz_invert(d.get_mpz_t(), e.get_mpz_t(), phi_n.get_mpz_t());
    keys.d = d;
    keys.e = e;
    keys.n = n;
    return keys;
}

// Function to encrypt a message using RSA encryption
mpz_class encrypt(mpz_class message, key_struct keys) {
    // Calculate c = m^e (mod n)
    
    mpz_powm(c, message, e, n);
}

// Function to decrypt a message using RSA encryption
mpz_class decrypt(mpz_class message, key_struct keys) {
    // Calculate m = c^d (mod n)
    mpz_init(message);
    mpz_powm(message, ciphertext, d, n);
}

int lr2() {
    // Generate two random prime numbers of 1024 bits each
    mpz_class p, q, n, e, d, phi;
    p = generate_prime(1024);
    q = generate_prime(1024);

    // Calculate the public key (n, e)
    auto pub = get_keys(p, q);

    // Calculate the value of d
    mpz_class d;
    mpz_class phi;
    mpz_sub_ui(p, p, 1);
    mpz_sub_ui(q, q, 1);
    mpz_mul(phi, p, q);
    mpz_invert(d, pub, phi);

    // Generate a message to encrypt
    mpz_t message;
    mpz_init(message);
    mpz_set_str(message, "15211\0", 10);

    // Encrypt the message
    mpz_t ciphertext;
    mpz_init(ciphertext);
    encrypt(ciphertext, message, n, e);
    printf("Ciphertext: %s\n", mpz_get_str(NULL, 10, ciphertext));

    // Decrypt the message
    mpz_t decrypted_message;
    mpz_init(decrypted_message);
    decrypt(decrypted_message, ciphertext, n, d);

    // Print the decrypted message
    printf("Decrypted message: %s\n", mpz_get_str(NULL, 10, decrypted_message));

    return 0;
}