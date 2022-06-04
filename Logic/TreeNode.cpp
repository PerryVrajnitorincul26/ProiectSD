//
// Created by perry on 6/4/22.
//
//TODO: Write tests for all this shit, or at least make sure this actually works
#include "TreeNode.h"

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

