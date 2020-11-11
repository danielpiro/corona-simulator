#ifndef GRAPH_H_
#define GRAPH_H_

#include <vector>
#include <list>

class Graph {
public:
    Graph(std::vector<std::vector<int>> matrix);

    Graph();

    std::vector<int> get_infected() const;

    void infectNode(int nodeInd);

    bool isInfected(int nodeInd);

    void Clear();

    std::vector<std::vector<int>> get_edges() const;

    void remove_edges(int node);

    Graph *clone() const;

    Tree *BFS(int rootLabel, const Session &session);

private:
    std::vector<std::vector<int>> edges;
    std::vector<int> infected;
};

#endif
