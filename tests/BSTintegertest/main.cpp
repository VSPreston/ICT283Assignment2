#include "BST.h"
#include <iostream>
#include <fstream>
#include <sstream>

// g++ -Wall -g -std=c++11 -ftime-report main.cpp -o main

int main() {
    BST<int> intbst;

    std::ifstream inputfile("numbers.txt");
    if (!inputfile) return -1;

    int number;
    while (inputfile >> number) {
        intbst.insert(number);
    }

    std::cout << "Testing Traversals:" << std::endl;
    std::cout << "---InOrder Traversal---" << std::endl;
    intbst.inorderTraversal();
    std::cout << "\n---PostOrder Traversal---" << std::endl;
    intbst.postorderTraversal();
    std::cout << "\n---PreOrder Traversal---" << std::endl;
    intbst.preorderTraversal();

    std::cout << "\nTesting search functions:" << std::endl;
    std::cout << "Finding Number 23:" << std::boolalpha <<intbst.search(23) << std::endl;
    std::cout << "Finding Number 16:" << std::boolalpha <<intbst.search(16) << std::endl;
    std::cout << "Finding Number 1:" << std::boolalpha <<intbst.search(1) << std::endl;
    std::cout << "\nTesting delete function" << std::endl;
    std::cout << "---Deleting 16---" << std::endl;
    intbst.deleteNode(16);
    std::cout << "---InOrder Traversal---" << std::endl;
    intbst.inorderTraversal();
    std::cout << "\nFinding Number 16:" << std::boolalpha << intbst.search(16) << std::endl;

    std::cout << "\nTesting insert functions:" << std::endl;
    std::cout << "---Inserting new number: 46---" << std::endl;
    intbst.insert(46);
    std::cout << "---InOrder Traversal---" << std::endl;
    intbst.inorderTraversal();
    std::cout << "\nFinding Number 46:" << std::boolalpha << intbst.search(46) << std::endl;

    return 0;

}
