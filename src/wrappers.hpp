#include <SDL2/SDL.h>
#include <tuple>
#include <vector>

namespace sdl2
{
/* Color constants */
using Color = std::tuple<Uint8, Uint8, Uint8>;

namespace color
{
const Color red{0xff, 0x0, 0x0};
const Color green{0x0, 0xff, 0x0};
const Color blue{0x0, 0x0, 0xff};
const Color white{0xff, 0xff, 0xff};
const Color black{0x0, 0x0, 0x0};
} // namespace color

class Error;
class SubSystem;
class Window;
class Renderer;
class Event;

class Error
{
      public:
	auto error(const char *) -> void;
};

class SubSystem : Error
{
      public:
	SubSystem(Uint32);
	~SubSystem();
};

class Renderer : Error
{
      public:
	static const auto accelerated{SDL_RENDERER_ACCELERATED};

	Renderer(const Window &, int, Uint32);
	~Renderer();

	auto setDrawColor(Color, Uint8) -> void;
	auto clear() -> void;
	auto present() -> void;

	auto drawCircle(std::tuple<int, int>, int) -> void;
	auto drawGrid(std::tuple<int, int>, int, int) -> void;
	auto
	fillGrid(std::tuple<int, int>, int, int, std::vector<std::vector<bool>>)
	    -> void;

      private:
	SDL_Renderer *ren;
};

class Window : Error
{
      public:
	static const Uint32 npos{SDL_WINDOWPOS_UNDEFINED};
	static const auto   shown{SDL_WINDOW_SHOWN};

	Window(const char *, int, int, int, int, Uint32);
	~Window();

	friend Renderer::Renderer(const Window &, int, Uint32);

      private:
	SDL_Window *win;
};

class Event
{
      public:
	auto poll() -> int;
	auto type() -> Uint32;

      private:
	SDL_Event event;
};

} // namespace sdl2
