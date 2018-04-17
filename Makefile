# Daniel Casper
# djc062000@utdallas.edu
# CS3377.002

CXX = g++
CPPFLAGS = -std=c++11 -Wall -I /scratch/perkins/include
LDLIBS = -lcdk -lcurses
LDFLAGS = -L /scratch/perkins/lib
PROJECTNAME = CS3377.Program6
EXECFILE = program6

OBJS = program6.o

all: $(EXECFILE)

clean:
	rm -f $(OBJS) $(EXECFILE) 

$(EXECFILE): $(OBJS)
	$(CXX) -static -o $@ $(LDFLAGS) $(OBJS) $(LDLIBS)

