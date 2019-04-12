# Definitions de macros

# CC     = g++
OUT = projet
CXX = g++
CXXFLAGS = -Wall -std=c++11 `pkg-config --cflags gtkmm-3.0`
LINKING = `pkg-config --cflags gtkmm-3.0`
LDLIBS = `pkg-config --libs gtkmm-3.0`
CFILES = ball.cc gui.cc main.cc obstacle.cc player.cc simulation.cc tools.cc
OFILES = ball.o  gui.o  main.o  obstacle.o  player.o  simulation.o  tools.o  

# Definition de la premiere regle
all: $(OUT)


$(OUT): $(OFILES)
	$(CXX) $(CXXFLAGS) $(OFILES) -o $@ $(LDLIBS)

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
# DO NOT DELETE THIS LINball.o: ball.cc ball.h define.h tools.h player.h obstacle.h
ball.o: ball.cc ball.h define.h tools.h player.h obstacle.h
gui.o: gui.cc gui.h ball.h define.h tools.h player.h obstacle.h \
 simulation.h error.h enum.h
main.o: main.cc simulation.h tools.h define.h player.h ball.h obstacle.h \
 error.h enum.h gui.h
obstacle.o: obstacle.cc obstacle.h define.h tools.h ball.h player.h
player.o: player.cc player.h define.h tools.h ball.h obstacle.h
simulation.o: simulation.cc simulation.h tools.h define.h player.h ball.h \
 obstacle.h error.h enum.h
tools.o: tools.cc tools.h define.h
