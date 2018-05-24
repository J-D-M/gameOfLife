#include <cctype>
#include <chrono>
#include <cstdio>
#include <string>
#include <thread>
#include <vector>

#include "world.hpp"

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

using namespace std;

auto
wait(int ms) -> void
{
	this_thread::sleep_for(chrono::milliseconds(ms));
}

auto
printUsage(char *name) -> void
{
	printf("Conway's game of life\n"
	       "Usage:\t %s\n\t%s [side length]\n"
	       "\t%s [height] [length]\n",
	       name,
	       name,
	       name);
}

auto
isNumber(char *str) -> bool
{
	while (*str) {
		if (!isdigit(*str++))
			return false;
	}
	return true;
}

auto
getDimensions(int argc, char **argv) -> std::pair<size_t, size_t>
{
	switch (argc) {
	case 1:
		return {20, 20};
		break;
	case 2:
		if (isNumber(*(argv + 1))) {
			size_t num = stoi(*(argv + 1));
			return {num, num};
		}
	case 3:
		if (isNumber(*(argv + 1)) && isNumber(*(argv + 2))) {
			return {stoi(*(argv + 1)), stoi(*(argv + 2))};
		}
	default:
		printUsage(*argv);
		exit(1);
		break;
	};
}

auto
printMap(vector<vector<bool>> const &m) -> void
{
	auto borderLine = [&m]() {
		for (size_t i = 0; i < m[0].size() + 2; i++)
			putchar('-');
		putchar('\n');
	};

	borderLine();
	for (auto const &row : m) {
		putchar('|');
		for (auto const &cell : row)
			putchar((cell ? '*' : ' '));
		puts("|");
	}
	borderLine();
}


auto
main(int argc, char **argv) -> int
{
	auto dimens = getDimensions(argc, argv);

	World w(dimens.first, dimens.second);

	for (;;) {
		printMap(w.getMap());
		w.update();
		wait(750);

		for (int i = 0; i < 50; i++)
			putchar('\n');
	}
}
