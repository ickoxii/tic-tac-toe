CFILES:=src/main.cpp
HFILES:=src/board.h src/ai.h
EXE:=a.out
CFLAGS:=-Wall -Werror -pedantic -std=c++17

build: $(CFILES) $(HFILES)
	g++ $(CFLAGS) $(CFILES) -o $(EXE)
.PHONY: build
