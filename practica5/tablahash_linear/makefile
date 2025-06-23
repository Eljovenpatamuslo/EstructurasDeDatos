# Makefile para P2E6
# ejecutar desde la terminal escribiendo "make" 
# genera automáticamente el ejecutable del programa

FLAGS = -Wall -g -Wextra -Werror -std=c99

programa: test.o utils.o tablahash.o contacto.o
	$(CC) -o $@ $^ $(FLAGS)

test.o: test.c
	$(CC) -c $< $(FLAGS)

utils.o: utils.c utils.h
	$(CC) -c $< $(FLAGS)

contacto.o: contacto.c contacto.h
	$(CC) -c $< $(FLAGS)

tablahash.o: tablahash.c tablahash.h
	$(CC) -c $< $(FLAGS)
	
clean:
	rm *.o
	rm programa

.PHONY = clean