cmake_minimum_required(VERSION 3.25)
project(maze)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCE_FILES
        src/main.cpp
        src/lib/cell.cpp
        src/lib/checker/breadth_first.cpp
        src/lib/checker/depth_first.cpp
        src/lib/game/fog.cpp
        src/lib/game/fog_hand.cpp
        src/lib/game/splatoon.cpp
        src/lib/game/tom_thumb.cpp
        src/lib/game/tom_thumb_hand.cpp
        src/lib/game/walk.cpp
        src/lib/maze.cpp
        src/lib/rand.cpp
        src/lib/reader.cpp
        src/lib/queue.cpp
        src/lib/show.cpp
        src/lib/solver/breadth_first.cpp
        src/lib/solver/depth_first.cpp
        src/lib/stack.cpp
        src/lib/wall.cpp
        src/lib/writer.cpp
)

set(SOURCE_FILES_GENERATOR
        src/main_generator.cpp
        src/lib/algo/back_tracking.cpp
        src/lib/algo/diagonal.cpp
        src/lib/algo/fractal.cpp
        src/lib/algo/wall_maker.cpp
        src/lib/cell.cpp
        src/lib/checker/depth_first.cpp
        src/lib/maze.cpp
        src/lib/queue.cpp
        src/lib/rand.cpp
        src/lib/show.cpp
        src/lib/solver/breadth_first.cpp
        src/lib/stack.cpp
        src/lib/wall.cpp
        src/lib/writer.cpp
)

set(SOURCE_FILES_DATA
        src/main_data.cpp
        src/lib/algo/back_tracking.cpp
        src/lib/algo/diagonal.cpp
        src/lib/algo/fractal.cpp
        src/lib/game/splatoon.cpp
        src/lib/algo/wall_maker.cpp
        src/lib/cell.cpp
        src/lib/checker/depth_first.cpp
        src/lib/game/fog.cpp
        src/lib/game/fog_hand.cpp
        src/lib/game/tom_thumb.cpp
        src/lib/game/tom_thumb_hand.cpp
        src/lib/maze.cpp
        src/lib/queue.cpp
        src/lib/rand.cpp
        src/lib/show.cpp
        src/lib/solver/breadth_first.cpp
        src/lib/stack.cpp
        src/lib/wall.cpp
        src/lib/writer.cpp
)

set(INCLUDE_DIRS
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

set(EXECUTABLE_PROJECT ${PROJECT_NAME}.out)
add_executable(${EXECUTABLE_PROJECT} ${SOURCE_FILES})
set(EXECUTABLE_PROJECT_GENERATOR ${PROJECT_NAME}_generator.out)
add_executable(${EXECUTABLE_PROJECT_GENERATOR} ${SOURCE_FILES_GENERATOR})
set(EXECUTABLE_PROJECT_DATA ${PROJECT_NAME}_data.out)
add_executable(${EXECUTABLE_PROJECT_DATA} ${SOURCE_FILES_DATA})

target_include_directories(${EXECUTABLE_PROJECT} PUBLIC ${INCLUDE_DIRS})
target_include_directories(${EXECUTABLE_PROJECT_GENERATOR} PUBLIC ${INCLUDE_DIRS})
target_include_directories(${EXECUTABLE_PROJECT_DATA} PUBLIC ${INCLUDE_DIRS})
target_link_directories(${EXECUTABLE_PROJECT} PUBLIC ${LINK_DIRS})
target_link_directories(${EXECUTABLE_PROJECT_GENERATOR} PUBLIC ${LINK_DIRS})
target_link_directories(${EXECUTABLE_PROJECT_DATA} PUBLIC ${LINK_DIRS})
target_link_libraries(${EXECUTABLE_PROJECT} PUBLIC ${LINK_LIBS})
target_link_libraries(${EXECUTABLE_PROJECT_GENERATOR} PUBLIC ${LINK_LIBS})
target_link_libraries(${EXECUTABLE_PROJECT_DATA} PUBLIC ${LINK_LIBS})

add_custom_target(run_test
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${EXECUTABLE_PROJECT} "-i" "src/instances/maze1.txt" "-s"
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${EXECUTABLE_PROJECT} "-i" "src/instances/maze1.txt" "-s" "-c" "-i" "src/instances/maze2.txt" "-s"
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${EXECUTABLE_PROJECT} "-i" "src/instances/maze1.txt" "-rs" "-a" "dfl" "-s"
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${EXECUTABLE_PROJECT} "-i" "src/instances/maze1.txt" "-rs" "-a" "dfr" "-s"
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${EXECUTABLE_PROJECT} "-i" "src/instances/maze1.txt" "-rs" "-a" "bf" "-s"
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${EXECUTABLE_PROJECT_GENERATOR} "-gs" "-d" "10" "10" "-s" "-o" "src/instances/tmp/maze1.txt"
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${EXECUTABLE_PROJECT} "-i" "src/instances/tmp/maze1.txt" "-rs" "-a" "dfl" "-s"
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${EXECUTABLE_PROJECT_GENERATOR} "-gs" "-d" "10" "10" "-a" "bt" "-s"
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${EXECUTABLE_PROJECT} "-gs" "-d" "10" "10" "-a" "wm" "-s" "-rs" "-a" "dfl" "-s"
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${EXECUTABLE_PROJECT_GENERATOR} "-gs" "-d" "10" "10" "-a" "d" "-s" "-o" "src/instances/tmp/maze1.txt"
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${EXECUTABLE_PROJECT} "-i" "src/instances/tmp/maze1.txt" "-rs" "-a" "dfr" "-s"
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${EXECUTABLE_PROJECT_GENERATOR} "-gs" "-d" "4" "4" "-a" "f" "-s" "-o" "src/instances/tmp/maze1.txt"
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${EXECUTABLE_PROJECT} "-i" "src/instances/tmp/maze1.txt" "-rs" "-a" "bf" "-s"
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${EXECUTABLE_PROJECT} "-gs" "-d" "10" "10" "-a" "wm" "-s" "-vs" "-a" "dfl" "-s"
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${EXECUTABLE_PROJECT_GENERATOR} "-gs" "-d" "10" "10" "-a" "d" "-s" "-o" "src/instances/tmp/maze1.txt"
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${EXECUTABLE_PROJECT} "-i" "src/instances/tmp/maze1.txt" "-vs" "-a" "dfr" "-s"
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${EXECUTABLE_PROJECT_GENERATOR} "-gs" "-d" "4" "4" "-a" "f" "-s" "-o" "src/instances/tmp/maze1.txt"
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${EXECUTABLE_PROJECT} "-i" "src/instances/tmp/maze1.txt" "-vs" "-a" "dfr" "-s"
        DEPENDS ${EXECUTABLE_PROJECT} ${EXECUTABLE_PROJECT_GENERATOR}
)

add_custom_target(run_algo_back_tracking
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${EXECUTABLE_PROJECT_GENERATOR} "-gs" "-d" "10" "10" "-a" "bt"
        DEPENDS ${EXECUTABLE_PROJECT} ${EXECUTABLE_PROJECT_GENERATOR}
)

add_custom_target(run_algo_back_tracking_test
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${EXECUTABLE_PROJECT_GENERATOR} "-gs" "-d" "10" "10" "-a" "bt"
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${EXECUTABLE_PROJECT_GENERATOR} "-gs" "-d" "10" "10" "-a" "back_tracking"
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${EXECUTABLE_PROJECT_GENERATOR} "-gs" "-d" "1" "1" "-a" "bt"
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${EXECUTABLE_PROJECT_GENERATOR} "-gs" "-d" "2" "2" "-a" "bt"
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${EXECUTABLE_PROJECT_GENERATOR} "-gs" "-d" "50" "50" "-a" "bt"
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${EXECUTABLE_PROJECT_GENERATOR} "-gs" "-d" "100" "100" "-a" "bt" "-o" "src/instances/tmp/maze1.txt"
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${EXECUTABLE_PROJECT} "-i" "src/instances/tmp/maze1.txt" "-vs"
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${EXECUTABLE_PROJECT} "-i" "src/instances/tmp/maze1.txt" "-rs"
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${EXECUTABLE_PROJECT_GENERATOR} "-g" "-d" "500" "500" "-a" "bt"
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${EXECUTABLE_PROJECT_GENERATOR} "-g" "-d" "750" "750" "-a" "bt"
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${EXECUTABLE_PROJECT_GENERATOR} "-g" "-d" "1000" "1000" "-a" "bt"
        #    COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${EXECUTABLE_PROJECT} "-g" "-d" "1250" "1250" "-a" "bt"
        #    COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${EXECUTABLE_PROJECT} "-g" "-d" "1500" "1500" "-a" "bt"
        DEPENDS ${EXECUTABLE_PROJECT} ${EXECUTABLE_PROJECT_GENERATOR}
)

add_custom_target(run_algo_diagonal
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${EXECUTABLE_PROJECT_GENERATOR} "-gs" "-d" "10" "10" "-a" "d"
        DEPENDS ${EXECUTABLE_PROJECT} ${EXECUTABLE_PROJECT_GENERATOR}
)

add_custom_target(run_algo_diagonal_test
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${EXECUTABLE_PROJECT_GENERATOR} "-gs" "-d" "10" "10" "-a" "d"
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${EXECUTABLE_PROJECT_GENERATOR} "-gs" "-d" "10" "10" "-a" "diagonal"
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${EXECUTABLE_PROJECT_GENERATOR} "-gs" "-d" "1" "1" "-a" "d"
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${EXECUTABLE_PROJECT_GENERATOR} "-gs" "-d" "2" "2" "-a" "d"
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${EXECUTABLE_PROJECT_GENERATOR} "-gs" "-d" "50" "50" "-a" "d"
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${EXECUTABLE_PROJECT_GENERATOR} "-gs" "-d" "100" "100" "-a" "d" "-o" "src/instances/tmp/maze1.txt"
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${EXECUTABLE_PROJECT} "-i" "src/instances/tmp/maze1.txt" "-vs"
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${EXECUTABLE_PROJECT} "-i" "src/instances/tmp/maze1.txt" "-rs"
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${EXECUTABLE_PROJECT_GENERATOR} "-g" "-d" "500" "500" "-a" "d"
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${EXECUTABLE_PROJECT_GENERATOR} "-g" "-d" "750" "750" "-a" "d"
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${EXECUTABLE_PROJECT_GENERATOR} "-g" "-d" "1000" "1000" "-a" "d"
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${EXECUTABLE_PROJECT_GENERATOR} "-g" "-d" "1250" "1250" "-a" "d"
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${EXECUTABLE_PROJECT_GENERATOR} "-g" "-d" "1500" "1500" "-a" "d"
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${EXECUTABLE_PROJECT_GENERATOR} "-g" "-d" "1750" "1750" "-a" "d"
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${EXECUTABLE_PROJECT_GENERATOR} "-g" "-d" "2000" "2000" "-a" "d"
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${EXECUTABLE_PROJECT_GENERATOR} "-g" "-d" "2250" "2250" "-a" "d"
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${EXECUTABLE_PROJECT_GENERATOR} "-g" "-d" "2500" "2500" "-a" "d"
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${EXECUTABLE_PROJECT_GENERATOR} "-g" "-d" "5000" "5000" "-a" "d"
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${EXECUTABLE_PROJECT_GENERATOR} "-g" "-d" "7500" "7500" "-a" "d"
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${EXECUTABLE_PROJECT_GENERATOR} "-g" "-d" "10000" "10000" "-a" "d"
        #    COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${EXECUTABLE_PROJECT} "-g" "-d" "25000" "25000" "-a" "d"
        #    COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${EXECUTABLE_PROJECT} "-g" "-d" "50000" "50000" "-a" "d"
        #    COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${EXECUTABLE_PROJECT} "-g" "-d" "75000" "75000" "-a" "d"
        #    COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${EXECUTABLE_PROJECT} "-g" "-d" "100000" "100000" "-a" "d"
        DEPENDS ${EXECUTABLE_PROJECT} ${EXECUTABLE_PROJECT_GENERATOR}
)

add_custom_target(run_algo_fractal
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${EXECUTABLE_PROJECT_GENERATOR} "-gs" "-d" "4" "4" "-a" "f" "-o" "src/instances/tmp/maze1.txt"
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${EXECUTABLE_PROJECT} "-i" "src/instances/tmp/maze1.txt" "-vs"
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${EXECUTABLE_PROJECT_GENERATOR} "-gs" "-d" "4" "4" "-a" "f" "-i" "-p" "0.25" "-o" "src/instances/tmp/maze1.txt"
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${EXECUTABLE_PROJECT} "-i" "src/instances/tmp/maze1.txt" "-vs" "-p"
        DEPENDS ${EXECUTABLE_PROJECT} ${EXECUTABLE_PROJECT_GENERATOR}
)

add_custom_target(run_algo_fractal_test
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${EXECUTABLE_PROJECT_GENERATOR} "-gs" "-d" "4" "4" "-a" "f"
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${EXECUTABLE_PROJECT_GENERATOR} "-gs" "-d" "4" "4" "-a" "fractal"
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${EXECUTABLE_PROJECT_GENERATOR} "-gs" "-d" "1" "1" "-a" "f"
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${EXECUTABLE_PROJECT_GENERATOR} "-gs" "-d" "2" "2" "-a" "f"
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${EXECUTABLE_PROJECT_GENERATOR} "-g" "-d" "4" "4" "-a" "f" "-o" "src/instances/tmp/maze1.txt"
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${EXECUTABLE_PROJECT} "-i" "src/instances/tmp/maze1.txt" "-vs"
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${EXECUTABLE_PROJECT} "-i" "src/instances/tmp/maze1.txt" "-rs"
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${EXECUTABLE_PROJECT_GENERATOR} "-g" "-d" "5" "5" "-a" "f"
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${EXECUTABLE_PROJECT_GENERATOR} "-g" "-d" "6" "6" "-a" "f"
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${EXECUTABLE_PROJECT_GENERATOR} "-g" "-d" "7" "7" "-a" "f"
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${EXECUTABLE_PROJECT_GENERATOR} "-g" "-d" "8" "8" "-a" "f"
        #    COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${EXECUTABLE_PROJECT} "-g" "-d" "9" "9" "-a" "f"
        #    COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${EXECUTABLE_PROJECT} "-g" "-d" "10" "10" "-a" "f"
        DEPENDS ${EXECUTABLE_PROJECT} ${EXECUTABLE_PROJECT_GENERATOR}
)

add_custom_target(run_algo_wall_maker
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${EXECUTABLE_PROJECT_GENERATOR} "-gs" "-d" "10" "10" "-a" "wm"
        DEPENDS ${EXECUTABLE_PROJECT} ${EXECUTABLE_PROJECT_GENERATOR}
)

add_custom_target(run_algo_wall_maker_test
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${EXECUTABLE_PROJECT_GENERATOR} "-gs" "-d" "10" "10" "-a" "wm"
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${EXECUTABLE_PROJECT_GENERATOR} "-gs" "-d" "10" "10" "-a" "wall_maker"
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${EXECUTABLE_PROJECT_GENERATOR} "-gs" "-d" "1" "1" "-a" "wm"
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${EXECUTABLE_PROJECT_GENERATOR} "-gs" "-d" "2" "2" "-a" "wm"
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${EXECUTABLE_PROJECT_GENERATOR} "-g" "-d" "50" "50" "-a" "wm" "-o" "src/instances/tmp/maze1.txt"
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${EXECUTABLE_PROJECT} "-i" "src/instances/tmp/maze1.txt" "-vs"
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${EXECUTABLE_PROJECT} "-i" "src/instances/tmp/maze1.txt" "-rs"
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${EXECUTABLE_PROJECT_GENERATOR} "-g" "-d" "100" "100" "-a" "wm"
        #        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${EXECUTABLE_PROJECT_GENERATOR} "-g" "-d" "500" "500" "-a" "wm"
        #    COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${EXECUTABLE_PROJECT} "-g" "-d" "750" "750" "-a" "wm"
        #    COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${EXECUTABLE_PROJECT} "-g" "-d" "1000" "1000" "-a" "wm"
        DEPENDS ${EXECUTABLE_PROJECT} ${EXECUTABLE_PROJECT_GENERATOR}
)

add_custom_target(run_checker_breadth_first
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${EXECUTABLE_PROJECT_GENERATOR} "-g" "-a" "back_tracking" "-o" "src/instances/tmp/maze1.txt"
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${EXECUTABLE_PROJECT} "-i" "src/instances/tmp/maze1.txt" "-vs" "-a" "bf"
        DEPENDS ${EXECUTABLE_PROJECT} ${EXECUTABLE_PROJECT_GENERATOR}
)

add_custom_target(run_checker_breadth_first_test
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${EXECUTABLE_PROJECT_GENERATOR} "-g" "-a" "back_tracking" "-o" "src/instances/tmp/maze1.txt"
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${EXECUTABLE_PROJECT} "-i" "src/instances/tmp/maze1.txt" "-vs" "-a" "bf"
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${EXECUTABLE_PROJECT} "-i" "src/instances/tmp/maze1.txt" "-vs" "-a" "breadth_first"
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${EXECUTABLE_PROJECT} "-g" "-a" "wall_maker" "-vs" "-a" "bf"
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${EXECUTABLE_PROJECT_GENERATOR} "-g" "-a" "diagonal" "-o" "src/instances/tmp/maze1.txt"
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${EXECUTABLE_PROJECT} "-i" "src/instances/tmp/maze1.txt" "-vs" "-a" "bf"
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${EXECUTABLE_PROJECT_GENERATOR} "-g" "-a" "fractal" "-d" "4" "4" "-o" "src/instances/tmp/maze1.txt"
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${EXECUTABLE_PROJECT} "-i" "src/instances/tmp/maze1.txt" "-vs" "-a" "bf"
        DEPENDS ${EXECUTABLE_PROJECT} ${EXECUTABLE_PROJECT_GENERATOR}
)

add_custom_target(run_checker_depth_first
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${EXECUTABLE_PROJECT_GENERATOR} "-g" "-a" "back_tracking" "-o" "src/instances/tmp/maze1.txt"
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${EXECUTABLE_PROJECT} "-i" "src/instances/tmp/maze1.txt" "-vs" "-a" "dfl"
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${EXECUTABLE_PROJECT} "-i" "src/instances/tmp/maze1.txt" "-vs" "-a" "dfr"
        DEPENDS ${EXECUTABLE_PROJECT} ${EXECUTABLE_PROJECT_GENERATOR}
)

add_custom_target(run_checker_depth_first_test
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${EXECUTABLE_PROJECT_GENERATOR} "-g" "-a" "back_tracking" "-o" "src/instances/tmp/maze1.txt"
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${EXECUTABLE_PROJECT} "-i" "src/instances/tmp/maze1.txt" "-vs" "-a" "dfl"
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${EXECUTABLE_PROJECT} "-i" "src/instances/tmp/maze1.txt" "-vs" "-a" "dfr"
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${EXECUTABLE_PROJECT} "-i" "src/instances/tmp/maze1.txt" "-vs" "-a" "depth_first_left"
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${EXECUTABLE_PROJECT} "-i" "src/instances/tmp/maze1.txt" "-vs" "-a" "depth_first_right"
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${EXECUTABLE_PROJECT_GENERATOR} "-g" "-a" "wall_maker" "-o" "src/instances/tmp/maze1.txt"
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${EXECUTABLE_PROJECT} "-i" "src/instances/tmp/maze1.txt" "-vs" "-a" "dfl"
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${EXECUTABLE_PROJECT} "-i" "src/instances/tmp/maze1.txt" "-vs" "-a" "dfr"
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${EXECUTABLE_PROJECT_GENERATOR} "-g" "-a" "diagonal" "-o" "src/instances/tmp/maze1.txt"
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${EXECUTABLE_PROJECT} "-i" "src/instances/tmp/maze1.txt" "-vs" "-a" "dfl"
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${EXECUTABLE_PROJECT} "-i" "src/instances/tmp/maze1.txt" "-vs" "-a" "dfr"
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${EXECUTABLE_PROJECT_GENERATOR} "-g" "-a" "fractal" "-d" "4" "4" "-o" "src/instances/tmp/maze1.txt"
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${EXECUTABLE_PROJECT} "-i" "src/instances/tmp/maze1.txt" "-vs" "-a" "dfl"
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${EXECUTABLE_PROJECT} "-i" "src/instances/tmp/maze1.txt" "-vs" "-a" "dfr"
        DEPENDS ${EXECUTABLE_PROJECT} ${EXECUTABLE_PROJECT_GENERATOR}
)

add_custom_target(run_solver_breadth_first
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${EXECUTABLE_PROJECT_GENERATOR} "-g" "-a" "back_tracking" "-o" "src/instances/tmp/maze1.txt"
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${EXECUTABLE_PROJECT} "-i" "src/instances/tmp/maze1.txt" "-rs" "-a" "bf"
        DEPENDS ${EXECUTABLE_PROJECT} ${EXECUTABLE_PROJECT_GENERATOR}
)

add_custom_target(run_solver_breadth_first_test
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${EXECUTABLE_PROJECT_GENERATOR} "-g" "-a" "back_tracking" "-o" "src/instances/tmp/maze1.txt"
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${EXECUTABLE_PROJECT} "-i" "src/instances/tmp/maze1.txt" "-rs" "-a" "bf"
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${EXECUTABLE_PROJECT} "-i" "src/instances/tmp/maze1.txt" "-rs" "-a" "breadth_first"
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${EXECUTABLE_PROJECT_GENERATOR} "-g" "-a" "wall_maker" "-o" "src/instances/tmp/maze1.txt"
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${EXECUTABLE_PROJECT} "-i" "src/instances/tmp/maze1.txt" "-rs" "-a" "bf"
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${EXECUTABLE_PROJECT_GENERATOR} "-g" "-a" "diagonal" "-o" "src/instances/tmp/maze1.txt"
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${EXECUTABLE_PROJECT} "-i" "src/instances/tmp/maze1.txt" "-rs" "-a" "bf"
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${EXECUTABLE_PROJECT_GENERATOR} "-g" "-a" "fractal" "-d" "4" "4" "-o" "src/instances/tmp/maze1.txt"
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${EXECUTABLE_PROJECT} "-i" "src/instances/tmp/maze1.txt" "-rs" "-a" "bf"
        DEPENDS ${EXECUTABLE_PROJECT} ${EXECUTABLE_PROJECT_GENERATOR}
)

add_custom_target(run_solver_depth_first
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${EXECUTABLE_PROJECT_GENERATOR} "-g" "-a" "back_tracking" "-o" "src/instances/tmp/maze1.txt"
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${EXECUTABLE_PROJECT} "-i" "src/instances/tmp/maze1.txt" "-rs" "-a" "dfl"
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${EXECUTABLE_PROJECT} "-i" "src/instances/tmp/maze1.txt" "-rs" "-a" "dfr"
        DEPENDS ${EXECUTABLE_PROJECT} ${EXECUTABLE_PROJECT_GENERATOR}
)

add_custom_target(run_solver_depth_first_test
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${EXECUTABLE_PROJECT_GENERATOR} "-g" "-a" "back_tracking" "-o" "src/instances/tmp/maze1.txt"
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${EXECUTABLE_PROJECT} "-i" "src/instances/tmp/maze1.txt" "-rs" "-a" "dfl"
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${EXECUTABLE_PROJECT} "-i" "src/instances/tmp/maze1.txt" "-rs" "-a" "dfr"
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${EXECUTABLE_PROJECT} "-i" "src/instances/tmp/maze1.txt" "-rs" "-a" "depth_first_left"
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${EXECUTABLE_PROJECT} "-i" "src/instances/tmp/maze1.txt" "-rs" "-a" "depth_first_right"
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${EXECUTABLE_PROJECT_GENERATOR} "-g" "-a" "wall_maker" "-o" "src/instances/tmp/maze1.txt"
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${EXECUTABLE_PROJECT} "-i" "src/instances/tmp/maze1.txt" "-rs" "-a" "dfl"
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${EXECUTABLE_PROJECT} "-i" "src/instances/tmp/maze1.txt" "-rs" "-a" "dfr"
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${EXECUTABLE_PROJECT_GENERATOR} "-g" "-a" "diagonal" "-o" "src/instances/tmp/maze1.txt"
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${EXECUTABLE_PROJECT} "-i" "src/instances/tmp/maze1.txt" "-rs" "-a" "dfl"
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${EXECUTABLE_PROJECT} "-i" "src/instances/tmp/maze1.txt" "-rs" "-a" "dfr"
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${EXECUTABLE_PROJECT_GENERATOR} "-g" "-a" "fractal" "-d" "4" "4" "-o" "src/instances/tmp/maze1.txt"
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${EXECUTABLE_PROJECT} "-i" "src/instances/tmp/maze1.txt" "-rs" "-a" "dfl"
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${EXECUTABLE_PROJECT} "-i" "src/instances/tmp/maze1.txt" "-rs" "-a" "dfr"
        DEPENDS ${EXECUTABLE_PROJECT} ${EXECUTABLE_PROJECT_GENERATOR}
)

add_custom_target(run_game_fog
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${EXECUTABLE_PROJECT_GENERATOR} "-g" "-a" "back_tracking" "-o" "src/instances/tmp/maze1.txt"
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${EXECUTABLE_PROJECT} "-i" "src/instances/tmp/maze1.txt" "-gs" "-t" "fog" "-s"
        DEPENDS ${EXECUTABLE_PROJECT} ${EXECUTABLE_PROJECT_GENERATOR}
)

add_custom_target(run_game_fog_test
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${EXECUTABLE_PROJECT_GENERATOR} "-g" "-a" "back_tracking" "-o" "src/instances/tmp/maze1.txt"
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${EXECUTABLE_PROJECT} "-i" "src/instances/tmp/maze1.txt" "-gs" "-t" "fog" "-s"
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${EXECUTABLE_PROJECT_GENERATOR} "-g" "-a" "back_tracking" "-d" "100" "100" "-o" "src/instances/tmp/maze1.txt"
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${EXECUTABLE_PROJECT} "-i" "src/instances/tmp/maze1.txt" "-g" "-t" "fog" "-s"
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${EXECUTABLE_PROJECT_GENERATOR} "-g" "-a" "wall_maker" "-o" "src/instances/tmp/maze1.txt"
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${EXECUTABLE_PROJECT} "-i" "src/instances/tmp/maze1.txt" "-gs" "-t" "fog"
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${EXECUTABLE_PROJECT_GENERATOR} "-g" "-a" "wall_maker" "-d" "100" "100" "-o" "src/instances/tmp/maze1.txt"
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${EXECUTABLE_PROJECT} "-i" "src/instances/tmp/maze1.txt" "-g" "-t" "fog" "-s"
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${EXECUTABLE_PROJECT_GENERATOR} "-g" "-a" "diagonal" "-o" "src/instances/tmp/maze1.txt"
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${EXECUTABLE_PROJECT} "-i" "src/instances/tmp/maze1.txt" "-gs" "-t" "fog" "-s"
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${EXECUTABLE_PROJECT_GENERATOR} "-g" "-a" "diagonal" "-d" "100" "100" "-o" "src/instances/tmp/maze1.txt"
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${EXECUTABLE_PROJECT} "-i" "src/instances/tmp/maze1.txt" "-g" "-t" "fog" "-s"
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${EXECUTABLE_PROJECT_GENERATOR} "-g" "-a" "fractal" "-d" "4" "4" "-o" "src/instances/tmp/maze1.txt"
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${EXECUTABLE_PROJECT} "-i" "src/instances/tmp/maze1.txt" "-gs" "-t" "fog" "-s"
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${EXECUTABLE_PROJECT_GENERATOR} "-g" "-a" "fractal" "-i" "-d" "4" "4" "-o" "src/instances/tmp/maze1.txt"
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${EXECUTABLE_PROJECT} "-i" "src/instances/tmp/maze1.txt" "-gs" "-t" "fog" "-s"
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${EXECUTABLE_PROJECT_GENERATOR} "-g" "-a" "fractal" "-d" "8" "8" "-o" "src/instances/tmp/maze1.txt"
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${EXECUTABLE_PROJECT} "-i" "src/instances/tmp/maze1.txt" "-g" "-t" "fog" "-s"
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${EXECUTABLE_PROJECT_GENERATOR} "-g" "-a" "fractal" "-i" "-d" "8" "8" "-o" "src/instances/tmp/maze1.txt"
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${EXECUTABLE_PROJECT} "-i" "src/instances/tmp/maze1.txt" "-g" "-t" "fog" "-s"
        DEPENDS ${EXECUTABLE_PROJECT} ${EXECUTABLE_PROJECT_GENERATOR}
)

add_custom_target(run_game_fog_hand
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${EXECUTABLE_PROJECT_GENERATOR} "-g" "-a" "back_tracking" "-o" "src/instances/tmp/maze1.txt"
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${EXECUTABLE_PROJECT} "-i" "src/instances/tmp/maze1.txt" "-gs" "-t" "fr" "-s"
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${EXECUTABLE_PROJECT} "-i" "src/instances/tmp/maze1.txt" "-gs" "-t" "fl" "-s"
        DEPENDS ${EXECUTABLE_PROJECT} ${EXECUTABLE_PROJECT_GENERATOR}
)

add_custom_target(run_game_fog_hand_test
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${EXECUTABLE_PROJECT_GENERATOR} "-g" "-a" "back_tracking" "-o" "src/instances/tmp/maze1.txt"
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${EXECUTABLE_PROJECT} "-i" "src/instances/tmp/maze1.txt" "-gs" "-t" "fr" "-s"
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${EXECUTABLE_PROJECT} "-i" "src/instances/tmp/maze1.txt" "-gs" "-t" "fl" "-s"
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${EXECUTABLE_PROJECT_GENERATOR} "-g" "-a" "back_tracking" "-d" "100" "100" "-o" "src/instances/tmp/maze1.txt"
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${EXECUTABLE_PROJECT} "-i" "src/instances/tmp/maze1.txt" "-g" "-t" "fr" "-s"
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${EXECUTABLE_PROJECT} "-i" "src/instances/tmp/maze1.txt" "-g" "-t" "fl" "-s"
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${EXECUTABLE_PROJECT_GENERATOR} "-g" "-a" "wall_maker" "-o" "src/instances/tmp/maze1.txt"
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${EXECUTABLE_PROJECT} "-i" "src/instances/tmp/maze1.txt" "-gs" "-t" "fr" "-s"
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${EXECUTABLE_PROJECT} "-i" "src/instances/tmp/maze1.txt" "-gs" "-t" "fl" "-s"
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${EXECUTABLE_PROJECT_GENERATOR} "-g" "-a" "wall_maker" "-d" "100" "100" "-o" "src/instances/tmp/maze1.txt"
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${EXECUTABLE_PROJECT} "-i" "src/instances/tmp/maze1.txt" "-g" "-t" "fr" "-s"
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${EXECUTABLE_PROJECT} "-i" "src/instances/tmp/maze1.txt" "-g" "-t" "fl" "-s"
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${EXECUTABLE_PROJECT_GENERATOR} "-g" "-a" "diagonal" "-o" "src/instances/tmp/maze1.txt"
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${EXECUTABLE_PROJECT} "-i" "src/instances/tmp/maze1.txt" "-gs" "-t" "fr" "-s"
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${EXECUTABLE_PROJECT} "-i" "src/instances/tmp/maze1.txt" "-gs" "-t" "fl" "-s"
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${EXECUTABLE_PROJECT_GENERATOR} "-g" "-a" "diagonal" "-d" "100" "100" "-o" "src/instances/tmp/maze1.txt"
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${EXECUTABLE_PROJECT} "-i" "src/instances/tmp/maze1.txt" "-g" "-t" "fr" "-s"
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${EXECUTABLE_PROJECT} "-i" "src/instances/tmp/maze1.txt" "-g" "-t" "fl" "-s"
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${EXECUTABLE_PROJECT_GENERATOR} "-g" "-a" "fractal" "-d" "4" "4" "-o" "src/instances/tmp/maze1.txt"
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${EXECUTABLE_PROJECT} "-i" "src/instances/tmp/maze1.txt" "-gs" "-t" "fr" "-s"
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${EXECUTABLE_PROJECT} "-i" "src/instances/tmp/maze1.txt" "-gs" "-t" "fl" "-s"
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${EXECUTABLE_PROJECT_GENERATOR} "-g" "-a" "fractal" "-i" "-d" "4" "4" "-o" "src/instances/tmp/maze1.txt"
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${EXECUTABLE_PROJECT} "-i" "src/instances/tmp/maze1.txt" "-gs" "-t" "fr" "-s"
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${EXECUTABLE_PROJECT} "-i" "src/instances/tmp/maze1.txt" "-gs" "-t" "fl" "-s"
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${EXECUTABLE_PROJECT_GENERATOR} "-g" "-a" "fractal" "-d" "8" "8" "-o" "src/instances/tmp/maze1.txt"
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${EXECUTABLE_PROJECT} "-i" "src/instances/tmp/maze1.txt" "-g" "-t" "fr" "-s"
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${EXECUTABLE_PROJECT} "-i" "src/instances/tmp/maze1.txt" "-g" "-t" "fl" "-s"
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${EXECUTABLE_PROJECT_GENERATOR} "-g" "-a" "fractal" "-i" "-d" "8" "8" "-o" "src/instances/tmp/maze1.txt"
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${EXECUTABLE_PROJECT} "-i" "src/instances/tmp/maze1.txt" "-g" "-t" "fr" "-s"
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${EXECUTABLE_PROJECT} "-i" "src/instances/tmp/maze1.txt" "-g" "-t" "fl" "-s"
        DEPENDS ${EXECUTABLE_PROJECT} ${EXECUTABLE_PROJECT_GENERATOR}
)

add_custom_target(run_all
        DEPENDS run_algo_back_tracking run_algo_diagonal run_algo_fractal run_algo_wall_maker run_checker_depth_first run_solver_breadth_first run_solver_depth_first
)

add_custom_target(run_all_test
        DEPENDS run_algo_back_tracking_test run_algo_diagonal_test run_algo_fractal_test run_algo_wall_maker_test run_checker_depth_first_test run_solver_breadth_first_test run_solver_depth_first_test
)
