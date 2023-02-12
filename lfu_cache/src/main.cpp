#include "cache.hpp"
#include <unistd.h>
#include <vector>
#include <fstream>
#include <algorithm>
#include <chrono>

struct page_t {
    int id = 0;
};

page_t slowGetPage(int key)
{
    return page_t{key};
}

int main()
{
    using namespace std::chrono;
    using fseconds = duration<float>;

    size_t size = 0;
    int number_of_page = 0;
    std::cin >> size >> number_of_page;

    Cache::LFUCache<page_t> cache{size};

    int hits = 0;
    auto start = system_clock::now();

    for (int i = 0; i < number_of_page; i ++) {
        int page_number = 0;
        std::cin >> page_number;
        if (cache.lookupUpdate(page_number, slowGetPage)) hits++;
    }

    auto end = system_clock::now() - start;
    std::cout << hits << '\n';
    //std::cout << "runtime " << duration_cast<fseconds>(end).count() << "c\n";
}