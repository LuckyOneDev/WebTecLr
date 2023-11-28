#pragma once
#include <iostream>
#include <mpir.h>

using namespace std;

// Function to generate a random prime number of given bit length
void generate_prime(mpz_t random_number, int bit_length) {
    // Initialize a random number generator
    gmp_randstate_t state;
    gmp_randinit_default(state);
    // Generate a random number of the given bit length
    mpz_init(random_number);
    gmp_randseed_ui(state, time(NULL));
    mpz_urandomb(random_number, state, bit_length);
    // Find the next prime number
    mpz_nextprime(random_number, random_number);
    // Clear the random number if it's not prime
    while (!mpz_probab_prime_p(random_number, 25)) {
        mpz_clear(random_number);
        mpz_init(random_number);
        gmp_randseed_ui(state, time(NULL));
        mpz_urandomb(random_number, state, bit_length);
        mpz_nextprime(random_number, random_number);
    }
}

// Function to calculate the public key for RSA encryption
void calculate_public_key(mpz_t n, mpz_t p, mpz_t q) {
    mpz_init(n);
    mpz_mul(n, p, q);

    // Calculate ϕ(n) = (p - 1) * (q - 1)
    mpz_t phi_n;
    mpz_init(phi_n);
    mpz_sub_ui(p, p, 1);
    mpz_sub_ui(q, q, 1);
    mpz_mul(phi_n, p, q);

    // Calculate e such that 1 < e < ϕ(n) and gcd(e, ϕ(n)) = 1
    mpz_t e;
    gmp_randstate_t state;
    gmp_randinit_default(state);

    mpz_init(e);
    mpz_urandomm(e, state, n);
    mpz_t gcd;
    mpz_init(gcd);
    mpz_gcd(gcd, e, phi_n);
    while (mpz_get_ui(gcd) != 1) {
        mpz_clear(e);
        mpz_init(e);
        mpz_urandomm(e, state, phi_n);
        mpz_gcd(gcd, e, phi_n);
    }

    // Calculate d such that e * d ≡ 1 (mod ϕ(n))
    mpz_t d;
    mpz_init(d);
    mpz_invert(d, e, phi_n);
}

// Function to encrypt a message using RSA encryption
void encrypt(mpz_t c, mpz_t message, mpz_t n, mpz_t e) {
    // Calculate c = m^e (mod n)
    mpz_init(c);
    mpz_powm(c, message, e, n);
}

// Function to decrypt a message using RSA encryption
void decrypt(mpz_t message, mpz_t ciphertext, mpz_t n, mpz_t d) {
    // Calculate m = c^d (mod n)
    mpz_init(message);
    mpz_powm(message, ciphertext, d, n);
}

int lr2() {
    // Generate two random prime numbers of 1024 bits each
    mpz_t p, q;
    generate_prime(p, 1024);
    generate_prime(q, 1024);

    // Calculate the public key (n, e)
    mpz_t n;
    calculate_public_key(n, p, q);
    mpz_t e;
    calculate_public_key(e, p, q);

    // Calculate the value of d
    mpz_t d;
    mpz_t phi;
    mpz_init(d);
    mpz_init(phi);
    mpz_sub_ui(p, p, 1);
    mpz_sub_ui(q, q, 1);
    mpz_mul(phi, p, q);
    mpz_invert(d, e, phi);

    // Generate a message to encrypt
    mpz_t message;
    mpz_init(message);
    mpz_set_str(message, "Hello world!", 10);

    // Encrypt the message
    mpz_t ciphertext;
    mpz_init(ciphertext);
    encrypt(ciphertext, message, n, e);

    // Decrypt the message
    mpz_t decrypted_message;
    mpz_init(decrypted_message);
    decrypt(decrypted_message, ciphertext, n, d);

    // Print the decrypted message
    printf("Decrypted message: %s\n", mpz_get_str(NULL, 10, decrypted_message));

    return 0;
}