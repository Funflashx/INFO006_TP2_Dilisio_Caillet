//
//  util.cpp
//  TP2-RSA-Caillet-Dilisio
//
//  Created by François Caillet on 09/03/2016.
//  Copyright © 2016 François Caillet. All rights reserved.
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

using namespace std;

struct timeval tv;

typedef pair<mpz_t,mpz_t> Valeur;

/*void inverse_modulaire(mpz_t a, mpz_t n, mpz_t r);
void bezout_rec(mpz_t a, mpz_t b,  Valeur r);*/
void gencle(string name, int t);
void find_prime_number(int t, gmp_randstate_t r_state, mpz_t n);

int main( int argc, char ** argv ) {

    if (argc != 3) {
        cout << "usage: " << argv[0] << " [name] [t]" << endl;
        cout << "\t [name] -- Nom des fichiers, [nom].pub et [nom].priv" << endl;
        cout << "\t [t] -- Taille des blocs." << endl;
        exit(1);
    }

    cout << "# generating RSA keys for bloc size" << argv[1] << "bits." << cout;
    gencle(argv[2], atoi(argv[1]));

    return 0;
}


/*void bezout_rec(mpz_t a, mpz_t b, Valeur r){
    Valeur v;
    mpz_t remainder, quotient;

    mpz_init(remainder);
    mpz_init(v.first);
    mpz_init(v.second);
    mpz_init(quotient);

    mpz_divmod(quotient,remainder,a,b);

    if ( mpz_cmp_ui(remainder, 0) == 0){
        mpz_init_set_str (v.first, "0", 10);
        mpz_init_set_str (v.second, "1", 10);
    } else {
        int q = a / b;
        v = bezout_rec(b, r);
        return make_pair(v.second, v.first-v.second*q);
    }
}

void inverse_modulaire(mpz_t a, mpz_t n, mpz_t r){
    bezout_rec(a, n, r);
    mpz_add(r,r.first,n);
    mpz_mod(r,r,n);
   // (bezout_rec(a, n).first+n);//%n;
}*/

void find_prime_number(int t, gmp_randstate_t r_state, mpz_t n){ //n est le result
    int reps = 0;

/**
 * reps = 2     if n is definitely prime
 * reps = 1     if n is probably prime (without being certain)
 * reps = 0     if n is definitly composite. There should be it.
 * **/

    do {
        mpz_urandomb(n, r_state, t);

    }while (!mpz_probab_prime_p ( n, reps ));//C'est probablement un prime
}


//Renvoie un nombre aléatoire e compris entre 2 et n-1  (n =p*q)  et qui est premier avec  (p-1)*(q-1)
void random_e(mpz_t phy, int t, gmp_randstate_t r_state, mpz_t e){

    mpz_t rop;
    mpz_init(rop);

    do {
        mpz_urandomb(e, r_state, t);
        mpz_gcd(rop,e,phy);

    }while (mpz_cmp_ui(rop,1) == 0 && mpz_cmp(e,phy) < 0);

    mpz_clear(rop);

}


void gencle(string name, int t){
    mpz_t p, q, n, b, phy_n, p2, q2, a, ab, r;
    unsigned long int seed;
    int taille = t;


    gmp_randstate_t r_state;

    seed = (int) getpid() + 65536*(int) getppid();

    if ( gettimeofday( &tv, NULL ) == 0 )
        seed += (int) (tv.tv_sec*1000000 + tv.tv_sec);

    gmp_randinit_default(r_state);
    gmp_randseed_ui(r_state, seed);

    //Initialisation des bigInt
    mpz_init(p);
    mpz_init(q);
    mpz_init(p2);
    mpz_init(q2);
    mpz_init(n);
    mpz_init(b);
    mpz_init(phy_n);
    mpz_init(a);
    mpz_init(ab);
    mpz_init(r);

    //Cherche p et q, deux nombres premiers distincts
    find_prime_number((taille/2)+16,r_state,p);
    find_prime_number((taille/2)+16,r_state,q);

    cout << "# p,q pair generated. public n is" << endl;
    // n = p*q
    mpz_mul (n, p, q);
    gmp_printf("%Zd\n", n);

    //(p-1)
    mpz_sub_ui (p2, p, 1);
    //(q-1)
    mpz_sub_ui (q2, q, 1);
    //(p-1)(q-1)
    mpz_mul (phy_n, p2, q2);

    random_e(phy_n,taille+32,r_state,a);
    mpz_invert(b,a,phy_n);
    cout << "# a,b pair generated. public b is" << endl;
    gmp_printf("%Zd\n", b);

    cout << "# check a*b=1 mod phi(n), a*b=1" << endl;
    mpz_mul (ab, a, b);
    mpz_mod (r,ab,phy_n);
    if(mpz_cmp_ui(r,1)==0){
        string filename_priv = name + ".priv";
        ofstream keypriv(filename_priv.c_str(), ios::out | ios::trunc );
        if (keypriv.is_open()){
            keypriv << taille << " " << n << " " << p << " " << q << " " << a << " " << b << "\n";
            string recap = "# Public/private RSA keys: t n p q a b\n";
            keypriv << recap;
            keypriv.close();
            chmod (filename_priv.c_str(), S_IRUSR | S_IWUSR);
            cout << "# OK : paire de cle stockee dans " << filename_priv << "\n" << endl;
        }else cerr << "This file cannot be create" << endl;

        string filename_pub = name + ".pub";
        ofstream keypub(filename_pub.c_str(), ios::out | ios::trunc );
        if (keypub.is_open()){
            keypub << taille << " " << n << " " << b << "\n";
            keypub.close();
            cout << "##########PUBLIC KEY##########" << endl;
            cout << taille << " " << n << " " << b << endl;
            string recap = "# Public RSA keys: t n b";
            cout << recap << endl;
        }else cerr << "This file cannot be create" << endl;


    } else {
        cout << "# NON-OK : restart gencle" << endl;
    }

    gmp_randclear(r_state);
    mpz_clears(p, q, n, b, phy_n, p2, q2, a, r);

}
