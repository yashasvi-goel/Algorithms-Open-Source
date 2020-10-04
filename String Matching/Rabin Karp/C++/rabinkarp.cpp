/*
The Rabin-Karp algorithm is used to quickly match string patterns in text.
Plagiarism detection is one of the many applications of string matching.
The rolling hash function being used is hash(x) = base^i*x[i] for each i in strlen(x)
*/
#include <iostream> // std::cout, std::cin
#include <cmath> // pow
#include <vector> // std::vector

// the base of the polinomials for the calculations of the rolling hash functions - the smaller the longer the string can be hashed
const int base = 2;
// a prime modulus to limit the size of the hash value
const long long modulus = 1000000007;

std::vector<size_t> rabin_karp(std::string text, std::string pattern, bool show_statistics = false)
{
    std::vector<size_t> found_indices;
    const size_t patternln = pattern.length(), textln = text.length();
    const long long ten_to_the_len = pow(base, patternln - 1);
    // count the number of hash values that we're 
    unsigned int wrong_hash_parities = 0;

    long long text_hash = text[0] - 'a' + 1, pattern_hash = pattern[0] - 'a' + 1;
    // create the initial hash-values of both the text and the pattern
    for (size_t i = 1; i < patternln; ++i)
    {
        pattern_hash = (base * pattern_hash + pattern[i] - 'a' + 1) % modulus;
        text_hash = (base * text_hash + text[i] - 'a' + 1) % modulus;
    }

    for (size_t i = 0; i <= textln - patternln; ++i)
    {
        if (pattern_hash == text_hash) // first check if the hashes are the same
        {
            if (text.compare(i, patternln, pattern) == 0) // only if they have equal hash values, do the O(n) string comparison
                found_indices.push_back(i);
            else // if the strings aren't the same, then we have two identical hash values for different strings
                ++wrong_hash_parities;
        }
        
        // if this is not the last character, update the hash of the text
        if (i != textln - patternln)
        {
            // roll down the hash
            text_hash = ((text_hash - (text[i] - 'a' + 1) * ten_to_the_len) * base + (text[i + patternln] - 'a' + 1)) % modulus;
            // modulu of a negative number is x + modulus
            if (text_hash < 0)
                text_hash += modulus;
        }
    }
    // if statistics were requested
    if (show_statistics)
        std::cout << std::endl << "Reached " << wrong_hash_parities << " hash parities reached without matched pattern" << std::endl;
    
    return found_indices;
}

int main()
{
    std::string text, pattern;
    std::cout<< "Enter Text: ";
    std::cin >> text;
    std::cout << "Enter Pattern: ";
    std::cin >> pattern;

    auto found_locations = rabin_karp(text, pattern, true);

    if (found_locations.empty())
        std::cout << "Pattern not Found!" << std::endl;
    else
        std::cout << "Pattern Found at Indices: ";
    
    for (auto index : found_locations)
        std::cout << index << ' ';

    return 0;
}
