#
# Eric Beets (beets) & Jack David (jackd)
#

CC=gcc
FLAGS= -Wall -Wextra
OUTPUT = prodcomm
SCAN_BUILD_DIR = scan-build-out

$(OUTPUT): prodcomm.o queue.o reader.o munch1.o munch2.o writer.o const.o
	$(CC) $(FLAGS) -o $@ $^ -lpthread

prodcomm.o: prodcomm.c
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

const.o: const.h const.c
	$(CC) $(FLAGS) -c $^

clean:
	rm -f $(OUTPUT) *.o *.gch

test: $(OUTPUT)
	./$(OUTPUT) < ~cs537-1/public/proj2/bigfile.txt

#
# Run the Clang Static Analyzer
#
scan-build: clean
	scan-build -o $(SCAN_BUILD_DIR) make

#
# View the one scan available using firefox
#
scan-view: scan-build
	firefox -new-window $(SCAN_BUILD_DIR)/*/index.html
