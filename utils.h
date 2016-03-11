//
// Created by François Caillet on 11/03/2016.
//

#include <iostream>
#include <stdio.h>
#include <utility>
#include <sys/types.h>
#include <unistd.h>
#include <sys/time.h>
#include <time.h>
#include <gmp.h>
#include <gmpxx.h>
#include <sys/stat.h>
#include <fstream>
#include <sstream>
#include <vector>


#ifndef utils
#define utils

using namespace std;

typedef pair<mpz_t,mpz_t> Valeur;

string readInput( std::istream & in );
vector<string> tokenizer( const string& p_pcstStr, char delim );

void find_prime_number(int t, gmp_randstate_t r_state, mpz_t n);
void random_e(mpz_t phy, int t, gmp_randstate_t r_state, mpz_t e);
void gencle(string name, int t);

void chiffre(string plain,int t, mpz_t n,  mpz_t b);

#endif //UTILS_H
