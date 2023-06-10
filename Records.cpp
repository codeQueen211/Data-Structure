//
// created by sara on 5/6/23
//
#include "Records.h"

Records::Records(int r_id , int r_amount, int r_sales): r_id(r_id),r_amount(r_amount),r_sales(r_sales)
{
}

Records::~Records()
{
}

bool Records::operator < (const Records &anotherRecords) const {
    return r_id < anotherRecords.r_id;
}
bool Records::operator > (const Records &anotherRecords) const {
    return r_id < anotherRecords.r_id;
}
bool Records::operator <= (const Records &anotherRecords) const {
    return r_id < anotherRecords.r_id;
}
bool Records::operator >= (const Records &anotherRecords) const {
    return r_id < anotherRecords.r_id;
}
bool Records::operator == (const Records &anotherRecords) const {
    return r_id < anotherRecords.r_id;
}
bool Records::operator != (const Records &anotherRecords) const {
    return r_id < anotherRecords.r_id;
}