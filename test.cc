#include "io/file.h"

#include "BinaryMapping/src/container.h"

int main() {
	TestStorage::File listFile("./storage/list");

	typedef BinaryMapping::PlainContainer<
		uint64_t, // Next-ID
		uint8_t,  // Status
		uint64_t // Payload
	> LinkedListContainer;
}
