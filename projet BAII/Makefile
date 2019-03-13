# Definitions de macros

CC     = g++
CFLAGS = -Wall -std=c++11
CFILES = test.cc tools.cc player.cc ball.cc obstacle.cc
OFILES = test.o tools.o player.o ball.o obstacle.o

# Definition de la premiere regle

test: $(OFILES)
	$(CC) $(OFILES) -o test

# Definitions de cibles particulieres

depend:
	@echo " *** MISE A JOUR DES DEPENDANCES ***"
	@(sed '/^# DO NOT DELETE THIS LINE/q' Makefile && \
	  $(CC) -MM $(CFLAGS) $(CFILES) | \
	  egrep -v "/usr/include" \
	 ) >Makefile.new
	@mv Makefile.new Makefile

clean:
	@echo " *** EFFACE MODULES OBJET ET EXECUTABLE ***"
	@/bin/rm -f *.o *.x *.c~ *.h~ prog

#
# -- Regles de dependances generees automatiquement
#
# DO NOT DELETE THIS LINE
test.o: test.cc player.h tools.h ball.h
tools.o: tools.cc tools.h
player.o: player.cc player.h tools.h
ball.o: ball.cc ball.h tools.h
