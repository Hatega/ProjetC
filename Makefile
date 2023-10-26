CC = gcc
CFLAGS = -Wall
SRC = main.c generate.c
OBJ = $(SRC:.c=.o)
EXECUTABLE = myprogram

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJ)
	$(CC) $(CFLAGS) $^ -o $@ -lssl -lcrypto

%.o: %.c
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f $(OBJ) $(EXECUTABLE)
