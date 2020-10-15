#include <iostream>
#include <unordered_map>
#include <vector>
#include <algorithm>
using human_t = unsigned char;
using pref_t = std::unordered_map<human_t, std::vector<human_t>>;
using matches_t = std::unordered_map<human_t, human_t>;

matches_t::iterator find_by_value(matches_t& matches, human_t w)
{
    auto found_it = matches.end();

    for (auto it = matches.begin(); it != matches.end(); ++it)
    {
        if (it->second == w)
        {
            found_it = it;
        }
    }
    return found_it;
}

matches_t gale_shapley(pref_t men_prefs, pref_t women_prefs)
{
    // create vectors of men and women who have yet to be matched
    std::vector<human_t> men, women;
    for (auto& entry : men_prefs) { men.push_back(entry.first); }
    for (auto& entry : women_prefs) { women.push_back(entry.first); }

    matches_t matches;
    while (!men.empty())
    {
        // find one of the men that have yet to be matched and remove him
        human_t m = men[0];

        // "favourite" woman m has yet to propose to
        human_t w = men_prefs[m][0];
        // remove m's favourite women as he will propose to her
        men_prefs[m].erase(men_prefs[m].begin()); 

        // check if w already has a match
        auto mtag_it = find_by_value(matches, w);

        // if no "contesting" man has been found
        if (mtag_it == matches.end()) 
        {
            matches[m] = w;

            // the man has been matched, remove him from the unmatched list
            men.erase(men.begin());
        }
        else
        {
            // if w preferes m over m' (m's prefrence index is lower that m''s)
            std::vector<human_t> w_prefs = women_prefs.find(w)->second;
            if (std::distance(std::find(w_prefs.begin(), w_prefs.end(), mtag_it->first),
                              std::find(w_prefs.begin(), w_prefs.end(), m)) > 0)
            {
                matches.erase(mtag_it);
                matches[m] = w;
                // the man has matched - remove it
                men.erase(men.begin());
            }
        }
    }
    return matches;
}

int main()
{
    pref_t men_prefs = {
        {'A', { 'Y', 'X', 'Z' }},
        {'B', { 'Z', 'Y', 'X' }},
        {'C', { 'X', 'Z', 'Y' }}
    };
    pref_t women_prefs = {
        {'X', { 'B', 'A', 'C' }},
        {'Y', { 'C', 'B', 'A' }},
        {'Z', { 'A', 'C', 'B' }}
    };
    for (auto& entry : gale_shapley(men_prefs, women_prefs))
        std::cout << entry.first << " : " << entry.second << std::endl;
    // { A: 'Y', C: 'X', B: 'Z' }
}
