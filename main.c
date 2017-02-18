/*
 *  Text-based dungeon/adventure game, for the
 *  UW Experimental College course in Intermediate C Programming
 *
 *  Copyright 1996-1999 Steve Summit
 *  scs@eskimo.com
 */

#include <stdio.h>
#include <stdlib.h>
#include "game.h"
#include "utils.h"
#include "defs.h"

#define MAXLINE 100

static struct actor player;

/* The main loop of the game.  At the top level, the action is	*/
/* simple: print a prompt, read a command string, parse the	*/
/* string, and try to execute it.  The parseline() and		*/
/* docommand() functions do most of the work; main() is just	*/
/* the conductor, directing the top-level flow.			*/

main()
{
char line[MAXLINE];
char *verb, *object;

	if(!readdatafile())
		exit(1);

	gotoroom(&player, getentryroom());	/* put actor in initial room */


listroom(&player);

while(TRUE)
	{
	printf("? ");
	fflush(stdout);
	
	if(getline(line, MAXLINE) == EOF)
		break;

	if(!parseline(line, &verb, &object))
		continue;

	docommand(&player, verb, object);
	}

return 0;
}
