#ifndef RECORDS_COMPANY_H
#define RECORDS_COMPANY_H

#include "utilesWet2.h"
#include "HashTable.h"
#include "unionFind.h"
#include "AVLTree.h"
#include "Records.h"


class RecordsCompany {
  private:
    // todo
    Records *records;
    int size; //the  size of the records array
    HashTable hash;
    UnionFind* unionFind; 
    AVLTree<int> tree;
    

  public:
    RecordsCompany();
    ~RecordsCompany();
    StatusType newMonth(int *records_stocks, int number_of_records);
    StatusType addCostumer(int c_id, int phone);
    Output_t<int> getPhone(int c_id);
    StatusType makeMember(int c_id);
    Output_t<bool> isMember(int c_id);
    StatusType buyRecord(int c_id, int r_id);
    StatusType addPrize(int c_id1, int c_id2, double  amount);
    Output_t<double> getExpenses(int c_id);
    StatusType putOnTop(int r_id1, int r_id2);
    StatusType getPlace(int r_id, int *column, int *hight);
    int findIndex(Records *records, int size, int r_id){
    for (int column = 0; column < size; column++) {
        if (records[column].get_r_id() == r_id) {
            return column;  // Return the index if the element is found
        }
    }
    return -1;  // Return -1 if the element is not found
}
};

#endif