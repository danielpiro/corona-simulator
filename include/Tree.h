#ifndef TREE_H_
#define TREE_H_

#include <vector>

class Session;

class Tree {
public:
    Tree(); //empty CTR

    Tree(int rootLabel); //CTR

    Tree(const Tree &aTree); //copy CTR

    const Tree &operator=(const Tree &aTree);//copy assignment operator

    Tree(Tree &&other); //move CTR

    Tree &operator=(Tree &&aTree); //move assignment operator

    virtual ~Tree(); //virtual Destructor

    static Tree *createTree(const Session &session, int rootLabel);

    virtual int traceTree() = 0;

    void addChild(const Tree &child);

    virtual Tree *clone() const = 0;

    void Clear();

    virtual int get_node();

    std::vector<Tree *> get_children();

    Tree *get_child(int label);

private:
    int node{};
    std::vector<Tree *> children;
};

class CycleTree : public Tree {
public:
    CycleTree(int rootLabel, int currCycle);

    virtual int traceTree();

    virtual Tree *clone() const;

private:
    int currCycle;
};

class MaxRankTree : public Tree {
public:
    MaxRankTree(int rootLabel);

    virtual int traceTree();

    virtual Tree *clone() const;

};

class RootTree : public Tree {
public:
    RootTree(int rootLabel);

    virtual int traceTree();

    virtual Tree *clone() const;
};

#endif
