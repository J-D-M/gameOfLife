#include <cstdlib>
#include <ctime>

#include "world.hpp"

using std::vector;

auto
World::generateWorld() -> void
{
	srand(time(nullptr));
	auto roll = []() { return rand() % 2; };

	for (size_t h = 0; h < height; h++)
		for (size_t l = 0; l < length; l++)
			map[h][l] = roll();
}

auto
World::countNeighbors(size_t h, size_t l) -> int
{
	auto rotR = [](auto a, auto b) { return (a + 1) % b; };
	auto rotL = [](auto a, auto b) { return (a ? a : b) - 1; };

	size_t ys[] = {rotL(h, height), h, rotR(h, height)};
	size_t xs[] = {rotL(l, length), l, rotR(l, length)};

	int ret{0};

	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			if (!(i == 1 && j == 1))
				ret += map[ys[i]][xs[j]];

	return ret;
}

World::World(size_t h, size_t l)
    : height{h}, length{l}, map(height, vector<bool>(length))
{
	generateWorld();
}

World::World(size_t x) : World(x, x) {}

auto
World::update() -> void
{
	for (size_t h = 0; h < height; h++) {
		for (size_t l = 0; l < length; l++) {
			int count = countNeighbors(h, l);
			map[h][l] = count == 3 || (map[h][l] && count == 2);
		}
	}
}

auto
World::getMap() -> vector<vector<bool>>
{
	return map;
}
