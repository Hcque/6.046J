CC = gcc
CFLAGS = -Wall -g -lstdc++


Binarytree: Binary_tree.o  
	$(CC) $(CFLAGS) -o Binarytree Binary_tree.o

Binary_tree.o: Binary_tree.cpp
	$(CC) $(CFLAGS) -c Binary_tree.cpp

clean:
	$(RM) prog *.o *~
