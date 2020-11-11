#ifndef TREE_H_
#define TREE_H_

#include <vector>

class Session;

class Tree {
public:
    Tree(int rootLabel); //CTR
    Tree(const Tree &aTree); //copy CTR
    Tree(); //empty CTR
    virtual ~Tree(); //virtual Destructor
    const Tree &operator=(const Tree &aTree);//copy assignment operator
    Tree(Tree &&other); //move CTR
    Tree &operator=(Tree &&aTree); //move assignment operator
    void Clear();

    void addChild(const Tree &child);

    static Tree *createTree(const Session &session, int rootLabel);

    virtual int traceTree() = 0;

    virtual int get_node();

    std::vector<Tree *> getChildren() const;

    virtual Tree *clone() const = 0;

private:
    int node;
    std::vector<Tree *> children;
};

class CycleTree : public Tree {
public:
    CycleTree(int rootLabel, int currCycle);

    int traceTree() override;

    Tree *clone() const override;

private:
    int currCycle;
};

class MaxRankTree : public Tree {
public:
    MaxRankTree(int rootLabel);

    int traceTree() override;

    Tree *clone() const override;
};

class RootTree : public Tree {
public:
    RootTree(int rootLabel);

    int traceTree() override;

    Tree *clone() const override;
};

#endif
