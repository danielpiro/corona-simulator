#ifndef GRAPH_H_
#define GRAPH_H_

#include <vector>
#include <list>

class Graph {
public:
    Graph(std::vector<std::vector<int>> matrix, std::vector<bool> visit, std::vector<bool> h);
    Graph(std::vector<std::vector<int>> matrix);
    Graph();
    std::vector<bool> get_visited() const;
    void infectNode(int nodeInd);
    bool isInfected(int nodeInd);
    void Clear();
    std::vector<std::vector<int>> get_edges() const;
    void remove_edges(int node);
    Graph *clone() const;
    Tree *BFS(int rootLabel, const Session &session);
    std::vector<bool> get_health() const;
//liel

private:
    std::vector<std::vector<int>> edges;
    std::vector<bool> visited;
    std::vector<bool> health;
};

#endif
