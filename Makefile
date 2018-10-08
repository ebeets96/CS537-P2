#
# Eric Beets (beets) & Jack David (jackd)
#

CC=gcc
FLAGS= -Wall -Wextra
OUTPUT = prodcomm

$(OUTPUT): prodcomm.o queue.o reader.o munch1.o munch2.o writer.o
	$(CC) $(FLAGS) -lpthread -o $@ $^

prodcomm.o: prodcomm.h prodcomm.c
	$(CC) $(FLAGS) -c $^

queue.o: queue.h queue.c
	$(CC) $(FLAGS) -c $^

reader.o: reader.h reader.c
	$(CC) $(FLAGS) -c $^

munch1.o: munch1.h munch1.c
	$(CC) $(FLAGS) -c $^

munch2.o: munch2.h munch2.c
	$(CC) $(FLAGS) -c $^

writer.o: writer.h writer.c
	$(CC) $(FLAGS) -c $^

clean:
	rm -f $(OUTPUT) *.o

test:
	./$(OUTPUT)
