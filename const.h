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

#ifndef CONST_H
#define CONST_H

#define GAME_NAME "My Game"

#define W_WIDTH  1024
#define W_HEIGHT 720
#define BACKGROUND_SIZE 40
#define BOX_SIZE 40
#define NBR_OF_BLOCKS 14

enum {GROUND , WALL , WOODEN_CASE , BALL, PLAYER  };
enum {UP , DOWN, RIGHT, LEFT, STILL };
enum {RANDOM, FIXED};
#endif
