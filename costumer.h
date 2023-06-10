//
// created by sara on 31/5/23
//

class costumer
{
private:
   int c_id;
   int c_phone;
   bool c_member; 

public:
    costumer(int c_id , int c_phone, bool c_member);
    ~costumer()= default;
    bool operator < (const costumer& other_costumer) const;
    bool operator > (const costumer& other_costumer) const;
    bool operator <= (const costumer& other_costumer) const;
    bool operator >= (const costumer& other_costumer) const;
    bool operator == (const costumer& other_costumer) const;
    bool operator != (const costumer& other_costumer) const;
    costumer* operator &(){
        return this;
    }
    void set_c_member(bool isMem){
        c_member = isMem;
    }
    bool get_c_member(){
        return c_member;
    }
    void set_c_phone(int phone){
        c_phone = phone;
    }
    int get_c_phone(){
        return c_phone;
    }
    void set_c_id(int id){
        c_id = id;
    }
    int get_c_id(){
        return c_id;
    }
};

