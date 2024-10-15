cmake_minimum_required(VERSION 3.10)
project(maze.out)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCE_FILES
    src/main.cpp
    src/lib/reader.cpp
    src/lib/maze.cpp
    src/lib/cell.cpp
    src/lib/wall.cpp
    src/lib/show.cpp
    src/lib/algo_cours.cpp
    src/lib/algo_diagonal.cpp
    src/lib/writer.cpp
    src/lib/checker.cpp
    src/lib/solver_1.cpp
    src/lib/algo_fractal.cpp
)

set(INCLUDE_DIRS
    src/lib
    SFML-2.5.1/include
)

set(LINK_DIRS
    SFML-2.5.1/lib
)

set(LINK_LIBS
    sfml-graphics
    sfml-window
    sfml-system
)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})

target_include_directories(${PROJECT_NAME} PUBLIC ${INCLUDE_DIRS})
target_link_directories(${PROJECT_NAME} PUBLIC ${LINK_DIRS})
target_link_libraries(${PROJECT_NAME} PUBLIC ${LINK_LIBS})

add_custom_target(run_test
    COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME} ""
    COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME} "test"
    COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME} "-i" "src/instances/maze1.txt"
    COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME} "-g" "-i" "src/instances/maze1.txt"
    COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME} "-g" "-i" "src/instances/maze1.txt" "-s" "-c" "-r" "-s"
    DEPENDS ${PROJECT_NAME}
)

add_custom_target(run_algo_cours
    COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME} "-g" "-d" "100" "100" "-vs" "-cm" "-rs" "-a" "1" "-o" "src/instances/tmp/maze1_algo_cours.txt"
    # COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME} "-gs" "-d" "30" "10"
    # COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME} "-gs" "-d" "10" "20"
    # COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME} "-gs" "-d" "30" "10"
    # COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME} "-gs" "-d" "30" "10"
    # COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME} "-gs" "-d" "10" "10"
    # COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME} "-gs" "-d" "20" "10"
    # COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME} "-g" "-d" "1000" "1000"
    DEPENDS ${PROJECT_NAME}
)

add_custom_target(run_checker
    COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME} "-g" "-t" "diagonal" "-vs" "-p"
    COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME} "-i" "src/instances/maze_notvalid1.txt" "-vs"
    COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME} "-i" "src/instances/maze_notperfect1.txt" "-vs" "-p"
    DEPENDS ${PROJECT_NAME}
)

add_custom_target(run_algo_diagonal
    COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME} "-gs" "-t" "diagonal" "-d" "20" "10" "-o" "src/instances/tmp/maze1_algo1.txt" "-vs"
    COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME} "-gs" "-t" "diagonal" "-d" "20" "20" "-o" "src/instances/tmp/maze2_algo1.txt" "-vs"
    COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME} "-gs" "-t" "diagonal" "-vs" "-c" "-gs" "-t" "diagonal" "-vs"
    DEPENDS ${PROJECT_NAME}
)

add_custom_target(run_algo_fractal
    COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME} "-gs" "-t" "fractal" "-d" "4" "10" "-o" "src/instances/tmp/maze1_algo_fractal.txt" "-vs"
    COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME} "-gs" "-t" "fractal" "-d" "6" "20" "-o" "src/instances/tmp/maze2_algo_fractal_1.txt" "-vs"
    COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME} "-gs" "-t" "fractal" "-vs" "-c" "-gs" "-t" "fractal" "-vs"
    DEPENDS ${PROJECT_NAME}
)

add_custom_target(run_solver_1
    COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME} "-gs" "-t" "diagonal" "-d" "100" "100" "-r" "-a" "1" "-s"
    COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME} "-i" "src/instances/maze_notvalid1.txt" "-rs" "-a" "1"
    COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME} "-i" "src/instances/maze_notperfect1.txt" "-s" "-rs" "-a" "1"
    COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME} "-gs" "-t" "diagonal" "-d" "20" "20" "-rs" "-a" "1"
    COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME} "-gs" "-t" "diagonal" "-rs" "-a" "1" "-c" "-gs" "-t" "diagonal" "-rs" "-a" "1"
    DEPENDS ${PROJECT_NAME}
)

add_custom_target(run_complex
    # COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME} "-g" "-t" "diagonal" "-d" "250" "250" "-r" "-a" "1" "-o" "src/instances/tmp/maze_complex_algo1.txt" "-cm" "-v"
    # COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME} "-g" "-t" "diagonal" "-d" "250" "250" "-r" "-a" "1r" "-o" "src/instances/tmp/maze_complex_algo2.txt" "-cm" "-v"
    COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME} "-g" "-t" "diagonal" "-d" "400" "400" "-o" "src/instances/tmp/maze_complex_algo3.txt" "-r" "-a" "1" "-cm" "-v"
    DEPENDS ${PROJECT_NAME}
)

add_custom_target(run_writer
    COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME} "-i" "src/instances/maze2.txt" "-o" "src/instances/tmp/maze2_writer.txt" "-c" "-i" "src/instances/maze3.txt" "-o" "src/instances/tmp/maze3_writer.txt"
    DEPENDS ${PROJECT_NAME}
)

add_custom_target(run_web
    COMMAND npm run dev
)

add_custom_target(run
    COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME} "-i" "src/instances/maze1.txt" "-s" "-c" "-i" "src/instances/maze2.txt" "-s" "-c" "-i" "src/instances/maze3.txt" "-s"
    DEPENDS ${PROJECT_NAME}
)
