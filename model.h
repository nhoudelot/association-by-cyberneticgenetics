typedef struct T3D_Color {
   double              r;
   double              g;
   double              b;
   double              a;
} T3D_Color;

typedef struct T3D_Vector {
   double              start_x;
   double              start_y;
   double              end_x;
   double              end_y;
   T3D_Color           color;
} T3D_Vector;

typedef struct T3D_Frame {
   int                max_vector;
   T3D_Vector        *vectors;
} T3D_Frame;

typedef struct T3D_Movie {
   int                max_frame;
   int                max_vector;
   T3D_Frame         *frames;
} T3D_Movie;

T3D_Movie *load_model(char *filename);
int resize_frame(T3D_Movie *movie, int frame, float width, float height);
int draw_model(T3D_Movie *movie, int frame, float X, float Y);
void motion1(T3D_Movie *movie, int from, int to, float process, float X, float Y);
void motion2(T3D_Movie *movie, int from, int to, float process, float X, float Y);
void scale_model(T3D_Movie *movie, int frame, float X, float Y, float scale);
void flipflop(T3D_Movie *movie, int frame1, int frame2, float X, float Y, unsigned int time, unsigned int duration);
void density(float startx, float starty, float endx, float endy, float density);
void blast(T3D_Movie *movie, int frame, float X, float Y, float progress);
