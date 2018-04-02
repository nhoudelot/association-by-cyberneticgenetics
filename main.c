#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>
#include <SDL/SDL_mixer.h>
#include <GL/gl.h>
#include <unistd.h>
#include <math.h>
#include "model.h"

int main(){
   SDL_Event event;
   T3D_Movie *movie;
   Uint32 now = 0, start;
   Mix_Music *music;

/* Initialization */
SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
SDL_SetVideoMode( 1024, 768, 16, SDL_OPENGL | SDL_GL_DOUBLEBUFFER | SDL_HWPALETTE | SDL_RESIZABLE | SDL_HWSURFACE);
SDL_ShowCursor(SDL_DISABLE);
glClearColor(0.0,0.0,0.0,0.0);
glMatrixMode(GL_PROJECTION);
glLoadIdentity();

glOrtho(0.0,800.0,600.0,0.0,-10.0,600.0);
if ((movie = load_model("/usr/share/association-by-cyberneticgenetics/model.TVF")) == NULL) printf("Error!\n");

Mix_OpenAudio(22050, AUDIO_S16, 2, 4096);
music = Mix_LoadMUS("/usr/share/association-by-cyberneticgenetics/the.monotonic.ogg");
Mix_PlayMusic(music, 0);

start = SDL_GetTicks();

while(Mix_PlayingMusic()){
   /* Event handling */
   while( SDL_PollEvent( &event) ){
      switch(event.type){
         case SDL_KEYDOWN:
            if (event.key.keysym.sym == SDLK_ESCAPE) Mix_HaltMusic();
	    if (event.key.keysym.sym == SDLK_SPACE) printf("%d\n", (int)now);/*FIXME This is very important to set the syncrone :-)*/
            break;
      }
   }

   /* Drawing */
   glClear(GL_COLOR_BUFFER_BIT);

   now = SDL_GetTicks() - start;
   /* Main title */
   if( (now > 0)       && (now < 4100))        { motion1(movie, 0, 1, (float)now / 3900.0, 0, 0);}
   if( (now > 4100)    && (now < 7800))        { motion2(movie, 1, 2, (float)(now - 4100)  / (4300  - 4100) , 0, 0); }
   if( (now > 7800)    && (now < 11800))       { motion2(movie, 2, 3, (float)(now - 7800)  / (8000  - 7800) , 0, 0); }
   if( (now > 11800)   && (now < 15566))       { motion2(movie, 3, 4, (float)(now - 11800) / (12000 - 11800), 0, 0); }

   /* Motto */
   if( (now > 15566)   && (now < 19446))       { motion2(movie, 4, 5, (float)(now - 15566) / (15800 - 15566), 0, 0); }
   if( (now > 19446)   && (now < 23331))       { motion2(movie, 5,25, (float)(now - 19446) / (19700 - 19446), 0, 0); }
   if( (now > 23331)   && (now < 27117))       { motion2(movie,25,26, (float)(now - 23331) / (23500 - 23331), 0, 0); }
   if( (now > 27117)   && (now < 30000))       { motion2(movie,26,45, (float)(now - 27117) / (27300 - 27117), 0, 0); }

   /* Draw a flower */
   if( (now > 31024)   && (now < 31804))       { motion1(movie, 6, 7, (float)(now - 31024) / (31500 - 31024), 0  , 490); }
   if( (now > 31804)   && (now < 33070))       { motion1(movie, 7, 8, (float)(now - 31804) / (32300 - 31804), 0  , 490); }
   if( (now > 33070)   && (now < 33763))       { motion1(movie, 8, 9, (float)(now - 33070) / (33570 - 33070), 0  , 490); }
   if( (now > 33763)   && (now < 65000))       { motion1(movie, 9,10, (float)(now - 33763) / (34000 - 33763), 0  , 490); }

   if( (now > 34912)   && (now < 35681))       { motion1(movie, 6, 7, (float)(now - 34912) / (35400 - 34912), 100, 490); }
   if( (now > 35681)   && (now < 36912))       { motion1(movie, 7, 8, (float)(now - 35681) / (36100 - 35681), 100, 490); }
   if( (now > 36912)   && (now < 37626))       { motion1(movie, 8, 9, (float)(now - 36912) / (37400 - 36912), 100, 490); }
   if( (now > 37626)   && (now < 65000))       { motion1(movie, 9,10, (float)(now - 37626) / (38000 - 37626), 100, 490); }

   if( (now > 38795)   && (now < 39594))       { 
	                                         motion1(movie, 6, 7, (float)(now - 38795) / (39300 - 38795), 250, 490);
						 motion1(movie, 6, 7, (float)(now - 38795) / (39300 - 38795), 320, 490);
	                                         motion1(movie, 6, 7, (float)(now - 38795) / (39300 - 38795), 650, 490);
						 motion1(movie, 6, 7, (float)(now - 38795) / (39300 - 38795), 520, 490);
                                               }
   if( (now > 39594)   && (now < 40728))       { 
	                                         motion1(movie, 7, 8, (float)(now - 39594) / (40090 - 39594), 250, 490);
		                                 motion1(movie, 7, 8, (float)(now - 39594) / (40090 - 39594), 320, 490);
                                                 motion1(movie, 7, 8, (float)(now - 39594) / (40090 - 39594), 650, 490);
	                                         motion1(movie, 7, 8, (float)(now - 39594) / (40090 - 39594), 520, 490);
                                               }
   if( (now > 40728)   && (now < 41415))       { 
	                                         motion1(movie, 8, 9, (float)(now - 40728) / (41200 - 40728), 250, 490);
                                                 motion1(movie, 8, 9, (float)(now - 40728) / (41200 - 40728), 320, 490);
                                                 motion1(movie, 8, 9, (float)(now - 40728) / (41200 - 40728), 650, 490);
                                                 motion1(movie, 8, 9, (float)(now - 40728) / (41200 - 40728), 520, 490);
                                               }
   if( (now > 41415)   && (now < 65000))       { 
	                                         motion1(movie, 9,10, (float)(now - 41415) / (41700 - 41415), 250, 490);
                                                 motion1(movie, 9,10, (float)(now - 41415) / (41700 - 41415), 320, 490);
                                                 motion1(movie, 9,10, (float)(now - 41415) / (41700 - 41415), 650, 490);
                                                 motion1(movie, 9,10, (float)(now - 41415) / (41700 - 41415), 520, 490);
                                               }

   if( (now > 42641)   && (now < 43407))       { motion1(movie, 6, 7, (float)(now - 42641) / (43100 - 42641), 430, 490); }
   if( (now > 43407)   && (now < 44592))       { motion1(movie, 7, 8, (float)(now - 43407) / (43907 - 43407), 430, 490); }
   if( (now > 44592)   && (now < 45327))       { motion1(movie, 8, 9, (float)(now - 44592) / (45080 - 44592), 430, 490); }
   if( (now > 45327)   && (now < 65000))       { motion1(movie, 9,10, (float)(now - 45327) / (45600 - 45327), 430, 490); }
   if( (now > 46000)   && (now < 50308))       { flipflop(movie,31,32, (now - 46000) / 100, 200, (now - 46000), 60); }
   if( (now > 50308)   && (now < 57000))       { motion1(movie,32,33, (float)(now - 50308) / (57000 - 50308), (now - 46000) / 100,180);}
   if( (now > 57000)   && (now < 65000))       { flipflop(movie,33,34, (now - 46000) / 100, 200, (now - 57000), 40);}

   /* dragon */
   if( (now > 65000)   && (now < 69389))       { draw_model(movie, 44, 0, 0); }
   if( (now > 69389)   && (now < 77075))       { motion1(movie,44,39, (float)(now - 69389) / (72000 - 69389), 0, 0); }
   if( (now > 77075)   && (now < 89140))       { motion1(movie,39,46, (float)(now - 77075) / (79000 - 77075), 0, 0); }
   if( (now > 80968)   && (now < 84855))       { /*draw_model(movie, 47, 0, 0);
	                                         draw_model(movie, 48, 0, 0);*/
						 motion1(movie,56,47, (float)(now - 80968) / (82000 - 80968), 0, 0);
						 motion1(movie,55,48, (float)(now - 80968) / (82000 - 80968), 0, 0);
   }
   if( (now > 84855)   && (now < 89000))       { motion1(movie,47,49, (float)(now - 84855) / (87000 - 84855), 0, 0); 
	                                         motion1(movie,48,40, (float)(now - 84855) / (87000 - 84855), 0, 0);
   }

   /* DNA */
   if( (now > 89140)   && (now < 92575))       { draw_model(movie, 52, 0, 0); }
   if( (now > 92575)   && (now < 96271))       { motion1(movie,52,57, (float)(now - 92575) / (95000 - 92575), 0, 0);}
   if( (now > 96271)   && (now < 100275))      { motion1(movie,57,51, (float)(now - 96271) / (98000 - 96271), 0, 0);}
   if( (now > 100275)  && (now < 107949))      { motion1(movie,51,36, (float)(now - 100275)/ (104000- 100275),0, 0);}
   /* clock */
   if( (now > 107949)  && (now < 108725))      { scale_model(movie,36,400,300, 1.2);}
   if( (now > 108725)  && (now < 109823))      { scale_model(movie,36,400,300, 1.6);}
   if( (now > 109823)  && (now < 110611))      { scale_model(movie,36,400,300, 2.0);}
   if( (now > 110611)  && (now < 111711))      { scale_model(movie,36,400,300, 1.0);}

   /* Door */
   if( (now > 111711)  && (now < 113656))      { draw_model(movie, 21, 300, 50);}
   if( (now > 113656)  && (now < 115782))      { motion1(movie,21,22, (float)(now - 113656) / (115000 - 113656), 300, 50); }
   if( (now > 115782)  && (now < 119937))      { scale_model(movie,22,432,310,1.0 + ((float)now - 115782.0) / 500.0 ); }

   /* Ship */
   if( (now > 119937)  && (now < 126083))      { flipflop(movie,23,24, 0, 0, (now - 119937), 1000); }
   /*127083 shoot */
   if( (now > 126083)  && (now < 128000))      { draw_model(movie, 35, 100, 0); density(347, 53, 455, 115, 0.2); }
   if( (now > 127070)  && (now < 127095))      { draw_model(movie, 38, 0, 125);}

   /* Sink */
   if( (now > 128000)  && (now < 129000))      { motion1(movie,27,28, (float)(now - 128000) / (129000 - 128000), -1400,-1000);}
   if( (now > 129000)  && (now < 130000))      { motion1(movie,28,29, (float)(now - 129000) / (130000 - 129000), -1400,-1000);}
   if( (now > 130000)  && (now < 131000))      { motion1(movie,29,30, (float)(now - 130000) / (131000 - 130000), -1400,-1000);}
   if( (now > 131000)  && (now < 133000))      { flipflop(movie,30,29,-1400,-1000,(now - 131000), 1000); }

   if( (now > 133000)  && (now < 135000))      { draw_model(movie, 35, 100, 0); density(347, 53, 455, 115, 0.2);}
   if( (now > 134780)  && (now < 134800))      { draw_model(movie, 38, 0, 125);}

   /*hervadas (i don't know the english word) */
   if( (now > 135000)  && (now < 138622))      {
	                                         motion1(movie,10,42, (float)(now - 135000) / (138000 - 135000),   0, 490);
						 motion1(movie,10,42, (float)(now - 135000) / (138000 - 135000), 100, 490);
	                                         motion1(movie,10,42, (float)(now - 135000) / (138000 - 135000), 250, 490);
	                                         motion1(movie,10,42, (float)(now - 135000) / (138000 - 135000), 320, 490);
	                                         motion1(movie,10,42, (float)(now - 135000) / (138000 - 135000), 650, 490);
	                                         motion1(movie,10,42, (float)(now - 135000) / (138000 - 135000), 520, 490);
	                                         motion1(movie,10,42, (float)(now - 135000) / (138000 - 135000), 430, 490);
   }
   if( (now > 138622)  && (now < 140000))      {
	                                         motion1(movie,42,43, (float)(now - 138622) / (139000 - 138622),   0, 490);
	                                         motion1(movie,42,43, (float)(now - 138622) / (139000 - 138622), 100, 490);
	                                         motion1(movie,42,43, (float)(now - 138622) / (139000 - 138622), 250, 490);
	                                         motion1(movie,42,43, (float)(now - 138622) / (139000 - 138622), 320, 490);
	                                         motion1(movie,42,43, (float)(now - 138622) / (139000 - 138622), 650, 490);
	                                         motion1(movie,42,43, (float)(now - 138622) / (139000 - 138622), 520, 490);
	                                         motion1(movie,42,43, (float)(now - 138622) / (139000 - 138622), 430, 490);
   }

   if( (now > 140000)  && (now < 143000))      { draw_model(movie, 35, 100, 0); density(347, 53, 455, 115, 0.2);}
   if( (now > 142390)  && (now < 142430))      { draw_model(movie, 38, 0, 125);}

   if( (now > 143000)  && (now < 145000))      { draw_model(movie, 59, 0, 0);}
   /* colibri */
   if( (now > 145000)  && (now < 157780)){ flipflop(movie, 53,54, 0, 0,now - 145000,40); }
   /*if( (now > 145000)  && (now < 150000))      { draw_model(movie, 53, 0, 0);}
   if( (now > 150000)  && (now < 157780))      { draw_model(movie, 54, 0, 0);}*/

   /* C64 */
   if( (now > 157780)  && (now < 160000))      { draw_model(movie, 37, 200, 200);}
   if( (now > 160000)  && (now < 164023))      { 
	   draw_model(movie, 35, 100, 0); density(347, 53, 455, 115, 0.2);
           draw_model(movie,37,800 - (now - 160000) / 10,200);
   }

   if( (now > 164023)  && (now < 164800))      { 
	   blast(movie, 35, 100, 0, (float)(now - 4023) / (4100 - 4023));
	   draw_model(movie,37,800 - (164023 - 160000) / 10,200);
   }

   if( (now > 164800)  && (now < 165000))      { draw_model(movie,37,800 - (164023 - 160000) / 10,200); }

   if( (now > 165000)  && (now < 167000))      {
	                                         motion1(movie,43,42, (float)(now - 165000) / (167000 - 165000),   0, 490);
	                                         motion1(movie,43,42, (float)(now - 165000) / (167000 - 165000), 100, 490);
	                                         motion1(movie,43,42, (float)(now - 165000) / (167000 - 165000), 250, 490);
	                                         motion1(movie,43,42, (float)(now - 165000) / (167000 - 165000), 320, 490);
	                                         motion1(movie,43,42, (float)(now - 165000) / (167000 - 165000), 650, 490);
	                                         motion1(movie,43,42, (float)(now - 165000) / (167000 - 165000), 520, 490);
	                                         motion1(movie,43,42, (float)(now - 165000) / (167000 - 165000), 430, 490);
   }
   if( (now > 167000)  && (now < 169377))      {
	                                         motion1(movie,42,10, (float)(now - 167000) / (169000 - 167000),   0, 490);
	                                         motion1(movie,42,10, (float)(now - 167000) / (169000 - 167000), 100, 490);
	                                         motion1(movie,42,10, (float)(now - 167000) / (169000 - 167000), 250, 490);
	                                         motion1(movie,42,10, (float)(now - 167000) / (169000 - 167000), 320, 490);
	                                         motion1(movie,42,10, (float)(now - 167000) / (169000 - 167000), 650, 490);
	                                         motion1(movie,42,10, (float)(now - 167000) / (169000 - 167000), 520, 490);
	                                         motion1(movie,42,10, (float)(now - 167000) / (169000 - 167000), 430, 490);
   }
   
   /* Greetings */
   if( (now > 169377)  && (now < 172799))      { draw_model(movie, 41,   0,   0);}
   if( (now > 172799)  && (now < 174939))      { draw_model(movie, 11, 100, 100);}
   if( (now > 174939)  && (now < 176640))      { draw_model(movie, 12, 100, 100);}
   if( (now > 176640)  && (now < 178612))      { draw_model(movie, 13, 10 , 400);}
   if( (now > 178612)  && (now < 180480))      { draw_model(movie, 14, 100, 100);}
   if( (now > 180480)  && (now < 182401))      { draw_model(movie, 15, 10 , 100);}
   if( (now > 182401)  && (now < 184421))      { draw_model(movie, 16, 100, 300);}
   if( (now > 184421)  && (now < 186241))      { draw_model(movie, 17, 100, 100);}
   if( (now > 186241)  && (now < 188237))      { draw_model(movie, 18, 100, 400);}
   if( (now > 188237)  && (now < 190000))      { draw_model(movie, 19,   0, 100);}
   if( (now > 190000)  && (now < 191974))      { draw_model(movie, 50, 100, 300);}
   /* SceneCon */
   if( (now > 191974))                         { draw_model(movie, 20, 100, 100);}

   SDL_GL_SwapBuffers();
}

/* Quit */
SDL_ShowCursor(SDL_ENABLE);
Mix_FreeMusic(music);
Mix_CloseAudio();
SDL_Quit();
free(movie);
return(0);
}
