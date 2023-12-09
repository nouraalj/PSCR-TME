CC = g++
CFLAGS = -Wall -Werror -O2 -std=c++11

all: fight fork_exo waitpid waitpid2

fight: fight.cpp rsleep.cpp
	$(CC) $(CFLAGS) $^ -o $@

fork_exo: fork_exo.cpp
	$(CC) $(CFLAGS) $^ -o $@

waitpid: waitpid.cpp
	$(CC) $(CFLAGS) $^ -o $@

waitpid2: waitpid2.cpp
	$(CC) $(CFLAGS) $^ -o $@

.PHONY: clean

clean:
	rm -f *.o fight fork_exo waitpid waitpid2