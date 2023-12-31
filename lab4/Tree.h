//
// Created by Smile on 2019/4/8.
//

#ifndef C_BINARYDIMEN_TREE_H
#define C_BINARYDIMEN_TREE_H

#include <stdio.h>
#include <iostream>
#include <vector>
using namespace std;

/****************************************************************
 *                    Write your code below
 ****************************************************************/

class TreeNode
{
  friend ostream &operator<<(ostream &out, const TreeNode &b);
  friend class BinaryTree;
  friend class BinaryDimonTree;

private:

public:
  /* data */
  int data[2];
  TreeNode *left;
  TreeNode *right;
  int level = 0;

  /* methods */
  int getX();  /* DO NOT CHANGE */
  int getY();  /* DO NOT CHANGE */
  ~TreeNode(); /* DO NOT CHANGE */
  TreeNode();
  TreeNode(int a, int b);
};


class BinaryDimonTree
{
friend istream &operator>>(istream &in, BinaryDimonTree &tree); /* DO NOT CHANGE */

private:

public:
  /* data */
  TreeNode *root;
  /* methods */
  BinaryDimonTree();          /* DO NOT CHANGE */
  TreeNode *find_nearest_node(int x, int y);  /* DO NOT CHANGE */

  void recur_search(TreeNode *cur, int x, int y, unsigned long long int &min_distance, TreeNode **guess);
  ~BinaryDimonTree();

  unsigned long long int distance(TreeNode *a, TreeNode *b);
};

#endif //C_BINARYDIMEN_TREE_H
