// #pragma once
#include <iostream>
#include<cmath>

class Heap
{
protected:
    size_t n_ary_type;
    size_t max_size;
    size_t current_size;
    int *table;
    void resize(size_t new_max_size);
    void move_up();
    void move_down();
    void move_up_swap();
    void move_down_swap();
    size_t find_max_child(size_t index, size_t number_of_children) const;


public:
    Heap(size_t n_ary_type, size_t max_size);
    void insert_value(int value);
    int remove_top();
    int get_top();
    bool is_empty() const;
    bool is_full() const;
    int &get_table() const;
    size_t get_current_size() const;
    size_t get_max_size() const;
    void set_current_size(size_t new_size);
    void print() const;
    void visualize() const;
    void visualize_binary() const;
};
