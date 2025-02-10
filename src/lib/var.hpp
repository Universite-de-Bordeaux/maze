#ifndef MAZE_VAR_HPP
#define MAZE_VAR_HPP

#define MAZE_ENV_FILE ".env"  //> Environment file

#define MAZE_OK 0             //> No error
#define MAZE_COMMAND_ERROR 1  //> Command line error
#define MAZE_FILE_ERROR 2     //> File error
#define MAZE_GRAPHIC_ERROR 3  //> Graphic error

#define MAZE_CELL_TOP 0     //> Top cell
#define MAZE_CELL_RIGHT 1   //> Right cell
#define MAZE_CELL_BOTTOM 2  //> Bottom cell
#define MAZE_CELL_LEFT 3    //> Left cell

#define MAZE_WALL_START_RIGHT_TOP 0    //> Start wall right top
#define MAZE_WALL_START 1              //> Start wall
#define MAZE_WALL_START_LEFT_BOTTOM 2  //> Start wall left bottom
#define MAZE_WALL_END_RIGHT_TOP 3      //> End wall right top
#define MAZE_WALL_END 4                //> End wall
#define MAZE_WALL_END_LEFT_BOTTOM 5    //> End wall left bottom

#define MAZE_WALL_COLOR 255, 255, 255    //> Wall color
#define MAZE_WALL_START_COLOR 255, 0, 0  //> Start wall color
#define MAZE_WALL_END_COLOR 0, 255, 0    //> End wall color

#define MAZE_STATUS_IDLE 0                    //> Idle cell
#define MAZE_STATUS_IDLE_COLOR 0, 0, 0        //> Idle cell color
#define MAZE_STATUS_VISITED 1                 //> Visited cell
#define MAZE_STATUS_VISITED_COLOR 0, 0, 128   //> Visited cell color
#define MAZE_STATUS_HOPELESS 2                //> Hopeless cell
#define MAZE_STATUS_HOPELESS_COLOR 0, 0, 255  //> Hopeless cell color
#define MAZE_STATUS_TOO_MANY_NEIGHBORS 3      //> Too many neighbors cell
#define MAZE_STATUS_TOO_MANY_NEIGHBORS_COLOR \
    128, 128, 0                              //> Too many neighbors cell color
#define MAZE_STATUS_WAY_OUT 4                //> Way out cell
#define MAZE_STATUS_WAY_OUT_COLOR 0, 125, 0  //> Way out cell color
#define MAZE_STATUS_CURRENT 5                //> Current cell
#define MAZE_STATUS_CURRENT_COLOR 125, 0, 0  //> Current cell color

#define NORTH 0  //> North direction
#define EAST 1   //> East direction
#define SOUTH 2  //> South direction
#define WEST 3   //> West direction
#define ALL 4    //> All directions

#define MAZE_MAX_WINDOW_RATIO 0.9  //> Max window ratio

static constexpr float MIN_ZOOM = 0.5f;
static constexpr float MAX_ZOOM = 5.0f;
static constexpr float ZOOM_FACTOR = 1.1f;

#endif  // MAZE_VAR_HPP
