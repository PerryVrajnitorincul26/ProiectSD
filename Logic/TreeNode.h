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
/*!
 *
 * @tparam dataType self explanatory container
 * @warning UNTESTED CODE
 * @todo test this lmao
 */
template<typename dataType>
class TreeNode {
    dataType content;
public:
    nodeType type;
    std::array<TreeNode *,4> children;
    TreeNode();
    explicit TreeNode(dataType, nodeType type = leaf);//Avoid being called implicitly
    ~TreeNode();
    void eatChildren();
    dataType avgChildren();
};



#endif //IMCOMP_TREENODE_H
