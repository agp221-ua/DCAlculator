#DESTDIR=/usr/local
DESTDIR=./usr
COMPLETIONDIRBASH=$(DESTDIR)/share/bash-completion/completions
COMPLETIONDIRZSH=$(DESTDIR)/share/zsh/site-functions
COMPLETIONSFILE=_dcalc
PROG=dcalc

all: $(PROG)

$(PROG): $(PROG).cpp exprtk.hpp
	g++ -O3 -o $@ $(PROG).cpp -w

install: $(PROG)
	#echo DESTDIR=$(DESTDIR)
	mkdir -p $(DESTDIR)/bin
	cp $(PROG) $(DESTDIR)/bin/
	mkdir -p $(COMPLETIONDIRBASH)
	cp ./completions/$(COMPLETIONSFILE) $(COMPLETIONDIRBASH)/$(COMPLETIONFILE)
	mkdir -p $(COMPLETIONDIRZSH)
	cp ./completions/$(COMPLETIONSFILE) $(COMPLETIONDIRZSH)/$(COMPLETIONFILE)

clean:
	rm -f *~ $(PROG) *.o

.PHONY: clean install all