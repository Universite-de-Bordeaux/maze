cmake_minimum_required(VERSION 3.10)
project(maze.out)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCE_FILES
    src/main.cpp
    src/lib/cell.cpp
    src/lib/maze.cpp
    src/lib/reader.cpp
    src/lib/show.cpp
    src/lib/wall.cpp
    src/lib/writer.cpp
    src/lib/algo/algo_backtracking.cpp
    src/lib/algo/algo_diagonal.cpp
    src/lib/algo/algo_fractal.cpp
    src/lib/algo/algo_wallmaker.cpp
    src/lib/checker/checker_depthfirst.cpp
    src/lib/solver/solver_breadthfirst.cpp
    src/lib/solver/solver_depthfirst.cpp
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
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME} "-i" "src/instances/maze1.txt" "-s"
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME} "-i" "src/instances/maze1.txt" "-s" "-c" "-i" "src/instances/maze2.txt" "-s"
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME} "-i" "src/instances/maze1.txt" "-rs" "-a" "dfl" "-s"
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME} "-i" "src/instances/maze1.txt" "-rs" "-a" "dfr" "-s"
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME} "-i" "src/instances/maze1.txt" "-rs" "-a" "bf" "-s"
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME} "-gs" "-d" "10" "10" "-s" "-rs" "-a" "dfl" "-s"
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME} "-gs" "-d" "10" "10" "-a" "bt" "-s"
        #    COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME} "-gs" "-d" "10" "10" "-a" "wm" "-s" "-rs" "-a" "dfl" "-s"
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME} "-gs" "-d" "10" "10" "-a" "d" "-s" "-rs" "-a" "dfr" "-s"
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME} "-gs" "-d" "4" "4" "-a" "f" "-s" "-rs" "-a" "bf" "-s"
        #    COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME} "-gs" "-d" "10" "10" "-a" "wm" "-s" "-vs" "-a" "dfl" "-s"
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME} "-gs" "-d" "10" "10" "-a" "d" "-s" "-vs" "-a" "dfr" "-s"
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME} "-gs" "-d" "4" "4" "-a" "f" "-s" "-vs" "-a" "dfr" "-s"
        DEPENDS ${PROJECT_NAME}
)

add_custom_target(run_algo_backtracking
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME} "-gs" "-d" "10" "10" "-a" "bt"
        DEPENDS ${PROJECT_NAME}
)

add_custom_target(run_algo_backtracking_test
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME} "-gs" "-d" "10" "10" "-a" "bt"
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME} "-gs" "-d" "10" "10" "-a" "backtracking"
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME} "-gs" "-d" "1" "1" "-a" "bt"
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME} "-gs" "-d" "2" "2" "-a" "bt"
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME} "-gs" "-d" "50" "50" "-a" "bt"
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME} "-gs" "-d" "100" "100" "-a" "bt" "-vs"
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME} "-gs" "-d" "100" "100" "-a" "bt" "-rs"
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME} "-g" "-d" "500" "500" "-a" "bt"
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME} "-g" "-d" "750" "750" "-a" "bt"
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME} "-g" "-d" "1000" "1000" "-a" "bt"
        #    COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME} "-g" "-d" "1250" "1250" "-a" "bt"
        #    COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME} "-g" "-d" "1500" "1500" "-a" "bt"
        DEPENDS ${PROJECT_NAME}
)

add_custom_target(run_algo_diagonal
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME} "-gs" "-d" "10" "10" "-a" "d"
        DEPENDS ${PROJECT_NAME}
)

add_custom_target(run_algo_diagonal_test
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME} "-gs" "-d" "10" "10" "-a" "d"
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME} "-gs" "-d" "10" "10" "-a" "diagonal"
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME} "-gs" "-d" "1" "1" "-a" "d"
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME} "-gs" "-d" "2" "2" "-a" "d"
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME} "-gs" "-d" "50" "50" "-a" "d"
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME} "-gs" "-d" "100" "100" "-a" "d" "-vs"
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME} "-gs" "-d" "100" "100" "-a" "d" "-rs"
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME} "-g" "-d" "500" "500" "-a" "d"
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME} "-g" "-d" "750" "750" "-a" "d"
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME} "-g" "-d" "1000" "1000" "-a" "d"
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME} "-g" "-d" "1250" "1250" "-a" "d"
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME} "-g" "-d" "1500" "1500" "-a" "d"
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME} "-g" "-d" "1750" "1750" "-a" "d"
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME} "-g" "-d" "2000" "2000" "-a" "d"
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME} "-g" "-d" "2250" "2250" "-a" "d"
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME} "-g" "-d" "2500" "2500" "-a" "d"
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME} "-g" "-d" "5000" "5000" "-a" "d"
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME} "-g" "-d" "7500" "7500" "-a" "d"
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME} "-g" "-d" "10000" "10000" "-a" "d"
        #    COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME} "-g" "-d" "25000" "25000" "-a" "d"
        #    COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME} "-g" "-d" "50000" "50000" "-a" "d"
        #    COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME} "-g" "-d" "75000" "75000" "-a" "d"
        #    COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME} "-g" "-d" "100000" "100000" "-a" "d"
        DEPENDS ${PROJECT_NAME}
)

add_custom_target(run_algo_fractal
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME} "-gs" "-d" "4" "4" "-a" "f" "-vs"
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME} "-gs" "-u" "-d" "4" "4" "-a" "f" "-vs" "-p"
        DEPENDS ${PROJECT_NAME}
)

add_custom_target(run_algo_fractal_test
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME} "-gs" "-d" "4" "4" "-a" "f"
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME} "-gs" "-d" "4" "4" "-a" "fractal"
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME} "-gs" "-d" "1" "1" "-a" "f"
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME} "-gs" "-d" "2" "2" "-a" "f"
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME} "-g" "-d" "4" "4" "-a" "f" "-vs"
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME} "-g" "-d" "4" "4" "-a" "f" "-rs"
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME} "-g" "-d" "5" "5" "-a" "f"
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME} "-g" "-d" "6" "6" "-a" "f"
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME} "-g" "-d" "7" "7" "-a" "f"
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME} "-g" "-d" "8" "8" "-a" "f"
        #    COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME} "-g" "-d" "9" "9" "-a" "f"
        #    COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME} "-g" "-d" "10" "10" "-a" "f"
        DEPENDS ${PROJECT_NAME}
)

add_custom_target(run_algo_wallmaker
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME} "-gs" "-d" "2" "2" "-a" "wm"
        DEPENDS ${PROJECT_NAME}
)

add_custom_target(run_algo_wallmaker_test
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME} "-gs" "-d" "10" "10" "-a" "wm"
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME} "-gs" "-d" "10" "10" "-a" "wallmaker"
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME} "-gs" "-d" "1" "1" "-a" "wm"
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME} "-gs" "-d" "2" "2" "-a" "wm"
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME} "-g" "-d" "50" "50" "-a" "wm" "-vs"
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME} "-g" "-d" "50" "50" "-a" "wm" "-rs"
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME} "-g" "-d" "100" "100" "-a" "wm"
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME} "-g" "-d" "500" "500" "-a" "wm"
        #    COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME} "-g" "-d" "750" "750" "-a" "wm"
        #    COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME} "-g" "-d" "1000" "1000" "-a" "wm"
        DEPENDS ${PROJECT_NAME}
)

add_custom_target(run_checker_depthfirst
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME} "-g" "-a" "backtracking" "-vs" "-a" "dfl"
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME} "-g" "-a" "backtracking" "-vs" "-a" "dfr"
        DEPENDS ${PROJECT_NAME}
)

add_custom_target(run_checker_depthfirst_test
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME} "-g" "-a" "backtracking" "-vs" "-a" "dfl"
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME} "-g" "-a" "backtracking" "-vs" "-a" "dfr"
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME} "-g" "-a" "backtracking" "-vs" "-a" "depthfirstleft"
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME} "-g" "-a" "backtracking" "-vs" "-a" "depthfirstright"
        #    COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME} "-g" "-a" "wallmaker" "-vs" "-a" "dfl"
        #    COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME} "-g" "-a" "wallmaker" "-vs" "-a" "dfr"
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME} "-g" "-a" "diagonal" "-vs" "-a" "dfl"
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME} "-g" "-a" "diagonal" "-vs" "-a" "dfr"
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME} "-g" "-a" "fractal" "-d" "4" "4" "-vs" "-a" "dfl"
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME} "-g" "-a" "fractal" "-d" "4" "4" "-vs" "-a" "dfr"
        DEPENDS ${PROJECT_NAME}
)

add_custom_target(run_solver_breadthfirst
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME} "-g" "-a" "backtracking" "-rs" "-a" "bf"
        DEPENDS ${PROJECT_NAME}
)

add_custom_target(run_solver_breadthfirst_test
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME} "-g" "-a" "backtracking" "-rs" "-a" "bf"
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME} "-g" "-a" "backtracking" "-rs" "-a" "breadthfirst"
        #    COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME} "-g" "-a" "wallmaker" "-rs" "-a" "bf"
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME} "-g" "-a" "diagonal" "-rs" "-a" "bf"
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME} "-g" "-a" "fractal" "-d" "4" "4" "-rs" "-a" "bf"
        DEPENDS ${PROJECT_NAME}
)

add_custom_target(run_solver_depthfirst
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME} "-g" "-a" "backtracking" "-rs" "-a" "dfl"
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME} "-g" "-a" "backtracking" "-rs" "-a" "dfr"
        DEPENDS ${PROJECT_NAME}
)

add_custom_target(run_solver_depthfirst_test
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME} "-g" "-a" "backtracking" "-rs" "-a" "dfl"
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME} "-g" "-a" "backtracking" "-rs" "-a" "dfr"
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME} "-g" "-a" "backtracking" "-rs" "-a" "depthfirstleft"
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME} "-g" "-a" "backtracking" "-rs" "-a" "depthfirstright"
        #    COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME} "-g" "-a" "wallmaker" "-rs" "-a" "dfl"
        #    COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME} "-g" "-a" "wallmaker" "-rs" "-a" "dfr"
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME} "-g" "-a" "diagonal" "-rs" "-a" "dfl"
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME} "-g" "-a" "diagonal" "-rs" "-a" "dfr"
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME} "-g" "-a" "fractal" "-d" "4" "4" "-rs" "-a" "dfl"
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME} "-g" "-a" "fractal" "-d" "4" "4" "-rs" "-a" "dfr"
        DEPENDS ${PROJECT_NAME}
)

add_custom_target(run_all
        DEPENDS run_algo_backtracking run_algo_diagonal run_algo_fractal run_algo_wallmaker run_checker_depthfirst run_solver_breadthfirst run_solver_depthfirst
)

add_custom_target(run_all_test
        DEPENDS run_algo_backtracking_test run_algo_diagonal_test run_algo_fractal_test run_algo_wallmaker_test run_checker_depthfirst_test run_solver_breadthfirst_test run_solver_depthfirst_test
)
