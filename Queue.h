#ifndef QUEUE_H
#define QUEUE_H

#include "ticket.h"
#include <iostream>
using namespace std;

class QueueNode
{
public:
    Ticket ticket;
    QueueNode *next;

    QueueNode(const Ticket &t)
        : ticket(t), next(nullptr) {}
};

class Queue
{
private:
    QueueNode *front;
    QueueNode *rear;
    int size;

public:
    Queue() : front(nullptr), rear(nullptr), size(0) {}

    ~Queue()
    {
        while (front != nullptr)
        {
            QueueNode *temp = front;
            front = front->next;
            delete temp;
        }
    }

    void enqueue(const Ticket &ticket)
    {
        QueueNode *newQueueNode = new QueueNode(ticket);
        if (rear == nullptr)
        {
            front = rear = newQueueNode;
        }
        else
        {
            rear->next = newQueueNode;
            rear = newQueueNode;
        }
        size++;
    }

    Ticket dequeue()
    {
        if (front == nullptr)
        {
            throw runtime_error("Queue is empty");
        }
        QueueNode *temp = front;
        Ticket ticket = temp->ticket;
        front = front->next;
        if (front == nullptr)
        {
            rear = nullptr;
        }
        delete temp;
        size--;
        return ticket;
    }

    bool isEmpty() const
    {
        return front == nullptr;
    }

    int getSize() const
    {
        return size;
    }

    void display() const
    {
        QueueNode *current = front;
        cout << "------------\n";
        while (current != nullptr)
        {
            cout << "Ticket ID: " << current->ticket.id
                 << ", Customer: " << current->ticket.customerName
                 << ", Priority: " << current->ticket.priority << "\n";
            current = current->next;
        }
        cout << "-----------------------------------------\n";
    }
};

#endif
