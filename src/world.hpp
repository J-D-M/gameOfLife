#include <vector>

class World
{
      public:
	World(size_t, size_t);
	World(size_t);

	auto update() -> void;
	auto getMap() -> std::vector<std::vector<bool>>;

      private:
	const size_t height;
	const size_t length;

	std::vector<std::vector<bool>> map;

	auto genRand() -> void;
};
