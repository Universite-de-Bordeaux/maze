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



run_cmd =./$(OUTPUT) $(1); \
	EXIT_CODE=$$?; \
    echo "Exit code: $$EXIT_CODE"; \
    if [ $$EXIT_CODE -ne 0 ]; then \
        echo "    Error: $(OUTPUT) returned non-zero exit code $$EXIT_CODE"; \
    fi

.PHONY: clean run
clean:
	@echo "Cleaning up..."
	@rm -f $(OUTPUT) */*.o
	@echo "Done."

run: $(OUTPUT)
	@echo "Running..."
	@$(call run_cmd, "")
	@$(call run_cmd, "Makefile")
	@echo "Done."
