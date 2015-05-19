#include "vim_keys.h"
#include <nspireio2.h>
#include <SDL/SDL.h>

bool vim_HandleKeys(SDL_keysym* sym, Panels* panels, Lines* lines) {
	char* key = SDL_GetKeyName(sym->sym);
	if (strstr(key, "backspace") != NULL) {
		key = "\b \b";
	}
	else if (strstr(key, "space") != NULL) {
		key = " ";
	}
	else if (strstr(key, "return") != NULL && strstr(vim_GetMode(), "insert") == NULL) {
		return vim_ExecCommand(panels, lines);
	}
	else if (strstr(key, "return") != NULL) {
		key = "\n";
	}
	else if (strstr(key, "tab") != NULL) {
		key = "    ";
	}
	else if (strstr(key, "left ctrl")) {
		key = ":";
		if (strstr(vim_GetMode(), "command") != NULL) {
			vim_ChangeMode("newline", panels);
		}
	}
	else if (strstr(key, "menu") != NULL) {
		return false;
	}
	else if (strstr(key, "i") && strstr(vim_GetMode(), "command") != NULL) {
		vim_ChangeMode("insert", panels);
		return true;
	}
	else if (strstr(key, "escape") != NULL) {
		vim_ChangeMode("command", panels);
		return true;
	}
	nio_PrintStr(vim_GetActivePanel(), key);
	return true;
}