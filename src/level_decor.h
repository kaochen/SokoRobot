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

#ifndef GAME_H
#define GAME_H

#include <stdlib.h>
#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <time.h>

#include "const.h"
#include "sprites.h"
#include "settings.h"


/* blit borders on walls */
int
blitBorders (Square grid[pref.max_X_Blocks][pref.max_Y_Blocks],
             SDL_Surface * screen,
             Sprites tableSurface[NBR_OF_IMAGES]);

/* add a more ground choice */
int
randomGround (Square grid[pref.max_X_Blocks][pref.max_Y_Blocks]);

/* add a more wall choice */
int
randomWall (Square grid[pref.max_X_Blocks][pref.max_Y_Blocks]);

/*change OUTSIDE subRole to get more choice between OUTSIDE, OUTSIDE2...*/
int
randomOutside (Square grid[pref.max_X_Blocks][pref.max_Y_Blocks]);

/* random number between two numbers */
int random_number (int min, int max);

/* blit corners */
int
blitCorners (Square grid[pref.max_X_Blocks][pref.max_Y_Blocks],
            SDL_Surface * screen,
            Sprites tableSurface[NBR_OF_IMAGES]);

/* Change GROUND that are outside the walls to OUTSIDE */
void
detectOutside (Square grid[pref.max_X_Blocks][pref.max_Y_Blocks]);
#endif
