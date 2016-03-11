//
//  gencle.cpp
//  TP2-RSA-Caillet-Dilisio
//
//  Created by François Caillet on 09/03/2016.
//  Copyright © 2016 François Caillet. All rights reserved.
//

#include "utils.h"

struct timeval tv;

int main( int argc, char ** argv ) {

    if (argc != 3) {
        cout << "usage: " << argv[0] << "[name] [t]" << endl;
        cout << "\t [name] -- Nom des fichiers, [nom].pub et [nom].priv" << endl;
        cout << "\t [t] -- Taille des blocs." << endl;
        exit(1);
    }

    cout << "# generating RSA keys for bloc size" << argv[1] << "bits." << cout;

    mpz_t p, q, n, b, phy_n, p2, q2, a, ab, r;
    unsigned long int seed;
    int taille = atoi(argv[1]);
    string name = argv[2];


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
    utils::find_prime_number((taille/2)+16,r_state,p);
    utils::find_prime_number((taille/2)+16,r_state,q);

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

    utils::random_e(phy_n,taille+32,r_state,a);
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


    return 0;
}
