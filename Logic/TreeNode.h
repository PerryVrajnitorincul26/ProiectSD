//
// Created by perry on 6/4/22.
//
#include <array>
#include <qdebug.h>
#ifndef IMCOMP_TREENODE_H
#define IMCOMP_TREENODE_H


enum nodeType:char {
    root, branch, leaf
};
enum nodeDirection:char{
    Nw, Sw, Se, Ne, C

};
enum nodeRight :char{
    N, S, W, E
};

/*!
 *
 * @tparam dataType self explanatory container
 * @warning UNTESTED CODE
 * @todo test this lmao
 */
template<typename dataType>
class TreeNode {
public:
    nodeType type;

    std::array<TreeNode *,4> children;
    nodeDirection direction;
    TreeNode*Parent;
    dataType content;

    TreeNode();
    explicit TreeNode(dataType, nodeType type = leaf);
     explicit TreeNode(dataType,nodeDirection direction=C);//Avoid being called implicitly
    ~TreeNode();
    TreeNode* GSN(nodeRight);
    bool CorectDirection(nodeRight);
    nodeDirection OpositeDirection();
    TreeNode*CompareNode(TreeNode*);

    void eatChildren();
    dataType avgChildren();
    TreeNode* DirectionChild(nodeDirection);

};



#endif //IMCOMP_TREENODE_H
