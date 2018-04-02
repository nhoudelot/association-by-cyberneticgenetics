#include "model.h"
#include <stdio.h>
#include <stdlib.h>
#include <GL/gl.h>
#include <math.h>

#define LINELEN 100
#define RND_MAX_LINES 5

T3D_Movie *load_model(char *filename){
   FILE        *moviefile;
   char         one_line[LINELEN];
   T3D_Movie   *movie = NULL;
   int          max_frame = 0, max_vector = 0, f_count = 0, v_count = 0;

   moviefile = fopen(filename,"r");
   if (moviefile == NULL) return(NULL);

   while(fgets(one_line,LINELEN,moviefile) != NULL){
      /* Model */
      if (one_line[0] == 'M'){
         sscanf(one_line,"M %d %d\n",&max_frame, &max_vector);
	 movie = malloc(sizeof(T3D_Movie));
	 if (movie == NULL) return(NULL);
	 movie->max_frame = max_frame;
	 movie->max_vector = max_vector;
         movie->frames = malloc(sizeof(T3D_Frame) * max_frame);
	 if (movie->frames == NULL) return(NULL);

      }
      /* Frame */
      if (one_line[0] == 'F'){
         sscanf(one_line,"F %d %d\n",&f_count,&max_vector);
	 movie->frames[f_count].max_vector = max_vector;
	 movie->frames[f_count].vectors = malloc(sizeof(T3D_Vector) * max_vector);
	 if (movie->frames[f_count].vectors == NULL) return(NULL);

	 v_count = 0;
	 if (f_count > max_frame) return(NULL);
      }
      /* Vertex */
      if (one_line[0] == 'V'){
         sscanf(one_line,"V %lf %lf %lf %lf\n",&movie->frames[f_count].vectors[v_count].start_x,
			                       &movie->frames[f_count].vectors[v_count].start_y,
					       &movie->frames[f_count].vectors[v_count].end_x,
					       &movie->frames[f_count].vectors[v_count].end_y);
	 v_count++;
      }
   }
   fclose(moviefile);
   return(movie);
}

int draw_model(T3D_Movie *movie, int frame, float X, float Y){
   int vectorcount, rnd_count;
   float rnd_x,rnd_y;

   glBegin(GL_LINES);
   for(vectorcount = 0; vectorcount < movie->frames[frame].max_vector; vectorcount++){
      glColor4f(1.1, 0.9, 1.0, 0.1);
	    for(rnd_count = 0; rnd_count < RND_MAX_LINES; rnd_count++){
	       rnd_x = X + drand48() * 10;
	       rnd_y = Y + drand48() * 10;

               glVertex2f(movie->frames[frame].vectors[vectorcount].start_x+rnd_x,
			  movie->frames[frame].vectors[vectorcount].start_y+rnd_y);
	       rnd_x = X + drand48() * 10;
	       rnd_y = Y + drand48() * 10;

	       glVertex2f(movie->frames[frame].vectors[vectorcount].end_x+rnd_x,
			  movie->frames[frame].vectors[vectorcount].end_y+rnd_y);
	    }
   }
   glEnd();
   return(0);
}

void motion1(T3D_Movie *movie, int from, int to, float progress, float X, float Y){
   int i, j, rnd_count;
   float x1, y1, x2, y2; /* z1 and z2 implemented later */
   float rnd_x, rnd_y;

   if (progress > 1.0) progress = 1.0;
   if (progress < 0.0) progress = 0.0;

   glBegin(GL_LINES);
   for(i = 0; i < movie->frames[to].max_vector; i++){
      if(i < movie->frames[from].max_vector) j = i;
      else j = 0; /*FIXME this implementation is not so elegant */
      x1 = (movie->frames[to].vectors[i].start_x - movie->frames[from].vectors[j].start_x) * progress;
      y1 = (movie->frames[to].vectors[i].start_y - movie->frames[from].vectors[j].start_y) * progress;
      x2 = (movie->frames[to].vectors[i].end_x   - movie->frames[from].vectors[j].end_x  ) * progress;
      y2 = (movie->frames[to].vectors[i].end_y   - movie->frames[from].vectors[j].end_y  ) * progress;
      for(rnd_count = 0; rnd_count < RND_MAX_LINES; rnd_count++){
         rnd_x = X + drand48() * 10;
         rnd_y = Y + drand48() * 10;
         glVertex2f(movie->frames[from].vectors[j].start_x + x1 + rnd_x,
                    movie->frames[from].vectors[j].start_y + y1 + rnd_y);
         rnd_x = X + drand48() * 10;
         rnd_y = Y + drand48() * 10;
         glVertex2f(movie->frames[from].vectors[j].end_x + x2 + rnd_x,
                    movie->frames[from].vectors[j].end_y + y2 + rnd_y);
      }
   }
   glEnd();
}


void motion2(T3D_Movie *movie, int from, int to, float p, float X, float Y){
   int i, j, rnd_count;
   float rnd_y, rnd_x;
   float half_startx, half_endx, half_starty, half_endy, center_startx, center_starty, center_endx, center_endy, r_start, r_end, rad_start, rad_end, start_x, start_y, end_x, end_y, process_start, process_end;

   if (p < 0.0) p = 0.0;
   if (p > 1.0) p = 1.0;

   glBegin(GL_LINES);
   for(i = 0; i < movie->frames[to].max_vector; i++){
      if( i < movie->frames[from].max_vector) j = i;
      else j = 0; /*FIXME this implementation is not so elegant */
      half_startx = (movie->frames[from].vectors[j].start_x - movie->frames[to].vectors[i].start_x) / 2.0;
      half_endx   = (movie->frames[from].vectors[j].end_x   - movie->frames[to].vectors[i].end_x  ) / 2.0;
      half_starty = (movie->frames[from].vectors[j].start_y - movie->frames[to].vectors[i].start_y) / 2.0;
      half_endy   = (movie->frames[from].vectors[j].end_y   - movie->frames[to].vectors[i].end_y  ) / 2.0;

      if(half_startx <= 0.0) process_start = 1.0 - p; else process_start = p;
      if(half_endx   <= 0.0) process_end   = 1.0 - p; else process_end   = p;

      center_startx = movie->frames[from].vectors[j].start_x - half_startx;
      center_endx   = movie->frames[from].vectors[j].end_x   - half_endx;
      center_starty = movie->frames[from].vectors[j].start_y - half_starty;
      center_endy   = movie->frames[from].vectors[j].end_y   - half_endy;

      r_start = sqrt(half_startx * half_startx + half_starty * half_starty);
      r_end   = sqrt(half_endx * half_endx + half_endy * half_endy);

      rad_start = atan(half_starty / half_startx) + 3.14 * process_start;
      rad_end   = atan(half_endy   / half_endx  ) + 3.14 * process_end;

      start_x = (cos(rad_start) * r_start) + center_startx;
      start_y = (sin(rad_start) * r_start) + center_starty;
      end_x   = (cos(rad_end  ) * r_end  ) + center_endx;
      end_y   = (sin(rad_end  ) * r_end  ) + center_endy;

      for(rnd_count = 0; rnd_count < RND_MAX_LINES; rnd_count++){
         rnd_x = X + drand48() * 10;
	 rnd_y = Y + drand48() * 10;
	 glVertex2f(start_x + rnd_x,
                    start_y + rnd_y);
	 rnd_x = X + drand48() * 10;
	 rnd_y = Y + drand48() * 10;
	 glVertex2f(end_x + rnd_x,
                    end_y + rnd_y);
 
      }
   }
   glEnd();
}

void scale_model(T3D_Movie *movie, int frame, float X, float Y, float scale){
   int vectorcount, rnd_count;
   float x1 = 1024.0, x2 = 0, y1 = 768.0, y2 = 0; /* bound region */
   float centerx, centery;
   float rnd_x, rnd_y;

   /*TODO if it is too slow it should be precalc */
   for(vectorcount = 0; vectorcount < movie->frames[frame].max_vector; vectorcount++){
      if(movie->frames[frame].vectors[vectorcount].start_x > x2) x2 = movie->frames[frame].vectors[vectorcount].start_x;
      if(movie->frames[frame].vectors[vectorcount].end_x   > x2) x2 = movie->frames[frame].vectors[vectorcount].end_x;
      if(movie->frames[frame].vectors[vectorcount].start_y > y2) y2 = movie->frames[frame].vectors[vectorcount].start_y;
      if(movie->frames[frame].vectors[vectorcount].end_y   > y2) y2 = movie->frames[frame].vectors[vectorcount].end_y;

      if(movie->frames[frame].vectors[vectorcount].start_x < x1) x1 = movie->frames[frame].vectors[vectorcount].start_x;
      if(movie->frames[frame].vectors[vectorcount].end_x   < x1) x1 = movie->frames[frame].vectors[vectorcount].end_x;
      if(movie->frames[frame].vectors[vectorcount].start_y < y1) y1 = movie->frames[frame].vectors[vectorcount].start_y;
      if(movie->frames[frame].vectors[vectorcount].end_y   < y1) y1 = movie->frames[frame].vectors[vectorcount].end_y;
   }

   centerx = (x2 - x1) / 2;
   centery = (y2 - y1) / 2;

   glBegin(GL_LINES);
   for(vectorcount = 0; vectorcount < movie->frames[frame].max_vector; vectorcount++){
      for(rnd_count = 0; rnd_count < RND_MAX_LINES; rnd_count++){
         rnd_x = drand48() * 10;
	 rnd_y = drand48() * 10;

	 glVertex2f(X - (centerx - movie->frames[frame].vectors[vectorcount].start_x) * scale + rnd_x,
                    Y - (centery - movie->frames[frame].vectors[vectorcount].start_y) * scale + rnd_y);
	 rnd_x = drand48() * 10;
	 rnd_y = drand48() * 10;
	 glVertex2f(X - (centerx - movie->frames[frame].vectors[vectorcount].end_x) * scale + rnd_x,
                    Y - (centery - movie->frames[frame].vectors[vectorcount].end_y) * scale + rnd_y);

      }
   }
   glEnd();
}

void flipflop(T3D_Movie *movie, int frame1, int frame2, float X, float Y, unsigned int time, unsigned int duration){
   static int startframe, endframe;
   static float prevprogress= 0.0;
   float progress;
   int dummy;

   /* awful trick, but the dedline is coming */
   if((startframe != frame1) && (startframe != frame2)){ 
      startframe = frame1;
      endframe = frame2;
      prevprogress = 0.0;
   }

   progress = (float)(time & duration) / (float)duration;

   if((prevprogress > 0.999) && (progress < 0.001)){
      dummy      = startframe;
      startframe = endframe;
      endframe   = dummy;
   }

   motion1(movie, startframe, endframe, progress, X, Y);
   prevprogress = progress;
}

void density(float startx, float starty, float endx, float endy, float density){
    float i,j;
    float area;
    float step;
    float rndx, rndy, probability;
    int k;

    area = abs(endx - startx * (endy - starty));

    step = area / (area * density);

    glColor4f(1.0, 1.0, 1.0, 0.1);
    glBegin( GL_POINTS );
       for(k = 0; k < (area * density); k++){
          rndx = drand48();
          rndy = drand48();
          probability = drand48();
          if( (probability < (sin(rndx / 0.3))) && (probability < (sin(rndy / 0.3))) ){
             i = rndx * (endx - startx) + startx;
             j = rndy * (endy - starty) + starty;
             glVertex2f(i,j);
          }
       }

    glEnd();
}

void blast(T3D_Movie *movie, int frame, float X, float Y, float progress){
   int j, rnd_count;
   float x1, y1, x2, y2; /* z1 and z2 implemented later */
   float rnd_x, rnd_y;

   if (progress > 1.0) progress = 1.0;
   if (progress < 0.0) progress = 0.0;

   glBegin(GL_LINES);
   for(j = 0; j < movie->frames[frame].max_vector; j++){
      x1 = (drand48() * 800.0   - movie->frames[frame].vectors[j].start_x) * progress;
      y1 = (drand48() * 600.0   - movie->frames[frame].vectors[j].start_y) * progress;
      x2 = (drand48() * 800.0   - movie->frames[frame].vectors[j].end_x  ) * progress;
      y2 = (drand48() * 600.0   - movie->frames[frame].vectors[j].end_y  ) * progress;
      for(rnd_count = 0; rnd_count < RND_MAX_LINES; rnd_count++){
         rnd_x = X + drand48() * 10;
         rnd_y = Y + drand48() * 10;
         glVertex2f(movie->frames[frame].vectors[j].start_x + x1 + rnd_x,
                    movie->frames[frame].vectors[j].start_y + y1 + rnd_y);
         rnd_x = X + drand48() * 10;
         rnd_y = Y + drand48() * 10;
         glVertex2f(movie->frames[frame].vectors[j].end_x + x2 + rnd_x,
                    movie->frames[frame].vectors[j].end_y + y2 + rnd_y);
      }
   }
   glEnd();

}
