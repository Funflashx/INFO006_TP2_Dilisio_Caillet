//
// Created by François Caillet on 11/03/2016.
//

#include "utils.h"


int main( int argc, char * argv [] ) {

    if (argc != 2){
        cout << "usage: " << argv[0] << "[name]" << endl;
        cout << "\t [name].priv " << endl;
        exit(1);
    }

    string line = "";
    string name = argv[1];
    string filename = name + ".priv";
    vector<string> x;
    int t = 0;
    mpz_t n,p,q,a,b;

    mpz_init(n);
    mpz_init(p);
    mpz_init(q);
    mpz_init(a);
    mpz_init(b);

    ifstream keypriv(filename);
    if (!keypriv.is_open()) {
        cerr << "Unable to open file";
        exit(1);
    }
    getline (keypriv, line);
    x = tokenizer(line, ' ');
    t = atoi(x[0].c_str());
    mpz_set_str(n,x[1].c_str(),10);
    mpz_set_str(p,x[2].c_str(),10);
    mpz_set_str(q,x[3].c_str(),10);
    mpz_set_str(a,x[4].c_str(),10);
    mpz_set_str(b,x[5].c_str(),10);

    keypriv.close();

    cout << dechiffre(t,a,n) << endl;

    mpz_clears(n,p,q,a,b,NULL);


}