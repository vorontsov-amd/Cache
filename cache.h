#pragma once 
#include <iostream>
#include <queue>
#include <unordered_map>

template <typename T, typename KeyT = int>
class Cache
{
private:
    size_t size;
    std::priority_queue<T> cache;
    std::unordered_map<KeyT, T> hash; 
public:
    template <typename F> 
    bool lookup_update(KeyT key, F slow_get_page);
    
    bool full() const;  
};

template <typename T, typename KeyT>
    template <typename F>
    bool Cache<T, KeyT>::lookup_update(KeyT key, F slow_get_page)
    {
        //
        return true;
    }
