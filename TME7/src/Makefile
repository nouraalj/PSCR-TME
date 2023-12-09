CC = g++
CFLAGS = -Wall -Wextra -Werror -O2 -std=c++11

SRC = prod_cons.cpp prod_cons_named
OBJ = $(SRC:.cpp=.p)

all: pipe prod_cons prod_cons_named 

pipe: pipe.cpp
	$(CC) $(CFLAGS) $^ -o $@


prod_cons: prod_cons.o
	$(CC) $(CFLAGS) $^ -o $@

prod_cons_named: prod_cons_named.o
	$(CC) $(CFLAGS) $^ -o $@

$(OBJ) : Stack.h

%.o:%.cpp
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: clean

clean:
	rm -f *.o pipe prod_cons prod_cons_named