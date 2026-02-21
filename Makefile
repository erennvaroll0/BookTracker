# Project Variables
CC = gcc
CFLAGS = -Iinclude -Wall -Wextra
SRC = src/main.c src/book.c
TARGET = book_tracker.exe

# Default target: Compiles the project
all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(SRC) $(CFLAGS) -o $(TARGET)

# Clean target: Removes the executable and database file (Windows compatible)
clean:
	if exist $(TARGET) del $(TARGET)
	if exist books.dat del books.dat

# Rebuild: Cleans and then recompiles
re: clean all

.PHONY: all clean re