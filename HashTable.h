

#ifndef HW2DATASTRUCTURE_HASHTABLE_H
#define HW2DATASTRUCTURE_HASHTABLE_H
#include <iostream>
#include "List.h"
#include "HashData.h"
#define INIT_SIZE 2

//static bool checkIfLectureExists(int arr[]);

/**
 * Description:             This is an implementation of the class HashTable That receive his data type and Hash
 *                          function as a template parameter
 * Template parameter:      Data - the type of data that we want to save in the Hash Table
 * Template Parameter:      fcn  - a function pointer to the Hash function That we will use on the input value and then
 *                               save them in the hash table accordingly
 * Feilds:                  array - The Dynamic array / List we use to save our data
 *                          size - the current size of the array
 *                          Hash - The Hash function received upon initialization
 *                          numOfElements - the current number O felements saved in the hash table
 *
 */

class HashTable {
    List **array;
    int size;
    int numOfElements;
    int c_id;
    //fcn Hash;

    /*
    * Description:         This is a private function for reHashing and resizing our dynamic array whe needed
    */
    void resize() {
        int new_size = 0;
        if (numOfElements == size) {
            new_size = 2 * size;
        } else if (numOfElements == size /4 ) {
            if (size >= 4)
                new_size = size / 2;
            else
                return;
        }
        //Hash = fcn(new_size);
        List** new_array = new List*[new_size];
        for(int i=0;i<new_size;i++) {
            new_array[i] = new List(0);
        };
        ListNode* curr;
        for(int i=0;i<size;i++) {
            curr=array[i]->getHead();
            while (curr!=NULL)
            {
                ListNode* node= new ListNode(*(curr->getData()));
                new_array[(curr->getData()->get_c_id())%new_size]->listAdd(node);//TODO change new_size with size
                curr=curr->getNext();
            }
            delete array[i];
        }
        delete[] array;
        array = new_array;
        size = new_size;
    }


public:
    /**
     * Description:         This is the constructor for class HashTable
     * Parameters:          size - an integer which represents the initial size of the hashtable
     * Return Values:       An instance for class HashTable
     */
    explicit HashTable(int size = INIT_SIZE):array(new List *[size]), size(size), numOfElements(0) {
        for (int i = 0; i < size; i++) {
            array[i] = new List(0);
        }
    }

    /*
     * Description:        The destructor for the HashTable class
     */
    ~HashTable() {
        for (int i = 0; i < size; i++) {
            delete array[i];
        }
        delete[] array;
    }

    /*
     * Description:         This method's purpose is to insert a new element to the Hash Table
     * Parameters:          data - the data we want to add to the hash table
     * Return Values:       True - if the insertion went as planned
     *                      False - elsewise ( for example if an item is inserted twice)
     */
    bool insert(int c_id , int c_phone, bool c_member) {
        if (find(c_id)) {
            return false;
        }
        HashData hashData=HashData(c_id, c_phone, c_member);
        ListNode *node = new ListNode(hashData);
        if(array[(c_id) % size]->getSize() == 0){
            numOfElements++;
        }
        if (numOfElements == size ) {
            resize();
        }
        array[(c_id) % size]->listAdd(node);
        //array[(serverId)%size]->listAdd(node);
        ///TODO:RETRIEVE
        /*if (++numOfElements == size) {
            resize();
        }*/
        return true;
    }

    /*
     * Description:         This method is intended to search for an element in the HashTable
     * Parameters:          data - the item we're searching for in the HashTable
     * Return Values:       True - if the data is in the HashTable
     *                      False - elsewise
     */
    ListNode* find(int c_id) {
        List *dataList = array[(c_id) % size];
        ListNode *curr = dataList->getHead();
        while (curr != nullptr) {
            if (curr->getData()->get_c_id() == c_id) {
                return curr;
            }
            curr = curr->getNext();
        }
        return nullptr;
    }

    bool remove(int c_id) {
        List *dataList = array[(c_id) % size];
        ListNode *curr = dataList->getHead();
        while (curr != NULL) {
            if (curr->getData()->get_c_id() == c_id) {
                dataList->listRemove(curr);
               if(array[(c_id) % size]->getSize() == 0){
                   numOfElements--;
               }
                if (numOfElements*4==size) {
                    resize();
                }
                return true;
            }
            else{
                curr=curr->getNext();
            }
        }
        return false;
    }

    int getHashTableSize() {
        return size;
    }
    int getPhone(int c_id) {
        ListNode* node = find(c_id);
        if (node != nullptr) {
            return node->getData()->get_c_phone();
        }
        return -1; 
    }
    bool getMember(int c_id) {
        ListNode* node = find(c_id);
        if (node != nullptr) {
            return node->getData()->get_c_member();
        }
        return -1; 
    }
    bool setMember(int c_id){
        ListNode* node = find(c_id);
        if (node != nullptr) {
            node->getData()->set_c_member(true);
       }
       return -1;
     }
         

    
};




#endif //HW2DATASTRUCTURE_HASHTABLE_H
