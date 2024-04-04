#ifndef BST_H
#define BST_H

#include <iostream>

/// @brief Struct representing a node in a binary search tree.
template <class Type>
struct node
{
    ///< Information stored in the node.
    Type info;

    ///< Pointer to the left child node.
    node<Type> *lLink;

    ///< Pointer to the right child node.
    node<Type> *rLink; 
};

/// @brief Class representing a Binary Search Tree (BST).
template <class elemType>
class BST{
public:
    ///Overloaded assignment operator.
    const BST<elemType>& operator=(const BST<elemType>&);

    /// @brief Checks if the binary tree is empty.
    /// @return True if the binary tree is empty, false otherwise.
    bool isEmpty() const;

    /// @brief Performs an inorder traversal of the binary tree.
    /// @param visit Pointer to a function that will be applied to each node's info.
    void inorderTraversal(void (*visit) (elemType&)) const;  

    /// @brief Performs a preorder traversal of the binary tree.
    /// @param visit Pointer to a function that will be applied to each node's info.
    void preorderTraversal(void (*visit) (elemType&)) const;

    /// @brief Performs a postorder traversal of the binary tree.
    /// @param visit Pointer to a function that will be applied to each node's info.
    void postorderTraversal(void (*visit) (elemType&)) const;

    /// @brief Destroys the binary tree.
    // Postcondition: Memory space occupied by each node
    // is deallocated.
    // root = nullptr;
    void destroyTree();

    /// @brief Searches for an item in the binary tree.
    /// @param searchItem The item to search for.
    /// @return True if the item is found, false otherwise.
    //Postcondition: Returns true if searchItem is found in
    // the binary tree; otherwise, returns
    // false.
    bool search(const elemType& searchItem) const;

    /// @brief Inserts an item into the binary tree.
    /// @param insertItem The item to insert.
    /// @param duplicates Pointer to a function when duplicate is found.
    void insert(const elemType& insertItem, void (*duplicates) ());

    /// @brief Deletes a node from the binary tree.
    /// @param deleteItem The item to delete.
    void deleteNode(const elemType& deleteItem);

    /// @brief Copy constructor of the BST class.
    /// Runs the copytree function if not null. 
    /// @param othertree the target tree to copy from.
    BST(const BST<elemType>& otherTree);

    /// @brief Default constructor.
    BST();

    /// @brief Destructor.
    ~BST();

    /// @brief Calculates the total number of elements in the BST.
    /// @return The total number of elements in the BST.
    int size();

protected:
    /// Pointer to the root node of the BST.
    node<elemType> *root;

private:

    /// @brief Makes a copy of the binary tree.
    /// @param copiedTreeRoot Reference to the root of the copied tree.
    /// @param otherTreeRoot Pointer to the root of the tree to be copied.
    void copyTree(node<elemType>* &copiedTreeRoot, node<elemType>* otherTreeRoot);

    /// @brief Destroys the binary tree.
    /// @param p Pointer to the root of the tree to be destroyed.
    void destroy(node<elemType>* &p);

    /// @brief Performs an inorder traversal of the binary tree.
    /// @param p Pointer to the root node of the subtree to be traversed.
    /// @param visit Pointer to a function that will be applied to each node's info.
    void inorder(node<elemType> *p, void (*visit) (elemType&)) const;

    /// @brief Performs a preorder traversal of the binary tree.
    /// @param p Pointer to the root node of the subtree to be traversed.
    /// @param visit Pointer to a function that will be applied to each node's info.
    void preorder(node<elemType> *p, void (*visit) (elemType&)) const;

    /// @brief Performs a postorder traversal of the binary tree.
    /// @param p Pointer to the root node of the subtree to be traversed.
    /// @param visit Pointer to a function that will be applied to each node's info.
    void postorder(node<elemType> *p, void (*visit) (elemType&)) const;

    /// @brief Deletes a node from the binary tree.
    /// @param p Pointer to the root of the subtree where the node is to be deleted.
    void deleteFromTree(node<elemType>* &p);

    /// @brief Counts the number of nodes in the binary tree.
    /// @param current Pointer to the root node of the subtree.
    /// @return The total number of nodes in the subtree.
    int countnodes(node<elemType> *current);

};

// implementations

template <class elemType>
const BST<elemType>& BST<elemType>::operator=(const BST<elemType>& otherTree)
{
    if (this != &otherTree) //avoid self-copy
        {
        if (root != nullptr) {//if the binary tree is not empty,
            //destroy the binary tree
            destroy(root);  
        }
        if (otherTree.root == nullptr) {
            root = nullptr;
        } else {
            copyTree(root, otherTree.root);
        }
        }//end else
    return *this;
}

template <class elemType>
bool BST<elemType>::isEmpty() const
{
    return (root == nullptr);
}

template <class elemType>
void BST<elemType>::inorderTraversal(void (*visit) (elemType&)) const
{
    inorder(root, *visit);
}

template <class elemType>
void BST<elemType>::preorderTraversal(void (*visit) (elemType&)) const
{
    preorder(root, *visit);
}

template <class elemType>
void BST<elemType>::postorderTraversal(void (*visit) (elemType&)) const
{
    postorder(root, *visit);
}

template <class elemType>
void BST<elemType>::destroyTree()
{
    destroy(root);
}

template <class elemType>
BST<elemType>::BST(const BST<elemType>& otherTree)
{
    if (otherTree.root == nullptr) { //otherTree is empty
        root = nullptr;
    } else {
        copyTree(root, otherTree.root);        
    }
}

template <class elemType>
BST<elemType>::BST()
{
    root = nullptr;
}

template <class elemType>
BST<elemType>::~BST()
{
    destroy(root);
}

template <class elemType>
void BST<elemType>::copyTree(node<elemType>* &copiedTreeRoot, node<elemType>* otherTreeRoot)
{
    if (otherTreeRoot == nullptr)
        copiedTreeRoot = nullptr;
    else
    {
        copiedTreeRoot = new node<elemType>;
        copiedTreeRoot->info = otherTreeRoot->info;
        copyTree(copiedTreeRoot->lLink, otherTreeRoot->lLink);
        copyTree(copiedTreeRoot->rLink, otherTreeRoot->rLink);
    }
}

template <class elemType>
void BST<elemType>::destroy(node<elemType>* &p)
{
    if (p != nullptr) {
        destroy(p->lLink);
        destroy(p->rLink);
        delete p;
        p = nullptr;
    }   
}

template <class elemType>
void BST<elemType>::inorder (node<elemType> *p, void (*visit) (elemType&)) const
{
    if (p != nullptr)
    {
        inorder(p->lLink, *visit);
        (*visit)(p->info);
        inorder(p->rLink, *visit);
    }
}
template <class elemType>
void BST<elemType>::preorder (node<elemType> *p, void (*visit) (elemType&)) const
{
    if (p != nullptr)
    {
        (*visit)(p->info);
        preorder(p->lLink, *visit);
        preorder(p->rLink, *visit);
    }
}

template <class elemType>
void BST<elemType>::postorder(node<elemType> *p, void (*visit) (elemType&)) const
{
    if (p != nullptr)
    {
        postorder(p->lLink, *visit);
        postorder(p->rLink, *visit);
        (*visit)(p->info);
    }
}

template <class elemType>
bool BST<elemType>::search (const elemType& searchItem) const {
    node<elemType> *current;
    bool found = false;
    if (root == nullptr) {
        std::cout << "Cannot search an empty tree." << std::endl;        
    } else {
        current = root;
        while (current != nullptr && !found) {
            if (current->info == searchItem) {
                found = true;                
            } else if (current->info > searchItem) {
                current = current->lLink;                
            } else {
                current = current->rLink;                
            }

        }//end while
    }//end else
    return found;
}//end search

template <class elemType>
void BST<elemType>::insert(const elemType& insertItem, void (*duplicates) ()) {
    node<elemType> *current; //pointer to traverse the tree
    node<elemType> *trailCurrent = nullptr; //pointer behind current
    node<elemType> *newNode; //pointer to create the node
    newNode = new node<elemType>;
    newNode->info = insertItem;
    newNode->lLink = nullptr;
    newNode->rLink = nullptr;
    if (root == nullptr){
        root = newNode;        
    } else {
        current = root;
        while (current != nullptr) {
            trailCurrent = current;
            if (current->info == insertItem) {
                (*duplicates) ();
                return;
            } else if (current->info > insertItem) {
                current = current->lLink;                
            } else {
                current = current->rLink;
            }
        }//end while
        if (trailCurrent->info > insertItem)
        trailCurrent->lLink = newNode;
        else
        trailCurrent->rLink = newNode;
    }
}//end insert

template <class elemType>
void BST<elemType>::deleteFromTree(node<elemType>* &p) {
    node<elemType> *current; //pointer to traverse the tree
    node<elemType> *trailCurrent; //pointer behind current
    node<elemType> *temp; //pointer to delete the node
    if (p == nullptr) {
        std::cout << "Error: The node to be deleted does not exist." << std::endl;        
    } else if (p->lLink == nullptr && p->rLink == nullptr) {
        temp = p;
        p = nullptr;
        delete temp;
    } else if (p->lLink == nullptr) {
        temp = p;
        p = temp->rLink;
        delete temp;
    } else if (p->rLink == nullptr) {
        temp = p;
        p = temp->lLink;
        delete temp;
    } else {
        current = p->lLink;
        trailCurrent = nullptr;
        while (current->rLink != nullptr)
        {
            trailCurrent = current;
            current = current->rLink;
        }//end while

        p->info = current->info;
        if (trailCurrent == nullptr){
        //current did not move;
        //current == p->lLink; adjust p  
        p->lLink = current->lLink;        
        } else {
            trailCurrent->rLink = current->lLink;            
        }
        delete current;
    }//end else
} //end deleteFromTree

template <class elemType>
void BST<elemType>::deleteNode (const elemType& deleteItem) {
    node<elemType> *current; //pointer to traverse the tree
    node<elemType> *trailCurrent; //pointer behind current
    bool found = false;
    if (this->root == nullptr) {
        std::cout << "Cannot delete from an empty tree."
        << std::endl;    
    } else {
        current = this->root;
        trailCurrent = this->root;
        while (current != nullptr && !found) {
            if (current->info == deleteItem){
                found = true;            
            } else {
                trailCurrent = current;
                if (current->info > deleteItem)
                current = current->lLink;
                else
                current = current->rLink;
            }
        }//end while
        if (current == nullptr){
            std::cout << "The item to be deleted is not in the tree."
            << std::endl;
        } else if (found) {
            if (current == this->root) {
                deleteFromTree(this->root);            
            } else if (trailCurrent->info > deleteItem) {
                deleteFromTree(trailCurrent->lLink);            
            } else {
                deleteFromTree(trailCurrent->rLink);            
            }
        } else {
            std::cout << "The item to be deleted is not in the tree."
            << std::endl;            
        }
    }
} //end deleteNode

template <class elemType>
int BST<elemType>::countnodes(node<elemType> *current) {
    if (current == nullptr) {
        return 0;
    } else {
        return 1 + countnodes(current->lLink) + countnodes(current-> rLink);
    }
}

template <class elemType>
int BST<elemType>::size() {
    if (this->isEmpty()) {
        return 0;
    } else {
        return countnodes(root);
    }
}

#endif
