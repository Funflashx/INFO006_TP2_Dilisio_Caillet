//
// Created by François Caillet on 14/03/2016.
//


#include "utils.h"

int main( int argc, char ** argv ) {

    if (argc != 3) {
        cout << "usage: " << argv[0] << "[nom] [fichier-signature]" << endl;
        cout << "\t [name] -- [nom].pub" << endl;
        cout << "\t [fichier-signature] -- ficher à vérifier" << endl;
        exit(1);
    }

    string name = argv[1];
    string filename = name + ".pub";

}
