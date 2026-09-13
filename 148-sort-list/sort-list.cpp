class Solution {
public:

    // Merge two sorted linked lists
    ListNode* merge(ListNode* l1, ListNode* l2) {

        ListNode dummy(0);
        ListNode* tail = &dummy;

        while (l1 && l2) {

            if (l1->val <= l2->val) {
                tail->next = l1;
                l1 = l1->next;
            }
            else {
                tail->next = l2;
                l2 = l2->next;
            }

            tail = tail->next;
        }

        // Attach remaining nodes
        if (l1)
            tail->next = l1;
        else
            tail->next = l2;

        return dummy.next;
    }

    ListNode* sortList(ListNode* head) {

        // 0 or 1 node → already sorted
        if (head == nullptr || head->next == nullptr)
            return head;

        // Find middle using slow and fast pointers
        ListNode* slow = head;
        ListNode* fast = head->next;

        while (fast && fast->next) {
            slow = slow->next;
            fast = fast->next->next;
        }

        // Split the list
        ListNode* second = slow->next;
        slow->next = nullptr;

        // Sort both halves
        ListNode* left = sortList(head);
        ListNode* right = sortList(second);

        // Merge sorted halves
        return merge(left, right);
    }
};