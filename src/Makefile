CC = g++
CFLAGS = -Wall -Wextra
OUTPUT = main

$(OUTPUT): main.cpp lib/reader.o
	@echo "Compiling..."
	@$(CC) $(CFLAGS) $^ -o $(OUTPUT)
	@echo "Done."

reader.o : lib/reader.hpp lib/maze.hpp

.PHONY: clean
clean:
	@echo "Cleaning up..."
	@rm -f $(OUTPUT) *.o ./lib/*.o
	@echo "Done."
