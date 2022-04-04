//
// Created by user on 2021-12-11.
//

#ifndef CHIPFALCON_NIST_H
#define CHIPFALCON_NIST_H
void randombytes_init(unsigned char *entropy_input,
                      unsigned char *personalization_string,
                      int security_strength);
int randombytes(unsigned char *x, unsigned long long xlen);

int
crypto_sign_keypair(unsigned char *pk, unsigned char *sk);

int
crypto_sign(unsigned char *sm, unsigned long long *smlen,
            const unsigned char *m, unsigned long long mlen,
            const unsigned char *sk);
int
crypto_sign_open(unsigned char *m, unsigned long long *mlen,
                 const unsigned char *sm, unsigned long long smlen,
                 const unsigned char *pk);

#endif //CHIPFALCON_NIST_H
