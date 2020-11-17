#include "../include/Session.h"
#include "../include/json.hpp"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;
using json = nlohmann::json;

Session::Session(const std::string &path) : g(), cycle(0) {
    json Json;
    ifstream i(path);
    i >> Json;
    for (auto element : Json["agents"]) {
        if (element[0] == "V") {
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

/*
 * the value in visited[1] wont save the changes.
 *
 */
void Session::simulate() {
    int size = 0;
    while (size < agents.size()) {
        size = agents.size();
        for (int i = 0; i < size; i++) {
            agents[i]->act(*this);
        }
        cycle++;
    }
    for (int j = 0; j < g.get_health().size(); ++j) {
        if(g.get_health()[j])
            cout<<j<<endl;
    }


}

void Session::addAgent(const Agent &agent) {
    Agent *tmp = agent.clone();
    agents.push_back(tmp);
}

void Session::setGraph(const Graph &graph) {
    g = graph;
}

void Session::enqueueInfected(int node) {
    if (!g.isInfected(node))
        g.infectNode(node);
    if (!g.get_health()[node]) {
        g.get_health()[node] = true;
        infected_queue.push_back(node);
    }
}

Graph& Session::getGraphRef() {
    return g;
}
//
//Graph Session::getGraphRef() const {
//    return g;
//}

int Session::dequeueInfected() {
    if (!infected_queue.empty()) {
        int toBFS = infected_queue.front();
        infected_queue.erase(infected_queue.begin());
        return toBFS;
    }
    return -1;
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

Session::Session(Session &&other) : cycle(other.cycle), treeType(other.treeType), g() {
    agents.swap(other.agents);
    infected_queue.swap(other.infected_queue);
    g = other.g;
    //other.clear();
}

Session &Session::operator=(Session &&aSession) {
    if (this != &aSession) {
        clear();
        cycle = aSession.cycle;
        aSession.cycle = 0;
        treeType = aSession.treeType;
        agents.swap(aSession.agents);
        infected_queue.swap(aSession.infected_queue);
    }
    return *this;
}


Session::~Session() {
    this->clear();
//add destructor for agents
}

const Session &Session::operator=(const Session &aSession) {
    if (this == &aSession) {
        return *this;
    }
    clear();
    cycle = aSession.cycle;
    for (int i = 0; i < agents.size(); i++) {
        agents.push_back(aSession.agents[i]);
    }
    return *this;
}

void Session::clear() {
    g.Clear();
    infected_queue.clear();
    for (unsigned int i = 0; i < agents.size(); i++)
        delete agents[i];
    agents.clear();
}

vector<int>& Session::get_queue(){
    return infected_queue;
}