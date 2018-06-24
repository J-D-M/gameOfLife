#include <fstream>
#include <iostream>
#include <vector>

#include "./world.hpp"
#include "./wrappers.hpp"

const int width{720};
const int height{720};
const int cell_count{15}; // world will be cell_count x cell_count

auto
main(int argc, char **argv) -> int
{
	using namespace std;
	using namespace sdl2;

	int grid_len{static_cast<int>(height * 0.9)};
	int gap{grid_len / cell_count}; // size of cell sides
	grid_len -= grid_len % gap;     // clean up rounding errors

	const tuple<int, int> corner{(width - grid_len) / 2,
	                             (height - grid_len) / 2};

	Window mainWin("Conway's Game of Life",
	               Window::npos,
	               Window::npos,
	               width,
	               height,
	               Window::shown);

	Renderer mainRen(mainWin, -1, Renderer::accelerated);
	Event    event;

	World world(cell_count);

	// main loop
	for (bool quit{false}; !quit;) {
		while (event.poll())
			if (event.type() == SDL_QUIT)
				quit = true;

		mainRen.setDrawColor(color::black, 0xff);
		mainRen.clear();

		mainRen.setDrawColor(color::white, 0xff);
		mainRen.drawGrid(corner, grid_len, gap);
		mainRen.fillGrid(corner, grid_len, gap, world.getMap());

		mainRen.present();

		world.update();

		SDL_Delay(750);
	}
}
