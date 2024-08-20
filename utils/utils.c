#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>

void die_with_error(int count, ...){
	va_list args;
	va_start(args, count);
	
	for(int i = 0; i < count; i++)
		printf("%s", va_arg(args, char *));	
	exit(EXIT_FAILURE);
};