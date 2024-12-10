#include <iostream>
using namespace std;

// --------------------------------- Linear Search ---------------------------------

Ticket *linearSearchID(LinkedListNode *head, int ticketID)
{
    LinkedListNode *current = head;
    while (current != nullptr)
    {

        if (current->ticket.id == ticketID)
        {
            return &(current->ticket);
        }
        current = current->next;
    }
    return nullptr;
}

// --------------------------------- Binary Search ---------------------------------

// Helper function for Binary Search
void sortID(Ticket *arr, int size)
{
    for (int i = 1; i < size; i++)
    {
        Ticket key = arr[i];
        int j = i - 1;

        while (j >= 0 && (arr[j].id > key.id))
        {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}

Ticket *binarySearchID(Ticket *arr, int size, int targetID)
{
    int left = 0;
    int right = size - 1;

    while (left <= right)
    {
        int mid = left + (right - left) / 2;

        if (arr[mid].id == targetID)
        {
            return &arr[mid];
        }

        if (arr[mid].id < targetID)
        {
            left = mid + 1;
        }

        else
        {
            right = mid - 1;
        }
    }
    return nullptr;
}

// --------------------------------- Interpolation Search ---------------------------------

Ticket *interpolationSearchID(LinkedListNode *head, int size, int ticketID)
{
    if (head == nullptr || size == 0)
        return nullptr;

    LinkedListNode *low = head;
    LinkedListNode *high = head;

    for (int i = 0; i < size - 1; ++i)
    {
        high = high->next;
    }

    while (low != high && low != nullptr && high != nullptr)
    {
        // Calculate the position using the interpolation formula
        int pos = (ticketID - low->ticket.id) * (size - 1) / (high->ticket.id - low->ticket.id);
        if (pos < 0 || pos >= size)
        {
            return nullptr;
        }

        LinkedListNode *current = low;
        for (int i = 0; i < pos; ++i)
        {
            if (current == nullptr)
            {
                return nullptr;
            }
            current = current->next;
        }

        // Check if we found the target ticket
        if (current->ticket.id == ticketID)
        {
            return &(current->ticket);
        }
        else if (current->ticket.id < ticketID)
        {
            low = current->next;
        }
        else
        {
            high = current;
        }
    }

    return nullptr;
}