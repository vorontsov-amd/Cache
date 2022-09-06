#include "cache.h"
#include <unistd.h>

struct page_t
{
    int number;

    page_t(int num) : number(num) {}

    int id() { return number; }
};



page_t slow_get_page(int key)
{
    sleep(1);
    std::cout << "download page\n";
    return page_t(key);
}


int main()
{    
    int size = 0, number_of_page = 0;
    std::cin >> size >> number_of_page;

    int hits = 0;
    Cache<page_t> cache(size);   
    for (int i = 0; i < number_of_page; i++)
    {
        int page_number = 0;
        std::cin >> page_number;
        if (cache.lookup_update(page_number, slow_get_page)) hits++;
    }

    std::cout << hits; 
}