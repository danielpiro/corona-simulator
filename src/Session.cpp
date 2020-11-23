#include "../include/Session.h"
#include "../include/json.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

using namespace std;
using json = nlohmann::json;

Session::Session(const std::string &path) : g(), treeType(), agents(), cycle(0), infected_queue() {
    json Json;
    ifstream i(path);
    i >> Json;
    for (auto element : Json["agents"]) { // parser agents and categorize them into virus or contact tracer
        if (element[0] == "V") {
            Agent *agent = new Virus(element[1]);
            addAgent(*agent);
            delete agent;
        } else {
            Agent *agent = new ContactTracer(element[1]);
            addAgent(*agent);
            delete agent;
        }
    }
    setTreeType(Json["tree"].get<string>().front()); //parser tree
    setGraph(Json["graph"].get<vector<vector<int>>>()); //parser graph
}

Session::Session(const Session &session) : g(), treeType(session.getTreeType()), agents(), cycle(), infected_queue() {
    for (auto agent : session.agents) {
        Agent *newAgent = agent->clone();
        agents.push_back(newAgent);
    }
}

const Session &Session::operator=(const Session &aSession) {
    if (this == &aSession) {
        return *this;
    }
    clear();
    cycle = aSession.cycle;
    for (size_t i = 0; i < agents.size(); i++) {
        agents.push_back(aSession.agents[i]);
    }
    return *this;
}

Session::Session(Session &&other) : g(), treeType(other.treeType), agents(), cycle(other.cycle), infected_queue() {
    agents.swap(other.agents);
    infected_queue.swap(other.infected_queue);
    g = other.g;
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
}

void Session::simulate() { //we keep looping until every connected component is either fully infected or healthy
    size_t size = 0;
    while (size < agents.size()) { //when size = agents.size we didnt add new agents and we got to the stopping point
        size = agents.size();
        for (size_t i = 0; i < size; i++) { // we run on the current agent list
            agents[i]->act(*this); //every agent act on his turn
        }
        cycle++;
    }
    vector<int> output;
    for (size_t j = 0; j < g.get_sick().size(); ++j) { 
        if (g.get_sick()[j])
            output.push_back(j);
    }
    to_json(g, output);

}

void Session::addAgent(const Agent &agent) {
    Agent *tmp = agent.clone();
    agents.push_back(tmp);
}

void Session::enqueueInfected(int node) {
    if (!g.isInfected(node))
        g.infectNode(node);
    if (!g.get_sick()[node]) { //if the node is already sick we dont add it to the infected queue
        g.get_sick()[node] = true;
        infected_queue.push_back(node);
    }
}

int Session::dequeueInfected() {
    if (!infected_queue.empty()) { //if there is a node in the queue we remove it and return it to the CT to bfs from it
        int toBFS = infected_queue.front();
        infected_queue.erase(infected_queue.begin());
        return toBFS;
    }
    return -1;
}

void Session::to_json(Graph graph, vector<int> infected) {
    json j;
    j["graph"] = graph.get_edges();
    j["infected"] = infected;
    ofstream os("output.json");
    os << setw(0) << j << endl;
    os.close();
}

void Session::clear() {
    g.Clear();
    infected_queue.clear();
    for (auto agent : agents)
        delete agent;
    agents.clear();
}

void Session::setGraph(const Graph &graph) {
    g = graph;
}

void Session::setTreeType(char tree) {
    if (tree == 'M')
        treeType = MaxRank;
    else if (tree == 'C')
        treeType = Cycle;
    else
        treeType = Root;
}

Graph &Session::getGraphRef() {
    return g;
}

TreeType Session::getTreeType() const {
    return treeType;
}


int Session::getCycle() const {
    return cycle;
}

vector<int> &Session::get_queue() {
    return infected_queue;
}


