#ifndef VIM_PANELS_H
#define VIM_PANELS_H

#include <nspireio2.h>
#include <stdbool.h>

#include "vim_lines.h"

#define X_FIELDS \
	X(nio_console, left, 10, 32, 0, 0, WHITE, BLACK) \
	X(nio_console, center, 54, 32, 12, 0, BLACK, WHITE) \
	X(nio_console, bottom, 54, 2, 0, 231, 7, BLACK)

extern char* active_mode;
extern nio_console* active_panel;

typedef struct {
#define X(type, panel, cols, rows, offx, offy, fg, bg) type panel;
	/*
	There are three separate panels:
		left_panel: line numbers, error markers
		bottom_panel: commands
		center_panel: main text body
	*/
	X_FIELDS
#undef X
} Panels;

void vim_Init(Panels*, Lines*);
void vim_CleanUpPanels(Panels*);
void vim_DrawPanels(Panels*);
void vim_InitPanels(Panels*);
bool vim_ExecCommand(Panels*, Lines*);
void vim_ChangeMode(char*, Panels*);
char* vim_GetMode();
char* vim_BuildPath(char*);
void vim_SaveFile(char*, nio_console*);
void vim_LoadFile(char*, Panels*, Lines*);
nio_console* vim_GetActivePanel();

#endif