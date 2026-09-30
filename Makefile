CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -g
SRC = $(wildcard *.c)
OBJ = $(SRC:.c=.o)
TARGET = mfms

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET) $(TARGET).exe