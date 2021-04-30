CC        = g++
CFLAGS    = -g3 -Wall 
SRCS      = B-tree.cpp veb-tree.cpp
OBJS      = $(SRCS:.cpp=.o)

all: $(SRCS) 

$(PROG): $(OBJS)
	$(CC) $(OBJS) 

B-tree: B-tree.o
	$(CC) $(CFLAGS) B-tree.cpp -o B-tree
	# ./B-tree

veb-tree: veb-tree.o
	$(CC) veb-tree.cpp -o veb-tree
	./veb-tree

clean:
	rm $(OBJS) 
