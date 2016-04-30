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

#ifndef SLC_C
#define SLC_C

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "../inc/slc.h"
#include "../inc/const.h"

//Read using libxml
#include <libxml2/libxml/tree.h>
#include <libxml2/libxml/parser.h>
#include <libxml2/libxml/xpath.h>
#include <libxml2/libxml/xpathInternals.h>

/* Initiatlize the list of levels */
S_LevelList *initLevelList ()
{
   S_LevelList *levelList = malloc (sizeof (*levelList));
   S_Level *level = malloc (sizeof (*level));
   if (levelList == NULL || level == NULL)
   {
      exit (EXIT_FAILURE);
   }
   /*load first level */
   strcpy (level->name, "");
   strcpy (level->file, "");
   level->height = 0;
   level->width = 0;
   level->number = 0;
   level->next = NULL;
   /* store adress of the first level */
   levelList->first = level;

   return levelList;
}

/*Add a level in the list*/
void addNewLevel (S_LevelList * levelList, char *name, int height, int width)
{
   S_Level *new = malloc (sizeof (*new));
   if (levelList == NULL || new == NULL)
   {
      exit (EXIT_FAILURE);
   }
   strcpy (new->name, name);
   new->height = height;
   new->width = width;

  /* insert new level the control and the last one of the list*/
   new->next = levelList->first;
   levelList->first = new;
}

/* read level list one by one */
void readLevelList (S_LevelList * levelList)
{
   if (levelList == NULL)
   {
      exit (EXIT_FAILURE);
   }
   S_Level *actual = levelList->first;
   while (actual != NULL)
   {
      fprintf (stderr, "%s, %d:%d\n", actual->name, actual->width,
               actual->height);
      actual = actual->next;
   }
}

/*Read a level */
int readXML (char *nameLevel)
{
   xmlDocPtr doc;

   /* Open SLC/XML file */
   doc = xmlParseFile ("levels/12_Blocks.slc");
   if (doc == NULL)
   {
      fprintf (stderr, "XML Document not valid\n");
      return 0;
   }

   // Start XPath
   xmlXPathInit ();
   // Create a context
   xmlXPathContextPtr ctxt = xmlXPathNewContext (doc);
   if (ctxt == NULL)
   {
      fprintf (stderr, "Error creating the context XPath\n");
      exit (-1);
   }

   /* Read Level */
   char path[MAX_CARACT] = "";
   sprintf (path, "/SokobanLevels/LevelCollection/Level[@Id=\"%s\"]/L/text()",
            nameLevel);
   xmlXPathObjectPtr xpathLevel =
      xmlXPathEvalExpression (BAD_CAST path, ctxt);
   if (xpathLevel == NULL)
   {
      fprintf (stderr, "Error on the xPathLevel expression\n");
      exit (-1);
   }
   /* Show the result */
   if (xpathLevel->type == XPATH_NODESET)
   {
      int i;
      xmlNodePtr n;
      printf ("Level: ");
      for (i = 0; i < 18; i++)
      {
         n = xpathLevel->nodesetval->nodeTab[i];
         if (n->type == XML_TEXT_NODE || n->type == XML_CDATA_SECTION_NODE)
         {
            fprintf (stderr, "%s\n", n->content);
         }
      }
   }

   /* free memory */
   xmlFreeDoc (doc);

   xmlXPathFreeObject (xpathLevel);
   xmlXPathFreeContext (ctxt);

   return 1;
}
#endif
