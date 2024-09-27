CC = g++
CFLAGS = -Wall -Wextra
OUTPUT = main

$(OUTPUT): main.cpp lib/reader.hpp lib/maze.hpp lib/cell.hpp lib/wall.hpp
	@echo "Compiling..."
	@$(CC) $(CFLAGS) $^ -o $(OUTPUT)
	@echo "Done."

reader.o : lib/reader.cpp lib/reader.hpp lib/maze.hpp lib/cell.hpp lib/wall.hpp

maze.o: lib/maze.cpp lib/maze.hpp lib/cell.hpp lib/wall.hpp

cell.o: lib/cell.cpp lib/cell.hpp lib/wall.hpp

wall.o: lib/wall.cpp lib/wall.hpp

.PHONY: clean
clean:
	@echo "Cleaning up..."
	@rm -f $(OUTPUT) */*.o
	@echo "Done."
