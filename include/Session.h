#ifndef SESSION_H_
#define SESSION_H_

#include <vector>
#include <string>
#include "../include/Tree.h"
#include "../include/Graph.h"
#include "../include/Agent.h"

class Agent;

enum TreeType {
    Cycle,
    MaxRank,
    Root
};

class Session {
public:
    Session(const std::string &path);

    virtual ~Session();

    void simulate();

    void addAgent(const Agent &agent);

    void setGraph(const Graph &graph);

Graph& getGraphRef();

    void enqueueInfected(int node);

    int dequeueInfected();

    TreeType getTreeType() const;

    void setTreeType(char tree);

    int getCycle() const;

    Session(const Session &session);
    std::vector<int> get_queue() const;
private:
    Graph g;
    TreeType treeType;
    std::vector<Agent *> agents;
    int cycle;
    std::vector<int> infected_queue;


};

#endif
