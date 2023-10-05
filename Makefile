#DESTDIR=/usr/local
DESTDIR=./usr
PROG=dcalc

all: $(PROG)

$(PROG): $(PROG).cpp exprtk.hpp
	g++ -o $@ $(PROG).cpp

install: $(PROG)
	#echo DESTDIR=$(DESTDIR)
	mkdir -p $(DESTDIR)/bin
	cp $(PROG) $(DESTDIR)/bin/

clean:
	rm -f *~ $(PROG) *.o

.PHONY: clean install all