class Solution {
public:
    ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {
        // Dummy node simplifies edge cases — no need to handle first node separately
        ListNode dummy(0);
        ListNode* current = &dummy;
        
        // Walk through both lists, picking the smaller node each time
        while (list1 != nullptr && list2 != nullptr) {
            if (list1->val <= list2->val) {
                current->next = list1;   // Attach list1's current node
                list1 = list1->next;     // Move list1 forward
            } else {
                current->next = list2;   // Attach list2's current node
                list2 = list2->next;     // Move list2 forward
            }
            current = current->next;     // Advance our merged list pointer
        }
        
        // One list may still have remaining nodes — just attach them
        current->next = (list1 != nullptr) ? list1 : list2;
        
        // dummy.val is 0 (placeholder), dummy.next is the actual head
        return dummy.next;
    }
};