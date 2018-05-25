#include <cstdlib>
#include <ctime>

#include "world.hpp"

using std::vector;

World::World(size_t h, size_t l)
    : height{h}, length{l}, map(height, vector<bool>(length))
{
	generateWorld();
}

World::World(size_t x) : World(x, x) {}

/*
 * Fill world randomly
 */

auto
World::generateWorld() -> void
{
	srand(time(nullptr));
	auto roll = []() { return rand() % 2; };

	for (size_t h = 0; h < height; h++)
		for (size_t l = 0; l < length; l++)
			map[h][l] = roll();
}

/*
 * Returns vector with the count of each cooresponding cells neighbors
 */

auto
World::countNeighbors() -> vector<vector<int>>
{
	vector<vector<int>> ret(height, vector<int>(length));

	auto rotL = [](size_t a, size_t b) { return (a ? a : b) - 1; };
	auto rotR = [](size_t a, size_t b) { return (a + 1) % b; };

	auto getCoords = [&rotL, &rotR](auto a, auto b) -> vector<size_t> {
		return {rotL(a, b), a, rotR(a, b)};
	};

	auto incNeighbors = [&ret](auto ys, auto xs) {
		for (size_t i = 0; i < 3; i++)
			for (size_t j = 0; j < 3; j++)
				if (!(i == 1 && j == 1))
					++ret[ys[i]][xs[j]];
	};

	for (size_t h = 0; h < height; h++)
		for (size_t l = 0; l < length; l++)
			if (map[h][l])
				incNeighbors(getCoords(h, height),
				             getCoords(l, length));

	return ret;
}

/*
 * update that state of every cell
 */

auto
World::update() -> void
{
	auto counts = countNeighbors();

	for (size_t h = 0; h < height; h++)
		for (size_t l = 0; l < length; l++)
			map[h][l] = counts[h][l] == 3 ||
			            (map[h][l] && counts[h][l] == 2);
}

auto
World::getMap() -> vector<vector<bool>>
{
	return map;
}
