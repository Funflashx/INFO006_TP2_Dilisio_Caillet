# INFO006_TP2_Dilisio_Caillet
Cryptosystème à clé publique RSA (version simplifiée)

##Installation

 ```bash
   make 
 ```
 
##Réalisation
- [x] gencle [nom] [t] : génère une paire de clé pour des blocs de taille [t] et les sauve dans les fichiers [nom].pub et [nom].priv
- [x] chiffre [nom] : chiffre le message sur l'entrée standard pour le destinataire de clé [nom].pub et sort le message chiffré sur la sortie standard
- [x] dechiffre [nom] : déchiffre le message sur l'entrée standard pour le récipendiaire [nom] et sort le message clair sur la sortie standard. On note que le programme va rechercher la clé privée dans le fichier [nom].priv de l'utilisateur.
- [x] signe : sort la signature sur la sortie standard. 
- [x] verifie [fichier-signature] : vérifie que le fichier-signature est bien la signature du message donné sur l'entrée standard pour l'émetteur [nom]. 
- [ ] fonction d'inverse modulaire , Non fonctionnel 
```c++
        mpz_t _N, _M, _RESULT;
        mpz_init(_N);
        mpz_init(_M);
        mpz_set_ui(_N,109);
        mpz_set_ui(_M,4567);
        mpz_init(_RESULT);
        inverse_modulaire(_N,_M,_RESULT); //util.h
        gmp_printf("INVERSE DE N MODULO M = %Zd\n", _RESULT);
    
//        NON FONCTIONNEL ...
//        Algorithme suivie :
//                    def inverseModulaire(a, n):
//                        return bezoutRec(a,n)[0]+n
//    
//                    def bezoutRec(a, b):
//                        if ( a% b == 0):
//                            return (0,1)
//                        else:
//                            r,q = a%b, a//b
//                            u, v = bezoutRec(b, r)
//                            return (v, u-v*q)                            
```

##Utilisation 
###./gencle \[name\] \[t\]
```bash
usage: ./gencle[name] [t]
         [name] -- Nom des fichiers, [nom].pub et [nom].priv
         [t] -- Taille des blocs.
         génère une paire de clé pour des blocs de taille [t] et les sauve dans les fichiers [nom].pub et [nom].priv
```
* EX:
```bash
./gencle fc_1024 1024

# generating RSA keys for bloc sizefc_1024bits.1# p,q pair generated. public n is
19872820959036495284170307648339339173360902989166649400255452947128455071828473794169624683545117304424863707975173723839183165448079440837311425136107464293912343206409157317740777464286762973026500496598588850992876492240726133854319272155323991222390834073864525625940006415000008595063923256423605528056385929463
# a,b pair generated. public b is
0
# check a*b=1 mod phi(n), a*b=1
# NON-OK : restart gencle

>>>>restart... 

# generating RSA keys for bloc sizefc_1024bits.1# p,q pair generated. public n is
81383538613220303460459716361579701350859779707537249179057711414670284899028574262377222436038441906465357715614198186901532182142105350334597677839828752161712413421620253862957083320599872403626800801328077311948603204563909766127241230689355988319006045952057115712983424032872732771453267480666681893163499432237
# a,b pair generated. public b is
68525426270871850845393741526449480906882630840672581649337968524013854363590762420126505574504877943634825432512109151371867143114863170762771167924277650386143638828082251514823762182488332518327437123988930617878538072410187892226777490817399061417102041169414291900121110794792380412400739295955232428724168819377
# check a*b=1 mod phi(n), a*b=1
# OK : paire de cle stockee dans fc_1024.priv

##########PUBLIC KEY##########
1024 81383538613220303460459716361579701350859779707537249179057711414670284899028574262377222436038441906465357715614198186901532182142105350334597677839828752161712413421620253862957083320599872403626800801328077311948603204563909766127241230689355988319006045952057115712983424032872732771453267480666681893163499432237 68525426270871850845393741526449480906882630840672581649337968524013854363590762420126505574504877943634825432512109151371867143114863170762771167924277650386143638828082251514823762182488332518327437123988930617878538072410187892226777490817399061417102041169414291900121110794792380412400739295955232428724168819377
# Public RSA keys: t n b

```

###./chiffre [name]
```bash
usage: ./chiffre[name]
         [name].pub 
         chiffre le message sur l'entrée standard pour le destinataire de clé [nom].pub et sort le message chiffré sur la sortie standard
```
* EXs:
```bash
cat message.txt | ./chiffre fc_32 >> message.chiffre
```
```bash
message.txt | ./chiffre fc_32

cat message.txt | ./chiffre fc_64  
6308558201374194995246053818
4892507329769254971186376326
47712238611703288618361854
4971163128536049694461745644
3845371055203111505360574381
4443587153914895755449475703
4873344356730135139199277434
393971731995645199951130912
2123459607820860183038071640
7706832527451482571442442093
3844851469903034702652021046
5650770503492972414844702588
6768488553386812099579388222
6244047914022546572468555482
# 111 bytes read, 14 blocs read.

```

###./dechiffre [name]
```bash
usage: ./dechiffre[name]
         [name].priv 
         déchiffre le message sur l'entrée standard pour le récipendiaire [nom] et sort le message clair
         sur la sortie standard. On note que le programme va rechercher la clé privée dans le fichier [nom].priv 
         de l'utilisateur.
```
* EXs:
```bash
cat message.chiffre | ./dechiffre fc_32
“- Ah ! Seigneur ! Donnez-moi la force et le courage De contempler mon coeur et mon corps sans dégoût !��
�
```
- [ ] bug 1 : la fin est illisible (toutefois le texte est clair...), cause : 0 de bourrage ? 

```bash
cat message.txt | ./chiffre fc_32 | ./dechiffre fc_32 

```

###./signe 
EXs:
```bash
echo -n hello | ./signe 
b373870b9139bbade83396a49b1afc9a`
```

```bash
echo -n hello | ./signe fc_XXX | ./chiffre fc_XXX >> empreinte.chiffre
```

###./verifie
```bash
usage: ./verifie[fichier]
         [fichier] -- ficher pour comparer (le clair, l'empreinte)
         prend en entrée standard le dechiffré donc l'autre empreinte
```

```
cat message.chiffre | ./dechiffre fc_32Red | verifie message
```
(non fonctionel à cause du bug 1)