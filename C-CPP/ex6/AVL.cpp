//
// Created by ElinorB on 29/12/2021.
//
#include "AVL.h"

AVL::AVL (std::vector<std::pair<double, double>>& coordinates)
{
    for(auto pair:coordinates){
        Apartment cur(pair);
            insert (cur);
    }
}
AVL::iterator AVL::find (const Apartment &data)
{

    for(auto it = begin(); it != end(); ++it){
        if(*it == data){
            return it;
        }
    }
    return end();
}
AVL::const_iterator AVL::find (const Apartment &data) const
{
    for(auto it = cbegin(); it != end(); ++it){
            if(*it == data){
                    return it;
                }
        }
    return cend();
}
std::ostream &operator<< (std::ostream &os, const AVL &avl)
{
    for(auto node : avl){
        std::cout << node;
    }
    return os;
}
void AVL::insert (const Apartment &apartment)
{
    node* new_node = new node(apartment,
                              nullptr, nullptr, nullptr);
    node* ptr = root_;
    if(ptr == nullptr){
        root_ = new_node;
        return;
    }
    // while ptr has right or left:
    // if apartment<ptr : ptr = left; continue;
    // if apartment > ptr : ptr = right; continue;
    // when ptr has no children: insert node accordingly
    while(ptr != nullptr){
        if(apartment<ptr->data_){
            if(ptr->left_ == nullptr){
                ptr->left_ = new_node;
                new_node->parent_ = ptr;
                    break;
            }
            ptr = ptr->left_;
                continue;
        }
        else{
            if(ptr->right_ == nullptr){
                ptr->right_ = new_node;
                new_node->parent_ = ptr;
                break;
            }
            ptr = ptr->right_;
        }
    }
    node* temp = ptr;
    if(ptr->height_ < 2){
        while(ptr != nullptr){
            ptr->height_ = max(get_height (ptr->left_) ,
                               get_height (ptr->right_)) + 1;
            ptr = rotation_helper (ptr, apartment);
            temp = ptr;
            ptr = ptr->parent_;
        }
        root_ = temp;
    }

}
void AVL::erase (const Apartment &apartment)
{
    root_ = delete_node (root_, apartment);
}

AVL::node* AVL::rotation_helper (node *ptr, const Apartment &apartment)
{

    int balance = ptr->height_difference();
    // LL case
    if(balance > 1 && apartment<ptr->left_->data_){
            return right_rotate(ptr);
    }
    //rr case
    if(balance < -1 && apartment>ptr->right_->data_){
            return left_rotate(ptr);
    }
    //lr case
    if(balance > 1 && apartment > ptr->left_->data_){
            ptr->left_ = left_rotate(ptr->left_);
            return right_rotate(ptr);
    }
    //rl case
    if(balance < -1 && apartment < ptr->right_->data_){
            ptr->right_ = right_rotate (ptr->right_);
            return left_rotate(ptr);
    }
    return ptr;
}
AVL::node* right_rotate(AVL::node *y)
{
    AVL::node *x = y->left_;
    AVL::node *sub_tree = x->right_;
    AVL::node *parent = y->parent_;

    // Perform the rotation

    if(y->parent_ != nullptr){
        if(y == y->parent_->right_){
            y->parent_->right_ = x;
        }
        else{
            if(y == y->parent_->left_){
                y->parent_->left_ = x;
            }
        }
    }
    x->right_ = y;
    y->left_ = sub_tree;
    y->parent_ = x;
    x->parent_ = parent;
    if(sub_tree != nullptr){
        sub_tree->parent_ = y;
    }
    y->left_ = sub_tree;


    // Update the heights
    y->height_ = AVL::max(get_height(y->left_),
                    get_height(y->right_)) + 1;
    x->height_ = AVL::max(get_height(x->left_),
                    get_height((x->right_))) + 1;

    // Return the new root
    return x;
}
AVL::node *left_rotate (AVL::node *x)
{
    AVL::node *y = x->right_;
    AVL::node *sub_tree = y->left_;
    AVL::node *parent = x->parent_;

    // Perform the rotation
    if(x->parent_ != nullptr){
        if(x->parent_->right_ == x){
            x->parent_->right_ = y;
        }
        else{
            if(x->parent_->left_ == x){
                x->parent_->left_ = y;
            }
        }
    }

    y->left_ = x;
    x->right_ = sub_tree;
    if(sub_tree != nullptr){
        sub_tree->parent_ = x;
    }
    x->parent_ = y;
    y->parent_ = parent;

    // Update the heights
    x->height_ = AVL::max(get_height((x->left_)),
                    get_height((x->right_))) + 1;
    y->height_ = AVL::max(get_height((y->left_)),
                    get_height((y->right_))) + 1;

    // Return the new root
    return y;
}
AVL::node *AVL::delete_node (AVL::node *root, const Apartment &data)
{

    if (root == nullptr)
        {
            return root;
        }
    // If the data to be deleted is smaller
    // than the root's data, then it's
    // in the left subtree
    if (data < root->data_)
        {
            root->left_ = delete_node (root->left_, data);
        }

        // If the data to be deleted is greater
        // than the root's data, then its
        // in the right subtree
    else{
        if (data > root->data_){
            root->right_ = delete_node(root->right_,data);
        }
    }
        // if data is same as root's data, then
        // this is the node we want to delete
    if((data == root->data_)){
        if ((root->left_ == nullptr) ||(root->right_ == nullptr)){
                node *temp = (root->left_!=nullptr) ?
                             root->left_ :root->right_;

                // No child case
                if (temp == nullptr)
                    {
                        temp = root;
                        root = nullptr;
                    }
                else {// One child case
                    *root = *temp; // Copy the contents of
                    // the non-empty child
                }
                delete temp;
            }
        else
            {
                node* temp = root->right_;
                while (temp->left_ != nullptr)
                    {
                        temp = temp->left_;
                    }
                root->data_ = temp->data_;

                // Delete the inorder successor
                root->right_ = delete_node(root->right_,
                                           temp->data_);
            }
    }
    // If the tree had only one node
    // then return
    if (root == nullptr)
        {
            return root;
        }

    // update the height of the current node
    root->height_ = 1 + max(get_height((root->left_)),
                           get_height((root->right_)));

    int balance = root->height_difference();

    // LL Case
    if (balance > 1 &&
        (root->left_)->height_difference() >= 0)
        {
            return right_rotate (root);
        }

    // LR Case
    if (balance > 1 &&
        (root->left_)->height_difference() < 0)
        {
            root->left_ = left_rotate(root->left_);
            return right_rotate(root);
        }

    // RR Case
    if (balance < -1 &&
        (root->right_)->height_difference() <= 0)
        {
            return left_rotate (root);
        }

    // RL Case
    if (balance < -1 &&
        (root->right_)->height_difference() > 0)
        {
            root->right_ = right_rotate(root->right_);
            return left_rotate(root);
        }

    return root;
}

AVL& AVL::operator=(const AVL& other){
    if(this != &other){
            delete root_;
            root_ = other.root_;
        }
    return *this;
}


