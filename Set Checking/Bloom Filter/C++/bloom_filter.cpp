#include <functional>
#include <iostream>
#include <string>
#include <cstring>

class bloom_filter
{
private:
    // k is number of hashes per element, filter_size is size of the filter array.
    // search threshold is number of calculations that need to be true in the array for the element to count as found
    size_t k, filter_size, search_threshold;
    std::hash<std::string> hasher;
    bool* hash_array;
    
public:
    bloom_filter(size_t filter_size, size_t function_count, size_t search_threshold)
        : filter_size(filter_size), search_threshold(search_threshold), k(function_count)
    {
        hash_array = new bool[filter_size];
        // set all the elements of the hash array to false
        memset(hash_array, false, filter_size);
    }
    ~bloom_filter()
    {
        delete[] hash_array;
    }
    void add(std::string url)
    {
        for (size_t i = 0; i < k; ++i)
        {
            hash_array[hasher(url.append(std::to_string(i))) % filter_size] = true;
        }
    }
    /* add from a range */
    template <class iterator>
    void add (iterator first, iterator last)
    {
        for (iterator it = first; it != last; ++it)
        {
            add(*it);
        }
    }
    /* returns true if there is a high enoguh chance that the item is located in the filter */
    bool check(std::string url)
    {
        size_t found = 0;
        for (size_t i = 0; i < k; ++i)
        {
            if (hash_array[hasher(url.append(std::to_string(i))) % filter_size])
            {
                ++found;
            }
        }
        return found > search_threshold;
    }
};

int main()
{
    bloom_filter bf(1009, 5, 2);
    const std::string unsecure_urls[5] = { "www.xyz.in", "www.hacking.com", "www.abc123.org", "www.pentest.com", "www.gugle.com"};
    bf.add(unsecure_urls, unsecure_urls + 5);
    const std::string test_urls[5] = {"www.google.com", "www.gugle.com", "www.github.com", "www.facebook.com", "www.xyz.in"};

    for (size_t i = 0; i < 5; ++i)
        std::cout << test_urls[i] << " is " << (bf.check(test_urls[i]) ? "not " : "") << "secure." << std::endl;
}
