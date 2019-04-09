OUT = projet
CXX = g++
CXXFLAGS = -Wall -std=c++11 `pkg-config --cflags gtkmm-3.0`
LINKING = `pkg-config --cflags gtkmm-3.0`
LDLIBS = `pkg-config --libs gtkmm-3.0`
CFILES = main.cc gui.cc player.cc ball.cc obstacle.cc tools.cc
OFILES = $(CFILES:.cc=.o)

all: $(OUT)


$(OUT): $(OFILES)
	$(CXX) $(CXXFLAGS) $(OFILES) -o $@ $(LDLIBS)

debug : CXXFLAGS= -D NDEBUG  -Wall -std=c++11 `pkg-config --cflags gtkmm-3.0`
debug: $(OFILES)
	$(CXX) $(CXXFLAGS) $(OFILES) -o projet  $(LDLIBS)

clean:
	@echo "* * *CLEANED* * *"
	@rm -f *.o $(OUT) *.cc~ *.h~
