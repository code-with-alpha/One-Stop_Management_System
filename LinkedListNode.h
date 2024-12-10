#include <iostream>
#include "ticket.h"

class LinkedListNode
{
public:
    Ticket ticket;
    LinkedListNode *next;

    LinkedListNode(const Ticket &ticket) : ticket(ticket), next(nullptr) {}
};