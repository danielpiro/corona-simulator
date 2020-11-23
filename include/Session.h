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


    Session(const Session &session);

    const Session &operator=(const Session &aSession);

    Session(Session &&other);

    Session &operator=(Session &&aSession);

    virtual ~Session();

    void simulate();

    void addAgent(const Agent &agent);

    void enqueueInfected(int node);

    int dequeueInfected();

    void to_json(Graph graph , std::vector<int> infected );

    void clear();

    void setGraph(const Graph &graph);

    void setTreeType(char tree);

    Graph &getGraphRef();

    TreeType getTreeType() const;

    int getCycle() const;

    std::vector<int> &get_queue();

private:
    Graph g;
    TreeType treeType;
    std::vector<Agent *> agents;
    int cycle;
    std::vector<int> infected_queue;

};

#endif
