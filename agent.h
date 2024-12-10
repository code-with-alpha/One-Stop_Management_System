#ifndef AGENT_H
#define AGENT_H

#include <string>
#include <iostream>
using namespace std;

class Agent
{
public:
    int id;
    string name;
    int assignedTickets[5];
    int ticketCount;
    bool isAvailable;

    // Constructor
    Agent(int id, const string &name)
        : id(id), name(name), ticketCount(0), isAvailable(true)
    {
        for (int i = 0; i < 5; i++)
        {
            assignedTickets[i] = -1;
        }
    }

    // method to assign tickets to the agent
    bool assignTicket(int ticketID)
    {
        if (ticketCount < 5)
        {
            assignedTickets[ticketCount++] = ticketID;
            if (ticketCount == 5)
            {
                isAvailable = false;
            }
            return true;
        }
        return false;
    }

    // method to Display all the ticket assigned to an Agent
    void displayAssignedTickets() const
    {
        cout << "Agent ID: " << id << ", Name: " << name << ", Assigned Tickets: ";
        for (int i = 0; i < ticketCount; i++)
        {
            cout << assignedTickets[i] << " ";
        }
        cout << (isAvailable ? "(Available)" : "(Unavailable)") << "\n";
    }
};

#endif