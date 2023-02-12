#include "perfectCache.hpp"

struct page_t {
    int id = 0;
};

page_t slowGetPage(int key) {
    return page_t{key};
}

int main(int argc, char** argv) { 

#ifdef PRINT_TIME
    using namespace std::chrono;
    using fseconds = duration<float>;
#endif

    int size = 0, number_of_pages = 0;
    std::cin >> size >> number_of_pages;

    std::vector<int> keys;
    
    int hits = 0;
    for (int i = 0; i < number_of_pages; i++) {   
        int page_number = 0;
        std::cin >> page_number;
        keys.push_back(page_number);
    }

    Cache::PerfectCache<page_t> cache(size, keys);

#ifdef PRINT_TIME
    auto start = system_clock::now();
#endif

    for (int i = 0; i < number_of_pages; i++) {   
        if (cache.lookupUpdate(slowGetPage)) hits++;
    }

#ifdef PRINT_TIME
    auto end = system_clock::now() - start;
#endif
    std::cout << hits << " \n";
#ifdef PRINT_TIME
    std::cout << "runtime " << duration_cast<fseconds>(end).count() << "c\n";
#endif

    return 0;
}