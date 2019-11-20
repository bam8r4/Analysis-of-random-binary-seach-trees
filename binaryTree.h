//Author of this code: Brent Moran

#ifndef BINARYTREE_H
#define BINARYTREE_H
#include <iostream>
#include <algorithm>    //This is to allow use of max command in treeHeight method.
using namespace std;

//Inserts a new node into the tree with the value in the TreeNode pointer.
//That value is then inserted into the tree.

class binaryTree
{
private:
  struct TreeNode
  {
      int height;        //Level in which the node is located.
      int value;         //Value in the node
      TreeNode *left;    //Pointer to left child
      TreeNode *right;   //Pointer to right child
  };

  TreeNode *root;   //Pointer to root node
  int maxHeight = 0;  //We are assuming the tree has nodes. This value will be reset when the height function and delete functions are called.
  int *maxHeightPtr = &maxHeight;

  //Private member functions
  void insert(TreeNode *&, TreeNode *&, int);
  void destroySubTree(TreeNode *);
  void deleteNode(int value, TreeNode *&);
  void makeDeletion(TreeNode *&);
  void treeHeight(TreeNode *, int *);
  void heightSetter(TreeNode *, int);
  void heightSetterDriver(int);



public:
  //Constructor
  binaryTree()
  {root = nullptr;}

  //Destructor
  ~binaryTree()
  {destroySubTree(root);}

  //Binary tree operations
  void insertNode(int value, int level);
  void remove(int value);
  int getMaxHeight();  //This just returns the value of max height so it can be printed.


  int treeHeight()
  {
    treeHeight(root, maxHeightPtr);
  }

};
void binaryTree::insert(TreeNode *&nodePtr,  TreeNode *&newNode, int level)
{
    if(nodePtr == nullptr)
    {
      nodePtr = newNode;    //Insert the node.
      nodePtr->height = level;
    }
    else if(newNode->value < nodePtr->value)
    {
      level = level + 1;
      insert(nodePtr->left, newNode, level);   //Search the left branch.
    }
    else
    {
      level = level + 1;
      insert(nodePtr->right, newNode, level);    //Search the right branch.
    }
}

//Creates new node and stores a num in it. It then passes that value to insert function.
void binaryTree::insertNode(int num, int level = 1)
{
    TreeNode *newNode = nullptr;    //Pointer to a new node.


    //Creation of a new node with num stored in it.
    newNode = new TreeNode;
    newNode->value = num;
    newNode->left = newNode->right = nullptr;

    insert(root, newNode, level);   //Insert new node.
}

//Called by the destructor to delete all nodes in the tree.
void binaryTree::destroySubTree(TreeNode *nodePtr)
{
    if(nodePtr)
    {
        if(nodePtr->left)
        {
          destroySubTree(nodePtr->left);
        }

        if(nodePtr->right)
        {
          destroySubTree(nodePtr->right);
        }
        delete nodePtr;
    }
}


//Calls deleteNode to delete the node with the value passes into deleteNode.
void binaryTree::remove(int num)
{
    this->maxHeight = 0; //If we delete a node we need to reset max height to zero for the next call of the treeHeight function.
    deleteNode(num, root);
}

//Deletes the node with value member same as num.
void binaryTree::deleteNode(int num, TreeNode *&nodePtr)
{
    if(num < nodePtr->value)
    {
      deleteNode(num, nodePtr->left);
    }
    else if(num > nodePtr->value)
    {
      deleteNode(num, nodePtr->right);
    }
    else
    {
      makeDeletion(nodePtr);
    }
}

void binaryTree::makeDeletion(TreeNode *&nodePtr)
{
    //Temp pointer to use in reattaching left subtree.
    TreeNode *tempNodePtr = nullptr;

    if(nodePtr == nullptr)
    {
      cout<<"Error: Can't delete an empty node."<<endl;
    }
    else if(nodePtr->right == nullptr)
    {
      tempNodePtr = nodePtr;
      nodePtr  = nodePtr->left;  //Reattaching the left child.
      delete tempNodePtr;
    }
    else if(nodePtr->left == nullptr)
    {
      tempNodePtr = nodePtr;
      nodePtr  = nodePtr->right;  //Reattaching right child.
      delete tempNodePtr;
    }
    else   //If the node has more than one child.
    {
      tempNodePtr = nodePtr->right;  //Move one node to the right.

      while(tempNodePtr->left)  //Go to the end left node.
      {
        tempNodePtr = tempNodePtr->left;
      }
      tempNodePtr->left = nodePtr->left;  //Reattach left subtree.
      tempNodePtr = nodePtr;

      nodePtr = nodePtr->right;  //Reattach right subtree.
      delete tempNodePtr;

    }
}


void binaryTree::heightSetterDriver(int setterValue = 1)
{
  heightSetter(root, setterValue);
}
void binaryTree::heightSetter(TreeNode *nodePtr, int setterValue)
{
  if(nodePtr)
  {
    nodePtr->height = setterValue;
    setterValue += 1;
    heightSetter(nodePtr->left,setterValue);
    heightSetter(nodePtr->right,setterValue);
  }

}

//Calling treeHeight recursively to find the height of the tree.
void binaryTree::treeHeight(TreeNode *nodePtr, int *maxHeightPtr)
{
  if(nodePtr)
  {

    if(nodePtr->height > this->maxHeight)
    {
      this->maxHeight = nodePtr->height;
    }
      treeHeight(nodePtr->left,maxHeightPtr);
      treeHeight(nodePtr->right,maxHeightPtr);
  }

}

//Output the height of the tree.
int binaryTree::getMaxHeight()
{
  heightSetterDriver();
  treeHeight(root, maxHeightPtr);
  return this->maxHeight;
}



#endif
