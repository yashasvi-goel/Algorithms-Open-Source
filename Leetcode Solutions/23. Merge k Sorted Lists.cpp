#include<bits/stdc++.h>
using namespace std;
struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};
class Solution {
    private:
        struct compare{
            bool operator()(ListNode* a, ListNode* b){
                return a->val>b->val;
            };
        };
    public:
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        
        if(lists.size()==0)
            return NULL;
        
        priority_queue<ListNode*,vector<ListNode*>,compare> q;
        
        int i=0,j,k=lists.size();
        // cout<<k<<endl;
        while(k--){
                if(lists[i]==NULL){
                    i++;
                    continue;
                }
                q.push(lists[i++]);
        }
        
        ListNode* ans=NULL,*temp;
        // cout<<q.top()->val<<endl;
        ans=new ListNode(0);
        temp=ans;
        while(!q.empty()){
            if(q.top()==NULL){
                q.pop();
                continue;
            }
            temp->next=new ListNode((q.top())->val);
            if(q.top()->next!=NULL)
                q.push(q.top()->next);
            q.pop();
            temp=temp->next;
        }
        return ans->next;
    }
};