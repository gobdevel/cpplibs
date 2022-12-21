#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "gpCache.h"
#include "doctest/doctest.h"

using namespace GpCpplib;

TEST_CASE("Testing Cache") {
    LruCache<int, int> cache{3};
    cache.put(1, 11);
    auto ret = cache.get(1);
    CHECK_FALSE(!ret);
    CHECK_EQ(ret.value().get(), 11);

    cache.put(2, 12);
    cache.put(3, 13);
    cache.put(4, 14);

    auto ret1 = cache.get(1);
    CHECK_FALSE(ret1);

    ret = cache.get(3);
    CHECK_FALSE(!ret);
    CHECK_EQ(ret.value().get(), 13);
}

TEST_CASE("Testing Cache 2") {
    LruCache<std::string, std::pair<int, int>> cache{3};
    cache.put(std::string("first"), std::make_pair(11, 12));
    auto ret = cache.get("first");
    CHECK_FALSE(!ret);
    CHECK_EQ(ret.value().get(), std::make_pair(11, 12));

    cache.put(std::string("second"), std::make_pair(13, 14));
    cache.put(std::string("third"), std::make_pair(15, 16));
    cache.put(std::string("fourth"), std::make_pair(17, 18));

    auto ret1 = cache.get("first");
    CHECK_FALSE(ret1);

    ret = cache.get("second");
    CHECK_FALSE(!ret);
    CHECK_EQ(ret.value().get(), std::make_pair(13, 14));

    cache.put(std::string("fifth"), std::make_pair(19, 20));
    cache.put(std::string("sixth"), std::make_pair(21, 22));

    ret = cache.get("second");
    CHECK_FALSE(!ret);
    CHECK_EQ(ret.value().get(), std::make_pair(13, 14));
}

TEST_CASE("Testing Cache Remove") {
    LruCache<int, int> cache{3};
    cache.put(1, 11);
    auto ret = cache.get(1);
    CHECK_FALSE(!ret);
    CHECK_EQ(ret.value().get(), 11);

    cache.remove(1);
    ret = cache.get(1);
    CHECK_FALSE(ret);

    cache.put(2, 12);
    cache.put(3, 13);
    cache.put(4, 14);

    cache.remove(3);
    ret = cache.get(3);
    CHECK_FALSE(ret);

    cache.put(1, 11);
    ret = cache.get(1);
    CHECK_FALSE(!ret);
    CHECK_EQ(ret.value().get(), 11);
}
