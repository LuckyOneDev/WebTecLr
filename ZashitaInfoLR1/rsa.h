#pragma once
#include <iostream>
#include <vector>
#include <mpirxx.h>
#include <sstream>

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
    mpz_class c;
    mpz_powm(c.get_mpz_t(), message.get_mpz_t(), keys.e.get_mpz_t(), keys.n.get_mpz_t());
    return c;
}

// Function to decrypt a message using RSA encryption
mpz_class decrypt(mpz_class ciphertext, key_struct keys) {
    // Calculate m = c^d (mod n)
    mpz_class message;
    mpz_powm(message.get_mpz_t(), ciphertext.get_mpz_t(), keys.d.get_mpz_t(), keys.n.get_mpz_t());
    return message;
}

// Encodes a string to an mpz_class
std::vector<mpz_class> encode(string str) {
    std::vector<mpz_class> result;
    for (int i = 0; i < str.length(); i++) {
        mpz_class cur;
        mpz_import(cur.get_mpz_t(), 1, 1, 1, 0, 0, &str[i]);
        result.push_back(cur);
    }
    return result;
}

// Decodes an mpz_class to a string
string decode(std::vector<mpz_class> message) {
    std::stringstream ss;
    for (auto& letter : message) // access by reference to avoid copying
    {
        ss << (char)letter.get_ui();
    }
    return ss.str();
}

int lr2(std::string text, int bits = 1024) {
    // Generate two random prime numbers of 1024 bits each
    mpz_class p, q, n, e, d, phi;
    p = generate_prime(bits);
    q = generate_prime(bits);

    // Calculate the public and private keys
    auto keys = get_keys(p, q);

    // Encode
    std::vector<mpz_class> message = encode(text);
    // Encrypt the message
    std::vector<mpz_class> ciphertext;
    for (auto letter : message)
    {
        ciphertext.push_back(encrypt(letter, keys));
    }
    
    // Encrypt the message
    std::vector<mpz_class> decrypted_message;
    for (auto letter : ciphertext)
    {
        decrypted_message.push_back(decrypt(letter, keys));
    }
    
    // Print
    auto decoded_orig = decode(message);
    auto decoded_after_ci = decode(decrypted_message);
    std::cout << "Message: " << decoded_orig << std::endl;
    std::cout << "Decrypted message: " << decoded_after_ci << std::endl;

    return 0;
}