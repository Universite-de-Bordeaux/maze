CC = g++
CFLAGS = -Wall -Wextra
OUTPUT = main

$(OUTPUT): main.cpp lib/reader.o lib/maze.o lib/cell.o lib/wall.o
	@echo "Compiling..."
	@$(CC) $(CFLAGS) $^ -o $(OUTPUT)
	@echo "Done."

reader.o : lib/reader.cpp lib/reader.hpp lib/maze.hpp lib/cell.hpp lib/wall.hpp

maze.o: lib/maze.cpp lib/maze.hpp lib/cell.hpp lib/wall.hpp

cell.o: lib/cell.cpp lib/cell.hpp lib/wall.hpp

wall.o: lib/wall.cpp lib/wall.hpp

run_output =echo "Running:./$(OUTPUT) $(1)"; \
  ./$(OUTPUT) $(1); \
    EXIT_CODE=$$?; \
    if [ $$EXIT_CODE -ne 0 ]; then \
        echo -e "\033[31mExit code: $$EXIT_CODE\033[0m"; \
        echo -e "\033[31mError: $(OUTPUT) returned non-zero exit code $$EXIT_CODE\033[0m"; \
    else \
        echo -e "\033[32mExit code: $$EXIT_CODE\033[0m"; \
        echo -e "\033[32mSuccess: $(OUTPUT) returned zero exit code\033[0m"; \
    fi

.PHONY: clean run
clean:
	@echo "Cleaning up..."
	@rm -f $(OUTPUT) */*.o
	@echo "Done."

run: $(OUTPUT)
	@echo "Running..."
	@echo "--------------------------------"
	@$(call run_output, "")
	@echo "--------------------------------"
	@$(call run_output, "test")
	@echo "--------------------------------"
	@$(call run_output, "Makefile")
	@echo "--------------------------------"
	@echo "Done."
