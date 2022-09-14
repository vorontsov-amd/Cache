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
    //sleep(1);
    //std::cout << "download page\n";
    return page_t(key);
}

void CacheTest()
{
    std::vector test_1 = {1, 2, 3, 4, 1, 2, 5, 1, 2, 4, 3 , 4};
    std::list<int> buf(test_1.size());
    std::copy(test_1.begin(), test_1.end(), buf.begin());
    
    const size_t SIZE = 4;
    Cache<page_t> cahce_1(SIZE);
    IdealCache<page_t> idcache_1(SIZE, buf);

    int hits = 0, idhits = 0;
    for (auto x : test_1)
    {
        if(cahce_1.lookup_update(x, slow_get_page)) hits++;
        if(idcache_1.lookup_update(slow_get_page)) idhits++;
    }

    const int EXPECTED_HITS = 6;
    if (hits != EXPECTED_HITS)
    {
        std::cout << "Test LFU cache failed. Expected 8. Recived " << hits << '\n';
    }
    if (idhits != EXPECTED_HITS)
    {
        std::cout << "Test Ideal cache failed. Expected 8. Recived " << idhits << '\n';    
    }
    if (hits == EXPECTED_HITS && idhits == EXPECTED_HITS)
    {
        std::cout << "Test passed\n";
    }
}

void CacheCompare()
{   
    int size = 0, number_of_page = 0;
    std::cin >> size >> number_of_page;

    int hits = 0;
    auto start = clock();
    std::list<int> buf;
    for (int i = 0; i < number_of_page; i ++)
    {
        int page_number = 0;
        std::cin >> page_number;
        buf.push_back(page_number);
    }

    IdealCache<page_t> idcache(size, buf);
    for (int i = 0; i < number_of_page; i++)
    {
        if (idcache.lookup_update(slow_get_page)) hits++;
    }

    auto end = clock() - start;
    std::cout << "hils ideal cache " << hits << "\n"; 
    std::cout << "runtime " << double(end) / CLOCKS_PER_SEC << "c\n";

    Cache<page_t> cache(size);   
    start = clock();
    hits = 0;
    for (auto it = buf.begin(); it != buf.end(); ++it)
    {
        int page_number = *it;
        if (cache.lookup_update(page_number, slow_get_page)) hits++;
    }

    end = clock() - start;
    std::cout << "hits LFM " << hits << "\n"; 
    std::cout << "runtime " << double(end) / CLOCKS_PER_SEC << "c\n";    
}


int main()
{    
    CacheTest();
    CacheCompare();
}
