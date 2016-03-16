//
// Created by François Caillet on 11/03/2016.
//

#include "utils.h"

// How to : cat message.txt | ./chiffre fc_XXX >> message.chiffre
// Or cat message.txt | ./chiffre fc_XXX

int main( int argc, char * argv [] )
{

    if (argc != 2){
        cout << "usage: " << argv[0] << "[name]" << endl;
        cout << "\t [name].pub " << endl;
        exit(1);
    }

    //string clair = readInput( cin );

    string line = "";
    string name = argv[1];
    string filename = name + ".pub";
    vector<string> x;
    int t = 0;
    mpz_t n, b;

    mpz_init(n);
    mpz_init(b);

    ifstream keypub(filename);
    if (!keypub.is_open()) {
        cerr << "Unable to open file";
        exit(1);
    }
    getline (keypub, line);
    x = tokenizer(line, ' ');
    t = atoi(x[0].c_str());
    mpz_set_str(n,x[1].c_str(),10);
    mpz_set_str(b,x[2].c_str(),10);

    keypub.close();

    chiffre(t,n,b);

    mpz_clears(n,b,NULL);

    return 0;
}