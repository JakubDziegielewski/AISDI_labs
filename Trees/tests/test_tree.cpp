//
//  test_tree.cpp
//  aisdi_trees
//
//  Created by Filip on 12/12/2023.
//

#include <stdio.h>
#include "../src/avl_tree.hpp"
#include "catch_amalgamated.hpp"


TEMPLATE_TEST_CASE("AVLTree insertion and rotation", "[avl_tree]", int, double, char) {

    SECTION("Inserting nodes and checking height balance") {
        AVLTree<TestType, std::string> avlTree;
        // Insert nodes and check height balance
        avlTree.insert_node(10, "Value10");
        REQUIRE(avlTree.get_balance(avlTree.get_root()) == 0);

        avlTree.insert_node(20, "Value20");
        avlTree.insert_node(25, "Value5");
        REQUIRE(avlTree.get_balance(avlTree.get_root())==0);

        avlTree.insert_node(30, "Value25");
        REQUIRE(avlTree.get_balance(avlTree.get_root()) == 1);

        avlTree.insert_node(24, "Value30");
        REQUIRE(avlTree.get_balance(avlTree.get_root()) == 1);
        
        avlTree.insert_node(7, "Value7");
        avlTree.insert_node(4, "Value4");
        REQUIRE(avlTree.get_balance(avlTree.get_root()) == 0);

        
    }

    SECTION("Inserting nodes and checking node heights") {
        AVLTree<TestType, std::string> avlTree;
        // Insert nodes and check node heights
        avlTree.insert_node(10, "Value10");
        REQUIRE(avlTree.get_node_height(avlTree.get_root()) == 0);

        avlTree.insert_node(20, "Value20");
        REQUIRE(avlTree.get_node_height(avlTree.get_root()) == 1);

        avlTree.insert_node(5, "Value5");
        REQUIRE(avlTree.get_node_height(avlTree.get_root()) == 1);

        avlTree.insert_node(25, "Value25");
        REQUIRE(avlTree.get_node_height(avlTree.get_root()) == 2);

        avlTree.insert_node(30, "Value30");
        REQUIRE(avlTree.get_node_height(avlTree.get_root()) == 2);
    }

    SECTION("Inserting nodes and checking tree structure after rotations") {
        AVLTree<TestType, std::string> avlTree;

        // Insert nodes and check tree structure after rotations
        avlTree.insert_node(10, "Value10");
        avlTree.insert_node(20, "Value20");
        avlTree.insert_node(5, "Value5");
        avlTree.insert_node(25, "Value25");
        avlTree.insert_node(30, "Value30");

        // Check the structure of the tree after rotations
        REQUIRE(avlTree.get_root()->get_key() == 10);
        REQUIRE(avlTree.get_root()->get_left()->get_key() == 5);
        REQUIRE(avlTree.get_root()->get_right()->get_key() == 25);
        REQUIRE(avlTree.get_root()->get_right()->get_right()->get_key() == 30);
    }
    
}


TEMPLATE_TEST_CASE("Binary Search Tree Operations", "[bst]", int, double, char) {
    SECTION("Insertion and Search") {
        BinarySearchTree<TestType, std::string> bst;

        REQUIRE(bst.find_node(5) == std::nullopt);

        bst.insert_node(5, "Value5");
        REQUIRE(bst.find_node(5) != std::nullopt);
        REQUIRE(bst.find_node(5)->get_key() == 5);
        REQUIRE(bst.find_node(5)->get_value() == "Value5");

        bst.insert_node(3, "Value3");
        bst.insert_node(7, "Value7");

        REQUIRE(bst.find_node(3) != std::nullopt);
        REQUIRE(bst.find_node(3)->get_key() == 3);
        REQUIRE(bst.find_node(3)->get_value() == "Value3");

        REQUIRE(bst.find_node(7) != std::nullopt);
        REQUIRE(bst.find_node(7)->get_key() == 7);
        REQUIRE(bst.find_node(7)->get_value() == "Value7");

        REQUIRE(bst.find_node(10) == std::nullopt);
    }

    SECTION("Deletion") {
        BinarySearchTree<TestType, std::string> bst;

        // Insert nodes
        bst.insert_node(5, "Value5");
        bst.insert_node(3, "Value3");
        bst.insert_node(7, "Value7");

        // Delete a leaf node
        bst.delete_node(3);
        REQUIRE(bst.find_node(3) == std::nullopt);

        // Delete a node with one child
        bst.delete_node(7);
        REQUIRE(bst.find_node(7) == std::nullopt);

        // Delete a node with two children
        bst.insert_node(8, "Value8");
        bst.insert_node(6, "Value6");
        bst.insert_node(10, "Value10");

        bst.delete_node(8);
        REQUIRE(bst.find_node(8) == std::nullopt);
        REQUIRE(bst.find_node(10) != std::nullopt);
        REQUIRE(bst.find_node(10)->get_key() == 10);
        REQUIRE(bst.find_node(10)->get_value() == "Value10");
    }
}


