//
// Created by François Caillet on 14/03/2016.
//


#include "utils.h"

//How to : cat message.chiffre | ./dechiffre fc_XXX | verifie message

int main( int argc, char ** argv ) {

    if (argc != 2) {
        cout << "usage: " << argv[0] << "[fichier-signature]" << endl;
        cout << "\t [name] -- [nom].priv" << endl;
        cout << "\t [fichier-signature] -- ficher à vérifier" << endl;
        exit(1);
    }

    string name = argv[1];
    string data = "";
    string line = "";
    string filename = name + ".txt";
    string empreint = readInput(cin);

    ifstream msgClr(filename);
    if (!msgClr.is_open()) {
        cerr << "Unable to open file";
        exit(1);
    }
    while (getline (msgClr, line)){
        data += line + "\n";
    }

    unsigned char empreint_generate[16];
    char empreint_generate_str[16];

    HashMD5((unsigned char *) data.c_str(), data.size(), empreint_generate);

    for (int i = 0; i < 16; ++i) {
        fprintf(stdout,"%02x", empreint_generate[i]);
    }

    if (strcmp(empreint.c_str(),empreint_generate_str)==0){
        cout << "# Vefification OK" << endl;
    } else{
        cout << "# Vefification NOK" << endl;
    }

    fprintf(stdout, "%s == %s\n", empreint.c_str(), empreint_generate_str);

    return 0;

}
