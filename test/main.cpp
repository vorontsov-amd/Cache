#include "../Cache/cache.h"
#include <unistd.h>
#include <vector>
#include <fstream>
#include <algorithm>

struct page_t
{
    int id;
    page_t() : page_t(0) {}
    page_t(int num) : id(num) {}
};

page_t slow_get_page(int key)
{
    return page_t(key);
}

int main()
{
    int size = 0, number_of_page = 0;
    std::cin >> size >> number_of_page;

    Cache<page_t> cache(size);

    int hits = 0;
    for (int i = 0; i < number_of_page; i ++)
    {
        int page_number = 0;
        std::cin >> page_number;
        if (cache.lookup_update(page_number, slow_get_page)) hits++;
    }

    std::cout << hits << '\n';
}