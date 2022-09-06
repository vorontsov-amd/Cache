#pragma once 
#include <iostream>
#include <list>
#include <unordered_map>
#include <typeinfo>

template <typename T, typename KeyT = int>
class Cache
{
private:
    using ListIt = typename std::list<std::pair<T, int>>::iterator;

    size_t size;
    std::list<std::pair<T, int>> cache;
    std::unordered_map<KeyT, ListIt> hash; 

public:
    Cache(size_t size_) : size(size_) {}

    template <typename F> 
    bool lookup_update(KeyT key, F slow_get_page);
    
    bool full() const { return cache.size() == size; } 
};


template <typename T, typename KeyT>
    template <typename F>
    bool Cache<T, KeyT>::lookup_update(KeyT key, F slow_get_page)
    {
        auto cmp = [](std::pair<T, int> left, std::pair<T, int> right) { return left.second > right.second; };

        auto hash_iterator = hash.find(key);
        
        if (hash_iterator == hash.end())
        {
            if (full())
            {
                cache.pop_back();
                hash.erase(cache.back().first.id());
            }
            auto page = slow_get_page(key);
            cache.push_front(std::pair(page, 1));
            hash[key] = cache.begin();
            cache.sort(cmp);
            return false;
        }
        
        auto list_iterator = hash_iterator->second;
        list_iterator->second++;
        
        cache.sort(cmp);
        return true;
    }

template <typename T>
std::ostream& operator<<(std::ostream& stream, const std::pair<T, int>&  pair)
{
    return stream << pair.first << " " << pair.second << "\n";
}
