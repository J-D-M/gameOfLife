#include "./wrappers.hpp"

namespace sdl2
{

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

auto
Renderer::setDrawColor(Color c, int alpha) -> void
{
	auto [red, green, blue] = c;
	SDL_SetRenderDrawColor(ren, red, green, blue, alpha);
}

auto
Renderer::clear() -> void
{
	SDL_RenderClear(ren);
}

auto
Renderer::present() -> void
{
	SDL_RenderPresent(ren);
}

auto
Renderer::drawGrid(std::tuple<int, int> corner, int len, int gap) -> void
{
	auto [x, y]{corner};

	for (int dis{gap}; dis <= len - gap; dis += gap) {
		SDL_RenderDrawLine(ren, x + dis, y, x + dis, y + len);
		SDL_RenderDrawLine(ren, x, y + dis, x + len, y + dis);
	}
}

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

auto
Renderer::fillGrid(std::tuple<int, int>           corner,
                   int                            len,
                   int                            gap,
                   std::vector<std::vector<bool>> map) -> void
{
	const int radius{static_cast<int>(gap * 0.30)};

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
