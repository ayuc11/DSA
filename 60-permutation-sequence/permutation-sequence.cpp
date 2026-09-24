#include <string>
#include <vector>

class Solution {
public:
    string getPermutation(int n, int k) {
        int fact = 1;
        vector<int> numbers;
        
        // Compute (n - 1)! and initialize numbers list [1, 2, ..., n]
        for (int i = 1; i < n; ++i) {
            fact *= i;
            numbers.push_back(i);
        }
        numbers.push_back(n);
        
        // Convert k to 0-based indexing
        k = k - 1;
        string result = "";
        
        while (true) {
            // Find current digit
            int index = k / fact;
            result += to_string(numbers[index]);
            numbers.erase(numbers.begin() + index);
            
            if (numbers.empty()) {
                break;
            }
            
            // Update k and factorial for the next digit
            k %= fact;
            fact /= numbers.size();
        }
        
        return result;
    }
};