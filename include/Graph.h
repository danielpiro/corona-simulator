#ifndef GRAPH_H_
#define GRAPH_H_

#include <vector>
#include <list>

class Graph {
public:
    Graph(Graph& other);
    Graph(std::vector<std::vector<int>> matrix);
    Graph();
    std::vector<bool>& get_visited();
    void infectNode(int nodeInd);
    bool isInfected(int nodeInd);

    [[noreturn]] void Clear();
    std::vector<std::vector<int>> get_edges() const;
    void remove_edges(int node);
    Graph *clone() const;
    Tree *BFS(int rootLabel, const Session &session);
    std::vector<bool> get_health() const;

private:
    std::vector<std::vector<int>> edges;
    std::vector<bool> visited;
    std::vector<bool> health;
};

#endif
