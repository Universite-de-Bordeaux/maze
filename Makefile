CC = g++
CFLAGS = -Wall -Wextra
OUTPUT = main

$(OUTPUT): main.cpp
	@echo "Compiling..."
	@$(CC) $(CFLAGS) $^ -o $(OUTPUT)
	@echo "Done."

.PHONY: clean
clean:
	@echo "Cleaning up..."
	@rm -f $(OUTPUT) *.o
	@echo "Done."
