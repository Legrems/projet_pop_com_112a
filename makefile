# Definitions de macros

CC     = g++
CXXFLAGS = -Wall -std=c++11
CFILES = ball.cc main.cc obstacle.cc player.cc simulation.cc tools.cc
OFILES = ball.o  main.o  obstacle.o  player.o  simulation.o  tools.o  

# Definition de la premiere regle

projet: $(OFILES)
	$(CC) $(OFILES) -o projet

# Definitions de cibles particulieres

depend:
	@echo " *** MISE A JOUR DES DEPENDANCES ***"
	@(sed '/^# DO NOT DELETE THIS LINE/q' makefile | \
	  sed "/^CFILES =*/c\\CFILES = `echo *.cc`" | \
	  sed "/^OFILES =*/c\\OFILES = `echo *.cc | sed 's/\.cc/.o /g'` " && \
	  $(CC) -MM $(CFILES) | \
	  egrep -v "/usr/include" \
	 )>makefile.new
	@mv makefile.new makefile

clean:
	@echo " *** EFFACE MODULES OBJET ET EXECUTABLE ***"
	@/bin/rm -f *.o projet *.c~ *.h~ *.new

#
# -- Regles de dependances generees automatiquement
#
# DO NOT DELETE THIS LINE
ball.o: ball.cc ball.h tools.h
main.o: main.cc simulation.h tools.h player.h obstacle.h ball.h define.h \
 error.h enum.h
obstacle.o: obstacle.cc obstacle.h tools.h
player.o: player.cc player.h tools.h
simulation.o: simulation.cc simulation.h tools.h player.h obstacle.h \
 ball.h define.h error.h enum.h
tools.o: tools.cc tools.h
