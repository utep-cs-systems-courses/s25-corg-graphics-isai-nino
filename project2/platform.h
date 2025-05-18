#ifndef platform_included
#define platform_included

extern char platCol;
extern char platRow;
extern char direction;
extern char width;

void move_left();
void move_right();
void erase_plat_col(char col, char row, char color);
void update_plat();
void set_boundaries_s();
void set_plat_color(int color);
#endif
