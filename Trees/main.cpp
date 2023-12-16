#include <iostream>
#include "src/avl_tree.hpp"
#include <sciplot/sciplot.hpp>
#include <chrono>
#include <random>
#include <algorithm>
#include <cmath>
#include <bits/stdc++.h>

#define STEP 1000
std::array<sciplot::Vec, 3> run_experiment(size_t thousands_checked, std::vector<int> &random_vector, Tree<int, int> &tree, bool perform_deletion)
{
    sciplot::Vec creation_times(0.0, thousands_checked);
    sciplot::Vec finding_times(0.0, thousands_checked);
    sciplot::Vec destruction_times(0.0, thousands_checked);
    auto start = std::chrono::high_resolution_clock::now();
    for (size_t i = 0; i < thousands_checked; i++)
    {

        // Inserting elements
        for (size_t j = i * STEP; j < (i + 1) * STEP; j++)
        {
            tree.insert_node(random_vector[j], 0);
        }
        auto stop = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start);
        creation_times[i] = duration.count();

    }

    start = std::chrono::high_resolution_clock::now();
    for (size_t i = 0; i < thousands_checked; i++)
    {
        for (size_t j = i * STEP; j < (i + 1) * STEP; j++)
        {
            tree.find_node(random_vector[j]);
        }
        auto stop = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start);
        finding_times[i] = duration.count();
    }

    // Removing elements, for BST
    if (perform_deletion)
    {
        start = std::chrono::high_resolution_clock::now();
        for (size_t i = 0; i < thousands_checked; i++)
        {
            for (size_t j = i * STEP; j < (i + 1) * STEP; j++)
            {
                tree.delete_node(random_vector[j]);
            }
            auto stop = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start);
            destruction_times[i] = duration.count();
        }
    }
    return {creation_times, finding_times, destruction_times};
}

std::array<sciplot::Vec, 3> measure_average_times(Tree<int, int> *tree, std::vector<int> &random_vector, size_t thousands_checked, size_t number_of_experiments, bool perform_deletion)
{
    sciplot::Vec creation_times(0.0, thousands_checked);
    sciplot::Vec finding_times(0.0, thousands_checked);
    sciplot::Vec destruction_times(0.0, thousands_checked);
    for (size_t experiment = 0; experiment < number_of_experiments; experiment++)
    {
        std::array<sciplot::Vec, 3> times = run_experiment(thousands_checked, random_vector, *tree, perform_deletion);
        creation_times += times[0];
        finding_times += times[1];
        destruction_times += times[2];
    }

    creation_times /= number_of_experiments;
    finding_times /= number_of_experiments;
    destruction_times /= number_of_experiments;
    return {creation_times, finding_times, destruction_times};
}

void create_plot(std::vector<sciplot::Vec> times, std::string file_name, std::vector<std::string> names)
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
        plot.drawPoints(xs, times[i]).pointType(3 + i * 2).pointSize(2).label(names[i]);
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
    srand(12);
    std::generate(random_vector.begin(), random_vector.end(), rand);

    BinarySearchTree<int, int> *bst = new BinarySearchTree<int, int>();
    std::array<sciplot::Vec, 3> bst_times = measure_average_times(bst, random_vector, thousands_checked, number_of_experiments, true);
    delete bst;

    AVLTree<int, int> *avl = new AVLTree<int, int>();
    std::array<sciplot::Vec, 3> avl_times = measure_average_times(avl, random_vector, thousands_checked, number_of_experiments, false);
    delete avl;

    std::vector<sciplot::Vec> creation_times = {bst_times[0], avl_times[0]};
    std::vector<sciplot::Vec> finding_times = {bst_times[1], avl_times[1]};
    std::vector<sciplot::Vec> destruction_times = {bst_times[2]};
    std::vector<std::string> names{"BST", "AVL"};
    create_plot(creation_times, "creating_tree_time_plot.png", names);
    create_plot(finding_times, "finding_key_time_plot.png", names);
    create_plot(destruction_times, "deletion_time_plot.png", names);

    return 0;
}
