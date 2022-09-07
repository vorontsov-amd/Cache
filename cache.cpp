#include "cache.h"
#include <unistd.h>

class page_t
{
private:
    int number;
public:
    page_t() = default;
    ~page_t() = default;
    page_t(int num) : number(num) {}
    int id() { return number; }
};



page_t slow_get_page(int key)
{
    //sleep(1);
    //std::cout << "download page\n";
    return page_t(key);
}


int main()
{    
    int size = 0, number_of_page = 0;
    std::cin >> size >> number_of_page;

    int hits = 0;
    Cache<page_t> cache(size);   
    
    auto start = clock();

    for (int i = 0; i < number_of_page; i++)
    {
        std::cout << i << "\n";
        int page_number = 0;
        std::cin >> page_number;
        if (cache.lookup_update(page_number, slow_get_page)) hits++;
        std::cout << i << "end\n";
    }

    auto end = clock() - start;

    std::cout << hits << "\n"; 

    std::cout << "runtime " << end / 1000.0 << "c\n";
}