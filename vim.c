#include <os.h>
#include <SDL/SDL.h>

#include "vim_panels.h"
#include "vim_lines.h"
#include "vim_keys.h"

int main(void) {
	Lines lines;
	Panels panels;
	vim_Init(&panels, &lines);
	SDL_Init(SDL_INIT_VIDEO);
	SDL_EnableUNICODE(1);
	SDL_Event e;
	while(1) {
		SDL_WaitEvent(&e);
		if (e.type == SDL_KEYDOWN) {
			if (!vim_HandleKeys(&e.key.keysym, &panels, &lines)) {
				break;
			}
		}
	}
	show_msgbox("warning", "exiting");
	SDL_Quit();
	vim_CleanUpPanels(&panels);
	return 0;
}

