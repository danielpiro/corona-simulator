#ifndef AGENT_H_
#define AGENT_H_

#include <vector>
class Session;
class Agent {
public:
    Agent();

    virtual void act(Session &session)=0;

    virtual Agent *clone() const = 0;
    virtual int getNode() const = 0;
};

class ContactTracer : public Agent {
public:
    ContactTracer(int noteInd);

    virtual Agent *clone() const;

    virtual void act(Session &session);
    virtual int getNode() const;

private:
    const int nodeInd;
};

class Virus : public Agent {
public:
    Virus(int nodeInd);

    virtual void act(Session &session);

    virtual Agent *clone() const;
    virtual int getNode() const;
private:
    const int nodeInd;
};

#endif
