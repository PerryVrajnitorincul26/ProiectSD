//
// Created by perry on 6/4/22.
//

#include "ImToQuadTree.h"
#include <opencv2/opencv.hpp>
#include <cmath>


inline int intlog(double base, double x) {
    return (int) ceil(log(x) / log(base));
}

template<typename dataType>
ImToQuadTree<dataType>::ImToQuadTree() {
    maxHeight = 0;
    root = nullptr;
}

template<typename dataType>
ImToQuadTree<dataType>::ImToQuadTree(cv::Mat Img):ImToQuadTree() {
    maxHeight = intlog(4, Img.total());
    iMat = Img;
};

template<typename dataType>
ImToQuadTree<dataType>::ImToQuadTree(std::string filepath):ImToQuadTree() {
    iMat = cv::imread(filepath, cv::IMREAD_COLOR);
    maxHeight = intlog(4, iMat.total());
    //Required to use nodeType::root because I didn't realise I was shadowing its value when I created this class :)
    root = new TreeNode<cv::Vec3b>(nodeType::root, nullptr);
    int size = 1 << maxHeight; // equivalent to 2^maxHeight
    size--;//Since images start at 0,0 they must end at maxsize-1
    generate({0, 0}, {size, size}, root);
}

template<typename dataType>
void ImToQuadTree<dataType>::generate(cv::Point nw, cv::Point se, TreeNode<dataType> *cNode) {
    cv::Point A2{0, 0};
    cv::Point A1{0, 0};
    int diff = (se.x - nw.x + 1) / 2;
    if (diff >= 1) {

        for (auto &i: cNode->children) {
            i = new TreeNode<dataType>({0, 0, 0}, nw, se, branch, cNode);
        }
        A1 = nw;
        A2.x = se.x - diff;
        A2.y = se.y - diff;
        generate(A1, A2, cNode->children[0]);

        A1.x = nw.x + diff;
        A1.y = nw.y;
        A2.x = se.x;
        A2.y = se.y - diff;
        generate(A1, A2, cNode->children[1]);


        A1.x = nw.x + diff;
        A1.y = nw.y + diff;
        A2 = se;
        generate(A1, A2, cNode->children[2]);

        A1.x = nw.x;
        A1.y = nw.y + diff;
        A2.x = se.x - diff;
        A2.y = se.y;
        generate(A1, A2, cNode->children[3]);

        bool idLeaf = true;
        for (auto const &i: cNode->children) {
            if (i->type != leaf) {
                idLeaf = false;
                break;
            }
        }

        for (int i = 0; i < 3 && idLeaf; i++) {
            if (cNode->children[i]->content != cNode->children[i + 1]->content)
                idLeaf = false;
        }
        if (idLeaf) {
            cNode->content = cNode->children[0]->content;
            cNode->delChildren();
            cNode->type = leaf;
        } else {
            cNode->propagateProp();
        }


    } else {
        cNode->type = leaf;
        if (nw.x < iMat.rows && nw.y < iMat.cols)
            cNode->content = iMat.at<cv::Vec3b>(nw.x, nw.y);
        else
            cNode->content = cv::Vec3b(0, 0, 0);
    }
    if (cNode->cDif)
        qDebug() << "At:" << nw.y << "|" << nw.x << " " << se.y << "|" << se.x << "  "
                 << cNode->content[0] << cNode->content[1] << cNode->content[2] << (se.x - nw.x + 1);
}


template<typename dataType>
std::vector<std::pair<cv::Point, cv::Point>>
ImToQuadTree<dataType>::getDiff(ImToQuadTree<dataType> *T1, unsigned long long threshold) {
    std::vector<std::pair<cv::Point, cv::Point>> difValues;
    auto N1 = this->root;
    auto N2 = T1->root;
    std::queue<TreeNode<dataType> *> Line1;
    std::queue<TreeNode<dataType> *> Line2;
    Line1.push(N1);
    Line2.push(N2);
    while ((!Line1.empty()) && (!Line2.empty())) {
        auto f1 = Line1.front();
        auto f2 = Line2.front();
        auto relDif = f1->colorDistance(f2);
        if (relDif > threshold) {
            if (f1->type != leaf && f2->type != leaf) {
                for (auto &iter: f1->children) {
                    Line1.push(iter);
                }
                for (auto &iter: f2->children) {
                    Line2.push(iter);
                }
            } else if (f2->type == leaf && f1->type == leaf) {
                difValues.push_back({f1->nw, f1->se});
                ///@warning possible bug here if f1-type is root, i'm assuming no image would be a block of identical pixels however
            } else if (f1->type == leaf) {
                std::queue<TreeNode<dataType> *> unEq;
                unEq.push(f2);
                while (!unEq.empty()) {
                    if (unEq.front()->type != leaf && relDif > threshold) {
                        for (auto &i: unEq.front()->children) {
                            unEq.push(i);
                        }
                    } else {
                        difValues.push_back({unEq.front()->nw, unEq.front()->se});
                    }
                    unEq.pop();
                    ///Undefined behaviour when unEq is empty, however relDif WILL be overwritten by the time it is used again
                    auto relDif = f1->colorDistance(unEq.front());
                }
            } else { //f2->type == leaf
                std::queue<TreeNode<dataType> *> unEq;
                unEq.push(f1);
                while (!unEq.empty()) {
                    if (unEq.front()->type != leaf && relDif > threshold) {
                        for (auto &i: unEq.front()->children) {
                            unEq.push(i);
                        }
                    } else {
                        difValues.push_back({unEq.front()->nw, unEq.front()->se});
                    }
                    unEq.pop();
                    ///Undefined behaviour when unEq is empty, however relDif WILL be overwritten by the time it is used again
                    auto relDif = f2->colorDistance(unEq.front());
                }
            }
        }

        Line1.pop();
        Line2.pop();
    }
    return difValues;
}


template<typename dataType>
void ImToQuadTree<dataType>::sanityCheck() {
    qDebug() << "sanity restored";
};

//Instantiation is required otherwise linker will not be able to access it.
template
class ImToQuadTree<cv::Vec3b>;
