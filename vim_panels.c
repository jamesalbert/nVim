#include <nspireio2.h>
#include "vim_panels.h"

char* active_mode = "insert";
nio_console* active_panel;

void vim_Init(Panels* panels, Lines* lines) {
	vim_InitPanels(panels);
	vim_DrawPanels(panels);
	vim_InitLines(lines, &panels->left);
	vim_ChangeMode("command", panels);
}

void vim_CleanUpPanels(Panels* panels) {
	nio_CleanUp(&panels->left);
	nio_CleanUp(&panels->bottom);
	nio_CleanUp(&panels->center);
}

void vim_DrawPanels(Panels* panels) {
#define X(type, panel, cols, rows, offx, offy, fg, bg) \
	nio_DrawConsole(&panels->panel);
X_FIELDS
#undef X
}	

void vim_InitPanels(Panels* panels) {
	clrscr();
#define X(type, panel, cols, rows, offx, offy, fg, bg) \
	nio_InitConsole(&panels->panel, cols, rows, offx, offy, fg, bg);
X_FIELDS
#undef X
}

bool vim_ExecCommand(Panels* panels, Lines* lines) {
	char* statement = (&panels->bottom)->data;
	char* cmd = "";
	char* filename = "";
	char *ch;
	bool single = true;
	ch = strtok(statement, " ");
	while (ch != NULL) {
		if (single) {
			cmd = ch;
		}
		else {
			filename = ch;
		}
		ch = strtok(NULL, " ");
		single = false;
	}
	if (strstr(cmd, ":wq")) {
		vim_SaveFile(filename, &panels->center);
		return false;
	}
	else if (strstr(cmd, ":q")) {
		return false;
	}
	else if (strstr(cmd, ":w")) {
		vim_SaveFile(filename, &panels->center);
		return true;
	}
	else if (strstr(cmd, ":edit")) {
		vim_LoadFile(filename, panels, lines);
		return true;
	}
	return true;
}

void vim_ChangeMode(char* mode, Panels* panels) {
	//nio_clear(bottom);
	int i;
	for (i = 0; i < 54; i++) {
		nio_printf(&panels->bottom, "\b \b");
	}
	if (strstr(mode, "insert") != NULL) {
		nio_printf(&panels->bottom, "-- INSERT --\t\t\t1,6\t\tAll");
		active_panel = &panels->center;
	}
	else if (strstr(mode, "command") != NULL) {
		active_panel = &panels->bottom;
	}
	else if (strstr(mode, "newline") != NULL) {
	}
	active_mode = mode;
}

char* vim_BuildPath(char* name) {
	char* full_path = "";
	strcat(full_path, "/Documents/apps/");
	strcat(full_path, name);
	strcat(full_path, ".tns");
	return full_path;
}

void vim_SaveFile(char* name, nio_console* panel) {
	char* path = vim_BuildPath(name);
	nio_save(path, panel);
}

void vim_LoadFile(char* name, Panels* panels, Lines* lines) {
	char* path = vim_BuildPath(name);
	nio_console* center = &panels->center;
	nio_console tmp;
	nio_free(&tmp);
	nio_load(path, &tmp);
	vim_CleanUpPanels(panels);
	Panels new_panels;
	Lines new_lines;
	vim_Init(&new_panels, &new_lines);
	new_panels.center = tmp;
	vim_DrawPanels(&new_panels);
	nio_CleanUp(&tmp);
}

char* vim_GetMode() {
	return active_mode;
}

nio_console* vim_GetActivePanel() {
	return active_panel;
}