/*
 *  Text-based dungeon/adventure game, for the
 *  UW Experimental College course in Intermediate C Programming
 *
 *  Copyright 1996-1999 Steve Summit
 *  scs@eskimo.com
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "game.h"
#include "defs.h" 
#include "utils.h"

static parsedatafile(FILE *);

readdatafile()
{
char *datfile = "dungeon.dat";
FILE *fp = fopen(datfile, "r");
if(fp == NULL)
	{
	fprintf(stderr, "can't open %s\n", datfile);
	return FALSE;
	}

parsedatafile(fp);
fclose(fp);
return TRUE;
}

#define MAXLINE 200
#define MAXARGS 30

static parsedatafile(FILE *fp)
{
	char line[MAXLINE], lineCopy[MAXLINE]; 
int ac;
char *av[MAXARGS];
struct room *currentroom = NULL;
struct object *currentobject = NULL;

while(fgetline(fp, line, MAXLINE) != EOF)
	{
	strcpy(lineCopy, line); 
	if(*line == '#')
		continue;
	ac = getwords(line, av, MAXARGS);
	if(ac == 0)
		continue;
	if(strcmp(av[0], "room") == 0)
		{
		/*changed from room to object, the word room is
		* the only that clears the current object*/
		currentobject = NULL;	
		if(ac < 2)
			fprintf(stderr, "missing room name\n");
		else if(strcmp(av[1], "end") != 0)
			{
			currentroom = newroom(av[1]);
			}
		}
	
	else if(strcmp(av[0], "object") == 0)
		{
	
		if(ac < 2)
			fprintf(stderr, "missing object name\n");
		else if(strcmp(av[1], "end") != 0)
			{
			currentobject = newobject(av[1]);
		
			/* temporary hardwired put in room: */
			currentobject->lnext = currentroom->contents;
			currentroom->contents = currentobject;
			}
		}

	else if(strcmp(av[0], "description") == 0)
	{
		char *p;
		for(p = lineCopy; !isspace(*p); p++);	/* skip "desc" */
		for(; isspace(*p); p++);				/* skip whitespace */
		if(currentobject != NULL)
			currentobject->desc = chkstrdup(p);
		else 
			currentroom->desc = chkstrdup(p);
	}

	/*if attribute after object declaration
	* test following argument after attribute
	* do a conditional switch that matches every possible state
	* NOT PICKING ATTRIBUTE:
	* 1st - desing a method to print the attributes of the object
	* in the description to see what happens between dungeon DAT and the
	* attribute property*/
	else if(strcmp(av[0], "attribute") == 0)////////////////////////////////////
		{
	
		if(ac < 2)
			fprintf(stderr, "missing attribute type\n");
		else if(strcmp(av[1], "container") != 0)
			currentobject->attrs |= CONTAINER;
		else if(strcmp(av[1], "closable") != 0)
			currentobject->attrs |= CLOSABLE;
		else if(strcmp(av[1], "open") != 0)
			currentobject->attrs |= OPEN;
		else if(strcmp(av[1], "heavy") != 0)
			currentobject->attrs |= HEAVY;
		else if(strcmp(av[1], "broken") != 0)
			currentobject->attrs |= BROKEN;
		else if(strcmp(av[1], "tool") != 0)
			currentobject->attrs |= TOOL;
		else if(strcmp(av[1], "soft") != 0)
			currentobject->attrs |= SOFT;
		else if(strcmp(av[1], "sharp") != 0)
			currentobject->attrs |= SHARP;
		else if(strcmp(av[1], "lock") != 0)
			currentobject->attrs |= LOCK;
		else if(strcmp(av[1], "key") != 0)
			currentobject->attrs |= KEY;
		else if(strcmp(av[1], "locked") != 0)
			currentobject->attrs |= LOCKED;
		else if(strcmp(av[1], "transparent") != 0)
			currentobject->attrs |= TRANSPARENT;
		else if(strcmp(av[1], "immobile") != 0)
			currentobject->attrs |= IMMOBILE;									
		}

	else if(strcmp(av[0], "roomexits") == 0)	/* temporary */
		{
		struct room *roomp;
		int i;
		if(ac < 2)
			{
			fprintf(stderr, "missing room name\n");
			continue;
			}
		roomp = findroom(av[1]);
		if(roomp == NULL)
			{
			fprintf(stderr, "no such room \"%s\"\n", av[1]);
			continue;
			}
		for(i = 2; i < ac; i++) // roomexits left over arguments
			{
			struct room *roomp2;
			int dir;
			char *p = strchr(av[i], ':');
			if(p == NULL)
				{
				fprintf(stderr, "bad exit syntax \"%s\"\n", av[i]);
				continue;
				}
			*p++ = '\0';	/* p now points at destination */
			roomp2 = findroom(p);
			if(roomp2 == NULL)
				{
				fprintf(stderr, "no such room \"%s\"\n", p);
				continue;
				}
			if(strcmp(av[i], "n") == 0)
				dir = NORTH;
			else if(strcmp(av[i], "e") == 0)
				dir = EAST;
			else if(strcmp(av[i], "w") == 0)
				dir = WEST;
			else if(strcmp(av[i], "s") == 0)
				dir = SOUTH;
			else if(strcmp(av[i], "ne") == 0)
				dir = NORTHEAST;
			else if(strcmp(av[i], "nw") == 0)
				dir = NORTHWEST;
			else if(strcmp(av[i], "se") == 0)
				dir = SOUTHEAST;
			else if(strcmp(av[i], "sw") == 0)
				dir = SOUTHWEST;
			else if(strcmp(av[i], "u") == 0)
				dir = UP;
			else if(strcmp(av[i], "d") == 0)
				dir = DOWN;
			else	{
				fprintf(stderr, "no such direction \"%s\"\n", av[i]);
				continue;
				}
			roomp->exits[dir] = roomp2;
			}
		}
	else	{
		fprintf(stderr, "bad keyword %s\n", av[0]);
		continue;
		}
	}
}

