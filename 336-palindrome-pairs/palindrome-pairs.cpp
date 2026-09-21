#include <vector>
#include <string>

class Solution {
    struct TrieNode {
        int wordIndex = -1;
        // Stores indices of words whose remaining prefix is a palindrome
        std::vector<int> palindromePrefixIds; 
        int children[26] = {0}; // Points to indices in the 'trie' array
    };

    std::vector<TrieNode> trie;

    // Helper to check if a substring is a palindrome
    bool isPalindrome(const std::string& s, int left, int right) {
        while (left < right) {
            if (s[left++] != s[right--]) return false;
        }
        return true;
    }

public:
    std::vector<std::vector<int>> palindromePairs(std::vector<std::string>& words) {
        // Initialize the root node at index 0
        trie.emplace_back(); 
        
        int n = words.size();
        
        // Step 1: Build a Trie mapping the REVERSED words
        for (int i = 0; i < n; ++i) {
            const std::string& word = words[i];
            int curr = 0; 
            
            // Traverse the word backwards
            for (int j = word.length() - 1; j >= 0; --j) {
                // If the remaining prefix of the original word is a palindrome
                if (isPalindrome(word, 0, j)) {
                    trie[curr].palindromePrefixIds.push_back(i);
                }
                
                int charIdx = word[j] - 'a';
                if (trie[curr].children[charIdx] == 0) {
                    trie[curr].children[charIdx] = trie.size();
                    trie.emplace_back();
                }
                curr = trie[curr].children[charIdx];
            }
            
            trie[curr].wordIndex = i;
            // The empty remaining prefix is always a palindrome
            trie[curr].palindromePrefixIds.push_back(i); 
        }
        
        std::vector<std::vector<int>> result;
        
        // Step 2: Search for palindromic pairs for each word
        for (int i = 0; i < n; ++i) {
            const std::string& word = words[i];
            int curr = 0;
            bool matchFailed = false;
            
            for (int j = 0; j < word.length(); ++j) {
                // Case 1: The current word is longer than the matched word in the Trie.
                // If we land on a finished word, check if the rest of our current word is a palindrome.
                if (trie[curr].wordIndex != -1 && trie[curr].wordIndex != i) {
                    if (isPalindrome(word, j, word.length() - 1)) {
                        result.push_back({i, trie[curr].wordIndex});
                    }
                }
                
                int charIdx = word[j] - 'a';
                if (trie[curr].children[charIdx] == 0) {
                    matchFailed = true;
                    break;
                }
                curr = trie[curr].children[charIdx];
            }
            
            // Case 2: The current word is completely traversed.
            // Check if any reversed words in the Trie have a remaining palindrome prefix.
            if (!matchFailed) {
                for (int id : trie[curr].palindromePrefixIds) {
                    if (i != id) {
                        result.push_back({i, id});
                    }
                }
            }
        }
        
        return result;
    }
};