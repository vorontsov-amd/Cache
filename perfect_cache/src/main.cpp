#include "perfectCache.hpp"

struct page_t {
    int id = 0;
};

page_t slow_get_page(int key) {
    return page_t{key};
}

int main(int argc, char** argv) { 

    int size = 0, number_of_pages = 0;
    std::cin >> size >> number_of_pages;

    std::vector<int> keys;
    int hits = 0;
    
    for (int i = 0; i < number_of_pages; i++)
    {   
        int page_number = 0;
        std::cin >> page_number;
        keys.push_back(page_number);
    }

    Cache::PerfectCache<page_t> cache(size, keys);

    for (int i = 0; i < number_of_pages; i++)
    {   
        if (cache.lookupUpdate(slow_get_page)) hits++;
    }

    std::cout << hits << " \n";
    return 0;
}