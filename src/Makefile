CC = g++
CFLAGS = -Wall -Wextra
OUTPUT = main

$(OUTPUT): main.cpp lib/reader.o lib/maze.o lib/cell.o lib/wall.o
	@echo "Compiling..."
	@$(CC) $(CFLAGS) $^ -o $(OUTPUT)
	@echo "Done."

reader.o : lib/reader.hpp lib/maze.hpp

maze.o: lib/maze.cpp lib/maze.hpp lib/reader.hpp

cell.o: lib/cell.cpp lib/cell.hpp lib/wall.hpp

wall.o: lib/wall.cpp

.PHONY: clean
clean:
	@echo "Cleaning up..."
	@rm -f $(OUTPUT) */*.o
	@echo "Done."
