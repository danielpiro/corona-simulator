#include "../include/Session.h"
#include <iostream>

using namespace std;


Tree::Tree(int rootLabel) : node(rootLabel) {
}

Tree::Tree(const Tree &aTree) : node(aTree.node), children() {
    children = aTree.children;
}

Tree::Tree() {}

const Tree &Tree::operator=(const Tree &aTree) {
    if (this == &aTree) {
        return *this;
    }
    Clear();
    node = aTree.node;
    children = aTree.children;
    return *this;
}

void Tree::Clear() {
    node = 0;
    for (auto elem: children)
        elem[0].Clear();
}

Tree::Tree(Tree &&other) : node(other.node) {
    children.swap(other.children);
    other.node = 0;
}

Tree &Tree::operator=(Tree &&other) {
    if (this != &other) {
        Clear();
        node = other.node;
        other.node = 0;
        children.swap(other.children);
    }
    return *this;
}


void Tree::addChild(const Tree &child) {
    Tree *copy = child.clone();
    children.push_back(copy);
}

int Tree::get_node() {
    return node;
}

Tree *Tree::createTree(const Session &session, int rootLabel) {
    if (session.getTreeType() == Cycle) {
        Tree *cycleTree = new CycleTree(rootLabel, session.getCycle());
        return cycleTree;
    } else if (session.getTreeType() == MaxRank) {
        Tree *maxRankTree = new MaxRankTree(rootLabel);
        return maxRankTree;
    } else {
        Tree *rootTree = new RootTree(rootLabel);
        return rootTree;
    }
}

std::vector<Tree *> Tree::getChildren() const {
    return children;
}

Tree::~Tree() {
    children.clear();
}

CycleTree::CycleTree(int rootLabel, int currCycle) : Tree(rootLabel), currCycle(currCycle) {

}


int CycleTree::traceTree() {
    vector<Tree *> temp = getChildren();
    int cycle = currCycle;
    while (cycle != 0 || !temp.empty()) {
        temp = temp[0]->getChildren();
        cycle--;
    }
    return temp[0]->get_node();
}

Tree *CycleTree::clone() const {
    return new CycleTree(*this);
}

MaxRankTree::MaxRankTree(int rootLabel) : Tree(rootLabel) {
}

int MaxRankTree::traceTree() {
    vector<Tree *> temp = getChildren();
    unsigned int max = temp[0]->getChildren().size(), ans = temp[0]->get_node(), index = 0;
    for (unsigned int i = 1; i < temp.size(); ++i) {
        if (temp[i]->getChildren().size() > max) {
            max = temp[i]->getChildren().size();
            ans = temp[i]->get_node();
            index = i;
        } else if (temp[i]->getChildren().size() == max) {
            if (i < index) {
                max = temp[i]->getChildren().size();
                ans = temp[i]->get_node();
                index = i;
            }
        }
    }
    return (int) ans;
}

Tree *MaxRankTree::clone() const {
    return new MaxRankTree(*this);
}

RootTree::RootTree(int rootLabel) : Tree(rootLabel) {
}

int RootTree::traceTree() {
    return get_node();
}

Tree *RootTree::clone() const {
    return new RootTree(*this);
}
