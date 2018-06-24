#include "./wrappers.hpp"

namespace sdl2
{

// Log error and exit with failure
auto
Error::error(const char *msg) -> void
{
	SDL_Log("%s"
	        "%s",
	        msg,
	        SDL_GetError());

	exit(EXIT_FAILURE);
}

/*
 * Subsystem
 */

SubSystem::SubSystem(Uint32 flags)
{
	if (SDL_Init(flags) < 0)
		error("Unable to initialize SDL");
}

SubSystem::~SubSystem() { SDL_Quit(); }

/*
 * Window
 */

Window::Window(const char *title,
               int         x,
               int         y,
               int         width,
               int         height,
               Uint32      flag)
    : win{SDL_CreateWindow(title, x, y, width, height, flag)}
{
	if (!win)
		error("Failed to created window");
}

Window::~Window() { SDL_DestroyWindow(win); }

/*
 * Renderer
 */

Renderer::Renderer(const Window &win, int index, Uint32 flags)
    : ren{SDL_CreateRenderer(win.win, index, flags)}
{
	if (!ren)
		error("Failed to create renderer");
}

Renderer::~Renderer() { SDL_DestroyRenderer(ren); }

// Set renderer draw color
auto
Renderer::setDrawColor(Color c, Uint8 alpha) -> void
{
	auto [red, green, blue] = c;
	SDL_SetRenderDrawColor(ren, red, green, blue, alpha);
}

// Fill renderer will current color
auto
Renderer::clear() -> void
{
	SDL_RenderClear(ren);
}

// Present renderer
auto
Renderer::present() -> void
{
	SDL_RenderPresent(ren);
}

/*
 * drawGrid
 * Draw a square grid using Lines
 * --------------------------------------------------
 *  corner : top left {x, y} of grid
 *  len    : length of each side of grid
 *  gap    : size of spaces inside grid
 */

auto
Renderer::drawGrid(std::tuple<int, int> corner, int len, int gap) -> void
{
	auto [x, y]{corner};

	for (int dis{gap}; dis <= len - gap; dis += gap) {
		SDL_RenderDrawLine(ren, x + dis, y, x + dis, y + len);
		SDL_RenderDrawLine(ren, x, y + dis, x + len, y + dis);
	}
}

/*
 * drawCircle
 * draw a circle onto the renderer
 * --------------------------------------------------
 *  origin : coordinate {x, y} of circle's origin
 *  radius : length of radius
 */

auto
Renderer::drawCircle(std::tuple<int, int> origin, int radius) -> void
{
	const double PI{atan(1) * 4};

	auto [oX, oY] = origin;

	for (double angle = 0; angle <= PI / 2; angle += (PI / 180)) {
		int x = cos(angle) * radius;
		int y = sin(angle) * radius;

		SDL_Rect tmp{oX - x, oY - y, x * 2, y * 2};

		SDL_RenderFillRect(ren, &tmp);
	}
}

/*
 * fillGrid
 * draw circles inside grid if cell is alive
 * --------------------------------------------------
 *  corner : top left corner {x, y} of the grid
 *  len    : length of the grids sides
 *  gap    : size of gaps in grid
 *  map    : bool map representing each cells state
 */

auto
Renderer::fillGrid(std::tuple<int, int>           corner,
                   int                            len,
                   int                            gap,
                   std::vector<std::vector<bool>> map) -> void
{
	const int radius{static_cast<int>(gap * 0.30)};

	// center of first circle
	auto [x, y]{corner};
	x += gap / 2;
	y += gap / 2;

	for (int i = 0; i < map.size(); i++) {
		for (int j = 0; j < map[0].size(); j++) {
			if (!map[i][j]) {
				continue;
			}

			std::tuple<int, int> circle_origin{x + i * gap,
			                                   y + j * gap};
			drawCircle(circle_origin, radius);
		}
	}
}

/*
 * Event
 */

auto
Event::poll() -> int
{
	return SDL_PollEvent(&event);
}

auto
Event::type() -> Uint32
{
	return event.type;
}

} // namespace sdl2
