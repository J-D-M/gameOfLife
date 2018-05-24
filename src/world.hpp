#include <vector>

class World
{
      private:
	size_t height;
	size_t length;
	std::vector<std::vector<bool>> map;

	auto generateWorld() -> void;
	auto countNeighbors(size_t, size_t) -> int;

      public:
	World(size_t, size_t);
	World(size_t);

	auto update() -> void;
	auto getMap() -> std::vector<std::vector<bool>>;
};
