#include "../include/Session.h"
#include "../include/json.hpp"
#include <iostream>
#include <fstream>


using namespace std;
using json = nlohmann::json;

Session::Session(const std::string &path) : g() {
    json Json;
    ifstream i(path);
    i >> Json;
    for (auto element : Json["agents"]) {
        if (element[0] == 'V') {
            Agent *agent = new Virus(element[1]);
            addAgent(*agent);
        } else {
            Agent *agent = new ContactTracer(element[1]);
            addAgent(*agent);
        }
    }
    treeType = Json["tree"][0];
    setTreeType(treeType); //parser tree
    setGraph(Json["graph"].get<vector<vector<int>>>()); //parser graph
    queue = agents;
}

void Session::simulate() {
    

}

void Session::addAgent(const Agent &agent) {
    Agent *tmp = agent.clone();
    agents.push_back(tmp);
}

void Session::setGraph(const Graph &graph) { //need to create = operator in graph
    g = graph;
}

void Session::enqueueInfected(int node) {
    g.infectNode(node);
}

Graph Session::getGraphRef() const {
    return g;
}

int Session::dequeueInfected() {
    int temp = queue.front()->getNode();
    queue.erase(queue.begin());
    return temp;
}

TreeType Session::getTreeType() const {
    return treeType;
}

void Session::setTreeType(char tree) {
    if (tree == 'M')
        treeType = MaxRank;
    else if (tree == 'C')
        treeType = Cycle;
    else
        treeType = Root;
}

int Session::getCycle() const {
    return cycle;
}

Session::Session(const Session &session) : g(), treeType(session.getTreeType()), agents() {
    for (unsigned int i = 0; i < session.agents.size(); i++) {
        Agent *newAgent = session.agents[i]->clone();
        agents.push_back(newAgent);
    }
}

Session::~Session() {
    g.Clear();
//destructor for agents
}