#ifndef bricks_included
#define bricks_included

typedef struct {
  int col;
  int row;
  int status;  
} Brick;

extern Brick bricks [5][8];

extern void bricks_init();
extern void draw_bricks();
extern void check_brick_collision();
void check_bounce_direction(char brickCol, char brickRow);

#endif 
