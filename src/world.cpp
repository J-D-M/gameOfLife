#include <cstdlib>
#include <ctime>

#include "world.hpp"

World::World(size_t h, size_t l)
    : height{h}, length{l}, map(height, std::vector<bool>(length))
{
	genRand();
}

World::World(size_t x) : World(x, x) {}

/*
 * Fill world randomly
 */

auto
World::genRand() -> void
{
	srand(time(nullptr));
	auto roll = [] { return rand() % 2; };

	for (auto &row : map)
		for (size_t i = 0; i < length; i++) // lol vector<bool>
			row[i] = roll();
}

/*
 * Counts cell's neighbors
 */

static auto
sumNeighbors(const std::vector<std::vector<bool>> &map, size_t y, size_t x)
    -> int
{
	int ret = 0;

	const size_t max_y{map.size()};
	const size_t max_x{map[0].size()};

	auto buildVec = [](auto a, auto b) -> std::vector<size_t> {
		return {(a ? a - 1 : b - 1), a, ((a + 1) % b)};
	};

	auto ys{buildVec(y, max_y)};
	auto xs{buildVec(x, max_x)};

	for (auto i : ys) {
		for (auto j : xs) {
			if (!(i == y && j == x))
				ret += map[i][j];
		}
	}

	return ret;
}

/*
 * update that state of every cell
 */

auto
World::update() -> void
{
	auto map_cpy{map};

	for (size_t h = 0; h < height; h++) {
		for (size_t l = 0; l < length; l++) {
			int count{sumNeighbors(map_cpy, h, l)};

			map[h][l] = (count == 3) || (map[h][l] && count == 2);
		}
	}
}

auto
World::getMap() -> std::vector<std::vector<bool>>
{
	return map;
}
