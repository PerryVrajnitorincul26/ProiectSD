//
// Created by perry on 6/4/22.
//
#include "TreeNode.h"
#include <QList>

template<typename dataType>
/*!
 *  This is also the implicit constructor, watch out this creates leafs by default
 * @tparam dataType can only be cv::Vec3b as of right now
 * @param type set to leaf By default
 * @param parent parent of node to be inserted
 */
TreeNode<dataType>::TreeNode(nodeType type, TreeNode *parent) {
    content = dataType();
    for (auto &iter: children) {
        iter = nullptr;
    }
    this->cDif = 0;
    this->parent = parent;
    this->type = type;
}

/*!
 *  Also assigns a value to nw, se and content
 * @tparam dataType can only be cv::Vec3b as of right now
 * @param content
 * @param upperLeft Point representing upper left corner of the area this node represents
 * @param lowerRight Point representing upper left corner of the area this node represents
 * @param type Either leaf, branch or root
 * @param parent Pointer to previous node in Tree, should be null when type = root
 */
template<typename dataType>
TreeNode<dataType>::TreeNode(dataType content, cv::Point upperLeft, cv::Point lowerRight, nodeType type,
                             TreeNode *parent):TreeNode(type, parent) {
    this->content = content;
    nw = upperLeft;
    se = lowerRight;
}

/*!
 * Simple deconstructor should hopefully work
 * @tparam dataType
 * @param content
 * @param type
 */
template<typename dataType>
TreeNode<dataType>::~TreeNode() {
    if (this->type != leaf) {
        for (auto &iter: children) {
            delete iter; // Delete on null pointer has no effect AFAIK.
        }
    }
}

/*!
 * Function that sets this nodes content equal to the average of it's children and avarage colour difference (cdif) to
 * the total of it's children + the difference between the colours of it's children and itself
 * The purpose of cDif is to enable a more "fuzzy match" match as that may be required when dealing with JPEG images
 * @tparam dataType
 */
template<typename dataType>
void TreeNode<dataType>::propagateProp() {
    cv::Vec3i avg{0, 0, 0};
    if (this->type != leaf) {
        for (const auto &it: this->children) {
            avg += it->content;
        }
        avg /= 4;
        this->content = (cv::Vec3i) avg;
        ///Propagate average
        for (const auto &it: this->children) {

            auto temp = avg - cv::Vec3i(it->content);
            this->cDif += it->cDif;
            this->cDif += abs(temp[0]);
            this->cDif += abs(temp[1]);
            this->cDif += abs(temp[2]);
        }

    }
}

/*!
 * Simple function used to safely remove child nodes
 * also used in Generation
 * @tparam dataType
 */
template<typename dataType>
void TreeNode<dataType>::delChildren() {
    for (auto &iter: children) {
        delete iter;
        iter = nullptr;
    }
}

template<typename dataType>
TreeNode<dataType>::TreeNode(dataType content, nodeDirection direction) {
    for (auto &iter: children) {
        iter = nullptr;
    }
    this->content = content;
    this->type = root;
    this->parent = nullptr;
};

template<typename dataType>
bool TreeNode<dataType>::CorectDirection(nodeRight D) {
    if (D == N) {
        if (this->direction == Ne || this->direction == Nw) {
            return true;
        } else return false;
    }
    if (D == E) {
        if (this->direction == Ne || this->direction == Se) {
            return true;
        } else return false;
    }
    if (D == W) {
        if (this->direction == Nw || this->direction == Sw) {
            return true;
        } else return false;
    }
    if (D == S) {
        if (this->direction == Sw || this->direction == Se) {
            return true;
        } else return false;
    }
    return false;
};

template<typename dataType>
nodeDirection TreeNode<dataType>::OpositeDirection() {
    if (this->direction == Ne) {
        return Nw;
    }
    if (this->direction == Se) {
        return Sw;
    }
    if (this->direction == Nw) {
        return Ne;
    }
    if (this->direction == Sw) {
        return Se;
    }
};

template<typename dataType>
TreeNode<dataType> *TreeNode<dataType>::DirectionChild(nodeDirection D) {
    if (D == Ne) {
        return this->children[0];
    }
    if (D == Se) {
        return this->children[1];
    }
    if (D == Sw) {
        return this->children[2];
    }
    if (D == Nw) {
        return this->children[3];
    }
};

template<typename dataType>
TreeNode<dataType> *TreeNode<dataType>::GSN(nodeRight Point) {
    TreeNode *N = new TreeNode;
    TreeNode *Rez = new TreeNode;
    Rez = this;
    N = this->parent;
    bool WaytoGo = true;
    QList<nodeDirection> Road;
    while (WaytoGo && Rez->parent != nullptr) {
        WaytoGo = CorectDirection(Point);
        Rez = N;
        N = N->parent;
        Road.append(Rez->OpositeDirection());
    }
    if (Rez->parent == nullptr) {
        return nullptr;
    }
    Rez = N;
    while (Road.size() > 0) {
        nodeDirection W = Road.first();
        if (this->type != leaf) {
            Rez = Rez->DirectionChild(W);
        } else {
            break;
        }
        Road.pop_front();
    }
}

template<typename dataType>
TreeNode<dataType> *TreeNode<dataType>::CompareNode(TreeNode<dataType> *Pixel) {
    if (this->content != Pixel->content) {
        return Pixel;
    }
    return nullptr;
}


/*!
 *   Instantiation is required here, otherwise class will not actually be compiled
 *   This is sadly a probably unwanted result of how templates and separate compilation work in c++ :(
 *   An alternative could've been to declare everything in the header.
 */
template
class TreeNode<cv::Vec3b>;
