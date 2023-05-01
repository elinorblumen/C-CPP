//
// Created by ElinorB on 29/12/2021.
//
#include "Apartment.h"
#include <math.h>
#define POWER2 2.0


Apartment::Apartment (const std::pair<double, double> &Coordinates):
_x(Coordinates.first),_y(Coordinates.second){}

double Apartment::get_x () const
{
    return _x;
}

double Apartment::get_y () const
{
    return _y;
}

bool Apartment::operator< (const Apartment &other) const
{

    double distance = sqrt (pow((this->get_x()-other.get_x()), POWER2) +
                                 pow ((this->get_y()-other.get_y()), POWER2));
    if (distance < EPSILON){
            return false;
    }
    double this_distance = sqrt (pow((this->get_x()-X_FEEL_BOX), POWER2) +
        pow ((this->get_y()-Y_FEEL_BOX), POWER2));
    double other_distance = sqrt (pow((other.get_x()-X_FEEL_BOX), POWER2) +
        pow ((other.get_y()-Y_FEEL_BOX), POWER2));

    return this_distance < other_distance;
}
bool Apartment::operator> (const Apartment &other) const
{
    double distance = sqrt (pow((this->get_x()-other.get_x()), POWER2) +
                            pow ((this->get_y()-other.get_y()), POWER2));
    if (distance < EPSILON){
            return false;
        }
    return !(*this < other);
}
bool Apartment::operator== (const Apartment &other) const
{
    double this_distance = sqrt (pow((this->get_x()-other.get_x()), POWER2) +
                                 pow ((this->get_y()-other.get_y()), POWER2));
    return this_distance < EPSILON;
}
std::ostream &operator<< (std::ostream &os, const Apartment &apartment)
{
    os <<  "(" << apartment.get_x() << ","
    << apartment.get_y() << ")" << std::endl;

    return os;
}
Apartment::Apartment (std::initializer_list<double>& in)
{
    if(in.size() == 2UL){
        std::initializer_list<double>::iterator it = in.begin();
        _x = *it++;
        _y = *it;
    }
}
