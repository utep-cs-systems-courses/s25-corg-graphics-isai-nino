#ifndef ball_included
#define ball_included

extern char ballCol;
extern char ballRow;
extern char ball_size;
extern char colDirection;
extern char rowDirection;

void erase_ball_col(int col, int row, int color, int size, int direction);
void erase_ball_row(int col, int row, int color, int size, int direction);

extern void update_ball_direction();
extern void redraw_ball();
extern void reset_ball_position();

#endif 
