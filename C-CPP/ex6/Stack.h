//
// Created by rotem on 07/10/2021.
//

#ifndef _STACK_H_
#define _STACK_H_
#include "Apartment.h"
#include <vector>
#include <initializer_list>
class Stack {

  std::vector<Apartment> _apartments;


 public:
  /**
   * The stack should support the stack_iterator (at least a forward
   * stack_iterator) so that the item at the top of the stack is the first item.
   */

  typedef typename std::reverse_iterator<std::vector<Apartment>::iterator> iterator;
  typedef const typename std::reverse_iterator<std::vector<Apartment>::const_iterator>
      const_iterator;
  iterator begin (){
      return _apartments.rbegin();
  }
  const_iterator begin () const{
      return _apartments.crbegin();
  }
  const_iterator cbegin () const{
      return _apartments.crbegin();
  }
  iterator end (){
      return _apartments.rend();
  }
  const_iterator end () const{
      return _apartments.crend();
  }
  const_iterator cend () const{
      return _apartments.crend();
  }
  /**
   * Default constructor, constructs an empty stack
   */
  Stack (){}
  /**
   * Constructor that gets an initialization list of apartments
   * and pushes them into the stack
   * @param l initialization list of apartments
   */
  Stack(std::initializer_list<Apartment> l);
  /**
   * Constructor that gets vector of pairs, and pushes them as apartments to
   * the stack, when the first pair is pushed first.
   * @param coordinates vector of pairs
   */
  Stack (std::vector<std::pair<double, double>> coordinates);
  /**
   * Pushes an apartment to the top of the stack
   * @param apartment
   */
  void push (const Apartment &apartment);
  /**
   * Pushes an apartment to the top of the stack
   * @param apartment
   */
  void push (const std::pair<double,double>&  pair);
  /**
   * A method that deletes the item from the top of the stack.
   * Calling this method with an empty stack will throw an out of
   * range exception with an informative message of your choice.
   */
  void pop ();
 /**
 *A method that returns true if the stack is empty and otherwise false.
 */
  bool empty () const;
  /**
  *A method that returns how many items are inside the stack.
  */
  size_t size () const;
  /**
   * Method that return the item from the top of the stack, but do not
   * remove it from it.
   * Calling this method with an empty stack will throw an out of
   * range exception with an informative message of your choice.
   * @return refernce to the top most item
   */
  Apartment& top ();
  /**
   * Method that return the item from the top of the stack, but do
   * not remove it from it.
   * Calling this method with an empty stack will throw an out of
   * range exception with an informative message of your choice.
   * @return copy to the top most item
   */
  Apartment top () const;

};

#endif //_STACK_H_
