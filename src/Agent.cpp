#include <iostream>
#include <include/Agent.h>

#include "../include/Session.h"

using namespace std;

Agent::Agent() {
}
Virus::Virus(const int nodeInd) : nodeInd(nodeInd) {
}

void Virus::act(Session &session) {
    session.enqueueInfected(this->getNode());
    Graph tmp = session.getGraphRef();
    for (unsigned int i = 0; i < tmp.get_edges()[nodeInd].size();i++)
        if (tmp.get_edges()[nodeInd][i] == 1) {
            if (!session.getGraphRef().get_visited()[i]) {
                session.getGraphRef().get_visited()[i] = true;
                Agent *v = new Virus((int)i);
                session.addAgent(*v);
                break;
            }
        }
    //tmp.Clear();
}

Agent *Virus::clone() const {
    return new Virus(*this);
}

int Virus::getNode() const {
    return nodeInd;
}

void ContactTracer::act(Session &session) {
    int toBFS = session.dequeueInfected();
    if (toBFS != -1) {
        Graph tmp = session.getGraphRef();
        Tree *bfs = tmp.BFS(toBFS, session);
        int toDisconnect = bfs->traceTree();
        if(toDisconnect!=-1)
            session.getGraphRef().remove_edges(toDisconnect);
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
