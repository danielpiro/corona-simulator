
#include "../include/Session.h"

using namespace std;

Tree::Tree() {}

Tree::Tree(int rootLabel) : node(rootLabel) {
}

Tree::Tree(const Tree &aTree) : node(aTree.node), children() {
    for (auto child : aTree.children) {
        children.push_back(child);
    }
}

const Tree &Tree::operator=(const Tree &aTree) {
    if (this == &aTree) {
        return *this;
    }
    Clear();
    node = aTree.node;
    for (auto child : aTree.children) {
        children.push_back(child);
    }
    return *this;
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

Tree::~Tree() {
    for (auto x : children) {
        delete x;
    }
    children.clear();
}

Tree *Tree::createTree(const Session &session, int rootLabel) { //create tree from given tree type and node
    if (session.getTreeType() == Cycle) {
        return new CycleTree(rootLabel, session.getCycle());
    } else if (session.getTreeType() == MaxRank) {
        return new MaxRankTree(rootLabel);
    } else {
        return new RootTree(rootLabel);
    }
}

void Tree::addChild(const Tree &child) {
    children.push_back(child.clone());

}

void Tree::Clear() {
    node = 0;
    for (auto &temp : children) {
        delete temp;
    }
    children.clear();

}

int Tree::get_node() {
    return node;
}

std::vector<Tree *> Tree::get_children() {
    return children;
}

Tree *Tree::get_child(int label) {
    if (this->get_node() == label)
        return this;
    for (auto &i : children) {
        if (i->get_child(label) != nullptr)
            return i->get_child(label);
    }
    return nullptr;
}

CycleTree::CycleTree(int rootLabel, int currCycle) : Tree(rootLabel), currCycle(currCycle) {}

int CycleTree::traceTree() { //traverse on the tree to the left most child and return his index
    Tree *tmp = this;
    int node = this->get_node(), cycle = currCycle;
    while (cycle > 0 && !tmp->get_children().empty()) { //we stopped when the cycle = 0 or when we got to the left most child in the tree
        node = tmp->get_children()[0]->get_node();
        tmp = tmp->get_children()[0];
        cycle--;
    }
    return node;
}

Tree *CycleTree::clone() const {
    return new CycleTree(*this);
}

MaxRankTree::MaxRankTree(int rootLabel) : Tree(rootLabel) {}

int MaxRankTree::traceTree() { /*trace the node with the highest rank (most children) if equal than we take the one with the deeper depth if this
 * also equals than we take the left most between them */
    vector<Tree *> temp = get_children();
    int ans = -1;
    if (!temp.empty()) {
        size_t max = temp[0]->get_children().size(), index = 0;
        ans = temp[0]->get_node();
        for (size_t i = 1; i < temp.size(); ++i) {
            if (temp[i]->get_children().size() > max) {
                max = temp[i]->get_children().size();
                ans = temp[i]->get_node();
                index = i;
            } else if (temp[i]->get_children().size() == max) {
                if (i < index) {
                    max = temp[i]->get_children().size();
                    ans = temp[i]->get_node();
                    index = i;
                }
            }
        }
    }
    return ans;
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