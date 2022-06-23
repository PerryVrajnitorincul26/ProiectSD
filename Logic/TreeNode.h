//
// Created by perry on 6/4/22.
//
#include <array>
#include <opencv2/core.hpp>
#include <qdebug.h>

#ifndef IMCOMP_TREENODE_H
#define IMCOMP_TREENODE_H


enum nodeType : char {
    root, branch, leaf
};
enum nodeDirection : char {
    Nw, Sw, Se, Ne, C

};
enum nodeRight : char {
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

    std::array<TreeNode *, 4> children;
    nodeDirection direction;
    TreeNode *parent;
    dataType content;
    cv::Point nw, se;

    unsigned long long cDif{};

    /*!
     * Intentionally declared as implicit constructor
     */
    TreeNode(nodeType = leaf, TreeNode * = nullptr);

    explicit TreeNode(dataType, cv::Point= {0, 0}, cv::Point= {0, 0}, nodeType type = leaf, TreeNode *parent = nullptr);

    explicit TreeNode(dataType, nodeDirection direction = C);//Avoid being called implicitly
    ~TreeNode();

    TreeNode *GSN(nodeRight);

    bool CorectDirection(nodeRight);

    nodeDirection OpositeDirection();

    TreeNode *CompareNode(TreeNode *);

    void delChildren();

    void propagateProp();

    TreeNode *DirectionChild(nodeDirection);

};


#endif //IMCOMP_TREENODE_H
