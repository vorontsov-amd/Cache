#pragma once 
#include <iostream>
#include <list>
#include <unordered_map>
#include <map>
#include <algorithm>

template <typename T, typename KeyT = int>
class Cache
{
private:
    using ListIt = typename std::list<KeyT>::iterator;

    size_t capacity;
    int min_counter;
    std::unordered_map<KeyT, T> cache; 
    std::unordered_map<KeyT, int> counters;
    std::unordered_map<KeyT, ListIt> iters;
    std::unordered_map<int, std::list<KeyT>> keys;


public:
    Cache() : Cache(10) {}
    Cache(size_t cap) : capacity(cap), min_counter(0) {}
    ~Cache() = default;

    template <typename F> 
    bool lookup_update(KeyT key, F slow_get_page);  
    
    bool full() const { return cache.size() == capacity; } 
};


template <typename T, typename KeyT>
    template <typename F>
    bool Cache<T, KeyT>::lookup_update(KeyT key, F slow_get_page)
    {
        bool KEY_NOT_FOUND = (cache.find(key) == cache.end());
        if (KEY_NOT_FOUND)
        {
            if (full())
            {              
                auto head_key = keys[min_counter].back();
                cache.erase(head_key);
                counters.erase(head_key);
                keys[min_counter].erase(iters[head_key]);
                iters.erase(head_key);
            }

            T page = slow_get_page(key);            
            cache[key] = page; 
            counters[key] = 1;
            keys[1].push_front(key);
            iters[key] = keys[1].begin();
            min_counter = 1;
            return false;
        }

        int counter = counters[key];
        counters[key] = counter + 1;
        keys[counter].erase(iters[key]);
        keys[counter + 1].push_front(key);
        iters[key] = keys[counter + 1].begin();

        bool INCREASE_COUNTER = (counter == min_counter && keys[min_counter].empty());  
        if (INCREASE_COUNTER) min_counter++;

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
    bool full() { return cache.size() == capacity; }
    IdealCache(size_t cap, const std::list<KeyT>& lst) : capacity(cap), keys(lst) { }

    template <typename F> 
    bool lookup_update(F slow_get_page);
};


template <typename T, typename KeyT>
    template <typename F>
    bool IdealCache<T, KeyT>::lookup_update(F slow_get_page)
    {
        auto key = keys.front();
        
        bool KEY_NOT_FOUND = (cache.find(key) == cache.end());
        if (KEY_NOT_FOUND)
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
