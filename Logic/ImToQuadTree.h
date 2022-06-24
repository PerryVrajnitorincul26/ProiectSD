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

template<typename dataType>
class ImToQuadTree {
    cv::Mat iMat;
    int maxHeight;
    TreeNode<dataType> *root;
    void generate(cv::Point nw, cv::Point se, TreeNode<dataType> *cNode);

    ImToQuadTree();

public:
    void showDifVect(std::vector<std::pair<cv::Point, cv::Point>>);


    ImToQuadTree(std::string filepath);

    std::vector<std::pair<cv::Point, cv::Point>> getDiff(ImToQuadTree<dataType> *, unsigned long long threshold);

    void sanityCheck();

};


#endif //IMCOMP_IMTOQUADTREE_H
