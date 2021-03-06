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

#ifndef SLC_H
#define SLC_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <dirent.h>

#include "const.h"
#include "level_decor.h"
#include "settings.h"
#include "menu.h"
#include "files.h"


//Read using libxml
#include <libxml2/libxml/tree.h>
#include <libxml2/libxml/parser.h>
#include <libxml2/libxml/xpath.h>
#include <libxml2/libxml/xpathInternals.h>



/* Functions ============================================ */

/* Levels ========================================= */
/* Initiatlize the list of levels */
S_LevelList *initLevelList ();

/*get levels infos from files */
int
readLevelsAttributs (S_FilesList * filesList,
                     S_LevelList * levelList);

/*Add first level into an empty list */
int
addFirstLevel (S_LevelList * levelList, char *fileName, char *name, char *author,
	       int height, int width);

/*Add a level in the list*/
void
addNewLevel (S_LevelList * levelList,
             char *fileName,
             char *name,
	     char *author,
             int height,
             int width);

/*Erase a level in the list from start*/
int delLevel (S_LevelList * levelList);

/* destroy level list */
void destroy (S_LevelList * levelList);

/* read level list one by one */
void readLevelList (S_LevelList * levelList);

/*Load slc level into the grid */
int
loadSlcLevel (S_LevelList * levelList,
              Square grid[pref.max_X_Blocks][pref.max_Y_Blocks],
              S_Menu gridMenu[pref.max_X_Blocks][pref.max_Y_Blocks]);

/*get levels infos from files */
int getNbrOfLevels (S_LevelList * levelList);

/*get a specific attribut from slc file*/
int
getAttributFromXML(const xmlNode *cur,
		   char *value,
		   const char *nodeName,
		   const char *attributName);
#endif
