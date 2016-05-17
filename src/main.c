/*C_SDL_Game is a simple SDL Game write to practice C
Authors: kao_chen
Copyright (C) 2016 kao_chen <kaochen2[at]gmail.com>

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
*/

#include <stdlib.h>
#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <time.h>

#include "../inc/const.h"
#include "../inc/game.h"
#include "../inc/level.h"
#include "../inc/menu.h"
#include "../inc/sprites.h"
#include "../inc/slc.h"


int main (int argc, char *argv[])
{
   /* start random processor just once */
   srand (time (NULL));

   /* Start and check if SDL start correctly */
   if (SDL_Init (SDL_INIT_VIDEO) == -1)
   {
      fprintf (stderr, "SDL initialization error: %s\n", SDL_GetError ());
      exit (EXIT_FAILURE);
   }

   /* Start SDL TTF */
   if (TTF_Init () == -1)
   {
      fprintf (stderr, "TTF_Init initialization error: %s\n",
               TTF_GetError ());
      exit (EXIT_FAILURE);
   }

   /* Create the window game */
   SDL_Window *window = SDL_CreateWindow (GAME_NAME,
                                          SDL_WINDOWPOS_UNDEFINED,
                                          SDL_WINDOWPOS_UNDEFINED,
                                          W_WIDTH,
                                          W_HEIGHT,
                                          SDL_WINDOW_MOUSE_FOCUS |
                                          SDL_WINDOW_MOUSE_CAPTURE);

   /* Set window icon */
   SDL_SetWindowIcon (window, IMG_Load ("img/icon.png"));

   /* Create a surface from the window */
   SDL_Surface *screen = NULL;
   screen = SDL_GetWindowSurface (window);

   /* Create a surface for the menu from the window */
   SDL_Surface *menu = NULL;
   menu = SDL_GetWindowSurface (window);

   /* Check if window and surface are created */
   if (window == NULL || screen == NULL || menu == NULL)
   {
      fprintf (stderr, "Creating the main window failed: %s\n",
               SDL_GetError ());
      exit (EXIT_FAILURE);
   }
   fprintf (stderr, "Creating the main window succeed\n");

   /* load images into a table of struct */
   Sprites tableSurface[NBR_OF_IMAGES];
   /* Player faces */
   loadSprite (&tableSurface[PLAYER_FRONT], "img/front.png");
   loadSprite (&tableSurface[PLAYER_BACK], "img/back.png");
   loadSprite (&tableSurface[PLAYER_LEFT], "img/left.png");
   loadSprite (&tableSurface[PLAYER_RIGHT], "img/right.png");
   /* walls */
   loadSprite (&tableSurface[WALL1_IMAGE], "img/wall.png");
   loadSprite (&tableSurface[WALL2_IMAGE], "img/wall2.png");
   loadSprite (&tableSurface[WALL3_IMAGE], "img/wall3.png");
   loadSprite (&tableSurface[WALL4_IMAGE], "img/wall4.png");
   loadSprite (&tableSurface[WALL_LEFT], "img/wallBorderLeft.png");
   loadSprite (&tableSurface[WALL_RIGHT], "img/wallBorderRight.png");
   loadSprite (&tableSurface[WALL_TOP], "img/wallBorderTop.png");
   loadSprite (&tableSurface[WALL_BOTTOM], "img/wallBorderBottom.png");
   /* grounds */
   loadSprite (&tableSurface[GROUND1_IMAGE], "img/background.bmp");
   loadSprite (&tableSurface[GROUND2_IMAGE], "img/background2.bmp");
   loadSprite (&tableSurface[GROUND3_IMAGE], "img/background3.bmp");
   /* boxes */
   loadSprite (&tableSurface[BOX_IMAGE], "img/box.png");
   loadSprite (&tableSurface[BOX_IMAGE_OK], "img/box_ok.png");
   /* goal */
   loadSprite (&tableSurface[GOAL_IMAGE], "img/goal.png");
   /* menu */
   loadSprite (&tableSurface[MENU_BACK], "img/menuBlock.png");
   /* outside the wall */
   loadSprite (&tableSurface[OUTSIDE], "img/outside.png");

   /* create a grid with coordinates x,y to locate things */
   Square grid[MAX_BLOCKS][MAX_BLOCKS];

   int levelChoice = 0;

   /*List slc files from the levels/ folder*/
   perror("Searching files in the levels folder. Perror");
   S_FilesList *filesList = initFilesList();
   listSlcLevelFiles(filesList);
   readFilesList (filesList);
   perror("Level folder explored. Perror");

   /*Read level from slc file in progress. */
   fprintf(stderr,"Get info from each files %s\n", SDL_GetError ());
   S_LevelList *levelList = initLevelList();
   readLevelList(levelList);
   perror("Read the level list. Perror");

   readLevelsAttributs(filesList ,levelList);
   perror("Get attributs from files. Perror");


    /* count all levels from all files */
    int max_Levels =  getNbrOfLevels(levelList);

     /*Load first game*/
    perror("Loading first level. Perror");
    loadSlcLevel (levelChoice,levelList, grid);
    perror("First level loaded. Perror");


   /* Set player position */
   SDL_Rect playerPos;
   int xPlayer = 0;
   int yPlayer = 0;

   /* display the level using the grid */
   displayLevel (grid, screen, tableSurface);

   /* diplay menu on top of the screen */
   displayMenu (levelChoice, menu, tableSurface,levelList);

   /* display Progress in the menu */
   displayProgress (grid, menu, tableSurface);

   /* refresh the window */
   SDL_UpdateWindowSurface (window);

/* wait for quit event */
   int carryOn = 1, x = 0, y = 0;
   SDL_Event event;
   while (carryOn)
   {
      SDL_WaitEvent (&event);
      switch (event.type)
      {
      case SDL_QUIT:
         carryOn = 0;
         break;
      case SDL_KEYDOWN:
         /* Get the player position */
         for (x = 0; x < X_BLOCKS; x++)
         {
            for (y = 0; y < Y_BLOCKS; y++)
            {
               if (grid[x][y].roleType == PLAYER)
               {
                  xPlayer = x;
                  yPlayer = y;
                  playerPos.x = x * BOX_SIZE;
                  playerPos.y = y * BOX_SIZE;
               }
            }
         }
         /* listen keyboard */
         switch (event.key.keysym.sym)
         {
         case SDLK_RIGHT:
            /* Don't go outside */
            if (xPlayer + 1 >= X_BLOCKS)
               break;
            /* Test if wall */
            if (grid[xPlayer + 1][yPlayer].roleType == WALL)
               break;
            /* Don't go outside with a box */
            if (grid[xPlayer + 1][yPlayer].roleType == BOX && xPlayer + 2 >= X_BLOCKS)
               break;
            /* Do not move a box if it is close to a wall or an other box */
            if (grid[xPlayer + 1][yPlayer].roleType == BOX
                && grid[xPlayer + 2][yPlayer].roleType == BOX
                && grid[xPlayer + 2][yPlayer].roleType == WALL)
               break;
            /* Move a box only if there is space to do it */
            if (grid[xPlayer + 1][yPlayer].roleType == BOX
                && grid[xPlayer + 2][yPlayer].roleType == GROUND
                || grid[xPlayer + 1][yPlayer].roleType == BOX
                && grid[xPlayer + 2][yPlayer].roleType == GOAL)
            {
               /* move the box */
               moveBox (xPlayer, yPlayer, grid, RIGHT, screen, tableSurface);
               /* move the player */
               blitPlayer (xPlayer, yPlayer, RIGHT,
                           grid, screen, tableSurface);
               /* update new player position */
               playerPos.x += BOX_SIZE;
               /* update status */
               grid[xPlayer + 2][yPlayer].roleType = BOX;
               grid[xPlayer][yPlayer].roleType = GROUND;
               grid[xPlayer + 1][yPlayer].roleType = PLAYER;
               break;
            }
            /* move only on grounds and Goals */
            if (grid[xPlayer + 1][yPlayer].roleType == GROUND || grid[xPlayer + 1][yPlayer].objectType == GOAL)
            {
               /* move the player */
               blitPlayer (xPlayer, yPlayer, RIGHT,
                           grid, screen, tableSurface);
               /* update new player position */
               playerPos.x += BOX_SIZE;
               /* update status */
               grid[xPlayer][yPlayer].roleType = GROUND;
               grid[xPlayer + 1][yPlayer].roleType = PLAYER;
               break;
            }
            break;

         case SDLK_LEFT:
            /* Don't go outside */
            if (xPlayer - 1 < 0)
               break;
            /* test if wall */
            if (grid[xPlayer - 1][yPlayer].roleType == WALL
                || grid[xPlayer - 1][yPlayer].roleType == BOX_OK)
               break;
            /* Don't go outside with a box */
            if (grid[xPlayer - 1][yPlayer].roleType == BOX && xPlayer - 2 < 0)
               break;
            /* Do not move a box if it is close to a wall or an other box */
            if (grid[xPlayer - 1][yPlayer].roleType == BOX
                && grid[xPlayer - 2][yPlayer].roleType == BOX
                && grid[xPlayer - 2][yPlayer].roleType == WALL)
               break;
            /* Move a box only if there is space to do it */
            if (grid[xPlayer - 1][yPlayer].roleType == BOX
                && grid[xPlayer - 2][yPlayer].roleType == GROUND
                || grid[xPlayer - 1][yPlayer].roleType == BOX
                && grid[xPlayer - 2][yPlayer].roleType == GOAL)
            {
               /* move the box */
               moveBox (xPlayer, yPlayer, grid, LEFT, screen, tableSurface);
               /* move the player */
               blitPlayer (xPlayer, yPlayer, LEFT,
                           grid, screen, tableSurface);
               /* update new player position */
               playerPos.x -= BOX_SIZE;
               /* update status */
               grid[xPlayer - 2][yPlayer].roleType = BOX;
               grid[xPlayer][yPlayer].roleType = GROUND;
               grid[xPlayer - 1][yPlayer].roleType = PLAYER;
               break;
            }
            /* move only on grounds and Goals */
            if (grid[xPlayer - 1][yPlayer].roleType == GROUND || grid[xPlayer - 1][yPlayer].roleType == GOAL)
            {
               /* move the player */
               blitPlayer (xPlayer, yPlayer, LEFT,
                           grid, screen, tableSurface);
               /* update new player position */
               playerPos.x -= BOX_SIZE;
               /* update status */
               grid[xPlayer][yPlayer].roleType = GROUND;
               grid[xPlayer - 1][yPlayer].roleType = PLAYER;
               break;
            }
            break;

         case SDLK_UP:
            /* Don't go outside */
            if (yPlayer - 1 < 0)
               break;
            /* test if wall */
            if (grid[xPlayer][yPlayer - 1].roleType == WALL)
               break;
            /* Don't go outside with a box */
            if (grid[xPlayer][yPlayer - 1].roleType == BOX && yPlayer - 2 < 0)
               break;
            /* Do not move a box if it is close to a wall or an other box */
            if (grid[xPlayer][yPlayer - 1].roleType == BOX
                && grid[xPlayer][yPlayer - 2].roleType == BOX
                && grid[xPlayer][yPlayer - 2].roleType == WALL)
               break;
            /* Move a box only if there is space to do it */
            if (grid[xPlayer][yPlayer - 1].roleType == BOX
                && grid[xPlayer][yPlayer - 2].roleType == GROUND
                || grid[xPlayer][yPlayer - 1].roleType == BOX
                && grid[xPlayer][yPlayer - 2].roleType == GOAL)
            {
               /* move the box */
               moveBox (xPlayer, yPlayer, grid, UP, screen, tableSurface);
               /* move the player */
               blitPlayer (xPlayer, yPlayer, UP, grid,
                           screen, tableSurface);
               /* update new player position */
               playerPos.y -= BOX_SIZE;
               /* update status */
               grid[xPlayer][yPlayer - 2].roleType = BOX;
               grid[xPlayer][yPlayer].roleType = GROUND;
               grid[xPlayer][yPlayer - 1].roleType = PLAYER;
               break;
            }
            /* move only on grounds and Goals */
            if (grid[xPlayer][yPlayer - 1].roleType == GROUND || grid[xPlayer][yPlayer - 1].roleType == GOAL)
            {
               /* move the player */
               blitPlayer (xPlayer, yPlayer, UP, grid,
                           screen, tableSurface);
               /* update new player position */
               playerPos.y -= BOX_SIZE;
               /* update status */
               grid[xPlayer][yPlayer].roleType = GROUND;
               grid[xPlayer][yPlayer - 1].roleType = PLAYER;
               break;
            }
            break;

         case SDLK_DOWN:
            /* Don't go outside */
            if (yPlayer + 1 >= Y_BLOCKS)
               break;
            /* test if wall */
            if (grid[xPlayer][yPlayer + 1].roleType == WALL)
               break;
            /* Don't go outside with a case */
            if (grid[xPlayer][yPlayer + 1].roleType == BOX && yPlayer + 2 >= Y_BLOCKS)
               break;
            /* Do not move a box if it is close to a wall or an other box */
            if (grid[xPlayer][yPlayer + 1].roleType == BOX  && grid[xPlayer][yPlayer + 2].roleType == BOX
                && grid[xPlayer][yPlayer + 2].roleType == WALL)
               break;
            /* Move a box only if there is space to do it */
            if (grid[xPlayer][yPlayer + 1].roleType == BOX
                && grid[xPlayer][yPlayer + 2].roleType == GROUND
                || grid[xPlayer][yPlayer + 1].roleType == BOX
                && grid[xPlayer][yPlayer + 2].roleType == GOAL)
            {
               /* move the Box */
               moveBox (xPlayer, yPlayer, grid, DOWN, screen, tableSurface);
               /* move the player */
               blitPlayer (xPlayer, yPlayer, DOWN,
                           grid, screen, tableSurface);
               /* update new player position */
               playerPos.y += BOX_SIZE;
               /* update status */
               grid[xPlayer][yPlayer + 2].roleType = BOX;
               grid[xPlayer][yPlayer].roleType = GROUND;
               grid[xPlayer][yPlayer + 1].roleType = PLAYER;
               break;
            }
            /* move only on grounds and Goals */
            if (grid[xPlayer][yPlayer + 1].roleType == GROUND || grid[xPlayer][yPlayer + 1].roleType == GOAL)
            {
               /* move the player */
               blitPlayer (xPlayer, yPlayer, DOWN,
                           grid, screen, tableSurface);
               /* update new player position */
               playerPos.y += BOX_SIZE;
               /* update status */
               grid[xPlayer][yPlayer].roleType = GROUND;
               grid[xPlayer][yPlayer + 1].roleType = PLAYER;
               break;
            }
            break;

            /* hit r to reset the current level */
         case SDLK_r:
            /* load the level */
	    loadSlcLevel (levelChoice,levelList, grid);
            /* display the level using grid */
            displayLevel (grid, screen, tableSurface);
            /* display menu on top of the screen */
            displayMenu ((levelChoice + 1), menu, tableSurface, levelList);
            fprintf (stderr, "Level %d\n loaded", (levelChoice + 1));
            break;

            /* hit n to load the next level */
         case SDLK_n:
            /* load next the level */
            if (levelChoice > (max_Levels - 1))
               levelChoice = (max_Levels - 1);
            if (levelChoice < (max_Levels - 1))
            {
               levelChoice += 1;

	      	        loadSlcLevel (levelChoice,levelList, grid);
               /* display the level using grid */
               displayLevel(grid, screen, tableSurface);
               /* display menu on top of the screen */
               displayMenu ((levelChoice + 1), menu, tableSurface, levelList);
               fprintf (stderr, "Level %d\n loaded", (levelChoice + 1));
            }
            break;
            /* hit p to load the previous level */
         case SDLK_p:
            /* load previous level*/
            if (levelChoice < 0)
               levelChoice = 0;
            if (levelChoice > 0)
            {
               levelChoice -= 1;
	      	loadSlcLevel (levelChoice,levelList, grid);
               /* display the level using grid*/
               displayLevel (grid, screen, tableSurface);
               /* display menu on top of the screen */
               displayMenu ((levelChoice + 1), menu, tableSurface, levelList);
               fprintf (stderr, "Level %d\n loaded", (levelChoice + 1));
            }
            break;
            /* hit q to quit */
         case SDLK_q:
            carryOn = 0;
            break;
         }

         /* display Progress in the menu */
         displayProgress (grid, menu, tableSurface);
         SDL_UpdateWindowSurface (window);
      }
   }

   /* clean */
   freeSprites (tableSurface);
   SDL_FreeSurface (screen);
   SDL_DestroyWindow (window);
   TTF_Quit ();
   SDL_Quit ();
   return EXIT_SUCCESS;
}
