#include "../include/Session.h"
#include <iostream>
#include <utility>

#include "list"

using namespace std;

Graph::Graph() = default;

Graph::Graph(const std::vector<std::vector<int>> &matrix) : visited(matrix.size()), sick(matrix.size()) {
    edges = matrix;
    for (size_t i = 0; i < visited.size(); ++i) {
        visited[i] = false;
        sick[i] = false;
    }

}

Graph::Graph(Graph &other) {
    edges = other.get_edges();
    visited = other.get_visited();
    sick = other.get_sick();
}


void Graph::infectNode(int nodeInd) { //infect the chosen node
    visited[nodeInd] = true;
}

bool Graph::isInfected(int nodeInd) { //check if the chosen node is infected
    return visited[nodeInd];
}

void Graph::remove_edges(int node) { //disconnect the node from his neighbors
    for (size_t i = 0; i < edges[node].size(); ++i)
        if (edges[node][i] == 1) {
            edges[node][i] = 0;
            edges[i][node] = 0;
        }
}

Tree *Graph::BFS(int rootLabel, const Session &session) { //create a bfs tree from the given graph
    auto curr_Tree = Tree::createTree(session, rootLabel);
    auto bfs_tree = curr_Tree;
    vector<bool> visit(edges.size(), false);
    vector<int> q;
    unsigned int vis;
    q.push_back(rootLabel);
    visit[rootLabel] = true;
    while (!q.empty()) {
        vis = q[0];
        q.erase(q.begin());
        for (size_t i = 0; i < edges.size(); i++) {
            if (edges[vis][i] == 1 && (!visit[i])) {
                q.push_back(i);
                visit[i] = true;
                Tree *temp = Tree::createTree(session, i);
                curr_Tree->addChild(*temp);
                delete temp;
            }
        }
        if (!q.empty()) {
            curr_Tree = bfs_tree->get_child(q.front());
        }
    }
    return bfs_tree;
}

Graph *Graph::clone() const {

    auto *clone = new Graph();
    clone->edges = this->edges;
    clone->sick = this->sick;
    clone->visited = this->visited;
    return clone;

}

void Graph::Clear() {
    edges.clear();
    visited.clear();
    sick.clear();
}

vector<bool> &Graph::get_sick() {
    return sick;
}

vector<bool> &Graph::get_visited() {
    return visited;
}

vector<vector<int>> &Graph::get_edges() {
    return edges;
}
