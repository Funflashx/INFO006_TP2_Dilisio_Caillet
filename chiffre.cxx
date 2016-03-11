//
// Created by François Caillet on 11/03/2016.
//

#include "utils.h"


int main( int argc, char * argv [] )
{

    if (argc != 2){
        cout << "usage: " << argv[0] << "[-p][name]" << endl;
        cout << "\t [name].pub " << endl;
        cout << "\t if -p so .my_rsa_keys/[name].pub" << endl;
        exit(1);
    }

    string clair = readInput( cin );

    string line = "";
    string name = argv[1];
    string filename = name + ".pub";
    vector<string> x;
    int t = 0;
    mpz_t n, b;

    mpz_init(n);
    mpz_init(b);

    ifstream keypub(filename);
    if (keypub.is_open())
    {
        getline (keypub, line);
        x = tokenizer(line, ' ');
        t = atoi(x[0].c_str());
        mpz_set_str(n,x[1].c_str(),10);
        mpz_set_str(b,x[2].c_str(),10);

        keypub.close();
    } else cerr << "Unable to open file";



    gmp_printf("N = %Zd\nB = %Zd\n",n,b);
    chiffre(clair,t,n,b);

    mpz_clears(n,b);

    return 0;
}