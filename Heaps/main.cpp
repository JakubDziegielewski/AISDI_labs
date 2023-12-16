#include "heap.hpp"
#include <iostream>
#include <sciplot/sciplot.hpp>
#include <chrono>
#include <random>
#include <algorithm>
#include <cmath>
#include <bits/stdc++.h>

#define STEP 10000

std::array<sciplot::Vec, 2> run_experiment(size_t thousands_checked, std::vector<int> &random_vector, Heap &heap)
{
    sciplot::Vec creation_times(0.0, thousands_checked);
    sciplot::Vec destruction_times(0.0, thousands_checked);
    for (size_t i = 0; i < thousands_checked; i++)
    {
        std::memset(&heap.get_table(), 0, heap.get_current_size());
        heap.set_current_size(0);
        auto start = std::chrono::high_resolution_clock::now();
        for (size_t j = 0; j < (i + 1) * STEP; j++)
        {
            heap.insert_value(random_vector[j]);
        }
        auto stop = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start);
        creation_times[i] = duration.count();
        start = std::chrono::high_resolution_clock::now();
        for (size_t j = 0; j < (i + 1) * STEP; j++)
        {
            heap.remove_top();
        }
        stop = std::chrono::high_resolution_clock::now();
        duration = std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start);
        destruction_times[i] = duration.count();
    }
    return {creation_times, destruction_times};
}

std::array<sciplot::Vec, 2> measure_average_times(Heap *heap, std::vector<int> &random_vector, size_t thousands_checked, size_t number_of_experiments)
{
    sciplot::Vec creation_times(0.0, thousands_checked);
    sciplot::Vec destruction_times(0.0, thousands_checked);
    for (size_t experiment = 0; experiment < number_of_experiments; experiment++)
    {
        std::array<sciplot::Vec, 2> times = run_experiment(thousands_checked, random_vector, *heap);
        creation_times += times[0];
        destruction_times += times[1];
    }

    creation_times /= number_of_experiments;
    destruction_times /= number_of_experiments;
    return {creation_times, destruction_times};
}

void create_plot(std::vector<sciplot::Vec> times, std::string file_name)
{
    sciplot::Plot2D plot;
    size_t thousands_checked = times[0].size();
    plot.xrange(0.0, (thousands_checked + 1) * STEP);

    plot.xlabel("Number of values");
    plot.ylabel("Time in nanoseconds");
    plot.legend()
        .atOutsideBottom()
        .displayHorizontal()
        .displayExpandWidthBy(2);
    for (size_t i = 0; i < times.size(); i++)
    {
        sciplot::Vec xs = sciplot::range(1, thousands_checked) * STEP;
        plot.drawPoints(xs, times[i]).pointType(3 + i * 2).pointSize(2).label(std::to_string(i + 2) + "-ary heap");
    }
    sciplot::Figure fig = {{plot}};
    sciplot::Canvas canvas = {{fig}};
    canvas.size(800, 800);

    canvas.save(file_name);
}

int main()
{
    size_t thousands_checked = 10;
    size_t number_of_experiments = 100;
    size_t vector_size = thousands_checked * STEP;
    std::vector<int> random_vector = std::vector<int>(vector_size, 0);
    srand(1);
    std::generate(random_vector.begin(), random_vector.end(), rand);
    Heap *binary_heap = new Heap(2, 10);
    std::array<sciplot::Vec, 2> binary_heap_times = measure_average_times(binary_heap, random_vector, thousands_checked, number_of_experiments);
    delete binary_heap;
    Heap *three_ary_heap = new Heap(3, 10);
    std::array<sciplot::Vec, 2> three_ary_heap_times = measure_average_times(three_ary_heap, random_vector, thousands_checked, number_of_experiments);
    delete three_ary_heap;
    Heap *four_ary_heap = new Heap(4, 10);
    std::array<sciplot::Vec, 2> four_ary__heap_times = measure_average_times(four_ary_heap, random_vector, thousands_checked, number_of_experiments);
    delete four_ary_heap;
    std::vector<sciplot::Vec> creation_times = {binary_heap_times[0], three_ary_heap_times[0], four_ary__heap_times[0]};
    std::vector<sciplot::Vec> destruction_times = {binary_heap_times[1], three_ary_heap_times[1], four_ary__heap_times[1]};
    create_plot(creation_times, "creating_heap_time_plot.png");
    create_plot(destruction_times, "destructing_heap_time_plot.png");

    return 0;
}
