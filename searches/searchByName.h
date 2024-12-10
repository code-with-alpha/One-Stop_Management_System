#include <iostream>
using namespace std;

// --------------------------------- Linear Search ---------------------------------

Ticket *linearSearchName(LinkedListNode *head, string targetCustomerName)
{
    LinkedListNode *current = head;
    while (current != nullptr)
    {

        if (current->ticket.customerName == targetCustomerName)
        {
            return &(current->ticket);
        }
        current = current->next;
    }
    return nullptr;
}

// --------------------------------- Binary Search ---------------------------------

// Helper Function for Binary Search
void sortName(Ticket *arr, int size)
{
    for (int i = 1; i < size; i++)
    {
        Ticket key = arr[i];
        int j = i - 1;

        while (j >= 0 && (arr[j].customerName > key.customerName))
        {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}

Ticket *binarySearchName(Ticket *arr, int size, string targetCustomerName)
{
    int left = 0;
    int right = size - 1;

    while (left <= right)
    {
        int mid = left + (right - left) / 2;

        if (arr[mid].customerName == targetCustomerName)
        {
            return &arr[mid];
        }

        if (arr[mid].customerName < targetCustomerName)
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