
#include "../include/Session.h"

using namespace std;

Agent::Agent() = default;

Agent::~Agent() = default;

ContactTracer::ContactTracer(int noteInd) : nodeInd(noteInd) {
}

Agent *ContactTracer::clone() const {
    return new ContactTracer(*this);
}

void ContactTracer::act(Session &session) {
    int toBFS = session.dequeueInfected(); //chek if there is a node in the infect queue
    if (toBFS != -1) { //if we found a node we run bfs from it
        Graph tmp = session.getGraphRef();
        auto bfs = tmp.BFS(toBFS, session);
        int toDisconnect = bfs->traceTree(); //we traced the tree to find a node to disconnect
        delete bfs;
        if (toDisconnect != -1)
            session.getGraphRef().remove_edges(toDisconnect); //we disconnect it from the graph
    }
}

int ContactTracer::getNode() const {
    return nodeInd;
}

Virus::Virus(const int nodeInd) : nodeInd(nodeInd) {
}

Agent *Virus::clone() const {
    return new Virus(*this);
}

void Virus::act(Session &session) {
    session.enqueueInfected(
            this->getNode()); //if the current node is not sick already,it will enter the infection queue
    Graph tmp = session.getGraphRef();
    for (size_t i = 0; i < tmp.get_edges()[nodeInd].size(); i++)
        if (tmp.get_edges()[nodeInd][i] == 1) { //look for the first neighbor oh the infected node
            if (!session.getGraphRef().get_visited()[i]) {
                session.getGraphRef().get_visited()[i] = true;
                Agent *v = new Virus(i); //create new virus on the node we infected
                session.addAgent(*v);
                delete v;
                break;
            }
        }
}

int Virus::getNode() const {
    return nodeInd;
}




