#include <vector>
#include <string>
#include <unordered_set>
#include <algorithm>

using namespace std;

class Solution {
public:
    string longestWord(vector<string>& words) {
        sort(words.begin(), words.end());
        
        unordered_set<string> validWords;
        string longest = "";

        for (const string& word : words) {
            if (word.length() == 1 || validWords.count(word.substr(0, word.length() - 1))) {
                validWords.insert(word);
                
                if (word.length() > longest.length()) {
                    longest = word;
                }
            }
        }
        
        return longest;
    }
};