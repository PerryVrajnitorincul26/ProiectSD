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
    iMat = cv::imread(filepath,cv::IMREAD_COLOR);
    maxHeight = intlog(4, iMat.total());
    root = new TreeNode<cv::Vec3b>();
    //cv::imshow("test",iMat);
    int size = 1<<maxHeight; // equivalent to 2^maxHeight
    size--;//Since images start at 0,0 they must end at maxsize-1
    generate({0, 0}, {size, size}, root);
}

template<typename dataType>
void ImToQuadTree<dataType>::generate(std::pair<int, int> nw, std::pair<int, int> se, TreeNode<dataType> *cNode) {
    std::pair<int, int> A2;
    std::pair<int, int> A1;
    int diff = (se.first - nw.first+1) / 2;
    if (diff >= 1) {

        for (auto &i: cNode->children) {
            i = new TreeNode<dataType>(branch, cNode);
        }
        A1 = nw;
        A2.first = se.first - diff;
        A2.second = se.second - diff;
        generate(A1, A2, cNode->children[0]);

        A1.first = nw.first + diff;
        A1.second = nw.second;
        A2.first = se.first;
        A2.second = se.second - diff;
        generate(A1, A2, cNode->children[1]);


        A1.first = nw.first + diff;
        A1.second = nw.second + diff;
        A2 = se;
        generate(A1, A2, cNode->children[2]);

        A1.first = nw.first;
        A1.second = nw.second + diff;
        A2.first = se.first - diff;
        A2.second = se.second;
        generate(A1, A2, cNode->children[3]);

        bool idLeaf = true;
        for(auto const &i : cNode->children){
            if(i->type!=leaf) {
                idLeaf = false;
                break;
            }
        }

        for(int i = 0; i<3 && idLeaf;i++){
            if(cNode->children[i]->content != cNode->children[i+1]->content)
                idLeaf = false;
        }
        if(idLeaf)
        {
            cNode->content = cNode->children[0]->content;
            cNode->delChildren();
            cNode->type=leaf;
            qDebug()<<"Ate at:"<<nw.second<<"|"<<nw.first<<" "<<se.second<<"|"<<se.first<<"  "<<cNode->content[0]<<cNode->content[1]<<cNode->content[2]<<(se.first - nw.first+1) ;
        }


    } else {
        cNode->type = leaf;
        if(nw.first<iMat.rows && nw.second<iMat.cols)
            cNode->content = iMat.at<cv::Vec3b>(nw.first, nw.second);
        else
            cNode->content = cv::Vec3b(0,0,0);
        //qDebug()<<cNode->content[0]<<cNode->content[1]<<cNode->content[2];
    }


}


template<typename dataType>
std::vector<std::pair<int, int>> ImToQuadTree<dataType>::CompareQuadtrees(ImToQuadTree<dataType> *T1) {
    std::vector<std::pair<int, int>> Diffrences;
    auto N1 = this->root;
    auto N2 = T1->root;
    std::queue<TreeNode<dataType> *> Line1;
    std::queue<TreeNode<dataType> *> Line2;
    Line1.push(N1);
    Line2.push(N2);
    while (N1 == nullptr && N2 == nullptr) {

        if (N1->CompareNode(N2) != nullptr) {

        }
        for (auto iter: Line1.front()->children) {
            Line1.push(iter);
        }
        for (auto iter: Line2.front()->children) {
            Line2.push(iter);
        }
        N1 = Line1.front();
        N2 = Line2.front();
        Line1.pop();
        Line2.pop();

    }

}

template<typename dataType>
void ImToQuadTree<dataType>::sanityCheck() {
    qDebug() << "sanity restored";
};

//Instantiation is required otherwise linker will not be able to access it.
template
class ImToQuadTree<cv::Vec3b>;
