#ifndef _GAME_CONFIG_H_
#define _GAME_CONFIG_H_

#define GRAVITY 2
#define XSPEED 7
#define YSPEED 16

/* MAP SIZE */
#define MAP_HEIGHT 460
#define MAP_WIDTH 760
#define BORDER_WIDTH 5

typedef enum {
    INACTIVE, 
    RUN,
    JUMP,
    FALL,
    WALL_CLIMB,
    CARRY,
    DIE
} Game_state;

typedef enum {INIT, DRAG} Item_state;


#endif /* _GAME_CONFIG_H_ */
