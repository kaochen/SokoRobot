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

#ifndef MENU_TEXT_H
#define MENU_TEXT_H

#include <stdlib.h>
#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL2_rotozoom.h>

#include "const.h"
#include "level_decor.h"
#include "menu.h"
#include "settings.h"
#include "slc.h"

enum {INFO,SHORTCUTS,SHORTCUTS1,SHORTCUTS2,SHORTCUTS3,SHORTCUTS4,SHORTCUTS5, ABOUT,ABOUT1,ABOUT2,MENU_SHORTCUT};

/* define images/sprites struct */
typedef struct
{
  SDL_Surface *textSurface;
} S_Text;

/*init the textSurface table */
void
tableTextSurface_init(S_Text tableTextSurface[NBR_OF_TEXT]);

/* free all text surfaces */
void
freeS_Text (S_Text tableTextSurface[NBR_OF_TEXT]);

/*make from a text a table and load it into the tableTextSurface*/
void
loadTextAsSurface(size_t t, S_Text tableTextSurface[NBR_OF_TEXT], char *text, size_t fontSize, size_t R, size_t G, size_t B, size_t A);

/* display shortcut in the menu */
int
displayShortcut (SDL_Surface * screen, S_Text tableTextSurface[NBR_OF_TEXT]);

/* display the level number */
int levelMenu (int levelNumber, SDL_Surface * screen,
		S_LevelList * levelList);

#endif