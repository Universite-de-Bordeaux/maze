CC = g++
CFLAGS = -Wall -Wextra
OUTPUT = src/main.out
SDLFLAGS = -LSFML-2.5.1/lib -ISFML-2.5.1/include -lsfml-graphics -lsfml-window -lsfml-system

$(OUTPUT): src/main.cpp src/lib/reader.o src/lib/maze.o src/lib/cell.o src/lib/wall.o src/lib/show.o src/lib/var.hpp src/lib/algo_cours.o src/lib/writer.o
	@echo "Compiling..."
	@$(CC) $(CFLAGS) $^ -o $(OUTPUT) $(SDLFLAGS)
	@echo "Done."

reader.o : src/lib/reader.cpp src/lib/reader.hpp src/lib/maze.hpp src/lib/cell.hpp src/lib/wall.hpp src/lib/var.hpp

maze.o: src/lib/maze.cpp src/lib/maze.hpp src/lib/cell.hpp src/lib/wall.hpp

cell.o: src/lib/cell.cpp src/lib/cell.hpp src/lib/wall.hpp

wall.o: src/lib/wall.cpp src/lib/wall.hpp

show.o: src/lib/show.cpp src/lib/show.hpp src/lib/maze.hpp src/lib/cell.hpp src/lib/wall.hpp src/lib/var.hpp

algo_cours.o: src/lib/algo_cours.cpp src/lib/algo_cours.hpp

writer.o : src/lib/writer.cpp src/lib/writer.hpp src/lib/maze.hpp src/lib/cell.hpp src/lib/wall.hpp src/lib/var.hpp

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
run_output =echo "Running:./$(OUTPUT) $1 $2 $3 $4 $5 $6 $7 $8 $9 ${10} ${11} ${12} ${13} ${14} ${15} ${16} ${17} ${18} ${19} ${20}"; \
  ./$(OUTPUT) $1 $2 $3 $4 $5 $6 $7 $8 $9 ${10} ${11} ${12} ${13} ${14} ${15} ${16} ${17} ${18} ${19} ${20}; \
    EXIT_CODE=$$?; \
    if [ $$EXIT_CODE -ne 0 ]; then \
        echo -e "\033[31mExit code: $$EXIT_CODE\033[0m"; \
        echo -e "\033[31mError: $(OUTPUT) returned non-zero exit code $$EXIT_CODE\033[0m"; \
    else \
        echo -e "\033[32mExit code: $$EXIT_CODE\033[0m"; \
        echo -e "\033[32mSuccess: $(OUTPUT) returned zero exit code\033[0m"; \
    fi; \
    echo "--------------------------------";

.PHONY: clean run_test run
# Clean up
clean:
	@echo "Cleaning up..."
	@rm -f $(OUTPUT) src/*/*.o
	@echo "Done."

# Run the program
# 1. Lancez le programme avec l'argument "-i instances/maze1.txt -s"
run: $(OUTPUT)
	@echo "Running..."
	@echo "--------------------------------"
	@$(call run_output, "-i", "src/instances/maze1.txt", "-s", "-c", "-i", "src/instances/maze2.txt", "-s", "-c", "-i", "src/instances/maze3.txt", "-s")
	@echo "Done."

# Run tests
# 1. Lancez le programme sans argument
# 2. Lancez le programme avec l'argument "test"
# 3. Lancez le programme avec l'argument "-i src/instances/maze1.txt"
# 4. Lancez le programme avec l'argument "-g -i src/instances/maze1.txt"
# 5. Lancez le programme avec l'argument "-g -i src/instances/maze1.txt -s -c -r -s"
run_test: $(OUTPUT)
	@echo "Running..."
	@echo "--------------------------------"
	@$(call run_output, "")
	@$(call run_output, "test")
	@$(call run_output, "-i", "src/instances/maze1.txt")
	@$(call run_output, "-g", "-i", "src/instances/maze1.txt")
	@$(call run_output, "-g", "-i", "src/instances/maze1.txt", "-s", "-c", "-r", "-s")
	@echo "Done."

run_algo: $(OUTPUT)
	@echo "Running..."
	@echo "--------------------------------"
	@$(call run_output, "-g","-d","20","10", "-s")
	@echo "Done."

run_writer: $(OUTPUT)
	@echo "Running..."
	@echo "--------------------------------"
	@$(call run_output, "-i", "src/instances/maze1.txt", "-o", "src/instances/maze1_writer.txt")
	@echo "Done."
