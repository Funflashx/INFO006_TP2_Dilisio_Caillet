####################################################
# A remplir par vous
# Repertoire GMP
GMPDIR=/usr/local
# Vos sources C, par exemple : SRC=source.c
SRC=
# Vos sources C++, par exemple : SRCXX=source2.cxx
SRCXX=utils.cxx
# Vos executables C, par exemple : EXEC=progc
EXEC=
# Vos executables C++, par exemple : EXECXX=progcxx
EXECXX=gencle chiffre

####################################################
# ne pas toucher
INCDIR=-I${GMPDIR}/include
LIBDIR=-L${GMPDIR}/lib
RUNTIMELIB=${GMPDIR}/lib
LIBS=-lgmp
LIBSXX=-lgmpxx -lgmp
CC=gcc -g -c
CXX=g++ -g -Wall -c
LD=gcc -Xlinker -rpath -Xlinker ${RUNTIMELIB}
LDXX=g++ -Xlinker -rpath -Xlinker ${RUNTIMELIB}
OBJ=${SRC:.c=.o}
OBJXX=${SRCXX:.cxx=.o}

all: $(EXEC) $(EXECXX)

%.o: %.cx
	$(CC) $(INCDIR) $<

%.o: %.cxx
	$(CXX) $(INCDIR) $<

# Gencle prog
gencle: $(OBJXX) gencle.cxx
	$(CXX) -c $(INCDIR) $@.cxx
	$(LDXX) $@.o $(OBJXX) $(LIBDIR) $(LIBSXX) -o $@

chiffre: $(OBJXX) chiffre.cxx
	$(CXX) -c $(INCDIR) $@.cxx
	$(LDXX) $@.o $(OBJXX) $(LIBDIR) $(LIBSXX) -o $@


clean:
	rm -f $(EXEC) $(EXEC:=.o) $(EXECXX) $(EXECXX:=.o) $(OBJ) $(OBJXX)