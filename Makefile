
CC=g++
CXX_CFLAGS=-Wall -g -I/usr/include
CXX_LDFLAGS=
LIBS=
EXEC=qt-threads
SRC=$(wildcard *.cpp)
HDR=$(wildcard *.hpp)
OBJ=$(patsubst %.cpp,%.o,$(SRC))
ARCHIVE=$(EXEC).tar.gz

all: $(SRC) $(EXEC)

compile: $(OBJ) $(SRC) $(HDR)

$(EXEC): $(OBJ) $(SRC) $(HDR)
	$(CC) -o $(EXEC) $(OBJ) $(CXX_LDFLAGS)

%.o: %.cpp
	$(CC) -c $(CXX_CFLAGS) $<

clean:
	rm -f $(OBJ)
	rm -f $(EXEC)
	rm -f $(ARCHIVE)

archive:
	tar -zcf $(ARCHIVE) $(SRC) $(DHR) Makefile
