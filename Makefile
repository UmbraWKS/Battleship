CC = gcc
CFLAGS = -g
LDFLAGS =

SRC = main.c
OBJ = $(SRC:.c=.o)

TARGET = battleship

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: clean
clean:
	rm -f $(OBJ) $(TARGET)
