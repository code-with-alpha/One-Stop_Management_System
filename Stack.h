#ifndef STACK_H
#define STACK_H

#include <iostream>
#include "ticket.h"
using namespace std;

class StackNode
{
public:
    Ticket ticket;
    StackNode *next;

    StackNode(const Ticket &t)
        : ticket(t), next(nullptr) {}
};

class Stack
{
private:
    StackNode *top;
    int size;

public:
    Stack() : top(nullptr), size(0) {}

    ~Stack()
    {
        while (top != nullptr)
        {
            StackNode *temp = top;
            top = top->next;
            delete temp;
        }
    }

    void push(const Ticket &ticket)
    {
        StackNode *newStackNode = new StackNode(ticket);
        newStackNode->next = top;
        top = newStackNode;
        size++;
    }

    Ticket pop()
    {
        if (top == nullptr)
        {
            throw runtime_error("Stack is empty");
        }
        StackNode *temp = top;
        Ticket ticket = temp->ticket;
        top = top->next;
        delete temp;
        size--;
        return ticket;
    }

    bool isEmpty() const
    {
        return top == nullptr;
    }

    int getSize() const
    {
        return size;
    }

    void display() const
    {
        StackNode *current = top;
        while (current != nullptr)
        {
            cout << "Ticket ID: " << current->ticket.id
                 << ", Customer: " << current->ticket.customerName
                 << "\n";
            current = current->next;
        }
        cout << "------------------------------------\n";
    }
};

#endif