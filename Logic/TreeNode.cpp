//
// Created by perry on 6/4/22.
//
//TODO: Write tests for all this shit, or at least make sure this actually works
#include "TreeNode.h"
    #include <QList>
template<typename dataType>
TreeNode<dataType>::TreeNode() {
    content = dataType();
    for (auto iter: children) {
        iter = nullptr;
    }
    type = leaf;
}

template<typename dataType>
TreeNode<dataType>::TreeNode(dataType content, nodeType type) {
    content = dataType();
    for (auto iter: children) {
        iter = nullptr;
    }
    this->type = type;
    this->content = content;
}

template<typename dataType>
TreeNode<dataType>::~TreeNode() {
    if (this->type != leaf) {
        for (auto iter: children) {
            delete iter; // Delete on null pointer has no effect afaik.
        }
    }
}

template<typename dataType>
dataType TreeNode<dataType>::avgChildren() {
    dataType tempValue = dataType();
    for (auto iter: children) {
        tempValue += iter->content;
    }
    return tempValue/4;
}

template<typename dataType>
void TreeNode<dataType>::eatChildren() {
    for (auto iter: children) {
        if (iter->type != leaf) {
            iter->eatChildren;
        }
        delete iter;
    }
}
template<typename dataType>
TreeNode<dataType>::TreeNode(dataType content, nodeDirection direction){
    for(auto iter:children){
        iter=nullptr;
    }
    this->content=content;
    this->type=root;
    this->Parent=nullptr;
};
template<typename dataType>
bool TreeNode<dataType>::CorectDirection(nodeRight D){
  if(D==N){
      if(this->direction==Ne || this->direction==Nw){
          return true;
      }
      else return false;
  }
  if(D==E){
      if(this->direction==Ne||this->direction==Se){
          return true;
      }
      else return false;
  }
  if(D==W){
      if(this->direction==Nw||this->direction==Sw){
          return true;
      }
      else return false;
  }
  if(D==S){
      if(this->direction==Sw||this->direction==Se){
          return true;
      }
      else return false;
  }
  return false;
};
template<typename dataType>
nodeDirection TreeNode<dataType>::OpositeDirection(){
    if(this->direction==Ne){
        return Nw;
    }
    if(this->direction==Se){
        return Sw;
    }
    if(this->direction==Nw){
        return Ne;
    }
    if(this->direction==Sw){
        return Se ;
    }
};

template<typename dataType>
TreeNode<dataType>* TreeNode<dataType>::DirectionChild(nodeDirection D){
    if(D==Ne){
        return this->children[0];
    }
    if(D==Se){
        return this->children[1];
    }
    if(D==Sw){
        return this->children[2];
    }
    if(D==Nw){
        return this->children[3];
    }
};
template<typename dataType>
 TreeNode<dataType>* TreeNode<dataType>::GSN(nodeRight Point){
   TreeNode*N=new TreeNode;
   TreeNode*Rez=new TreeNode;
   Rez=this;
   N=this->Parent;
   bool WaytoGo=true;
   QList<nodeDirection> Road;
   while(WaytoGo&&Rez->Parent!=nullptr){
       WaytoGo=CorectDirection(Point);
       Rez=N;
       N=N->Parent;
       Road.append(Rez->OpositeDirection());
   }
   if(Rez->Parent==nullptr){
       return nullptr;
   }
   Rez=N;
   while(Road.size()>0){
       nodeDirection W=Road.first();
       if(this->type!=leaf){
           Rez=Rez->DirectionChild(W);
       }
       else{
           break;
       }
       Road.pop_front();
   }
}
 template<typename dataType>
 TreeNode<dataType>* TreeNode<dataType>::CompareNode(TreeNode<dataType>*Pixel){
     if(this->content!=Pixel->content){
         return Pixel;
     }
     return nullptr;
 }
