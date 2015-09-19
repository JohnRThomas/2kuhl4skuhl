CC=g++
CFLAGS= -g -pthread
LIBS = /usr/local/lib/libvrpn.a /usr/local/lib/libquat.a
DEPS = kalman.h kuhl-nodep.h vecmat.h vrpn-help.h vecmat.h
VEC = vecmat.o 
OBJ = kalman.o kuhl-nodep.o vrpn-help.o recorder.o 
SERV = fake-server.o
EXE = recorder

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS) 

$(EXE): $(OBJ) $(VEC)
	$(CC) -o $@ $^ $(CFLAGS) -o recorder $(LIBS)

server: $(SERV) $(VEC)
	$(CC) -o $@ $^ $(CFLAGS) -o server $(LIBS)

clean:
	rm -f -r *.o $(EXE) server *.dSYM
