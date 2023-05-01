//
// Created by ElinorB on 30/12/2021.
//

#include "MesureTimeHelper.h"
#include "Apartment.h"
#include "AVL.h"
#include "Stack.h"
#include "Find.h"
#include <vector>
#include <chrono>
#include <unordered_set>


#define X_DATA 31.81428051893798
#define Y_DATA 35.18577781093502
//typename enable_if<__is_duration<_ToDuration>::value, _ToDuration>::type
//std::chrono::duration_cast<std::chrono::nanoseconds>(t2-t1).count();

void bonus(){

    Apartment x({X_DATA, Y_DATA});

    std::vector<std::pair<double, double>> vector = xy_from_file (
        "/Users/elinorblumenfeld/Dropbox/2021:2022/C-CPP/CPP/ex6/apartments100.txt");
    std::vector<std::pair<double, double>> vector1000 = xy_from_file (
        "/Users/elinorblumenfeld/Dropbox/2021:2022/C-CPP/CPP/ex6/apartments1000.txt");
    std::vector<std::pair<double, double>> vector10000 = xy_from_file (
        "/Users/elinorblumenfeld/Dropbox/2021:2022/C-CPP/CPP/ex6/apartments10000.txt");

    //***********************************//
    //***********************************//
    //Stack//
    //***********************************//
    //***********************************//
    std::cout << "checking time for: 100 apartments insert, Stack: " << std::endl;
    auto t1 = std::chrono::high_resolution_clock::now();
    Stack stack(vector);
    auto t2 = std::chrono::high_resolution_clock::now();
    std::cout << "checking time for: 100 apartments insert, Stack: time is:  ";
    std::cout << std::chrono::duration_cast<std::chrono::nanoseconds>(t2-t1).count() << std::endl;
    std::cout << std::endl;


    std::cout << "checking time for: 1000 apartments insert, Stack: " << std::endl;
    auto t3 = std::chrono::high_resolution_clock::now();
    Stack stack2(vector1000);
    auto t4 = std::chrono::high_resolution_clock::now();
    std::cout << "checking time for: 1000 apartments insert, Stack: time is:  ";
    std::cout << std::chrono::duration_cast<std::chrono::nanoseconds>(t4-t3).count() << std::endl;
    std::cout << std::endl;


    std::cout << "checking time for: 10000 apartments insert, Stack: " << std::endl;
    auto t5 = std::chrono::high_resolution_clock::now();
    Stack stack3(vector10000);
    auto t6 = std::chrono::high_resolution_clock::now();
    std::cout << "checking time for: 10000 apartments insert, Stack: time is:  ";
    std::cout << std::chrono::duration_cast<std::chrono::nanoseconds>(t4-t3).count() << std::endl;
    std::cout << std::endl;


    std::cout << "checking time for: 100 apartments find, Stack: " << std::endl;
    auto t7 = std::chrono::high_resolution_clock::now();
    (void)std::find(stack.begin(), stack.end(), x);
    auto t8 = std::chrono::high_resolution_clock::now();
    std::cout << "checking time for: 100 apartments find, Stack: time is:  ";
    std::cout << std::chrono::duration_cast<std::chrono::nanoseconds>(t8-t7).count() << std::endl;
    std::cout << std::endl;


    std::cout << "checking time for: 1000 apartments find, Stack: " << std::endl;
    auto t9 = std::chrono::high_resolution_clock::now();
    (void)std::find(stack2.begin(), stack2.end(), x);
    auto t10 = std::chrono::high_resolution_clock::now();
    std::cout << "checking time for: 1000 apartments find, Stack: time is:  ";
    std::cout << std::chrono::duration_cast<std::chrono::nanoseconds>(t10-t9).count() << std::endl;
    std::cout << std::endl;


    std::cout << "checking time for: 10000 apartments find, Stack: " << std::endl;
    auto t11 = std::chrono::high_resolution_clock::now();
    (void)std::find(stack3.begin(), stack3.end(), x);
    auto t12 = std::chrono::high_resolution_clock::now();
    std::cout << "checking time for: 10000 apartments find, Stack: time is:  ";
    std::cout << std::chrono::duration_cast<std::chrono::nanoseconds>(t12-t11).count() << std::endl;
    std::cout << std::endl;


    //***********************************//
    //***********************************//
    //AVL tree//
    //***********************************//
    //***********************************//

    std::cout << "checking time for: 100 apartments insert, AVL tree: " << std::endl;
    auto t13 = std::chrono::high_resolution_clock::now();
    AVL tree(vector);
    auto t14 = std::chrono::high_resolution_clock::now();
    std::cout << "checking time for: 100 apartments insert, AVL tree: time is:  ";
    std::cout << std::chrono::duration_cast<std::chrono::nanoseconds>(t2-t1).count() << std::endl;
    std::cout << std::endl;


    std::cout << "checking time for: 1000 apartments insert, AVL tree: " << std::endl;
    auto t15 = std::chrono::high_resolution_clock::now();
    AVL tree2(vector1000);
    auto t16 = std::chrono::high_resolution_clock::now();
    std::cout << "checking time for: 1000 apartments insert, AVL tree: time is:  ";
    std::cout << std::chrono::duration_cast<std::chrono::nanoseconds>(t4-t3).count() << std::endl;
    std::cout << std::endl;


    std::cout << "checking time for: 10000 apartments insert, AVL tree: " << std::endl;
    auto t17 = std::chrono::high_resolution_clock::now();
    AVL tree3(vector10000);
    auto t18 = std::chrono::high_resolution_clock::now();
    std::cout << "checking time for: 10000 apartments insert, AVL tree: time is:  ";
    std::cout << std::chrono::duration_cast<std::chrono::nanoseconds>(t4-t3).count() << std::endl;
    std::cout << std::endl;

    //***********************************//
    //STL find//
    //***********************************//
    std::cout << "checking time for: 100 apartments STL find, AVL tree: " << std::endl;
    auto t19 = std::chrono::high_resolution_clock::now();
    (void)std::find(tree.begin(), tree.end(), x);
    auto t20 = std::chrono::high_resolution_clock::now();
    std::cout << "checking time for: 100 apartments STL find, AVL tree: time is:  ";
    std::cout << std::chrono::duration_cast<std::chrono::nanoseconds>(t8-t7).count() << std::endl;
    std::cout << std::endl;


    std::cout << "checking time for: 1000 apartments STL find, AVL tree: " << std::endl;
    auto t21 = std::chrono::high_resolution_clock::now();
    (void)std::find(tree2.begin(), tree2.end(), x);
    auto t22 = std::chrono::high_resolution_clock::now();
    std::cout << "checking time for: 1000 apartments STL find, AVL tree: time is:  ";
    std::cout << std::chrono::duration_cast<std::chrono::nanoseconds>(t10-t9).count() << std::endl;
    std::cout << std::endl;


    std::cout << "checking time for: 10000 apartments STL find, AVL tree: " << std::endl;
    auto t23 = std::chrono::high_resolution_clock::now();
    (void)std::find(tree3.begin(), tree3.end(), x);
    auto t24 = std::chrono::high_resolution_clock::now();
    std::cout << "checking time for: 10000 apartments STL find, AVL tree: time is:  ";
    std::cout << std::chrono::duration_cast<std::chrono::nanoseconds>(t12-t11).count() << std::endl;
    std::cout << std::endl;


    //***********************************//
    //AVL find//
    //***********************************//
    std::cout << "checking time for: 100 apartments AVL find, AVL tree: " << std::endl;
    auto t25 = std::chrono::high_resolution_clock::now();
    (void)tree.find (x);
    auto t26 = std::chrono::high_resolution_clock::now();
    std::cout << "checking time for: 100 apartments AVL find, AVL tree: time is:  ";
    std::cout << std::chrono::duration_cast<std::chrono::nanoseconds>(t26-t25).count() << std::endl;
    std::cout << std::endl;


    std::cout << "checking time for: 1000 apartments AVL find, AVL tree: " << std::endl;
    auto t27 = std::chrono::high_resolution_clock::now();
    (void)tree2.find (x);
    auto t28 = std::chrono::high_resolution_clock::now();
    std::cout << "checking time for: 1000 apartments AVL find, AVL tree: time is:  ";
    std::cout << std::chrono::duration_cast<std::chrono::nanoseconds>(t28-t27).count() << std::endl;
    std::cout << std::endl;


    std::cout << "checking time for: 10000 apartments AVL find, AVL tree: " << std::endl;
    auto t29 = std::chrono::high_resolution_clock::now();
    (void)tree3.find (x);
    auto t30 = std::chrono::high_resolution_clock::now();
    std::cout << "checking time for: 10000 apartments AVL find, AVL tree: time is:  ";
    std::cout << std::chrono::duration_cast<std::chrono::nanoseconds>(t30-t21).count() << std::endl;
    std::cout << std::endl;


    //***********************************//
    //***********************************//
    //Unsorted set//
    //***********************************//
    //***********************************//

    std::cout << "checking time for: 100 apartments insert, Unordered set: " << std::endl;
    auto t31 = std::chrono::high_resolution_clock::now();
    std::unordered_set<Apartment, MyHashFunction> my_set(vector.begin(), vector.end());
    auto t32 = std::chrono::high_resolution_clock::now();
    std::cout << "checking time for: 100 apartments insert, Unordered set: time is:  ";
    std::cout << std::chrono::duration_cast<std::chrono::nanoseconds>(t32-t31).count() << std::endl;
    std::cout << std::endl;


    std::cout << "checking time for: 1000 apartments insert, Unordered set: " << std::endl;
    auto t33 = std::chrono::high_resolution_clock::now();
    std::unordered_set<Apartment, MyHashFunction> my_set2(vector1000.begin(), vector1000.end());
    auto t34 = std::chrono::high_resolution_clock::now();
    std::cout << "checking time for: 1000 apartments insert, Unordered set: time is:  ";
    std::cout << std::chrono::duration_cast<std::chrono::nanoseconds>(t34-t33).count() << std::endl;
    std::cout << std::endl;


    std::cout << "checking time for: 10000 apartments insert, Unordered set: " << std::endl;
    auto t35 = std::chrono::high_resolution_clock::now();
    std::unordered_set<Apartment, MyHashFunction> my_set3(vector10000.begin(), vector10000.end());
    auto t36 = std::chrono::high_resolution_clock::now();
    std::cout << "checking time for: 10000 apartments insert, Unordered set: time is:  ";
    std::cout << std::chrono::duration_cast<std::chrono::nanoseconds>(t36-t35).count() << std::endl;
    std::cout << std::endl;

    //***********************************//
    //Set find function//
    //***********************************//
    std::cout << "checking time for: 100 apartments Set find, Unordered set: " << std::endl;
    auto t37 = std::chrono::high_resolution_clock::now();
    (void)my_set.find (x);
    auto t38 = std::chrono::high_resolution_clock::now();
    std::cout << "checking time for: 100 apartments Set find, Unordered set: time is:  ";
    std::cout << std::chrono::duration_cast<std::chrono::nanoseconds>(t38-t37).count() << std::endl;
    std::cout << std::endl;


    std::cout << "checking time for: 1000 apartments Set find, Unordered set: " << std::endl;
    auto t39 = std::chrono::high_resolution_clock::now();
    (void)my_set2.find (x);
    auto t40 = std::chrono::high_resolution_clock::now();
    std::cout << "checking time for: 1000 apartments Set find, Unordered set: time is:  ";
    std::cout << std::chrono::duration_cast<std::chrono::nanoseconds>(t40-t39).count() << std::endl;
    std::cout << std::endl;


    std::cout << "checking time for: 10000 apartments Set find, Unordered set: " << std::endl;
    auto t41 = std::chrono::high_resolution_clock::now();
    (void)my_set3.find (x);
    auto t42 = std::chrono::high_resolution_clock::now();
    std::cout << "checking time for: 10000 apartments Set find, Unordered set: time is:  ";
    std::cout << std::chrono::duration_cast<std::chrono::nanoseconds>(t42-t41).count() << std::endl;
    std::cout << std::endl;


    //***********************************//
    //Find find//
    //***********************************//
    std::cout << "checking time for: 100 apartments my Find function, find, Unordered set: " << std::endl;
    auto t43 = std::chrono::high_resolution_clock::now();
    (void)find (my_set.begin(), my_set.end(), x);
    auto t44 = std::chrono::high_resolution_clock::now();
    std::cout << "checking time for: 100 apartments my Find function, find, Unordered set: time is:  ";
    std::cout << std::chrono::duration_cast<std::chrono::nanoseconds>(t44-t43).count() << std::endl;
    std::cout << std::endl;


    std::cout << "checking time for: 1000 apartments my Find function, find, Unordered set: " << std::endl;
    auto t45 = std::chrono::high_resolution_clock::now();
    (void)find (my_set2.begin(), my_set2.end(), x);
    auto t46 = std::chrono::high_resolution_clock::now();
    std::cout << "checking time for: 1000 apartments my Find function, find, Unordered set: time is:  ";
    std::cout << std::chrono::duration_cast<std::chrono::nanoseconds>(t46-t45).count() << std::endl;
    std::cout << std::endl;

    std::cout << "checking time for: 10000 apartments my Find function, find, Unordered set: " << std::endl;
    auto t47 = std::chrono::high_resolution_clock::now();
    (void)find (my_set3.begin(), my_set3.end(), x);
    auto t48 = std::chrono::high_resolution_clock::now();
    std::cout << "checking time for: 10000 apartments my Find function, find, Unordered set: time is:  ";
    std::cout << std::chrono::duration_cast<std::chrono::nanoseconds>(t48-t47).count() << std::endl;
    std::cout << std::endl;
}
