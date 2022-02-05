#include <iostream>
#include "Citizen.h"
#include "exceptions.h"
using std::string;
using std::cout;
using std::endl;
using namespace mtm;
int mtm::Citizen::getId() const {
 return Id;
}
string Citizen::getFirstName() const
{
    return FirstName;
}
string Citizen::getLastName() const
{
    return LastName;
}

int Citizen::getBirthYear() const
{
    return BirthYear;
}
bool mtm::operator<(const Citizen& citizen1 ,const Citizen& citizen2)
{
    return citizen1.Id < citizen2.Id;
}
bool mtm::operator==(const Citizen& citizen1 ,const Citizen& citizen2) {
    return citizen1.Id == citizen2.Id ;
}
bool operator>(const Citizen& citizen1 ,const Citizen& citizen2)
{
    return citizen2 < citizen1 ;
}
bool operator<=(const Citizen& citizen1 ,const Citizen& citizen2)
{
    return !(citizen2 < citizen1);
}
bool operator>=(const Citizen& citizen1 ,const Citizen& citizen2 )
{
    return !(citizen1 < citizen2);
}

