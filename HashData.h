

#ifndef HW2DATASTRUCTURE_HASHDATA_H
#define HW2DATASTRUCTURE_HASHDATA_H


class HashData{
    int c_id;
    int c_phone;
    bool c_member; 
//datacenter=c_phone, serverid=c_id, traffic=c_member

public:
    explicit HashData(int c_id,int c_phone,bool c_member): c_id(c_id),c_phone(c_phone)
            ,c_member(c_member){
    }
    /*~HashData(){
        delete[] hours;
        delete[] groups;
        delete[] students;
    }*/
    void set_c_phone(int p){
        c_phone=p;
    }
    void set_c_member(int m){
        c_member=m;
    }
    void set_c_id(int c){
        c_id=c;
    }
    int get_c_phone(){
        return c_phone;
    }
    int get_c_member(){
        return c_member;
    }
    int get_c_id(){
        return c_id;
    }
    HashData &operator=(const HashData &data){
        if(this == &data){
            return *this;
        }
        // for(int i=1;i<HOURS;i++)
        // {
        //     hours[i]=data.hours[i];
        //     groups[i]=data.groups[i];
        //     students[i]=data.students[i];
        // }
       c_id = data.c_id;
        // roomID=data.roomID;
        return *this;
    }

    /* HashData(const HashData &data):hours(new int[HOURS]),groups(new int[HOURS]),students(new int[HOURS]),roomID(data.roomID){
         for(int i=1;i<HOURS;i++)
         {
             hours[i]=data.hours[i];
             groups[i]=data.groups[i];
             students[i]=data.students[i];
         }
     }*/

    /*int* getHoursArr(){
        return hours;
    }

    void setCourseHour(int course,int hour){
        hours[hour]=course;
    }

    int* getGroupsArr(){
        return groups;
    }

    void setGroupHour(int group,int hour){
        groups[hour]=group;
    }

    int* getStudentsArr(){
        return students;
    }

    void setStudentsHour(int studentsNum,int hour){
        students[hour]=studentsNum;
    }


    int getRoomId(){
        return roomID;
    }*/
  
};

#endif //HW2DATASTRUCTURE_HASHDATA_H
