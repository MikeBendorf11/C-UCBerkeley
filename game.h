/*
 *  Text-based dungeon/adventure game, for the
 *  UW Experimental College course in Intermediate C Programming
 *
 *  Copyright 1996-1999 Steve Summit
 *  scs@eskimo.com
 */

#include <stdio.h>

#define MAXNAME 20	/* maximum length of object or room name */
#define MAXDESCS 100 /* maximum lenght of room and object descriptions+*/

struct object
	{
	char name[MAXNAME];
	unsigned int attrs;
	struct object *contents;	/* contents (if container) */
	struct object *lnext;		/* next in list of contained objects */
					/* (i.e. in this object's container) */
	char *desc;			/* long description */
	};


struct actor
	{
	struct room *location;
	struct object *contents;	/* possessions */
	};

#define NEXITS 10

struct room
	{
	char name[MAXNAME];
	char * desc;
	struct object *contents;
	struct room *exits[NEXITS];
	};//+

struct sentence
	{
	char *verb;
	struct object *object;
	char *preposition;
	struct object *xobject;	/* object of preposition */
	};

/* object bitwise operators */

#define CONTAINER	0x0001//+
#define CLOSABLE	0x0002
#define OPEN		0x0004
#define HEAVY		0x0008
#define BROKEN		0x0010
#define TOOL		0x0020
#define SOFT		0x0040
#define SHARP		0x0080
#define LOCK		0x0100
#define KEY			0x0200
#define LOCKED		0x0400
#define TRANSPARENT	0x0800
#define IMMOBILE	0x1000

#define Iscontainer(o) ((o)->attrs & CONTAINER)
#define Isopen(o) ((o)->attrs & OPEN)


/* direction indices in exits array: */

#define NORTH		0
#define SOUTH		1
#define EAST		2
#define WEST		3
#define NORTHEAST	4
#define NORTHWEST	5
#define SOUTHEAST	6
#define SOUTHWEST	7
#define UP			8
#define DOWN		9



/* status return value for commands: */

#define FAILURE		0	/* command completed unsuccessfully */
#define SUCCESS		1	/* command completed successfully */
#define CONTINUE	2	/* command not completed */
#define ERROR		3	/* internal error */

extern int parseline(struct actor *, char *, struct sentence *);
extern docommand(struct actor *, struct sentence *);

extern int readdatafile(void);
extern int dumpdata(char *);

char *plural(char *);
char * getLast(char * );
extern struct object *newobject(char *);
extern int putobject(struct actor *, struct object *, struct object *);//+
extern struct object *findobject(struct actor *, char *);
extern int contains(struct object *, struct object *);
extern int takeobject(struct actor *, struct object *);
extern int dropobject(struct actor *, struct object *);
extern int putobject(struct actor*, struct object*, struct object*); //+
extern void listobjects(struct object *);
extern void dumpobjects(FILE *);
extern int obj_indexof(struct object *);
extern int hasattr(struct object *, char *);
extern void setattr(struct object *, char *);
extern void unsetattr(struct object *, char *);

extern struct room *newroom(char *);
extern struct room *findroom(char *);
extern struct room *getentryroom(void);
void listroom(struct actor *);
extern int gotoroom(struct actor *, struct room *);
extern void dumprooms(FILE *);

