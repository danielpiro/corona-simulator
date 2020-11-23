#ifndef GRAPH_H_
#define GRAPH_H_

#include <vector>
#include <list>

class Graph {
public:
    Graph();

    Graph(const std::vector<std::vector<int>> &matrix);

    Graph(Graph &other);

    void infectNode(int nodeInd);

    bool isInfected(int nodeInd);

    void remove_edges(int node);

    Tree *BFS(int rootLabel, const Session &session);

    Graph *clone() const;

    void Clear();

    std::vector<bool> &get_sick();

    std::vector<bool> &get_visited();

    std::vector<std::vector<int>> &get_edges();

private:
    std::vector<std::vector<int>> edges;
    std::vector<bool> visited;
    std::vector<bool> sick;
};

#endif
