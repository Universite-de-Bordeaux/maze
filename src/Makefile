CC = g++
CFLAGS = -Wall -Wextra
OUTPUT = main.out

$(OUTPUT): main.cpp lib/reader.o lib/maze.o lib/cell.o lib/wall.o
	@echo "Compiling..."
	@$(CC) $(CFLAGS) $^ -o $(OUTPUT)
	@echo "Done."

reader.o : lib/reader.cpp lib/reader.hpp lib/maze.hpp lib/cell.hpp lib/wall.hpp

maze.o: lib/maze.cpp lib/maze.hpp lib/cell.hpp lib/wall.hpp

cell.o: lib/cell.cpp lib/cell.hpp lib/wall.hpp

wall.o: lib/wall.cpp lib/wall.hpp

# Run the program with the given arguments
# $1: The first argument
# $2: The second argument
# $3: The third argument
# La fonction run_output est une fonction qui permet d'afficher le résultat de l'exécution du programme
# Elle prend en paramètre les arguments passés à la commande make run_test ou make run
# Elle affiche le résultat de l'exécution du programme
# Si le programme retourne un code d'erreur, elle affiche un message d'erreur
# Si le programme retourne un code de succès, elle affiche un message de succès
# Les messages d'erreur sont affichés en rouge
# Les messages de succès sont affichés en vert
run_output =echo "Running:./$(OUTPUT) $1 $2 $3"; \
  ./$(OUTPUT) $1 $2 $3; \
    EXIT_CODE=$$?; \
    if [ $$EXIT_CODE -ne 0 ]; then \
        echo -e "\033[31mExit code: $$EXIT_CODE\033[0m"; \
        echo -e "\033[31mError: $(OUTPUT) returned non-zero exit code $$EXIT_CODE\033[0m"; \
    else \
        echo -e "\033[32mExit code: $$EXIT_CODE\033[0m"; \
        echo -e "\033[32mSuccess: $(OUTPUT) returned zero exit code\033[0m"; \
    fi

.PHONY: clean run_test run
# Clean up
clean:
	@echo "Cleaning up..."
	@rm -f $(OUTPUT) */*.o
	@echo "Done."

# Run the program
# 1. Lancez le programme avec l'argument "instances/maze1.txt -v"
run: $(OUTPUT)
	@echo "Running..."
	@echo "--------------------------------"
	@$(call run_output, "instances/maze1.txt", "-r")
	@echo "--------------------------------"
	@echo "Done."

# Run tests
# 1. Lancez le programme sans argument
# 2. Lancez le programme avec l'argument "test"
# 3. Lancez le programme avec l'argument "instances/maze1.txt -v"
# 4. Lancez le programme avec l'argument "instances/maze1.txt -r"
run_test: $(OUTPUT)
	@echo "Running..."
	@echo "--------------------------------"
	@$(call run_output, "")
	@echo "--------------------------------"
	@$(call run_output, "test")
	@echo "--------------------------------"
	@$(call run_output, "instances/maze1.txt", "-v")
	@echo "--------------------------------"
	@$(call run_output, "instances/maze1.txt", "-r")
	@echo "--------------------------------"
	@echo "Done."
