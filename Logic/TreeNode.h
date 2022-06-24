//
// Created by perry on 6/4/22.
//
#include <array>
#include <opencv2/core.hpp>
#include <qdebug.h>

#ifndef IMCOMP_TREENODE_H
#define IMCOMP_TREENODE_H

/*!
 * Used only in TreeNode MIGHT be able to be declared inside it but changing that would require a ton of effort at this point
 */
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
 * Class used for representing nodes inside our quadtree structure
 * @tparam dataType Can only be cv::Vec3b despide being a deplated function as it is split into a header and implementation.
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
    inline unsigned long long colorDistance(TreeNode <dataType> * rhs) {
        unsigned long long total = this->cDif;
        total+=rhs->cDif;
        auto temp1 = (cv::Vec3i) this->content;
        auto temp2 = (cv::Vec3i) rhs->content;
        temp1 -= temp2;
        for (int i = 0; i < 3; i++) {
            total += abs(temp1[i]);
        }
        return total;
    }
    unsigned long long cDif;

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
