//
// Created by perry on 6/4/22.
//
/*!
 * DO NOT use "using namespace cv" please it'd be ideal if we kept use of OPENCV obvious
 */
#include "TreeNode.h"
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <vector>
#include <queue>
#ifndef IMCOMP_IMTOQUADTREE_H
#define IMCOMP_IMTOQUADTREE_H

template<typename dataType>///I'd suggest using something like cv::Vec3b
class ImToQuadTree {
    cv::Mat iMat;
    int maxHeight;
    TreeNode<dataType> *root;
    TreeNode<dataType>*generate( std::pair<int,int>nw,std::pair<int,int>se, TreeNode<dataType> *parent);

public:

    ImToQuadTree();
    ImToQuadTree(cv::Mat);
    ImToQuadTree(std::string filepath);
    std::vector<std::pair<int,int>> CompareQuadtrees(ImToQuadTree<dataType>*);
    cv::Mat getPixMap();

};


#endif //IMCOMP_IMTOQUADTREE_H
