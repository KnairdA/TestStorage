#include "io/file.h"

#include "storage/storage.h"
#include "BinaryMapping/src/type/tuple.h"
#include "BinaryMapping/src/type/custom_serializable.h"

#include <iostream>

int main() {
	typedef TestStorage::Storage<
		BinaryMapping::PlainTuple<
			std::uint32_t,
			BinaryMapping::ByteField<32>
		>
	> StorageType;
	
	StorageType storage("./storage/test");

	StorageType::container area(storage.at(5, 10));

	for ( auto iter(area->begin());
	      iter != area->end();
	      ++iter ) {
		(*iter).set<0>(84);
	}

	StorageType::element test(storage.add());

	test->set<0>(42);
}
