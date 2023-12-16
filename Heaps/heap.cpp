#include "heap.hpp"
#include <limits.h>
#include <sstream>

// for visualization purposes
#define PARENT(i) ((i-1) / 2)
#define NUM_NODES 15
#define LINE_WIDTH 70

Heap::Heap(size_t n_ary_type, size_t max_size) : n_ary_type(n_ary_type), max_size(max_size)
{
    table = new int[max_size];
    current_size = 0;
    if (n_ary_type < 1)
    {
        throw std::invalid_argument("N-ary type smaller than 2");
    }
}

void Heap::insert_value(int value)
{
    if (is_full())
    {
        resize(max_size * 2);
    }
    table[current_size] = value;
    current_size++;
    move_up();
}

int Heap::remove_top()
{
    if (!is_empty())
    {
        int top = table[0];
        table[0] = table[current_size - 1];
        current_size--;
        move_down();

        if (current_size + 3 < max_size / 2)
        {
            resize(max_size / 2);
        }
        return top;
    }
    else
    {
        throw std::out_of_range("Trying to remove from an empty Heap");
    }
}

int Heap::get_top(){
    return table[0];
}

int &Heap::get_table() const
{
    return *this->table;
}

std::size_t Heap::get_current_size() const
{
    return this->current_size;
}
std::size_t Heap::get_max_size() const
{
    return this->max_size;
}

bool Heap::is_empty() const
{
    return this->current_size == 0;
}

bool Heap::is_full() const
{
    return this->current_size == this->max_size;
}

void Heap::resize(size_t new_max_size)
{
    size_t old_size = this->max_size;
    this->max_size = new_max_size;
    int *new_table = new int[max_size];
    if (new_max_size > old_size)
    {
        for (size_t i = 0; i < old_size; i++)
        {
            new_table[i] = table[i];
        }
    }
    else
    {
        for (size_t i = 0; i < new_max_size; i++)
        {
            new_table[i] = table[i];
        }
    }

    delete[] table;
    this->table = new_table;
}

void Heap::move_up()
{
    size_t index = current_size - 1;
    int moving_value = table[index];

    while (index > 0 && moving_value > table[(index - 1) / n_ary_type])
    {
        table[index] = table[(index - 1) / n_ary_type];
        index = (index - 1) / n_ary_type;
    }
    table[index] = moving_value;
}

void Heap::move_up_swap()
{
    size_t index = current_size - 1;

    while (index > 0 && table[index] > table[(index - 1) / n_ary_type])
    {
        std::swap(table[index], table[(index - 1) / n_ary_type]);
        index = (index - 1) / n_ary_type;
    }
}

void Heap::move_down()
{
    size_t index = 0;
    int moving_value = table[index];

    while ((index + 1) * n_ary_type < current_size)
    {
        size_t index_of_max_child = find_max_child(index, n_ary_type);

        if (moving_value <= table[index_of_max_child])
        {
            table[index] = table[index_of_max_child];
            index = index_of_max_child;
        }
        else
        {
            break;
        }
    }

    size_t uneven_children = (current_size - 1) % n_ary_type;

    if (index * n_ary_type + uneven_children < current_size)
    {
        size_t index_of_max_child = find_max_child(index, n_ary_type);
        if (moving_value <= table[index_of_max_child])
        {
            table[index] = table[index_of_max_child];
            index = index_of_max_child;
        }
    }
    table[index] = moving_value;
}

void Heap::move_down_swap()
{
    size_t index = 0;

    while ((index + 1) * n_ary_type < current_size)
    {
        size_t index_of_max_child = find_max_child(index, n_ary_type);

        if (table[index] <= table[index_of_max_child])
        {
            std::swap(table[index], table[index_of_max_child]);
            index = index_of_max_child;
        }
        else
        {
            break;
        }
    }

    size_t uneven_children = (current_size - 1) % n_ary_type;

    if (index * n_ary_type + uneven_children < current_size)
    {
        size_t index_of_max_child = find_max_child(index, n_ary_type);
        if (table[index] <= table[index_of_max_child])
        {
            std::swap(table[index], table[index_of_max_child]);
            index = index_of_max_child;
        }
    }
}

size_t Heap::find_max_child(size_t index, size_t number_of_children) const
{
    int max_child = INT_MIN;
    size_t index_of_max_child = index * n_ary_type + 1;
    for (size_t i = 1; i <= number_of_children; i++)
    {
        if (table[index * n_ary_type + i] > max_child)
        {
            max_child = table[index * n_ary_type + i];
            index_of_max_child = index * n_ary_type + i;
        }
    }
    return index_of_max_child;
}

void Heap::print() const
{
    std::cout << "Index | Value | Parent Index \n";
    std::cout << 0 << "     |   " << table[0] << "  |" << std::endl;
    for (size_t i = 1; i < std::min(current_size, static_cast<size_t>(10)); i++)
    {
        std::cout << i << "     |   " << table[i] << "  |   " << (i - 1) / n_ary_type << std::endl;
    }
    for (size_t i = 10; i < std::min(current_size, static_cast<size_t>(99)); i++)
    {
        std::cout << i << "    |   " << table[i] << "  |   " << (i - 1) / n_ary_type << std::endl;
    }
}

void Heap::set_current_size(size_t new_size)
{
    current_size = new_size;
}

void Heap::visualize() const {
    
        int height = static_cast<int>(std::ceil(std::log(current_size + 1) / std::log(n_ary_type)));

        int index = 0;
        for (int level = 0; level < height; ++level) {
            int levelNodes = std::min(static_cast<int>(pow(n_ary_type, level)), static_cast<int>(current_size - index));

            // Calculate the spacing between nodes
            int spacesBetween = std::max(2 * height - 1, static_cast<int>(pow(n_ary_type, height - level + 1))) - 1;

            // Print leading spaces
            for (int i = 0; i < spacesBetween / 10; ++i) {
                std::cout << " ";
            }

            // Print nodes on this level
            for (int i = 0; i < levelNodes; ++i) {
                std::cout << table[index++];
                if (i < levelNodes - 1) {
                    // Print spaces between nodes
                    for (int j = 0; j < spacesBetween/4; ++j) {
                        if(level==height-1){
                            std::cout << " ";
                            if((i+1)%n_ary_type==0){
                                if(j==0){
                                std::cout << ";";
                                }
                            }
                        }
                        else{
                        std::cout << " ";
                        }
                    }
                }
            }

            std::cout << std::endl;
        }
    }

void Heap::visualize_binary() const {

int tree[NUM_NODES];
int print_pos[NUM_NODES];
int i, j, k, pos, x=1, level=0;

    for(int k=0; k<NUM_NODES; k++){
        tree[k]=table[k];
    }

print_pos[0] = 0;
for(i=0,j=1; i<NUM_NODES; i++,j++) {
    pos = print_pos[PARENT(i)] + (i%2?-1:1)*(LINE_WIDTH/(pow(2,level+1))+1);

    for (k=0; k<pos-x; k++) printf("%c",i==0||i%2?' ':'-');
    printf("%d",tree[i]);

    print_pos[i] = x = pos+1;
    if (j==pow(2,level)) {
        printf("\n");
        level++;
        x = 1;
        j = 0;
    }
}
}