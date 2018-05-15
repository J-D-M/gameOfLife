#include "./world.cpp"
#include <algorithm>
#include <cassert>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <vector>
#include <unistd.h>

using namespace std;

auto
main(int argc, char **argv) -> int
{
	size_t world_size = (argc > 1) ? stoi(*(argv + 1)) : 20;
	World w(world_size);

	for (;;) {
		w.draw();
		w.update();
		sleep(1);
	}
}
