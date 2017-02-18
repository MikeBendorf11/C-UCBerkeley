#include <ctype.h>
#include <string.h>


char * getLast(char * input)
{
	char * p;
	for(p=input; *p!='\0'; p++);
	p--;
	return p;
}


char *plural(char * input)
{
	char * p;
	char * plural1 = "s";
	char * plural2= "es";
	
	if(strlen(input)<3) 
		return input;

	p = getLast(input);
	
	switch(*p)
	{
		case 'n' : case 'h': 
		case 'x': case 'z': case 'o':
			strcat(input, plural2); 
			break;
		case 's' :
			break;
		default:
			strcat(input, plural1);
	}
	return input;
}



