#include "../include/Session.h"
#include "../include/json.hpp"
#include <iostream>
#include <fstream>
#include <string>

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
   setTreeType(Json["tree"].get<string>().front()); //parser tree
   setGraph(Json["graph"].get<vector<vector<int>>>()); //parser graph
}

void Session::simulate() {
   int size = agents.size();
   for (int i = 0; i < size ; i++) {
       if (size <= agents.size()){
           Agent *curr = agents[i];
           curr->act(*this);
       }
       size = agents.size();
   }

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
    /*int temp = queue.front()->getNode();
    queue.erase(queue.begin());
    return temp;
     */
}

TreeType Session::getTreeType() const { //problem with getting treetype we get the index of the enum list
    if (treeType == 0)
        return Cycle;
    else if(treeType == 1)
        return MaxRank;
    else
        return Root;
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
    infected_queue.clear();
//add destructor for agents
}

std::vector<int> Session::get_queue() const {
    return infected_queue;
}
