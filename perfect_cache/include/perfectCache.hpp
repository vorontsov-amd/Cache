#include <iostream>
#include <iterator>
#include <list>
#include <unordered_map>
#include <vector>
#include <chrono>
#include <functional>

namespace Cache {

    template <typename T, typename KeyT = int>
    class PerfectCache final
    {
    private:
        using stream_it = typename std::vector<KeyT>::iterator;
        using cache_it  = typename std::vector<std::pair<T, KeyT>>::iterator;

        //Data--------------------------------------------------------------------------------------------
        std::vector<KeyT> key_stream;
        std::vector<std::pair<T, KeyT>> cache;

        stream_it key_iterator = key_stream.begin();

        size_t capacity;
        //------------------------------------------------------------------------------------------------
    public: 
        PerfectCache(size_t capacity_, const std::vector<KeyT>& key_stream_) : capacity{capacity_}, key_stream(key_stream_) {}

        //Methods-----------------------------------------------------------------------------------------
        bool lookupUpdate(const std::function<T(KeyT)>& slowGetPage);
        //------------------------------------------------------------------------------------------------

    private:

        cache_it findLastKey() {   
            auto erase = cache.begin();
            auto pos   = key_stream.begin();

            for (auto cache_it = cache.begin(); cache_it != cache.end(); ++cache_it) {
                auto candidate = std::find(key_stream.begin(), key_stream.end(), cache_it->second);

                if (candidate > pos) {
                    pos   = candidate;
                    erase = cache_it;
                }
            }
            return erase;
        }

        //------------------------------------------------------------------------------------------------

        cache_it findInCache(KeyT key) {
            return std::find_if(cache.begin(), cache.end(), [key](std::pair<T,KeyT>& elem) {
                return elem.second == key;
            });
        }

        //------------------------------------------------------------------------------------------------              

        bool full() const { return cache.size() == capacity; }
    
    };

    //----------------------------------------------------------------------------------------------------              

    template <typename T, typename KeyT>
    bool PerfectCache<T, KeyT>::lookupUpdate(const std::function<T(KeyT)>& slowGetPage) {   
        
        auto key = *key_iterator++;
        if (findInCache(key) == cache.end()) {

            if (std::find(key_iterator, key_stream.end(), key) == key_stream.end()) {
                return false;
            }

            if(full()) {
                auto res = findLastKey();
                cache.erase(res);
            }

            cache.push_back(std::pair{slowGetPage(key), key}); 
            return false;
        }

        return true;
    }
};