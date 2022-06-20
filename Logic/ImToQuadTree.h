//
// Created by perry on 6/4/22.
//
/*!
 * DO NOT use "using namespace cv" please it'd be ideal if we kept use of OPENCV obvious
 */
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#ifndef IMCOMP_IMTOQUADTREE_H
#define IMCOMP_IMTOQUADTREE_H

template<typename dataType>///I'd suggest using something like cv::Vec3b
class ImToQuadTree {
    ImToQuadTree();

public:
    ImToQuadTree(cv::Mat);
    cv::Mat getPixMap();
};


#endif //IMCOMP_IMTOQUADTREE_H
