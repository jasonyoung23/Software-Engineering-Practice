#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <limits.h>
#include <vector>
#include <queue>
#include <algorithm>

#include "Tree.h"

using namespace std;

/****************************************************************
 *                    Write your code below
 ****************************************************************/
ostream &operator<<(ostream &out, const TreeNode &b) {
    // TODO: Your code here
    //input a 2D-Tree and the rule is given below;
    return out;
}

TreeNode::TreeNode() {
    data[0] = 0;
    data[1]=0;
    left = NULL;
    right = NULL;
}

TreeNode::TreeNode(int a, int b) {
    data[0] = a;
    data[1] = b;
    left = NULL;
    right = NULL;
}

int TreeNode::getX() {
    // TODO: Your code here
    return data[0];
}

int TreeNode::getY() {
    // TODO: Your code here
    return data[1];
}

TreeNode::~TreeNode() {
    // TODO: Your code here
    delete left;
    delete right;
}

TreeNode* insertTree(int a, int b, TreeNode *rt, int level)
{
    if (rt==NULL){
        rt = new TreeNode(a,b);
        rt->level = level%2;
        return rt;
    }else{
        if (level%2==0){
            if (a < rt->data[0]){
                rt->left = insertTree(a,b,rt->left, level+1);
            }else{
                rt->right = insertTree(a,b,rt->right, level+1);
            }
        }else{
            if (b < rt->data[1]){
                rt->left = insertTree(a,b,rt->left, level+1);
            }else{
                rt->right = insertTree(a,b,rt->right, level+1);
            }
        }
        return rt;
    }
}

istream &operator>>(istream &in, BinaryDimonTree &tree) {
    // TODO: Your code here
    int m=0,a,b;
    in>>m;
    for (int i=0; i<m; i++)
    {
        in>>a>>b;
        tree.root = insertTree(a, b, tree.root, 0);
    }
    return in;
}

BinaryDimonTree::BinaryDimonTree() {
    // TODO: Your code here
    // the construct function of class BDT
    root = NULL;
}

unsigned long long int BinaryDimonTree::distance(TreeNode *a, TreeNode *b){
    unsigned long long int dist = ((a->getX() - b->getX()) * (a->getX() - b->getX())    +
                                   (a->getY() - b->getY()) * (a->getY() - b->getY()));
    return dist;
}
TreeNode *BinaryDimonTree::find_nearest_node(int x, int y) {
    // TODO: Your code here
    TreeNode *guess = NULL;
    unsigned long long int best_dist = 9223372036854775807;
    recur_search(root, x, y, best_dist, &guess);
    return (guess);
}

void BinaryDimonTree::recur_search(TreeNode *cur, int x, int y,
                                   unsigned long long int  &min_distance, TreeNode **guess) {
    // TODO: Your code here
    TreeNode *A = new TreeNode(x,y);
    if (cur==NULL) {
        return ;
    }
    unsigned long long int  dist = distance(cur,A);
    if (
            (dist < min_distance) ||
            (dist == min_distance  && cur->getX() < (*guess)->getX()) ||
            (dist == min_distance  && cur->getX() == (*guess)->getX() && cur->getY() < (*guess)->getY())
            ){
        min_distance = dist;
        *guess = cur;
    }
    int ii = cur->level;
    TreeNode* otherbranch = NULL;
    if (A->data[ii] < cur->data[ii]){
        otherbranch = cur->right;
        recur_search(cur->left,x,y,min_distance,guess);
    }else{
        otherbranch = cur->left;
        recur_search(cur->right,x,y,min_distance,guess);
    }

    if((cur->data[ii] - A->data[ii]) * (cur->data[ii] - A->data[ii]) < min_distance) {
        recur_search(otherbranch, x, y, min_distance, guess);
    }
    return;
}

BinaryDimonTree::~BinaryDimonTree()
{
    // TODO: Your code here DONE
    //the deconstruct function which is used to reclaim all the data in the 2D-Tree,
    //and you should explain your implementation to us when your lab is examined
    delete root;
}

