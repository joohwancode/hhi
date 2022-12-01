.PHONY: test

CC=gcc
CFLAGS=-I -Wall -g -DSENTINEL
OBJS=test-rbtree.o new_rbtree.o delete_rbtree.o rbtree_erase.o rbtree_find.o rbtree_insert.o rbtree_max.o rbtree_min.o rbtree_to_array.o rotate.o
TARGET=test-rbtree

$(TARGET): $(OBJS)
	$(CC) -o $@ $(OBJS)		
	valgrind ./test-rbtree

# test: test-rbtree
# 	./test-rbtree
# 	valgrind ./test-rbtree

test-rbtree.o: test-rbtree.c rbtree.h
new_rbtree.o: new_rbtree.c
rbtree_erase.o: rbtree_erase.c rotate.h
rbtree_find.o: rbtree_find.c
rbtree_insert.o: rbtree_insert.c rotate.h
rbtree_max.o: rbtree_max.c
rbtree_min.o: rbtree_min.c
rbtree_to_array.o: rbtree_to_array.c
rotate.o: rotate.c rotate.h
delete_rbtree.o: delete_rbtree.c


clean:
	rm -f test-rbtree *.o
