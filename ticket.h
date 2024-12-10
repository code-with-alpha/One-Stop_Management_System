#ifndef TICKET_H
#define TICKET_H

#include <string>
#include <ctime>

using namespace std;

class Ticket
{
public:
    int id;
    string customerName;
    int priority;
    string description;
    time_t creationTime;
    bool isOpen;
    time_t closeTime;

    Ticket(){}
    Ticket(int id, const string &name, int priority, const string &desc)
        : id(id), customerName(name), priority(priority), description(desc), isOpen(true)
    {
        creationTime = time(nullptr);
        closeTime = 0;
    }
};

#endif