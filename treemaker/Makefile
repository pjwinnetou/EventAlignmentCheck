PROG = RunEvt

all: $(PROG)

OBJ = RunEvt.o RunEvt_main.o
INC = -I. -I/usr/local/include -I$(OFFLINE_MAIN)/include/Event -I$(OFFLINE_MAIN)/include 
LIB = -pthread -L$(OFFLINE_MAIN)/lib -lNoRootEvent 

CXX = g++
CFLAGS = -Wall -g -std=c++17 `root-config --cflags`
LDFLAGS = -g `root-config --glibs` -lMathMore -Wl,-rpath,$(OFFLINE_MAIN)/lib:$(ROOTSYS)/lib 

$(PROG): $(OBJ)
	$(CXX) -o $(PROG) $(LDFLAGS) $(OBJ) $(LIB) 

clean:
	rm -f $(PROG) *.o *.so *.d *~ core*

.cc.o:
	$(CXX) -c $(CFLAGS) $(INC) $<
