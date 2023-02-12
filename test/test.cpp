#include "cache.hpp"
#include "perfectCache.hpp"
#include <fstream>

struct page_t {
    int id;
};

page_t slow_get_page(int key) {
    return page_t{key};
}

int LFU(std::ifstream& file) {
   
    int size = 0, number_of_pages = 0;
    file >> size >> number_of_pages;
    
    Cache::Cache<page_t> cache(size);

    int hits = 0;
    for (int i = 0; i < number_of_pages; i++)
    {
        int page_number = 0;
        file >> page_number;
        if (cache.lookup_update(page_number, slow_get_page)) hits++;
    }

    return hits;
}

int perfect(std::ifstream &file)
{
    int size = 0, number_of_pages = 0;
    file >> size >> number_of_pages;

    std::vector<int> keys;

    int hits = 0;
    
    for (int i = 0; i < number_of_pages; i++)
    {   
        int page_number = 0;
        file >> page_number;
        keys.push_back(page_number);
    }

    Cache::PerfectCache<page_t> caches(size, keys);

    for (int i = 0; i < number_of_pages; i++)
    {   
        if (caches.lookupUpdate(slow_get_page)) hits++;
    }

    return hits;
}