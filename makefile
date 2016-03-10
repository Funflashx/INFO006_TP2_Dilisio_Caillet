####################################################
# A remplir par vous
# Repertoire GMP
GMPDIR=/usr/local
# Vos sources C++, par exemple : SRCXX=source2.cxx
SRCXX=gencle.cxx
# Vos executables C++, par exemple : EXECXX=progcxx
EXECXX=gencle

####################################################
# ne pas toucher
INCDIR=-I${GMPDIR}/include
LIBDIR=-L${GMPDIR}/lib
RUNTIMELIB=${GMPDIR}/lib
LIBSXX=-lgmpxx -lgmp
CXX=g++ -g -Wall -c
LDXX=g++ -Xlinker -rpath -Xlinker ${RUNTIMELIB}
OBJXX=${SRCXX:.cxx=.o}

all: $(EXECXX)

%.o: %.cxx
	$(CXX) $(INCDIR) $<

# Gencle prog
gencle: $(OBJXX) gencle.cxx
	$(CXX) -c $(INCDIR) $@.cxx
	$(LDXX) $(OBJXX) $(LIBDIR) $(LIBSXX) -o $@

clean:
	rm -f $(EXEC) $(EXEC:=.o) $(EXECXX) $(EXECXX:=.o) $(OBJ) $(OBJXX)