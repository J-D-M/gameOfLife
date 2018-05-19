#include <cstdlib>
#include <ctime>
#include <vector>

/*
 * Conway's Game of Life
 * ----------------------
 *
 * 1. Any live cell with fewer than two live neighbors dies, as if caused by
 * under population.
 *
 * 2. Any live cell with two or three live neighbors lives on to the next
 * generation.
 *
 * 3. Any live cell with more than three live neighbors dies, as if by
 * overpopulation.
 *
 * 4. Any dead cell with exactly three live neighbors becomes a live cell, as if
 * by reproduction.
 */

class World
{
	using vvbool = std::vector<std::vector<bool>>;

	size_t size;
	vvbool map;

	/*
	 * Method: gen
	 * fill map array randomly
	 */

	auto
	gen() -> void
	{
		srand(time(nullptr));
		size_t flags = rand() % (size * size) + 1;

		for (size_t i = 0; i < size; i++)
			for (size_t j = 0; j < size; j++)
				map[i][j] = flags & (1 << ((i + 1) * (j + 1)));
	}

	auto
	countNeighbors(size_t y, size_t x) -> int
	{
		int ret       = 0;
		auto rotRight = [s = size](auto a) { return (a + 1) % s; };
		auto rotLeft = [s = size](auto a) { return a ? a - 1 : s - 1; };

		size_t ys[] = {rotLeft(y), y, rotRight(y)};
		size_t xs[] = {rotLeft(x), x, rotRight(x)};

		for (int i = 0; i < 3; i++)
			for (int j = 0; j < 3; j++)
				if (!(j == 1 && i == 1))
					ret += map[ys[i]][xs[j]];

		return ret;
	}

	auto
	updateCell(size_t y, size_t x) -> bool
	{
		size_t neighbors = countNeighbors(y, x);

		return (neighbors == 3 || (map[y][x] && neighbors == 2));
	}

      public:
	World(size_t s) : size{s}, map(s, std::vector<bool>(s)) { gen(); }

	/*
	 * Method: update
	 * update every cell
	 */

	auto
	update() -> void
	{
		vvbool new_map(size, std::vector<bool>(size));

		for (size_t i = 0; i < size; i++)
			for (size_t j = 0; j < size; j++)
				new_map[i][j] = updateCell(i, j);

		map = new_map;
	}

	auto
	getMap() -> vvbool
	{
		return map;
	}
};
