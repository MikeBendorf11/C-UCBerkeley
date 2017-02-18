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
	char line[MAXLINE], lineCopy[MAXLINE]; //+
int ac;
char *av[MAXARGS];
struct room *currentroom = NULL;
struct object *currentobject = NULL;

while(fgetline(fp, line, MAXLINE) != EOF)
	{
	strcpy(lineCopy, line); //+
	if(*line == '#')
		continue;
	ac = getwords(line, av, MAXARGS);
	if(ac == 0)
		continue;
	if(strcmp(av[0], "room") == 0)//////////////////////////// 
		{
		/*changed from room to object*/
		currentobject = NULL;	//+
		if(ac < 2)
			fprintf(stderr, "missing room name\n");
		else if(strcmp(av[1], "end") != 0)
			{
			currentroom = newroom(av[1]);
		/*	if(strcmp(av[2], "description") == 0 )//+
				{
				int i, position, limit;
				position = strlen(av[0]) + strlen(av[1]) 
					+ strlen(av[2]) + 3;
				limit = strlen(lineCopy)-position;
				for(i=0; i<limit; i++, position++)
					currentroom->description[i]=lineCopy[position];
				}*/
			}
		}
	
	else if(strcmp(av[0], "object") == 0)///////////////////////
		{
			/*this shit does nothing //+
		/*currentobject = NULL;	/* finish previous object */
		if(ac < 2)
			fprintf(stderr, "missing object name\n");
		else if(strcmp(av[1], "end") != 0)
			{
			currentobject = newobject(av[1]);
			/*if(strcmp(av[2], "description") == 0 )//+
				{
				int i, position, limit;
				position = strlen(av[0]) + strlen(av[1]) 
					+ strlen(av[2]) + 3;
				limit = strlen(lineCopy)-position;
				for(i=0; i<limit; i++, position++)
					currentobject->description[i]=lineCopy[position];
				}*/
			/* temporary hardwired put in room: */
			currentobject->lnext = currentroom->contents;
			currentroom->contents = currentobject;
			}
		}

	else if(strcmp(av[0], "desc") == 0)//+
	{
		char *p;
		for(p = lineCopy; !isspace(*p); p++);	/* skip "desc" */
		for(; isspace(*p); p++);				/* skip whitespace */
		if(currentobject != NULL)
			currentobject->description = chkstrdup(p);
		else 
			currentroom->description = chkstrdup(p);
		
		/* 1. 
		 * 2. while av[0] != room, object
		 * 3. get another line
		 * 4. check current allocation to desc string
		 * 5. if to little reallocate
		 * 6. otherwise copy the current line*/
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

