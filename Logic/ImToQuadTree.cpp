//
// Created by perry on 6/4/22.
//

#include "ImToQuadTree.h"
#include <cmath>


int intlog(double base, double x) {
    return (int)(log(x) / log(base));
}
template<typename dataType>
cv::Mat ImToQuadTree<dataType>::getPixMap() {

};

template<typename dataType>
TreeNode<dataType>* ImToQuadTree<dataType>::generate( std::pair<int,int>nw,std::pair<int,int>se, TreeNode<dataType> *parent)
{
    std::pair<int,int>A2;
    std::pair<int,int>A1;
    int diff = A2.first - A1.first;
    if(diff>1){

            A1=nw;
            A2.first=se.first-diff;
            A2.second=se.second-diff;
            generate(A1,A2,parent[0]);

            A1.first=nw.first+diff;
            A1.second=nw.first;
            A2.first=se.first;
            A2.second=se.second-diff;
            generate(A1,A2,parent[1]);


            A1.first=nw.first+diff;
            A1.second=nw.second+diff;
            A2 = se;
            generate(A1,A2,parent[2]);

            A1.first=nw.first;
            A1.second=nw.second+diff;
            A2.first=se.first-diff;
            A2.second=se.second;
            generate(A1,A2,parent[3]);


        }
    else{
        int i=A2.first,j=A2.second;
            TreeNode<dataType>*N=TreeNode(iMat.at<cv::Vec3b>(i,j),leaf);
          return N  ;

    }


}

template<typename dataType>
ImToQuadTree<dataType>::ImToQuadTree()
{
    maxHeight = 0;
    root = nullptr;
}

template <typename dataType>
ImToQuadTree<dataType>::ImToQuadTree(cv::Mat Img){
   maxHeight=intlog(4,Img.total());
   iMat = Img;
};

template <typename dataType>
ImToQuadTree<dataType>::ImToQuadTree(std::string filepath){
    iMat = cv::imread(filepath);

};
template <typename dataType>
std::vector<std::pair<int,int>> ImToQuadTree<dataType>::CompareQuadtrees(ImToQuadTree<dataType>*T1){
    TreeNode<dataType>* N1=new TreeNode<dataType>;
    TreeNode<dataType>* N2=new TreeNode<dataType>;
     std::vector<std::pair<int,int>> Diffrences;
    N1=this->root;
    N2=T1->root;
    std::queue<TreeNode<dataType>> Line1;
     std::queue<TreeNode<dataType>> Line2;
     Line1.push(N1);
     Line2.push(N2);
    while(N1==nullptr&&N2==nullptr){

        if(N1->CompareNode(N2)!=nullptr){

        }
        for(auto iter: Line1.front()->children){
            Line1.push(iter);
        }
        for(auto iter: Line2.front()->children){
            Line2.push(iter);
        }
        N1=Line1.first();
        N2=Line2.first();
        Line1.pop();
        Line2.pop();

    }

};
