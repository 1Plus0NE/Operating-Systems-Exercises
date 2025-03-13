CC = gcc
CFLAGS = -Wall -Wextra -g
OBJ = person.o personManager.o main.o
TARGET = program

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ)

person.o: person.c person.h
	$(CC) $(CFLAGS) -c person.c -o person.o

personManager.o: personManager.c personManager.h person.h
	$(CC) $(CFLAGS) -c personManager.c -o personManager.o

main.o: main.c personManager.h person.h
	$(CC) $(CFLAGS) -c main.c -o main.o

clean:
	rm -f $(OBJ) $(TARGET)
