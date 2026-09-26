class Solution {
    ListNode* head;
public:
    Solution(ListNode* head) {
        this->head = head;
    }
    
    int getRandom() {
        int ans = head->val;
        ListNode* cur = head;
        int i = 1;
        while (cur) {
            if (rand() % i == 0) {
                ans = cur->val;
            }
            cur = cur->next;
            ++i;
        }
        return ans;
    }
};