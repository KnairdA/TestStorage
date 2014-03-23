#include "io/file.h"

#include "block/block_storage.h"

#include <iostream>

int main() {
	TestStorage::BlockStorage<32> blocks32("./storage/32");

	blocks32.add(10000);

	std::cout << blocks32.size();
}
