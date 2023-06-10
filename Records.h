//
// created by sara on 31/5/23
//

class Records
{
private:
   int r_id; //records id
   int r_amount; //the number of copies each record hash
   int r_sales; //the number of sales each record has
public:
    Records(int r_id , int r_amount, int r_sales);
    ~Records()=default;
    bool operator < (const Records& anotherRecords) const;
    bool operator > (const Records& anothercostumer) const;
    bool operator <= (const Records& anothercostumer) const;
    bool operator >= (const Records& anothercostumer) const;
    bool operator == (const Records& anothercostumer) const;
    bool operator != (const Records& anothercostumer) const;
    Records* operator &(){
        return this;
    }
    void set_r_id(int id){
        r_id = id;
    }
    int get_r_id(){
        return r_id;
    }
    void set_r_amount(int amount){
        r_amount = amount;
    }
    int get_r_amount(){
        return r_amount;
    }
    void set_r_sales(int sales){
        r_sales = sales;
    }
    void update_r_sales(){
        r_sales++;
    }
    int get_r_sales(){
        return r_sales;
    }
     int getNumSales() const {
        return r_sales;
    }

};


