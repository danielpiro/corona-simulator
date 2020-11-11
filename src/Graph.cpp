#include "../include/Session.h"
#include <iostream>
#include <utility>
#include "list"

using namespace std;

Graph::Graph(std::vector<std::vector<int>> matrix) {
    edges = std::move(matrix);
}

Graph::Graph() {}

void Graph::Clear() {
    edges.clear();
    infected.clear();
}

void Graph::infectNode(int nodeInd) {
    this->infected.push_back(nodeInd);
}

bool Graph::isInfected(int nodeInd) {
    for (unsigned int i = 0; i < infected.size(); ++i) {
        if (infected[i] == nodeInd)
            return true;
    }
    return false;
}

std::vector<int> Graph::get_infected() const {
    return infected;
}

std::vector<std::vector<int>> Graph::get_edges() const {
    return edges;
}

void Graph::remove_edges(int node) {
    for (int i = 0; i < edges[node].size(); ++i)
        if (edges[node][i] == 1) {
            edges[node][i] = 0;
            edges[i][node] = 0;
        }
}

Graph *Graph::clone() const {
    auto *clone = new Graph();
    clone->edges = this->get_edges();
    clone->infected = this->infected;
    return clone;
}

Tree *Graph::BFS(int rootLabel, const Session &session) {
    Tree *curr_Tree = Tree::createTree(session, rootLabel);
    vector<bool> visited(edges.size(), false);
    vector<int> q;
    unsigned int vis;
    q.push_back(rootLabel);
    visited[rootLabel] = true;
    while (!q.empty()) {
        vis = q[0];
        q.erase(q.begin());
        for (unsigned int i = 0; i < edges.size(); i++) {
            if (edges[vis][i] == 1 && (!visited[i])) {
                q.push_back(i);
                visited[i] = true;
                Tree *temp = Tree::createTree(session, (int)i);
                curr_Tree->addChild(*temp);
                temp->Clear();
            }
        }
    }
    return curr_Tree;
}