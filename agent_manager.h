#ifndef AGENT_MANAGER_H
#define AGENT_MANAGER_H

#include "agent.h"
#include <iostream>
using namespace std;

class AgentManager
{
private:
    Agent **agents;
    int agentCount;
    int capacity;

    // mathod to expand the capacity to store new registered agents
    void expandCapacity()
    {
        int newCapacity = capacity * 2;
        Agent **newAgents = new Agent *[newCapacity];
        for (int i = 0; i < agentCount; i++)
        {
            newAgents[i] = agents[i];
        }
        delete[] agents;
        agents = newAgents;
        capacity = newCapacity;
    }

public:
    AgentManager(int initialCapacity = 10) : agentCount(0), capacity(initialCapacity)
    {
        agents = new Agent *[capacity];
    }

    ~AgentManager()
    {
        for (int i = 0; i < agentCount; i++)
        {
            delete agents[i];
        }
        delete[] agents;
    }

    // method to add new agent
    bool addAgent(int id, const string &name)
    {
        if (agentCount == capacity)
        {
            expandCapacity();
        }
        agents[agentCount++] = new Agent(id, name);
        return true;
    }

    // methods to assign tickets to the agent
    bool assignTicketToAgent(int ticketID)
    {
        for (int i = 0; i < agentCount; i++)
        {
            if (agents[i]->isAvailable && agents[i]->assignTicket(ticketID))
            {
                cout << "Assigned Ticket ID \"" << ticketID << "\" to Agent \"" << agents[i]->name << "\" with Agent ID \"" << agents[i]->id << "\"\n";
                return true;
            }
        }
        cout << "No available agents to assign\n";
        return false;
    }

    // method to Display all the current agents
    void displayAllAgents() const
    {
        cout << "----------------\n";
        for (int i = 0; i < agentCount; i++)
        {
            agents[i]->displayAssignedTickets();
        }
        cout << "--------------------------------------------------------------\n";
    }
};

#endif
