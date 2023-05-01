//
// Created by ElinorB on 29/12/2021.
//

#include "Stack.h"
#include "Apartment.h"

Stack::Stack (std::vector<std::pair<double, double>> coordinates):
_apartments()
{
    coordinates.shrink_to_fit();
    _apartments.reserve (coordinates.size());
    for (auto pair:coordinates){
        this->push(pair);
    }
}
Stack::Stack (std::initializer_list<Apartment> l)
{
    for(auto coordinates : l){
            push(coordinates);
        }
}
void Stack::push (const Apartment &apartment)
{
    _apartments.push_back (apartment);
}
void Stack::push (const std::pair<double,double>& pair)
{
    Apartment cur({pair.first, pair.second});
    _apartments.push_back (cur);
}
void Stack::pop ()
{
    if(_apartments.empty()){
        throw std::out_of_range ("Error: cannot pop an empty stack!");
    }
    _apartments.pop_back();
}
bool Stack::empty () const
{
    return _apartments.empty();
}
size_t Stack::size () const
{
    return _apartments.size();
}
Apartment &Stack::top ()
{
    if(_apartments.empty()){
        throw std::out_of_range ("Error: Stack is empty!");
    }
    return _apartments.back();
}
Apartment Stack::top () const
{
    if(_apartments.empty()){
        throw std::out_of_range ("Error: Stack is empty!");
    }
    return _apartments.back();
}


