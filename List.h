//
// Created by Weaam on 12/01/2020.
//

#ifndef HW2DATASTRUCTURE_LIST_H
#define HW2DATASTRUCTURE_LIST_H

#include "ListNode.h"
class List{
    int size;
    ListNode* head;

public:
    List(int size):size(size),head(NULL){};
    List(const List &list):size(list.size),head(list.head){};
    List &operator=(const List &list){
        if(this == &list){
            return *this;
        }
        size=list.size;
        head=list.head;
        return *this;
    }

    static void deleteList(ListNode* node){
        if(!node){
            return;
        }
        deleteList(node->getNext());
        delete node;
    }

    ~List(){
        deleteList(head);
    }

    ListNode* getHead(){
        return head;
    }

    int getSize(){
        return size;
    }

    void listAdd(ListNode* node){
        if( head != NULL ){                     // changed from !head to head!=NULL
            node->setNext(head);
            head->setPrevious(node);
        }
        head=node;
        size++;
    }

    void listRemove(ListNode* node){
        if(node->getPrevious() != NULL){
            node->getPrevious()->setNext(node->getNext());
        }
        else{
            head=node->getNext();
        }
        if (node->getNext() != NULL){                     // added the "if" check if at the previous line it is needed too
            node->getNext()->setPrevious(node->getPrevious());
        }
        else{
            node->setPrevious(NULL);
        }
        delete node;
        size--;
    }
};

#endif //HW2DATASTRUCTURE_LIST_H
