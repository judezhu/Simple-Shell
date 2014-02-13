#makefile4
CC=g++ -std=c++0x 
CFLAGS=-I.
OBJ = Shell.o Shell-driver.o

%.o: %.cpp %.h
	$(CC) -c -o $@ $< $(CFLAGS)

Shell-driver: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

clean:
	rm -f Shell-driver Shell-driver.o Shell.o core
	
