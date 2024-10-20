//
// Created by yuan su on 24-10-19.
//
#include <iostream>

using namespace std;

struct ListNode {
    int val;
    ListNode* next;
    explicit ListNode(int v) : val(v), next(nullptr) {}
    ListNode(int v, ListNode* n) : val(v), next(n) {}
};

class Solution {
public:
    using PLL = std::pair<ListNode*, ListNode*>;
    PLL reversePartial(ListNode* l, ListNode* r) {
        if (r == l) return std::pair<ListNode*, ListNode*>(l, r);
        ListNode* dummy = new ListNode(0, l);
        ListNode* cur = l;
        // 头插法倒序
        while (cur != r) {
            ListNode* tmp = cur->next;
            cur->next = dummy->next;
            dummy->next = cur;
            cur = tmp;
        }
        r->next = dummy->next;
        dummy->next = r;
        return std::pair<ListNode*, ListNode*>(dummy->next, l);
    }

    ListNode* reverseBetween(ListNode* head, int left, int right) {
        ListNode* dummy = new ListNode(0, head);
        int cnt = -1;
        ListNode* cur = dummy;
        ListNode* pre = dummy;
        ListNode* rnext;
        while (cnt < right) {
            ++cnt;
            if (cnt == left - 1) pre = cur;
            if (cnt == right) break;
            cur = cur->next;
        }
        rnext = cur->next;
        // cout << pre->next->val << " " << cur->val << endl;
        auto [nl, nr] = reversePartial(pre->next, cur);
        pre->next = nl;
        nr->next = rnext;
        return dummy->next;
    }
};

int main() {

    return 0;
}

