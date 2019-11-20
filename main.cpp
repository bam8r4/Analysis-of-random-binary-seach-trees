//Author of this code: Brent Moran

#include <iostream>
#include <cstdlib>
#include "binaryTree.h"   //We are using a binary tree that was written for a previous project.
using namespace std;      //do to this some of the methods will not apply here. We will modify the ones we need for our purposes.

int main()
{
  int n = 1; //This value after cin will represent the number of nodes each binary tree will have.
  int t = 1; //This value after cin will represent the number of trees that we will create with n nodes.
  int sum = 0; //This value will store the heights of our trees. Then will be used to average the values.

  do{
      cout<<"\nInput how many trees should be formed: ";
      cin>>t;
      cout<<"\nInput what the size of each tree should be: ";
      cin>>n;

      int height[t];

      //This will build our binary search tree.
      for(int i = 0; i < t; i++)
      {

        binaryTree tree;    //Each run through the loop we are making a new binary tree.

        for(int j = 0; j < n; j++)
        {
          tree.insertNode(rand()%10000);    //We are inserting n random integer nodes in the tree.
        }
        height[i] = tree.getMaxHeight();    //Here is where we will return an integer value that represents our height.
      }



      cout<<endl;
      for(int i = 0; i < t; i++)
      {
        //cout<<"The height of tree "<<i+1<<" is "<<height[i]<<endl;
        sum += height[i];
      }

      cout<<"The average height of "<<t<<" trees with "<<n<<" nodes is: "<<sum/t<<endl;
      cout<<endl;
      sum = 0;
    }while(t>0 && n>0);

}
