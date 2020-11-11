#ifndef AGENT_H_
#define AGENT_H_

#include <vector>
class Session;
class Agent {
public:
    Agent();

    virtual void act(Session &session) = 0;

    virtual Agent *clone() const = 0;
    virtual int getNode() const = 0;
};

class ContactTracer : public Agent {
public:
    ContactTracer(int noteInd);

    Agent *clone() const override;

    void act(Session &session) override;
    int getNode() const override;

private:
    const int nodeInd;
};

class Virus : public Agent {
public:
    Virus(int nodeInd);

    void act(Session &session) override;

    Agent *clone() const override;
    int getNode() const override;
private:
    const int nodeInd;
};

#endif
