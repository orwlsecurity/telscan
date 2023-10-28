CC 		:= gcc
COUT 	:= telscan
CSRC 	:= telscan.c
CFLAGS 	:= -Wall -Wextra -O2 --std=c99

.PHONY: all build clean

all: build $(COUT)
	./$(COUT)
build:
	$(CC) -o $(COUT) $(CSRC) $(CFLAGS)
clean:
	rm -f $(COUT)
