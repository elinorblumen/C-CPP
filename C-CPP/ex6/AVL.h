//
// Created by rotem on 07/10/2021.
//

#ifndef _AVL_H_
#define _AVL_H_
#define INITIALIZE_SIZE 1
#include <vector>
#include "Apartment.h"
#include <iostream>
#include <initializer_list>
#include <math.h>

class AVL {
 public:

  /**
   * To manage the tree nodes, we use a nested struct. This struct contains the
   * apartment corresponding to the node, the left son and the right son of the
   * node, both of them node type themselves.
   */
  struct node {
      /**
       * Constructor - It can be expanded
       * @param data the corresponding apartment object
       * @param left child
       * @param right child
       */
      node (Apartment data, node *left, node *right, node *parent)
          : data_ (data), left_ (left), right_ (right), parent_(parent),height_(INITIALIZE_SIZE)
      {}
      ~node(){
          delete right_;
          delete left_;
      }
      /**
       *
       * @return the left child of this node
       */
      node *get_left () const
      {
        return left_;
      }
      /**
       *
       * @return the right child of this node
       */
      node *get_right () const
      {
        return right_;
      }
      /**
     *
     * @return the const reference apartment of this node
     */
      const Apartment &get_data () const
      {
        return data_;
      }
      friend int get_height(const node* node){
          if (node == nullptr){
              return 0;
          }
          return node->height_;
      }
      int height_difference()const {
          return get_height(left_) - get_height(right_);
      }

      Apartment data_;
      node *left_, *right_, *parent_;
      int height_;

  };
  /**
   * Constructor. Constructs an empty AVL tree
   */
  AVL ():root_(nullptr){}

  /**
   * Copy constructor
   * @param other
   */
//  AVL (const AVL &other):root_(other.root_){}
  AVL (node* node):root_(node){}
  /**
   * A constructor that receives a vector of a pairs. Each such pair is an
   * apartment that will inserted to the tree. Insert can be used to insert the
   * apartments a vector of a pairs
   * @param coordinates
   */
  AVL (std::vector<std::pair<double, double>>& coordinates);

  ~AVL(){
      delete root_;
  }
  /**
   *
   * @return the root node of this tree
   */
  node *get_root () const{
    return root_;
  }
  /**
   * The function inserts the new apartment into the tree so that it maintains
   * the legality of the tree.
   * @param apartment
   */
  void insert (const Apartment &apartment);
  /**
   * The function deletes the apartment from the tree (if it is in that tree)
   * so that it maintains
   * the legality of the tree.
   * @param apartment
   */
  void erase (const Apartment &apartment);
  friend node* right_rotate(AVL::node *y);
  friend node* left_rotate (AVL::node *y);
  node* rotation_helper(node* ptr, const Apartment &apartment);
  node* delete_node(node* root, const Apartment& data);

  //************************//
  // Iterators //
  // ***********************//
  class ConstIterator;
  /**
   * Iterator class
   */
  class Iterator{
    node* cur_;
   public:
    typedef Apartment value_type;
    typedef Apartment& reference;
    typedef Apartment* pointer;
    typedef std::forward_iterator_tag iterator_category;
    typedef std::ptrdiff_t difference_type;

    friend class ConstIterator;
    /**
     * Constructor of iterator
     * @param cur node to construct from
     */
    Iterator(node *cur): cur_(cur){}
    /**
     * operator ++ in its pre implementation
     * @param cur current node in iterator
     */
    Iterator& operator++(){

        // 1. if node has left or otherwise right- return it
        if(cur_ != nullptr){
            if(cur_->left_ != nullptr){
                cur_ = cur_->left_;
                    return *this;
            }
            if(cur_->right_ != nullptr){
                cur_ = cur_->right_;
                    return *this;
            }
            //2. else, search for the first predecessor that has a right
            // that is different from the current node and return it
            // if there isn't one return null ptr

            node *ptr = cur_->parent_;
            if(ptr == nullptr){
                cur_ = ptr;
                return *this;
            }
            while(ptr->right_ != cur_ && ptr->right_ == nullptr){
                cur_ = ptr;
                ptr = ptr->parent_;
            }
            if(ptr->right_ != cur_){
                cur_ = ptr->right_;
                return *this;
            }
            while(ptr != nullptr && (ptr->right_ == cur_ || ptr->right_ == nullptr)){
                cur_ = ptr;
                ptr = ptr->parent_;
            }
            if(ptr != nullptr && ptr->right_ != cur_){
                cur_ = ptr->right_;
                    return *this;
            }
            while(cur_ != nullptr){
                ptr = cur_;
                cur_ = cur_->right_;
            }
                return *this;
        }
        return *this;
    }
    /**
     * operator ++ in its post implementation
     * @param cur current node in iterator
     */
    Iterator operator++(int){
        Iterator temp = *this;
        // 1. if node has left or otherwise right- return it
        if(cur_ != nullptr){
            if(cur_->left_ != nullptr){
                    cur_ = cur_->left_;
                    return temp;
                }
            if(cur_->right_ != nullptr){
                    cur_ = cur_->right_;
                    return temp;
                }
            //2. else, search for the first predecessor that has a right
            // that is different from the current node and return it
            // if there isn't one return null ptr

            node *ptr = cur_->parent_;
            if(ptr == nullptr){
                    cur_ = ptr;
                    return temp;
                }
            while(ptr->right_ != cur_ && ptr->right_ == nullptr){
                    cur_ = ptr;
                    ptr = ptr->parent_;
                }
            if(ptr->right_ != cur_){
                    cur_ = ptr->right_;
                    return temp;
                }
            while(ptr != nullptr && (ptr->right_ == cur_ || ptr->right_ == nullptr)){
                    cur_ = ptr;
                    ptr = ptr->parent_;
                }
            if(ptr != nullptr && ptr->right_ != cur_){
                    cur_ = ptr->right_;
                    return temp;
                }
            while(cur_ != nullptr){
                    ptr = cur_;
                    cur_ = cur_->right_;
                }
            return temp;
        }
        return temp;
    }
    /**
     * operator ==
     * @param rhs right hand side of equality
     * @return true if equal false otherwise
     */
    bool operator== (const Iterator &rhs) const
    {
        return cur_ == rhs.cur_;
    }
    /**
     * operator !=
     * @param rhs right hand side of inequality
     * @return true if not equal false otherwise
     */
    bool operator!= (const Iterator &rhs) const
    {
        return !(rhs == *this);
    }
    /**
     * operator *
     * @return the apartment in current node
     */
    reference operator*(){
        return cur_->data_;
    }
    /**
     * operator ->
     * @return the apartment in current node
     */
    pointer operator->(){
        return &cur_->data_;
    }
    /**
     * helper function that returns the current node pointer
     * @return current node pointer
     */
    node* get_cur(){
        return cur_;
    }
  };
  /**
   * class const iterator
   */
  class ConstIterator {
    node *cur_;
   public:
    typedef const Apartment value_type;
    typedef const Apartment& reference;
    typedef const Apartment* pointer;
    typedef std::forward_iterator_tag iterator_category;
    typedef std::ptrdiff_t difference_type;
    /**
     * Constructor of iterator
     * @param cur node to construct from
     */
    ConstIterator(node *cur):cur_(cur){}
    ConstIterator(const Iterator& it): cur_(it.cur_){}
    /**
     * operator ++ in its pre implementation
     * @param cur current node in iterator
     */
    ConstIterator operator++ ()
    {
        // 1. if node has left or otherwise right- return it
        if(cur_ != nullptr){
            if(cur_->left_ != nullptr){
                    cur_ = cur_->left_;
                    return *this;
                }
            if(cur_->right_ != nullptr){
                    cur_ = cur_->right_;
                    return *this;
                }
            //2. else, search for the first predecessor that has a right
            // that is different from the current node and return it
            // if there isn't one return null ptr

            node *ptr = cur_->parent_;
            if(ptr == nullptr){
                    cur_ = ptr;
                    return *this;
                }
            while(ptr->right_ != cur_ && ptr->right_ == nullptr){
                    cur_ = ptr;
                    ptr = ptr->parent_;
                }
            if(ptr->right_ != cur_){
                    cur_ = ptr->right_;
                    return *this;
                }
            while(ptr != nullptr && (ptr->right_ == cur_ || ptr->right_ == nullptr)){
                    cur_ = ptr;
                    ptr = ptr->parent_;
                }
            if(ptr != nullptr && ptr->right_ != cur_){
                    cur_ = ptr->right_;
                    return *this;
                }
            while(cur_ != nullptr){
                    ptr = cur_;
                    cur_ = cur_->right_;
                }
            return *this;
        }
        return *this;
    }
    /**
     * operator ++ in its post implementation
     * @param cur current node in iterator
     */
    ConstIterator operator++ (int)
    {
        ConstIterator temp = *this;
        // 1. if node has left or otherwise right- return it
        if(cur_ != nullptr){
            if(cur_->left_ != nullptr){
                    cur_ = cur_->left_;
                    return temp;
                }
            if(cur_->right_ != nullptr){
                    cur_ = cur_->right_;
                    return temp;
                }
            //2. else, search for the first predecessor that has a right
            // that is different from the current node and return it
            // if there isn't one return null ptr

            node *ptr = cur_->parent_;
            if(ptr == nullptr){
                    cur_ = ptr;
                    return temp;
                }
            while(ptr->right_ != cur_ && ptr->right_ == nullptr){
                    cur_ = ptr;
                    ptr = ptr->parent_;
                }
            if(ptr->right_ != cur_){
                    cur_ = ptr->right_;
                    return temp;
                }
            while(ptr != nullptr && (ptr->right_ == cur_ || ptr->right_ == nullptr)){
                    cur_ = ptr;
                    ptr = ptr->parent_;
                }
            if(ptr != nullptr && ptr->right_ != cur_){
                    cur_ = ptr->right_;
                    return temp;
                }
            while(cur_ != nullptr){
                    ptr = cur_;
                    cur_ = cur_->right_;
                }
            return temp;
        }
        return temp;
    }
    /**
     * operator ==
     * @param rhs right hand side of equality
     * @return true if equal false otherwise
     */
    bool operator== (const ConstIterator &rhs) const
    {
        return cur_ == rhs.cur_;
    }
    /**
     * operator !=
     * @param rhs right hand side of inequality
     * @return true if not equal false otherwise
     */
    bool operator!= (const ConstIterator &rhs) const
    {
        return !(rhs == *this);
    }
    /**
     * operator *
     * @return the apartment in current node
     */
    value_type operator* () const
    {
        return cur_->data_;
    }
    /**
     * operator ->
     * @return the apartment in current node
     */
    pointer operator-> () const
    {
        return &cur_->data_;
    }
    /**
     * helper function that returns the current node pointer
     * @return current node pointer
     */
    node* get_cur(){
        return cur_;
    }
  };
  using iterator = Iterator; // same as typedef Iterator iterator;
  using const_iterator = ConstIterator;

  iterator begin (){
      return iterator(root_);
  }
  const_iterator begin () const{
      return const_iterator(root_);
  }
  const_iterator cbegin () const{
      return const_iterator(root_);
  }
  iterator end (){
      return iterator(nullptr);
  }
  const_iterator end () const{
      return const_iterator(nullptr);
  }
  const_iterator cend () const{
      return const_iterator(nullptr);
  }
  /**
   * The function returns an iterator to the item that corresponds to the item
   * we were looking for. If there is no such member, returns end ().
   * @param data apartment to search
   * @return iterator to the item that corresponds to the item
   * we were looking for. If there is no such member, returns end ().
   */
  iterator find (const Apartment &data);
  /**
   * The function returns an iterator to the item that corresponds to the item
   * we were looking for. If there is no such member, returns end ().
   * @param data apartment to search
   * @return iterator to the item that corresponds to the item
   * we were looking for. If there is no such member, returns end ().
   */
  const_iterator find (const Apartment &data) const;
  /**
   * Insertion operator, prints the apartment in the tree in preorder traversal.
   * Each apartmnet will be printed in the format: (x,y)\n
   * @param os reference to std::ostream
   * @param avl tree
   * @return os reference to std::ostream
   */
  friend std::ostream &operator<< (std::ostream &os, const AVL &avl);
  /**
   * assignment operator
   * @param other AVL to assign from
   * @return assigned AVL reference
   */
  AVL& operator=(const AVL& other);
  /**
   * operator equal
   * @param other other AVL to check if equal to
   * @return true if equal false otherwise
   */
  bool operator==(const AVL& other){return this == &other;}
  /**
   * static helper function that checks which
   * of two ints is maximal
   * @param a first int
   * @param b second int
   * @return  max of two ints
   */
  static int max(int a, int b){return (a > b)? a : b;}

 private:
  node *root_{};
};


#endif //_AVL_H_
