#pragma once 
#include <iostream>
#include <list>
#include <unordered_map>
#include <map>
#include <algorithm>
#include <functional>


#ifndef CACHE_VERSION
    #define CACHE_VERSION 2
#endif


namespace Cache {


#if CACHE_VERSION == 1

    //First implementation LFU cache ---------------------------------------------------------------------
    template <typename T, typename KeyT = int>
    class LFUCache final
    {
    private:

        using ListIt = typename std::list<KeyT>::iterator;

        struct element final
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
        LFUCache(size_t cap = 10) : capacity(cap), min_counter(0) {}

        bool lookupUpdate(KeyT key, const std::function<T(KeyT)>& slow_get_page);
        
    private:
        bool full() const { return cache.size() == capacity; } 
    };

    //----------------------------------------------------------------------------------------------------

    template <typename T, typename KeyT>
    bool LFUCache<T, KeyT>::lookupUpdate(KeyT key, const std::function<T(KeyT)>& slow_get_page)
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

    //----------------------------------------------------------------------------------------------------

#elif CACHE_VERSION == 2

    //Second implementstion LFU cache. Work faster then the first version --------------------------------
    template <typename T, typename KeyT = int>
    class LFUCache final
    {
    private:
        struct element;
        
        using Parent_it = typename std::list<std::pair<int, std::list<element>>>::iterator;
        using Iterator  = typename std::list<element>::iterator;

        struct element final
        {
            T page;
            Parent_it parent_it;
            KeyT key;
        };

        size_t capacity;

        std::unordered_map<KeyT, Iterator> htable;
        std::list<std::pair<int, std::list<element>>> count_list;

    public:
        LFUCache(size_t capacity_ = 10) : capacity{capacity_} {}

        bool lookupUpdate(KeyT key, const std::function<T(KeyT)>& slowGetPage);

    private:
        bool full() const { return htable.size() == capacity; }
    };

    //----------------------------------------------------------------------------------------------------

    template <typename T, typename KeyT>
    bool LFUCache<T, KeyT>::lookupUpdate(KeyT key, const std::function<T(KeyT)>& slowGetPage) {   
        
        auto lfu_node = count_list.begin();
        auto hit = htable.find(key);
        
        if(hit == htable.end()) {   
            if(full()) {   
                auto lfu_key = lfu_node->second.back().key;
                htable.erase(lfu_key);
                count_list.front().second.pop_back(); 
            }

            if (lfu_node->first != 1) {   
                count_list.emplace_front(std::pair(1, std::list<element>{}));
            }

            element new_elem = { slowGetPage(key), count_list.begin(), key };
            count_list.front().second.push_front(new_elem);
            htable[key] = count_list.front().second.begin();

            return false;
        }

        auto elem_it = hit->second;
        auto freq_it = elem_it->parent_it;
        auto next_freq_it = std::next(elem_it->parent_it);
        
        if(next_freq_it == count_list.end() or (next_freq_it->first != (freq_it->first + 1))) {   
            next_freq_it = count_list.insert(next_freq_it, std::pair(((freq_it->first) + 1), std::list<element>{}));
        }

        auto& list = freq_it->second;
        auto& next_list = next_freq_it->second;
        
        next_list.splice(next_list.begin(), list, elem_it);
        
        elem_it->parent_it = next_freq_it;
        if((freq_it->second).empty()) {   
            count_list.erase(freq_it);
        }

        return true;
    }
    //----------------------------------------------------------------------------------------------------


#endif

};

