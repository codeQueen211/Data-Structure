//
// created by sara on 5/6/23
//
#include "costumer.h"

costumer::costumer(int c_id , int c_phone, bool c_member): c_id(c_id), c_phone(c_phone),c_member(c_member)
{
}

costumer::~costumer()
{
}

bool costumer::operator < (const costumer &other_costumer) const {
    return c_id < other_costumer.c_id;
}

bool costumer::operator > (const costumer &other_costumer) const {
    return c_id > other_costumer.c_id;
}

bool costumer::operator >= (const costumer &other_costumer) const {
    return c_id > other_costumer.c_id;
}

bool costumer::operator <= (const costumer &other_costumer) const {
    return c_id > other_costumer.c_id;
}

bool costumer::operator == (const costumer &other_costumer) const {
    return c_id > other_costumer.c_id;
}
bool costumer::operator != (const costumer &other_costumer) const {
    return c_id > other_costumer.c_id;
}
