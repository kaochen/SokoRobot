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

#ifndef SETTINGS_H
#define SETTINGS_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "const.h"

/* Searching for preferences.ini */
void
searchPrefFile(char * prefFile);

/* load settings from pref file */
S_preferences *
loadPrefStruct(void);

/*read window height and width from the preference file */
int getPrefAsInt (const char *prefName);

/*get char value from the preference file */
void getPrefChar(char * ret, const char *setting);

int getWindow_width ();

int getWindow_height ();




/* write a pref char */
int writePrefChar (const char *prefName, const char *value);
#endif
