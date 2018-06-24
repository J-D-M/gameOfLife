#include <fstream>
#include <iostream>
#include <vector>

#include "./world.hpp"
#include "./wrappers.hpp"

const int width{720};
const int height{720};

auto
main(int argc, char **argv) -> int
{
	using namespace std;
	using namespace sdl2;

	Window mainWin("Conway's Game of Life",
	               Window::npos,
	               Window::npos,
	               width,
	               height,
	               Window::shown);

	Renderer mainRen(mainWin, -1, Renderer::accelerated);
	Event    event;

	int len{static_cast<int>(height * 0.9)};

	const int map_size{15};
	const int gap{len / map_size};

	len -= len % gap; // clean up rounding errors

	const tuple<int, int> corner{(width - len) / 2, (height - len) / 2};

	World world(map_size);

	for (bool quit{false}; !quit;) {
		while (event.poll())
			if (event.type() == SDL_QUIT)
				quit = true;

		mainRen.setDrawColor(color::black, 0xff);
		mainRen.clear();

		mainRen.setDrawColor(color::white, 0xff);
		mainRen.drawGrid(corner, len, gap);
		mainRen.fillGrid(corner, len, gap, world.getMap());
		mainRen.present();

		world.update();

		SDL_Delay(750);
	}
}
