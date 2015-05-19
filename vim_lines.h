#ifndef VIM_LINES_H
#define VIM_LINES_H
#define LINE_BUFFER_SIZE 29

#include <nspireio2.h>

typedef struct Lines {
	int buffer[LINE_BUFFER_SIZE];
} Lines;

void vim_InitLines(Lines*, nio_console*);

#endif