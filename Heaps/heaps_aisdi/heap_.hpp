//
//  heap.hpp
//  heaps_aisdi
//
//  Created by Filip on 25/11/2023.
//

#ifndef heap_hpp
#define heap_hpp

#include <stdio.h>
#include <vector>
#include <iostream>
#include <cmath>



class Heap{
    
private:
    int *arr; //array or vector that need to be transformed into heap
    int n_size; // size of the array to be created
    int current_size;
//    int n_num_heap; // how many children should each node have

public:
    Heap(int n_size);
    void up_heap(int elem);
    void down_heap(int elem);
    int pop(); // deletes and returns the root element (down_heap inside)
    void push(int elem); // adds an element to the end of the heap (up_heap inside)
    int min(); // return the top element
    
    void visualizeHeap();
    void realocate();
    
    int parent(int idx); //return the parent index
    int child_l(int idx); //return the child index
    int child_r(int idx); // as above

    int get_current_size() const;
    void print();
    void delete_key(int idx); //delete a certain element
    void add_key(double elem); //add new element
    
    
    
    
};
#endif /* heap_hpp */
