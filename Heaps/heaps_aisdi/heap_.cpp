//
//  heap.cpp
//  heaps_aisdi
//
//  Created by Filip on 25/11/2023.
//

#include "heap_.hpp"

Heap::Heap(int n_size){
    if(n_size>0){
        arr = new int[n_size];
        current_size=0;
    }
}

int Heap::min(){
    return arr[0];
}

void Heap::realocate(){
    if(current_size==n_size){
        int new_size = 2*n_size;
        int *arr2 = new int [new_size];
        for(int i=0; i<current_size; i++){
            arr2[i]=arr[i];
        }
        arr=arr2;
        delete[] arr2;
        n_size=new_size;
    }
}


int Heap::pop(){
    int min = Heap::min();
    arr[0]=arr[current_size-1];
    
    down_heap(0);
    current_size--;
    return min;
}
void Heap::push(int elem){
    if(current_size==n_size){
        realocate();
    }
    arr[current_size]=elem;
    up_heap(current_size);
    current_size++;

}

void Heap::up_heap(int idx){
    int temp = arr[idx];
    while(idx!=0 && arr[idx]<arr[parent(idx)]){
        arr[idx]=arr[parent(idx)];
        idx=parent(idx);
    }
    arr[idx]=temp;
}

void Heap::down_heap(int idx){
//    int temp = arr[idx];
    while(child_l(idx)<current_size){
        int child = child_l(idx);
        if(child+1 < current_size && arr[child]>arr[child+1]) child=child+1;
        if(arr[idx]<arr[child]) break;
//        arr[idx]=arr[child];
        std::swap(arr[idx], arr[child]);
        idx=child;
    }
//    arr[idx] = temp;
}

void Heap::print(){
    for(int i=0; i<current_size; i++){
        std::cout<<arr[i]<<" ";
    }
    std::cout<<"\n";
}

int Heap::parent(int idx){
    return (idx-1)/2;
}

int Heap::child_l(int idx){
    return 2*idx+1;
}

int Heap::child_r(int idx){
    return 2*idx+2;
}

void delete_key(int idx); //delete a certain element - check if it differs from the pop() method
void add_key(double elem); //add new element

int Heap::get_current_size() const{
    return current_size;
}

void Heap::visualizeHeap() {
    int height = static_cast<int>(log2(current_size)) + 1;

        int index = 0;
        for (int level = 0; level < height; ++level) {
            int levelNodes = std::min(1 << level, static_cast<int>(current_size - index));

            // Calculate the spacing between nodes
            int spacesBetween = std::max(2 * height - 1, 1 << (height - level + 1)) - 1;

            // Print leading spaces
            for (int i = 0; i < spacesBetween / height; ++i) {
                if(i==(spacesBetween / height)){
                    std::cout<<"";
                    break;
                }
                std::cout << "  ";
            }

            // Print nodes on this level
            for (int i = 0; i < levelNodes; ++i) {
                std::cout << arr[index++];
                if (i < levelNodes - 1) {
                    // Print spaces between nodes
                    if(level==height-1){
                        for (int j = 0; j < spacesBetween/5; ++j) {
                            std::cout << " ";
                        }
                    }
                    else{
                        for (int j = 0; j < spacesBetween; ++j) {
                            std::cout << " ";
                        }
                    }
                }
            }

            std::cout << std::endl;
        }
    }
