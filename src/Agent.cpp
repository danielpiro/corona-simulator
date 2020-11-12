#include <iostream>
#include "../include/Session.h"

using namespace std;

Agent::Agent() {
}
Virus::Virus(const int nodeInd) : nodeInd(nodeInd) {
}

void Virus::act(Session &session) {
    Graph *tmp = session.getGraphRef().clone();

    for (unsigned int i = 0; i < tmp->get_edges()[nodeInd].size();i++)
        if (tmp->get_edges()[nodeInd][i] == 1) {
            if (!tmp->isInfected(tmp->get_edges()[nodeInd][i])) {
                session.getGraphRef().infectNode((int)i);
                Agent *v = new Virus((int)i);
                session.addAgent(*v);
            }
        }
    tmp->Clear();
}
Agent *Virus::clone() const {
    return new Virus(*this);
}

int Virus::getNode() const {
    return nodeInd;
}

void ContactTracer::act(Session &session) {
    Graph *tmp = session.getGraphRef().clone();
    Tree *bfs = tmp->BFS(nodeInd, session);
    int toDisconnect = bfs->traceTree();
    session.getGraphRef().remove_edges(toDisconnect);
    tmp->Clear();
    bfs->Clear();
}

ContactTracer::ContactTracer(int noteInd) : nodeInd(noteInd) {
}

Agent *ContactTracer::clone() const {
    return new ContactTracer(*this);
}

int ContactTracer::getNode() const {
    return nodeInd;
}
