#include <iostream>
#include <iomanip>
#include <ctime>
#include "LinkedListNode.h"
#include "./sorts/sortByPriority.h"
#include "./sorts/sortByCreationTime.h"
#include "./sorts/sortByName.h"
#include "./searches/searchByID.h"
#include "./searches/searchByName.h"
using namespace std;

class LinkedList
{
private:
    LinkedListNode *head;
    LinkedListNode *tail;
    int size;

public:
    LinkedList() : head(nullptr), tail(nullptr), size(0) {}

    ~LinkedList()
    {
        while (head != nullptr)
        {
            LinkedListNode *temp = head;
            head = head->next;
            delete temp;
        }
    }

    // method to add a new node (i.e. ticket) to the list
    void add(const Ticket &ticket)
    {
        LinkedListNode *newNode = new LinkedListNode(ticket);
        if (head == nullptr)
        {
            head = tail = newNode;
        }
        else
        {
            tail->next = newNode;
            tail = newNode;
        }
        size++;
    }

    // method to remove a ticket from the list
    bool remove(int ticketID)
    {
        LinkedListNode *current = head;
        LinkedListNode *previous = nullptr;

        while (current != nullptr)
        {
            if (current->ticket.id == ticketID)
            {
                if (previous == nullptr)
                {
                    head = current->next;
                }
                else
                {
                    previous->next = current->next;
                }

                if (current == tail)
                {
                    tail = previous;
                }
                delete current;
                size--;
                return true;
            }
            previous = current;
            current = current->next;
        }
        return false;
    }

    // method to search for a particular ticket in the list using ticket ID
    Ticket *searchByID(int ticketID, int choice)
    {

        if (choice == 0)
        {
            Ticket *result = linearSearchID(head, ticketID);
            return result;
            // return (linearSearch(head, ticketID));
        }
        else if (choice == 1)
        {
            Ticket *ticketArray = new Ticket[size]; // empty tickets array
            LinkedListNode *current = head;

            // copying tickets from linked list to array
            for (int i = 0; i < size; i++)
            {
                ticketArray[i] = current->ticket;
                current = current->next;
            }

            // to apply binary search, list must be sorted...!
            sortID(ticketArray, size);
            Ticket *result = binarySearchID(ticketArray, size, ticketID);

            // delete[] ticketArray;
            return result;
        }
        else if (choice == 2)
        {
            return interpolationSearchID(head, size, ticketID);
        }
        cout << "Invalid choice for search algorithm. Using the default i.e. Linear Search" << endl;
        return linearSearchID(head, ticketID);
    }

    // method to search for a ticket using ticket name
    Ticket *searchByName(string ticketName, int choice)
    {
        if (choice == 0)
        {
            Ticket *result = linearSearchName(head, ticketName);
            return result;
            // return (linearSearch(head, ticketID));
        }
        else if (choice == 1)
        {
            Ticket *ticketArray = new Ticket[size]; // empty tickets array
            LinkedListNode *current = head;

            // copying tickets from linked list to array
            for (int i = 0; i < size; i++)
            {
                ticketArray[i] = current->ticket;
                current = current->next;
            }

            // to apply binary search, list must be sorted...!
            sortName(ticketArray, size);
            Ticket *result = binarySearchName(ticketArray, size, ticketName);

            // delete[] ticketArray;
            return result;
        }
        else if (choice == 2)
        {
            cout << "Interpolation is not available for searching by name. Using the default i.e. Linear Search" << endl;
            return linearSearchName(head, ticketName);
        }

        cout << "Invalid choice for search algorithm. Using the default i.e. Linear Search" << endl;
        return linearSearchName(head, ticketName);
    }

    // method to display all the tickets in the list
    void displayAll() const
    {
        LinkedListNode *temp = head;
        while (temp != nullptr)
        {
            cout << "---------------\n";
            cout << "Ticket ID: " << temp->ticket.id
                 << ", Customer: " << temp->ticket.customerName
                 << ", Priority: " << temp->ticket.priority
                 << ", Creation Time: " << put_time(localtime(&temp->ticket.creationTime), "%Y-%m-%d %H:%M:%S")
                 << ", Status: " << (temp->ticket.isOpen ? "Open" : "Closed") << "\n";

            if (!temp->ticket.isOpen)
            {
                cout << "Close Time: " << &temp->ticket.closeTime << endl;
            }
            temp = temp->next;
        }
        cout << "--------------------------------------------------------------------------------------\n";
    }

    // method to sort the tickets, based on priority
    void sortByPriority(int choice)
    {
        // Insertion Sort
        if (choice == 0)
        {
            insertionSortSBP(head);
        }

        // Bubble Sort
        else if (choice == 1)
        {
            bubbleSortSBP(head);
        }

        // Selection Sort
        else if (choice == 2)
        {
            selectionSortSBP(head);
        }

        // Quick Sort
        else if (choice == 3)
        {
            head = quickSortSBP(head, getTail(head));
        }

        // Merge Sort
        else if (choice == 4)
        {
            head = mergeSortSBP(head);
        }

        // Exceptional Case...!
        else
        {
            cout << "Invalid Choice for sorting algorithm. Using the Default i.e. Insertion Sort" << endl;
            insertionSortSBP(head);
        }
    }

    // method to sort the tickets based on ticket's creation time
    void sortByCreationTime(int choice)
    {
        // Insertion Sort
        if (choice == 0)
        {
            insertionSortSBC(head);
        }

        // Bubble Sort
        else if (choice == 1)
        {
            bubbleSortSBC(head);
        }

        // Selection Sort
        else if (choice == 2)
        {
            selectionSortSBC(head);
        }

        // Quick Sort
        else if (choice == 3)
        {
            head = quickSortSBC(head, getTail(head));
        }

        // Merge Sort
        else if (choice == 4)
        {
            head = mergeSortSBC(head);
        }

        // Exceptional Case...!
        else
        {
            cout << "Invalid Choice for sorting algorithm. Using the Default i.e. Insertion Sort" << endl;
            insertionSortSBC(head);
        }
    }

    // method to sort the tickets based on Customer Name on ticket
    void sortByCustomerName(int choice)
    {
        // Insertion Sort
        if (choice == 0)
        {
            insertionSortSBN(head);
        }

        // Bubble Sort
        else if (choice == 1)
        {
            bubbleSortSBN(head);
        }

        // Selection Sort
        else if (choice == 2)
        {
            selectionSortSBN(head);
        }

        // Quick Sort
        else if (choice == 3)
        {
            head = quickSortSBN(head, getTail(head));
        }

        // Merge Sort
        else if (choice == 4)
        {
            head = mergeSortSBN(head);
        }

        // Exceptional Case...!
        else
        {
            cout << "Invalid Choice for sorting algorithm. Using the Default i.e. Insertion Sort" << endl;
            insertionSortSBN(head);
        }
    }

    LinkedListNode *getTail(LinkedListNode *node)
    {
        while (node != nullptr && node->next != nullptr)
        {
            node = node->next;
        }
        return node;
    }
    // get the size of the list (i.e. number of tickets in the list)
    int getSize() const
    {
        return size;
    }

    // helper function to get the head of the list
    LinkedListNode *getHead() const
    {
        return head;
    }
};