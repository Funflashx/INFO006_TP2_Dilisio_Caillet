//
// Created by François Caillet on 14/03/2016.
//


#include "utils.h"

//How to : echo -n hello | ./signe fc_XXX | ./chiffre fc_XXX >> empreinte.chiffre

int main( int argc, char ** argv ) {

    string message = readInput(cin);
    unsigned char empreint[16];

    HashMD5((unsigned char *) message.c_str(), message.size(),empreint);

    for (int i = 0; i < 16; ++i) {
        fprintf(stdout,"%02x", empreint[i]);
    }

    return 0;
}