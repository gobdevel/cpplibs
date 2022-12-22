#include "gpAllocator.h"
#include "doctest/doctest.h"

using namespace GpCpplib;

TEST_CASE("Testing Allocator") {
   CustomAllocator<int> alloc;
   auto var = alloc.allocate(1);
   CHECK(var);

   alloc.construct(var, 10);
   CHECK_EQ(*var, 10);

   CHECK_FALSE(alloc.allocate(0));
   alloc.deallocate(var, 1);
}
