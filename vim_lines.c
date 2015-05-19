#include "vim_lines.h"
#include <nspireio2.h>

void vim_InitLines(Lines* lines, nio_console* left_panel) {
	int i;
	for (i = 0; i < LINE_BUFFER_SIZE; i++) {
		(*lines).buffer[i] = i+1;
		char* space = "";
		if (i < 9) {
			space = " ";
		}
		nio_fprintf(left_panel, "%s%d\n", space, (*lines).buffer[i]);
	}
}