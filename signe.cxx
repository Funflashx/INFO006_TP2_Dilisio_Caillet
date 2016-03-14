//
// Created by François Caillet on 14/03/2016.
//


#include "utils.h"

int main( int argc, char ** argv ) {

    if (argc != 2) {
        cout << "usage: " << argv[0] << "[name]" << endl;
        cout << "\t [name] -- [nom].priv pour obtenir la clé privée." << endl;
        exit(1);
    }

    string line = "";
    string name = argv[1];
    string filename = name + ".priv";
    string message = readInput(cin);
    unsigned char empreint[16];
    vector<string> x;
    HashMD5((unsigned char *) message.c_str(), message.size(),empreint);

    for (int i = 0; i < 16; ++i) {
        fprintf(stdout,"%02x", empreint[i]);
    }

    return 0;
}