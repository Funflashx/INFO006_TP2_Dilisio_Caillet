//
// Created by François Caillet on 11/03/2016.
//

#include "utils.h"


void HashMD5(unsigned char* pPlain, int nPlainLen, unsigned char* pHash)
{
    MD5(pPlain, nPlainLen, pHash);
}

string dechiffre(int t, const mpz_t a,const mpz_t n){


    int bytes = t / 8 ;
    string line = "";
    char block[bytes];
    mpz_t clair;
    mpz_t crypte;
    mpz_init(clair);
    mpz_init(crypte);

    string clair_str = "";
    while ( getline(cin,line))
    {
        if (line[0] != '#')
        {
            mpz_set_str(crypte,line.c_str(),10);
            mpz_powm(clair,crypte,a,n);
            mpz_export (block, NULL, 0, sizeof block, 0, 0,clair);

            for (int i = bytes-1; i >= 0 ; --i)
            {
                clair_str += block[i];
                //cout << block[i] << endl;
            }
        }
    }
    mpz_clears(clair,crypte,NULL);
    return clair_str;

}

string ECB(const string & data, int blocksize, int p){
    string out = "";
    out += data.substr(p, blocksize+1);
    return out;
}

int letterToASCII(char x)
{
    return (int)x;
}

unsigned long int wordToNumber(string block){
    int t;
    unsigned long int clair;
    t = block.length();

    stringstream oss;

    for (unsigned int i = 0; i < t-1; i++)
    {
        oss << letterToASCII(block[i]);
    }

    istringstream iss(oss.str());
    iss >> clair;

    return clair;
}


void chiffre(int t, const mpz_t n, const mpz_t b){
    int bytes = t / 8 ;

    char block[bytes];
    int bytes_read = 0;
    int block_read = 0;
    int c_read;
    mpz_t clair, crypte;
    mpz_init(clair);
    mpz_init(crypte);

    while (!cin.eof())
    {
        cin.read(block,bytes);
        c_read = cin.gcount();
        memset(block,0,bytes-c_read);
        mpz_import(clair, bytes, 1, sizeof(block[0]), 0, 0, block);

        mpz_powm(crypte,clair,b,n);
        gmp_printf("%Zd\n",crypte);

        bytes_read += c_read;
        ++block_read;
    }
    cout << "# "<< bytes_read << " bytes read, " <<  block_read << " blocs read." << endl;
    mpz_clears(clair, crypte, NULL);
}

vector<string> tokenizer( const string& p_pcstStr, char delim )  {
    vector<string> tokens;
    stringstream   mySstream( p_pcstStr );
    string         temp;

    while( getline( mySstream, temp, delim ) ) {
        tokens.push_back( temp );
    }

    return tokens;
}

string readInput( istream & in )
{
    ostringstream s( ostringstream::out );
    while ( in.good() )
    {
        char c;
        in >> c;
        s << c;
    }
    return s.str();
}

void find_prime_number(int t, gmp_randstate_t r_state, mpz_t n){ //n est le block
    int reps = 0;

/**
 * reps = 2     if n is definitely prime
 * reps = 1     if n is probably prime (without being certain)
 * reps = 0     if n is definitly composite. There should be it.
 * **/


    do {
        mpz_urandomb(n, r_state, t);

    } while (!mpz_probab_prime_p(n, reps));//C'est probablement un prime


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


