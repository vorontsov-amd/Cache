#include "gtest/gtest.h"
#include <fstream>
#include "cache.hpp"
#include "perfectCache.hpp"

struct page_t {
    int id;
};

page_t slow_get_page(int key) {
    return page_t{key};
}

//--------------------------------------------------------------------------------------------------------

int TestLFU(std::ifstream &file) {
   
    size_t size = 0;
    int number_of_pages = 0;
    file >> size >> number_of_pages;
    
    Cache::LFUCache<page_t> cache{size};

    int hits = 0;
    for (int i = 0; i < number_of_pages; i++) {
        int page_number = 0;
        file >> page_number;
        if (cache.lookupUpdate(page_number, slow_get_page)) hits++;
    }

    return hits;
}

//--------------------------------------------------------------------------------------------------------

int TestPerfect(std::ifstream &file)
{
    size_t size = 0;
    int number_of_pages = 0;
    file >> size >> number_of_pages;

    std::vector<int> keys;

    int hits = 0;
    for (int i = 0; i < number_of_pages; i++) {   
        int page_number = 0;
        file >> page_number;
        keys.push_back(page_number);
    }

    Cache::PerfectCache<page_t> caches(size, keys);

    for (int i = 0; i < number_of_pages; i++) {   
        if (caches.lookupUpdate(slow_get_page)) hits++;
    }

    return hits;
}

//--------------------------------------------------------------------------------------------------------

#ifndef PROJECT_DIR_PATH
    #define PROJECT_DIR_PATH ""
#endif

std::string concat(std::string str) {
    return PROJECT_DIR_PATH + str;
}

//--------------------------------------------------------------------------------------------------------

TEST(TestLFU_cache, TestNumber0) {   
    std::ifstream file(concat("/test/tests/TestLFU0.txt"));
    EXPECT_EQ(TestLFU(file), 5);
    file.close();
}

TEST(TestLFU_cache, TestNumber1) {
    std::ifstream file(concat("/test/tests/TestLFU1.txt"));
    EXPECT_EQ(TestLFU(file), 2);
    file.close();
}

TEST(TestLFU_cache, TestNumber2) {
    std::ifstream file(concat("/test/tests/TestLFU2.txt"));
    EXPECT_EQ(TestLFU(file), 3);
    file.close();
}

TEST(TestPerfect_cache, TestNumber0) {
    std::ifstream file(concat("/test/tests/Testperf0.txt"));
    EXPECT_EQ(TestPerfect(file), 5);
    file.close();
}

TEST(TestPerfect_cache, TestNumber1) {
    std::ifstream file(concat("/test/tests/Testperf1.txt"));
    EXPECT_EQ(TestPerfect(file), 4);
    file.close();
}

TEST(TestPerfect_cache, TestNumber2) {
    std::ifstream file(concat("/test/tests/Testperf2.txt"));
    EXPECT_EQ(TestPerfect(file), 7);
    file.close();
}

//--------------------------------------------------------------------------------------------------------

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
