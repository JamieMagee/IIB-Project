CXXFLAGS += -ggdb `pkg-config opencv --cflags`
LINKFLAGS += `pkg-config opencv --libs`

all: clean online offline

online:
	g++ $(CXXFLAGS) -o online online.cc $(LINKFLAGS)
	
offline:
	g++ $(CXXFLAGS) -o offline offline.cc $(LINKFLAGS)

clean:
	rm -f online
	rm -f offline
