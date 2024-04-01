#ifndef BST_H
#define BST_H

#include <iostream>

template <class Type>
struct node
{
    Type info;
    node<Type> *lLink;
    node<Type> *rLink;
};

template <class elemType>
class BST{
public:
    //Overload the assignment operator.
    const BST<elemType>& operator=(const BST<elemType>&);

    //Function to determine whether the binary tree is empty.
    //Postcondition: Returns true if the binary tree is empty;
    // otherwise, returns false.
    bool isEmpty() const;

    //Function to do an inorder traversal of the binary tree.
    //Postcondition: Nodes are printed in inorder sequence.
    void inorderTraversal(void (*visit) (elemType&)) const;  

    //Function to do a preorder traversal of the binary tree.
    //Postcondition: Nodes are printed in preorder sequence.
    void preorderTraversal(void (*visit) (elemType&)) const;

    //Function to do a postorder traversal of the binary tree.
    //Postcondition: Nodes are printed in postorder sequence.
    void postorderTraversal(void (*visit) (elemType&)) const;

    //Function to destroy the binary tree.
    //Postcondition: Memory space occupied by each node
    // is deallocated.
    // root = nullptr;
    void destroyTree();

    //Function to determine if searchItem is in the binary
    //tree.
    //Postcondition: Returns true if searchItem is found in
    // the binary tree; otherwise, returns
    // false.
    bool search(const elemType& searchItem) const;

    //Function to insert insertItem in the binary tree.
    //Postcondition: If there is no node in the binary tree
    // that has the same info as insertItem, a
    // node with the info insertItem is created
    // and inserted in the binary search tree.
    // Takes in a function pointer to display duplicate error.
    void insert(const elemType& insertItem, void (*duplicates) ());

    //Function to delete deleteItem from the binary tree
    //Postcondition: If a node with the same info as
    // deleteItem is found, it is deleted from
    // the binary tree.
    // If the binary tree is empty or
    // deleteItem is not in the binary tree,
    // an appropriate message is printed.
    void deleteNode(const elemType& deleteItem);

    //Copy constructor
    BST(const BST<elemType>& otherTree);

    //Default constructor
    BST();


    ~BST();
    //Destructor

protected:
    node<elemType> *root;

private:
    void copyTree(node<elemType>* &copiedTreeRoot, node<elemType>* otherTreeRoot);
    //Makes a copy of the binary tree to which
    //otherTreeRoot points.
    //Postcondition: The pointer copiedTreeRoot points to
    // the root of the copied binary tree.

    void destroy(node<elemType>* &p);
    //Function to destroy the binary tree to which p points.
    //Postcondition: Memory space occupied by each node, in
    // the binary tree to which p points, is
    // deallocated.
    // p = nullptr;

    void inorder(node<elemType> *p, void (*visit) (elemType&)) const;
    //Function to do an inorder traversal of the binary
    //tree to which p points.
    //Postcondition: Nodes of the binary tree, to which p
    // points, are printed in inorder sequence.

    void preorder(node<elemType> *p, void (*visit) (elemType&)) const;
    //Function to do a preorder traversal of the binary
    //tree to which p points.
    //Postcondition: Nodes of the binary tree, to which p
    // points, are printed in preorder
    // sequence.

    void postorder(node<elemType> *p, void (*visit) (elemType&)) const;
    //Function to do a postorder traversal of the binary
    //tree to which p points.
    //Postcondition: Nodes of the binary tree, to which p
    // points, are printed in postorder
    // sequence.

    void deleteFromTree(node<elemType>* &p);

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

#endif
