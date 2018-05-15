#include <cstdio>
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

#define UP_ONE_LINE "\x1b[1A"

class World
{
	using vvbool = std::vector<std::vector<bool>>;

	size_t size;
	vvbool world;

	/*
	 * Method: gen
	 * fill world array randomly
	 */

	auto
	gen() -> void
	{
		srand(time(nullptr));
		size_t flags = rand() % (size * size) + 1;

		for (size_t i = 0; i < size; i++)
			for (size_t j = 0; j < size; j++)
				world[i][j] =
				    flags & (1 << ((i + 1) * (j + 1)));
	}

	/*
	 * Method: drawEdge
	 * draw the edge that goes on top and bottom
	 */

	auto
	drawEdge() -> void
	{
		putchar('|');
		for (size_t i = 0; i < size; i++)
			putchar('-');
		puts("|");
	}

	/*
	 * Method: drawRow
	 * draw a single row
	 * -----------------
	 *  @param row: vector<bool>, draws a '@' for every true and ' ' for
	 *  false
	 */

	auto
	drawRow(std::vector<bool> const &row) -> void
	{
		putchar('|');
		for (auto cell : row)
			putchar(cell ? '@' : ' ');
		puts("|");
	}

	auto
	pSucc(size_t x) -> size_t
	{
		return (x + 1) % size;
	}

	auto
	pPred(size_t x) -> size_t
	{
		return x ? x - 1 : size - 1;
	}

	auto
	countNeighbors(size_t y, size_t x) -> int
	{
		int ret = 0;

		size_t ys[] = {pPred(y), y, pSucc(y)};
		size_t xs[] = {pPred(x), x, pSucc(x)};

		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				if (!(j == 1 && i == 1)) {
					ret += world[ys[i]][xs[j]];
				}
			}
		}

		return ret;
	}

	auto
	updateCell(size_t y, size_t x) -> bool
	{
		size_t neighbors = countNeighbors(y, x);

		return (neighbors == 3 || (world[y][x] && neighbors == 2));
	}

      public:
	World(size_t s) : size{s}, world(s, std::vector<bool>(s)) { gen(); }

	/*
	 * Method: draw
	 * draw the world array
	 */

	auto
	draw() -> void
	{
		static bool first = true;

		if (!first) {
			for (size_t i = 0; i < size + 2; i++)
				printf(UP_ONE_LINE);
		} else {
			first = false;
		}

		drawEdge();

		for (auto const &row : world)
			drawRow(row);

		drawEdge();
	}

	/*
	 * Method: update
	 * update every cell
	 */

	auto
	update() -> void
	{
		vvbool new_world(size, std::vector<bool>(size));

		for (size_t i = 0; i < size; i++)
			for (size_t j = 0; j < size; j++)
				new_world[i][j] = updateCell(i, j);

		world = new_world;
	}
};
