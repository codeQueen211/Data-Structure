//
//created by sara on 07/06/23
//




#include "recordsCompany.h"
RecordsCompany::RecordsCompany(){ //DONE
    records = nullptr;
    size = 0;
    // Initialize other member variables
    hash = HashTable(); // Assuming HashTable has a default constructor
    tree = AVLTree<int>(); // Assuming AVLTree has a default constructor 
    unionFind = new UnionFind(size); // Pass the desired value for 'size' to the UnionFind constructor
}

RecordsCompany:: ~RecordsCompany(){ //DONE
     delete[] records;
     delete unionFind; // Assuming unionFind is a pointer to the UnionFind object
    // Perform any other necessary cleanup
}

StatusType RecordsCompany::newMonth(int *records_stocks, int number_of_records){ //NOT DONE
    //TODO
     // Checking for invalid input
    if (number_of_records < 0) {
        return StatusType::INVALID_INPUT;
    }

    // Freeing existing records in the array
    if (records != nullptr) {
        free(records);
    }

    // Resetting expenses to 0 for all customers in the tree
    tree.updateExpenses(0);

    // Updating the size of the records array
    size = number_of_records;

    // Allocating memory for the records array
    records = (Records*)malloc(number_of_records * sizeof(Records));
    if (records == nullptr) {
        return StatusType::ALLOCATION_ERROR;
    }

    // Initializing each record with the stock amount
    for (int i = 0; i < number_of_records; i++) {
        records[i] = Records(i, records_stocks[i], 0);
    }

    return StatusType::SUCCESS;
    //if there are records in the array===> free
    //inorder over the tree and set expenses==0
    // set size to num/-of/-records
    //malloc records= malloc(number_of_records*sizeof(Records))
    //for(in records)===> malloc or a constructor of record
    //records[i].r_amount=recordsStock[i]
}

StatusType RecordsCompany::addCostumer(int c_id, int phone){ //DONE
    //TODO
    if ((c_id < 0)  || (phone < 0)) {
        return StatusType::INVALID_INPUT;
    }
    //check if this costumer is already in the hash tabel 
    if(hash.find(c_id) != nullptr){
        return StatusType::ALREADY_EXISTS;
    }
    //add the costumer to the hash tabel
   bool insertSuccess = hash.insert(c_id, phone, false);
    if (insertSuccess) {
        return StatusType::SUCCESS;
    }
    return StatusType::ALLOCATION_ERROR;

}

Output_t<int> RecordsCompany::getPhone(int c_id){ //DONE
    //TODO
     if ((c_id < 0)) {
        return StatusType::INVALID_INPUT;
    }
    //check if a costumer with c_id exists
    if (hash.find(c_id) == nullptr)
    {
        return StatusType::DOESNT_EXISTS;
    }
    return hash.getPhone(c_id); 
}

StatusType RecordsCompany::makeMember(int c_id){ //DONE
    //TODO
     if ((c_id < 0)) {
        return StatusType::INVALID_INPUT;
    }
    //check if a costumer with this id exists
    if (hash.find(c_id) == nullptr){
        return StatusType::DOESNT_EXISTS;
    }

    //check if the costumer is aleady a memeber 
    if(tree.find(c_id)){
        return StatusType::ALREADY_EXISTS; 
    }
    // add costumer to member tree and fix c_memebr to true
    bool insertSuccess = tree.insert(c_id,0);//????? idk if it's ok to add the mem with 0 expeness
    bool memberSuccess=hash.setMember(c_id);
    if (insertSuccess && memberSuccess) {
        return StatusType::SUCCESS;
    }
    return StatusType::ALLOCATION_ERROR;
    }

Output_t<bool> RecordsCompany::isMember(int c_id){ //DONE
    //TODO
     if ((c_id < 0)) {
        return StatusType::INVALID_INPUT;
    }
    //check if the costumer exists
    if (hash.find(c_id)== nullptr)
    {
        return StatusType::DOESNT_EXISTS;
    }
    //checking if the costumr is a memebr
    bool memberSuccess=hash.getMember(c_id);
    if (memberSuccess)
    {
       return StatusType::SUCCESS;
    }
}

StatusType RecordsCompany::buyRecord(int c_id, int r_id){ //DONE
    //TODO
   // Checking for invalid input
    if (r_id < 0 || c_id < 0) {
        return StatusType::INVALID_INPUT;
    }
    // Checking if the record ID is out of bounds
    if (hash.find(c_id)==nullptr && r_id>= size) {
        return StatusType::DOESNT_EXISTS;
    }
    // Adding the sale to the record in case not a memebr 
    // Updating the expenses to the customer if they are a member with t + 100, where t is the number of sales the record already had
    if (hash.getMember(c_id)==true) {
        int t = records[r_id].getNumSales();
        int newExpenses = t + 100;
        tree.findAndUpdate(c_id, newExpenses);
        // Updating the number of sales of the record
        records[r_id].set_r_sales(t + 1);
    }
    return StatusType::SUCCESS;
}

StatusType RecordsCompany::addPrize(int c_id1, int c_id2, double  amount){ //NOT DONE
    //TODO
     if ((c_id1 < 0) || (c_id2<c_id1) || (amount<0)) {
        return StatusType::INVALID_INPUT;
    }
    return StatusType::SUCCESS;
}

Output_t<double> RecordsCompany::getExpenses(int c_id){ //DONE
    //TODO
     if ((c_id < 0)) {
        return StatusType::INVALID_INPUT;
    }
    // Check if the customer exists 
    if (!hash.find(c_id)){
        return StatusType::DOESNT_EXISTS;
    }
    // Get the customer's expenses using the AVL tree
    return tree.findAndGet(c_id);
}

StatusType RecordsCompany::putOnTop(int r_id1, int r_id2){ //NOT DONE
    //TODO
     if ((r_id1 < 0) || (r_id2 <0)) {
        return StatusType::INVALID_INPUT;
    }
    //cheching if records exist
    if (r_id1>=size ||r_id2>=size)
    {
        return StatusType::DOESNT_EXISTS;
    }
    //check if r_id1 and r_id2 are already on top of each-other
    if (unionFind->find(r_id1)==unionFind->find(r_id2))
    {
        return StatusType::FAILURE;
    }else{
        //put r_id1 on top of r_id2
        unionFind->unite(r_id1,r_id2);
        //update the hight of all records in r_id1 to hight1=hight1+hight2
       int hight1= records[r_id1].get_r_amount();
       int hight2= records[r_id2].get_r_amount();
       records[r_id1].set_r_amount(hight1+hight2);
    }
}
 //the column is the index of the record in records array
 //the hight is the number of copies for that record
StatusType RecordsCompany::getPlace(int r_id, int *column, int *hight){ //NOT DONE
    //TODO
     if ((r_id < 0)) {
        return StatusType::INVALID_INPUT;
    }
     if ((column==nullptr) && (hight==nullptr)) {
        return StatusType::INVALID_INPUT;
    }
     //check if the record exists
    if (r_id>=size)
    {
        return StatusType::DOESNT_EXISTS;
    }
    //return the hgiht and the column of the r_id
    int index = findIndex(records, size, r_id);
    if (index == -1) {
        return StatusType::DOESNT_EXISTS;
    }
    // Set the column and height values
    *column = index;
    *hight = records[index].get_r_amount();
   
    return StatusType::SUCCESS;
}


