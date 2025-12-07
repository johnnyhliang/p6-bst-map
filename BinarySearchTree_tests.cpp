#include "BinarySearchTree.hpp"
#include "unit_test_framework.hpp"
#include <sstream>
#include <string>
#include <vector>

using std::ostringstream;
using std::string;
using std::vector;

TEST(test_init) {
    BinarySearchTree<int> tree;
    ASSERT_TRUE(tree.empty());
    ASSERT_EQUAL(tree.size(), 0u);
    ASSERT_EQUAL(tree.height(), 0u);
    ASSERT_TRUE(tree.check_sorting_invariant());

    ostringstream os;
    tree.traverse_inorder(os);
    ASSERT_TRUE(os.str() == "");

    ASSERT_TRUE(tree.begin() == tree.end());
    ASSERT_TRUE(tree.min_element() == tree.end());
    ASSERT_TRUE(tree.max_element() == tree.end());
    ASSERT_TRUE(tree.min_greater_than(0) == tree.end());
}
TEST(test_sorting_fr) {
    BinarySearchTree<int> tree;
        vector<int> values = {50, 25, 75, 10, 30, 60, 90, 5, 15, 27, 40, 55, 65, 85, 95};
        for (int val : values) {
            tree.insert(val);
            ASSERT_TRUE(tree.check_sorting_invariant());
        }
        
        
        ASSERT_EQUAL(tree.size(), 15u);
        ASSERT_TRUE(tree.check_sorting_invariant());
    
}
TEST(test_one) {
    BinarySearchTree<int> tree;
    tree.insert(5);
    ASSERT_FALSE(tree.empty());
    ASSERT_EQUAL(tree.size(), 1u);
    ASSERT_EQUAL(tree.height(), 1u);
    ASSERT_TRUE(tree.check_sorting_invariant());

    ostringstream os1;
    tree.traverse_inorder(os1);
    ASSERT_TRUE(os1.str() == "5 ");
    ostringstream os2;
    tree.traverse_preorder(os2);
    ASSERT_TRUE(os2.str() == "5 ");

    ASSERT_EQUAL(*tree.begin(), 5);
    ASSERT_EQUAL(*tree.min_element(), 5);
}

TEST(test_right) {
    BinarySearchTree<int> tree;
    tree.insert(10); tree.insert(20); tree.insert(30);
    ASSERT_EQUAL(tree.size(), 3u);
    ASSERT_EQUAL(tree.height(), 3u);
    ASSERT_TRUE(tree.check_sorting_invariant());

    ostringstream os1;
    tree.traverse_inorder(os1);
    ASSERT_TRUE(os1.str() == "10 20 30 ");
    ostringstream os2;
    tree.traverse_preorder(os2);
    ASSERT_TRUE(os2.str() == "10 20 30 ");
}

TEST(test_left) {
    BinarySearchTree<int> tree;
    tree.insert(30); tree.insert(20); tree.insert(10);
    ASSERT_EQUAL(tree.size(), 3u);
    ASSERT_EQUAL(tree.height(), 3u);
    ASSERT_TRUE(tree.check_sorting_invariant());

    ostringstream os1;
    tree.traverse_inorder(os1);
    ASSERT_TRUE(os1.str() == "10 20 30 ");
    ostringstream os2;
    tree.traverse_preorder(os2);
    ASSERT_TRUE(os2.str() == "30 20 10 ");
}

TEST(test_both) {
    BinarySearchTree<int> tree;
    tree.insert(50);
    tree.insert(30);
    tree.insert(70);
    tree.insert(20);
    tree.insert(40);
    tree.insert(60);
    tree.insert(80);

    ASSERT_EQUAL(tree.size(), 7u);
    ASSERT_EQUAL(tree.height(), 3u);
    ASSERT_TRUE(tree.check_sorting_invariant());

    ostringstream os1;
    tree.traverse_inorder(os1);
    ASSERT_TRUE(os1.str() == "20 30 40 50 60 70 80 ");
    ostringstream os2;
    tree.traverse_preorder(os2);
    ASSERT_TRUE(os2.str() == "50 30 20 40 70 60 80 ");
}

TEST(test_iterator) {
    BinarySearchTree<int> tree;
    vector<int> data = {50, 30, 70, 20, 40};
    for (int i: data) tree.insert(i);
    vector<int> expected_sorted = {20, 30, 40, 50, 70};
    vector<int> actual_sorted;

    for (int elt : tree) {
        actual_sorted.push_back(elt);
    }
    
    ASSERT_EQUAL(expected_sorted.size(), actual_sorted.size());
    for (int i = 0; i < expected_sorted.size(); ++i) {
        ASSERT_EQUAL(expected_sorted[i], actual_sorted[i]);
    }

    ASSERT_EQUAL(*tree.min_element(), 20);
    ASSERT_EQUAL(*tree.max_element(), 70);
    ASSERT_EQUAL(*tree.min_greater_than(30), 40);
    ASSERT_TRUE(tree.min_greater_than(70) == tree.end());
}

TEST(test_find_and_insert) {
    BinarySearchTree<int> tree;
    auto it50 = tree.insert(50);
    ASSERT_EQUAL(*it50, 50);

    tree.insert(30);
    tree.insert(70);
    ASSERT_EQUAL(*tree.find(50), 50);
    ASSERT_EQUAL(*tree.find(30), 30);
    ASSERT_TRUE(tree.find(10) == tree.end());
}

TEST(test_copy) {
    BinarySearchTree<int> tree1;
    tree1.insert(10);
    tree1.insert(5);
    tree1.insert(15);
    BinarySearchTree<int> tree2 = tree1;

    ASSERT_EQUAL(tree1.size(), 3u);
    ASSERT_EQUAL(tree2.size(), 3u);
    
    ostringstream os1;
    os1 << tree1;
    ostringstream os2;
    os2 << tree2;
    ASSERT_TRUE(os1.str() == "[ 5 10 15 ]");
    ASSERT_TRUE(os1.str() == os2.str());

    tree2.insert(20);
    ASSERT_EQUAL(tree1.size(), 3u);
    ASSERT_EQUAL(tree2.size(), 4u);
}

TEST(test_assignment) {
    BinarySearchTree<int> tree1;
    tree1.insert(10);
    tree1.insert(5);

    BinarySearchTree<int> tree2;
    tree2.insert(100);
    tree2.insert(200);

    tree2 = tree1;
    ASSERT_EQUAL(tree1.size(), 2u);
    ASSERT_EQUAL(tree2.size(), 2u);
    
    ostringstream oss1;
    oss1 << tree1;
    ostringstream oss2;
    oss2 << tree2;

    ASSERT_TRUE(oss1.str() == oss2.str());
    ASSERT_TRUE(tree2.find(100) == tree2.end());
}

TEST(test_find_deep_tree) {
    BinarySearchTree<int> tree;
    
    tree.insert(50);
    tree.insert(25);
    tree.insert(75);
    tree.insert(10);
    tree.insert(35);
    tree.insert(60);
    tree.insert(90);
    tree.insert(5);
    tree.insert(30);
    
    
    ASSERT_EQUAL(*tree.find(5), 5);
    ASSERT_EQUAL(*tree.find(30), 30);
    ASSERT_EQUAL(*tree.find(60), 60);
    ASSERT_EQUAL(*tree.find(90), 90);
    

    ASSERT_TRUE(tree.find(100) == tree.end());
    ASSERT_TRUE(tree.find(1) == tree.end());
    ASSERT_TRUE(tree.find(40) == tree.end());
}

TEST(test_min_greater_than_comprehensive) {
    BinarySearchTree<int> tree;
    tree.insert(50);
    tree.insert(25);
    tree.insert(75);
    tree.insert(10);
    tree.insert(35);
    tree.insert(60);
    tree.insert(90);
    
    
    ASSERT_EQUAL(*tree.min_greater_than(50), 60);
    
    ASSERT_EQUAL(*tree.min_greater_than(35), 50);
    ASSERT_EQUAL(*tree.min_greater_than(25), 35);
    ASSERT_EQUAL(*tree.min_greater_than(10), 25);
    ASSERT_TRUE(tree.min_greater_than(90) == tree.end());
    ASSERT_EQUAL(*tree.min_greater_than(0), 10);
}

TEST_MAIN()
