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

	StorageType::element test(storage.add());

	test->set<0>(42);
}
