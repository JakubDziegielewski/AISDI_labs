#include "catch_amalgamated.hpp"
#include "heap.hpp"
#include <sstream>
#include <iostream>
#include <random>


TEST_CASE("Heap functionality", "[Heap]"){
    SECTION("Basic functionality") {
        Heap heap(3, 10);
        REQUIRE(heap.is_empty());
        REQUIRE_FALSE(heap.is_full());
        REQUIRE(heap.get_current_size() == 0);
        REQUIRE(heap.get_max_size() == 10);

        heap.insert_value(10);
        REQUIRE_FALSE(heap.is_empty());
        REQUIRE_FALSE(heap.is_full());
        REQUIRE(heap.get_current_size() == 1);

        int top = heap.remove_top();
        REQUIRE(top == 10);
        REQUIRE(heap.is_empty());
        REQUIRE_FALSE(heap.is_full());
        REQUIRE(heap.get_current_size() == 0);
    }

    SECTION("Insertion and removal") {
        srand(0);
        std::vector<int> random_vector(1000);
        std::generate(random_vector.begin(), random_vector.end(), rand);
        int max_value=0;
        for(size_t i=2; i<6; i++){
            Heap *heap1 = new Heap(i, 1000);
            for(size_t j=0; j<1000; j++){
                heap1->insert_value(random_vector[j]);
                REQUIRE(heap1->get_current_size()==j+1);
            }
            for (size_t i = 0; i < random_vector.size(); ++i) {
                if (random_vector[i] > max_value) {
                    max_value = random_vector[i];
                }
            }
            REQUIRE(heap1->get_top()==max_value);
            
            for(size_t j=0; j<1000; j++){
                heap1->remove_top();
                REQUIRE(heap1->get_current_size()==1000-j-1);
        }
    }

        Heap *heap = new Heap(2, 5);
        int *wsk = &heap->get_table();
        for (int i = 5; i >= 1; --i) {
            heap->insert_value(i);
            REQUIRE(heap->get_current_size() == static_cast<size_t>(5 - i + 1));
            REQUIRE(wsk[0]==5);
        }

        for (size_t i = 5; i >= 1; --i) {
            heap->insert_value(i);
            REQUIRE(heap->get_current_size() == 5+(5-i+1));
        }

        REQUIRE(heap->is_full());

        int removed = heap->remove_top();
        REQUIRE(removed == 5);
        REQUIRE_FALSE(heap->is_full());
        REQUIRE(heap->get_current_size() == 9);

        removed = heap->remove_top();
        REQUIRE(removed == 5);
        REQUIRE_FALSE(heap->is_full());
        REQUIRE(heap->get_current_size() == 8);
    }

    SECTION("Resizing") {
        Heap heap(2, 5);

        for (int i = 1; i <= 10; ++i) {
            heap.insert_value(i);
            REQUIRE(heap.get_current_size() == static_cast<size_t>(i));
        }

        REQUIRE(heap.is_full());
        REQUIRE(heap.get_max_size() == 10);
        heap.insert_value(11);
        REQUIRE(heap.get_max_size()==20);
    }
}