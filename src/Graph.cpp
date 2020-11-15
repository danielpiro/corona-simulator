#include "../include/Session.h"
#include <iostream>
#include <utility>
#include <include/Graph.h>

#include "list"

using namespace std;

Graph::Graph(Graph& other){
    edges = other.get_edges();
    visited = other.get_visited();
    health = other.get_health();
}

Graph::Graph() {}

Graph::Graph(std::vector<std::vector<int>> matrix): visited(matrix.size()), health(matrix.size()) {
    edges = matrix;
    for (int i = 0; i < visited.size(); ++i) {
        visited[i] = false;
        health[i] = false;
    }

}

void Graph::Clear() {
    edges.clear();
    visited.clear();
}

void Graph::infectNode(int nodeInd) {
    visited[nodeInd] = true;
    return;
    cout<<"visit"<<endl;
}

bool Graph::isInfected(int nodeInd) {
    return visited[nodeInd];
}

vector<bool>& Graph::get_visited() {
    return visited;
}

vector<vector<int>>& Graph::get_edges(){
    return edges;
}

void Graph::remove_edges(int node) {
    for (unsigned int i = 0; i < edges[node].size(); ++i)
        if (edges[node][i] == 1) {
            edges[node][i] = 0;
            edges[i][node] = 0;
        }
}

Graph *Graph::clone() const {

   auto *clone = new Graph();
    clone->edges = this->edges;
    clone->health = this->health;
    clone->visited = this->visited;
    return clone;

}

Tree *Graph::BFS(int rootLabel, const Session &session) {
    Tree *curr_Tree = Tree::createTree(session, rootLabel);
    vector<bool> visit(edges.size(), false);
    vector<int> q;
    unsigned int vis;
    q.push_back(rootLabel);
    visit[rootLabel] = true;
    while (!q.empty()) {
        vis = q[0];
        q.erase(q.begin());
        for (unsigned int i = 0; i < edges.size(); i++) {
            if (edges[vis][i] == 1 && (!visit[i])) {
                q.push_back(i);
                visit[i] = true;
                Tree *temp = Tree::createTree(session, (int)i);
                curr_Tree->addChild(*temp);
                //temp->Clear();
            }
        }
    }
    return curr_Tree;
}

vector<bool>& Graph::get_health() {
    return health;
}
