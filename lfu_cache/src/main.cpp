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
#ifdef PRINT_TIME
    using namespace std::chrono;
    using fseconds = duration<float>;
#endif

    size_t size = 0;
    int number_of_page = 0;
    std::cin >> size >> number_of_page;

    Cache::LFUCache<page_t> cache{size};

    
#ifdef PRINT_TIME
    auto start = system_clock::now();
#endif

    int hits = 0;
    for (int i = 0; i < number_of_page; i ++) {
        int page_number = 0;
        std::cin >> page_number;
        if (cache.lookupUpdate(page_number, slowGetPage)) hits++;
    }

#ifdef PRINT_TIME
    auto end = system_clock::now() - start;
#endif
    std::cout << hits << '\n';
#ifdef PRINT_TIME
    std::cout << "runtime " << duration_cast<fseconds>(end).count() << "c\n";
#endif
}