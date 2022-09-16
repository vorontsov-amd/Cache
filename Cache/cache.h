#pragma once 
#include <iostream>
#include <list>
#include <unordered_map>
#include <map>
#include <algorithm>
#include <functional>

template <typename T, typename KeyT = int>
class Cache
{
private:

    using ListIt = typename std::list<KeyT>::iterator;

    struct element
    {
        T page;
        int counter;
        ListIt iter;
    };

    size_t capacity;
    int min_counter;
    std::unordered_map<KeyT, element> cache; 
    std::unordered_map<int, std::list<KeyT>> keys;


public:
    Cache() : Cache(10) {}
    Cache(size_t cap) : capacity(cap), min_counter(0) {}
    ~Cache() = default;

    bool lookup_update(KeyT key, std::function<T(KeyT)> slow_get_page);
    
    bool full() const { return cache.size() == capacity; } 
};


template <typename T, typename KeyT>
bool Cache<T, KeyT>::lookup_update(KeyT key, std::function<T(KeyT)> slow_get_page)
{
    if (cache.find(key) == cache.end())
    {
        if (full())
        {              
            auto head_key = keys[min_counter].back();
            auto head_iter = cache[head_key].iter;
            keys[min_counter].erase(head_iter);
            cache.erase(head_key);
        }

        T page = slow_get_page(key); 
        keys[1].push_front(key);           
        cache[key] = { page, 1, keys[1].begin() }; 
        min_counter = 1;
        return false;
    }

    int counter = cache[key].counter;
    auto iterator = cache[key].iter;

    keys[counter].erase(iterator);
    keys[counter + 1].push_front(key);
    cache[key].counter = counter + 1;
    cache[key].iter = keys[counter + 1].begin();

    if (counter == min_counter && keys[min_counter].empty()) min_counter++;
    return true;
}
    


template <typename T, typename KeyT = int>
class IdealCache
{
private:
    size_t capacity;
    std::list<KeyT> keys;
    std::unordered_map<KeyT, T> cache;
    std::unordered_map<int, KeyT> keys_map;
public:
    IdealCache(size_t cap, const std::list<KeyT>& lst) : capacity(cap), keys(lst) { }

    bool full() { return cache.size() == capacity; }
    bool lookup_update(std::function<T(KeyT)> slow_get_page);
};


template <typename T, typename KeyT>
bool IdealCache<T, KeyT>::lookup_update(std::function<T(KeyT)> slow_get_page)
{
    auto key = keys.front();
    
    if (cache.find(key) == cache.end())
    {
        if (full())
        {              
            int min_frequency = INT32_MAX;
            for (auto pair : cache)
            {
                int frequency = std::count(keys.begin(), keys.end(), pair.first);
                keys_map[frequency] = pair.first;
                min_frequency = (frequency < min_frequency) ? frequency : min_frequency;
            }
            cache.erase(keys_map[min_frequency]);
            keys_map.erase(min_frequency);
        }
        cache[key] = slow_get_page(key);

        keys.pop_front();
        return false;
    }
    keys.pop_front();
    return true;
}
