//
// Created by Weaam on 12/01/2020.
//

#ifndef HW2DATASTRUCTURE_LISTNODE_H
#define HW2DATASTRUCTURE_LISTNODE_H

#include "HashData.h"
class ListNode {
    HashData data;
    ListNode *next;
    ListNode* previous;

public:
    ListNode(HashData data):data(data),next(NULL),previous(NULL){};
    ListNode &operator=(const ListNode &node){
        if(this == &node){
            return *this;
        }
        data = node.data;
        next = node.next;
        previous=node.previous;
        return *this;
    }

    ListNode(const ListNode &node):data(node.data),next(node.next),previous(node.previous){
        *next = *(node.next);
        *previous=*(node.previous);
    }

    ~ListNode()= default;

    ListNode* getNext(){
        return next;
    }

    ListNode* getPrevious(){
        return previous;
    }

    void setNext(ListNode* n){
        this->next=n;
    }

    void setPrevious(ListNode* pre){
        this->previous=pre;
    }

    HashData* getData(){
        return &data;
    }
    void setData(HashData h){
        data=h;
    }
};
#endif //HW2DATASTRUCTURE_LISTNODE_H
