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
    src/lib/algo_1.cpp
    src/lib/writer.cpp
    src/lib/checker.cpp
    src/lib/solver_1.cpp
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
    COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME} "-g" "-d" "10" "10" "-s"
    DEPENDS ${PROJECT_NAME}
)

add_custom_target(run_checker
    COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME} "-g" "-t" "1" "-vs" "-p"
    COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME} "-i" "src/instances/maze_notvalid1.txt" "-vs"
    COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME} "-i" "src/instances/maze_notperfect1.txt" "-vs" "-p"
    DEPENDS ${PROJECT_NAME}
)

add_custom_target(run_algo_1
    COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME} "-gs" "-t" "1" "-d" "20" "10" "-o" "src/instances/tmp/maze1_algo1.txt" "-vs"
    COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME} "-gs" "-t" "1" "-d" "20" "20" "-o" "src/instances/tmp/maze2_algo1.txt" "-vs"
    COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME} "-gs" "-t" "1" "-vs" "-c" "-gs" "-t" "1" "-vs"
    DEPENDS ${PROJECT_NAME}
)

add_custom_target(run_solver_1
    COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME} "-gs" "-t" "1" "-d" "100" "100" "-r" "-a" "1" "-s"
    COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME} "-i" "src/instances/maze_notvalid1.txt" "-rs" "-a" "1"
    COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME} "-i" "src/instances/maze_notperfect1.txt" "-s" "-rs" "-a" "1"
    COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME} "-gs" "-t" "1" "-d" "20" "20" "-rs" "-a" "1"
    COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME} "-gs" "-t" "1" "-rs" "-a" "1" "-c" "-gs" "-t" "1" "-rs" "-a" "1"
    DEPENDS ${PROJECT_NAME}
)

add_custom_target(run_complex
    # COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME} "-g" "-t" "1" "-d" "250" "250" "-r" "-a" "1" "-o" "src/instances/tmp/maze_complex_algo1.txt" "-cm" "-v"
    # COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME} "-g" "-t" "1" "-d" "250" "250" "-r" "-a" "1r" "-o" "src/instances/tmp/maze_complex_algo2.txt" "-cm" "-v"
    COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME} "-g" "-t" "1" "-d" "1000" "1000" "-o" "src/instances/tmp/maze_complex_algo3.txt" "-r" "-a" "1" "-cm" "-v"
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
