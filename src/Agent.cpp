#include <iostream>
#include "../include/Session.h"

using namespace std;

Agent::Agent() {
}
Virus::Virus(const int nodeInd) : nodeInd(nodeInd) {
}

void Virus::act(Session &session) {
    Graph *tmp = session.getGraphRef().clone();
    if (!tmp->get_health()[nodeInd]) {
        tmp->get_health()[nodeInd] = true;
        session.get_queue().push_back(nodeInd);
    }
    for (unsigned int i = 0; i < tmp->get_edges()[nodeInd].size();)
        if (tmp->get_edges()[nodeInd][i] == 1) {
            if (!tmp->isInfected(tmp->get_edges()[nodeInd][i])) {
                session.getGraphRef().infectNode((int) i);
                Agent *v = new Virus((int) i);
                session.addAgent(*v);
                break;
                }
            }
    tmp->Clear();
}

Agent *Virus::clone() const {
    return new Virus(*this);
    cout<<"hello";
}

int Virus::getNode() const {
    return nodeInd;
}

void ContactTracer::act(Session &session) {
    if (session.get_queue().size() != 0) {
        int toBFS = session.get_queue().front();
        session.get_queue().erase(session.get_queue().begin());
        Graph *tmp = session.getGraphRef().clone();
        Tree *bfs = tmp->BFS(toBFS, session);
        int toDisconnect = bfs->traceTree();
        if (toDisconnect != toBFS) {
            session.getGraphRef().remove_edges(toDisconnect);
            tmp->Clear();
            bfs->Clear();
        }
    }
}

ContactTracer::ContactTracer(int noteInd) : nodeInd(noteInd) {
}

Agent *ContactTracer::clone() const {
    return new ContactTracer(*this);
}

int ContactTracer::getNode() const {
    return nodeInd;
}
