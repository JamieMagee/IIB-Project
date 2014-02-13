CXXFLAGS += -ggdb `pkg-config opencv --cflags`
LINKFLAGS += `pkg-config opencv --libs`
SRC = $(wildcard *.cc)

all: clean optical-flow

optical-flow:
	g++ $(CXXFLAGS) -o optical-flow $(SRC) $(LINKFLAGS)

clean:
	rm -rf optical-flow