IODIR:=test-io
IOFILES:=$(wildcard $(IODIR)/*)
TESTBOARD:=tests/board-test.cpp
TESTREMOVE:=tests/remove-test.cpp
CFILES:=src/main.cpp
HFILES:=include/board.h include/ai.h

EXE:=bin/tttb
TEXE:=bin/test

CFLAGS:=-Wall -Werror -pedantic -std=c++17

help:
	@echo "build | compiles the program"
	@echo "      |   g++ $(CFLAGS) $(CFILES) -o $(EXE)"
	@echo "test  | compiles our unit test"
	@echo "      |   g++ $(CFLAGS) $(TESTBOARD) -o $(TEXE)"
	@echo "clean | remove any compile binaries"
.PHONY: help

build: $(CFILES) $(HFILES) Makefile
	g++ $(CFLAGS) $(CFILES) -o $(EXE)
.PHONY: build

tiny-bot: tiny/ttttttt.cpp Makefile
	g++ $(CFLAGS) tiny/ttttttt.cpp -o bin/ttttttt
.PHONY: tiny-bot

test-ai: $(TESTBOARD) $(HFILES) Makefile
	g++ $(CFLAGS) $(TESTBOARD) -o $(TEXE)
	$(TEXE)
.PHONY: test-ai

test-remove: $(TESTREMOVE) $(HFILES) Makefile
	g++ $(CFLAGS) $(TESTREMOVE) -o bin/test-remove
.PHONY: test-remove

unit-test: $(TESTBOARD) $(HFILES) Makefile
	g++ $(CFLAGS) $(TESTBOARD) -o $(TEXE)
	@for file in $(FILES); do \
		@echo "$(FILES)"; \
		@echo "$(IODIR)"; \
		./$(TEXE) < $$file; \
	done
.PHONY: test

clean: Makefile
	@for file in bin/*; do \
		rm -i $$file; \
	done
	@for file in logs/*; do \
		rm -i $$file; \
	done
.PHONY: clean
