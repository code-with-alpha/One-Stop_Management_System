#include <iostream>
using namespace std;

LinkedListNode *get_tail(LinkedListNode *node)
{
    while (node != nullptr && node->next != nullptr)
    {
        node = node->next;
    }
    return node;
}

// --------------------------------- Bubble Sort ---------------------------------

void bubbleSortSBN(LinkedListNode *&head)
{
    if (head == nullptr || head->next == nullptr)
    {
        return;
    }

    bool swapped;
    LinkedListNode *current;
    LinkedListNode *last = nullptr;

    do
    {
        swapped = false;
        current = head;

        while (current->next != last)
        {
            if (current->ticket.customerName > current->next->ticket.customerName)
            {

                swap(current->ticket, current->next->ticket);
                swapped = true;
            }
            current = current->next;
        }
        last = current;
    } while (swapped);
}

// --------------------------------- Selection Sort ---------------------------------

void selectionSortSBN(LinkedListNode *head)
{
    if (head == nullptr || head->next == nullptr)
    {
        return;
    }

    LinkedListNode *sortedHead = head;
    while (sortedHead != nullptr)
    {
        // Find the node with the least character in customerName in the unsorted part of the list
        LinkedListNode *minNode = sortedHead;
        LinkedListNode *current = sortedHead->next;

        while (current != nullptr)
        {
            if (current->ticket.customerName < minNode->ticket.customerName)
            {
                minNode = current;
            }
            current = current->next;
        }

        if (minNode != sortedHead)
        {
            swap(sortedHead->ticket, minNode->ticket);
        }

        sortedHead = sortedHead->next;
    }
}

// --------------------------------- Insertion Sort ---------------------------------

void insertionSortSBN(LinkedListNode *&head)
{
    if (head == nullptr || head->next == nullptr)
    {
        return;
    }
    LinkedListNode *sorted = nullptr;
    LinkedListNode *current = head;

    while (current != nullptr)
    {
        LinkedListNode *next = current->next;
        if (sorted == nullptr || sorted->ticket.customerName > current->ticket.customerName)
        {
            current->next = sorted;
            sorted = current;
        }
        else
        {
            LinkedListNode *sortedCurrent = sorted;
            while ((sortedCurrent->next != nullptr) && ((sortedCurrent->next->ticket.customerName) <= (current->ticket.customerName)))
            {
                sortedCurrent = sortedCurrent->next;
            }
            current->next = sortedCurrent->next;
            sortedCurrent->next = current;
        }
        current = next;
    }

    head = sorted;
}

// --------------------------------- Quick Sort ---------------------------------

// helper function for Quick Sort
LinkedListNode *partitionSBN(LinkedListNode *head, LinkedListNode *end, LinkedListNode **newHead, LinkedListNode **newEnd)
{
    LinkedListNode *pivot = end;
    LinkedListNode *prev = nullptr;
    LinkedListNode *curr = head;
    LinkedListNode *tail = pivot;

    *newHead = nullptr;

    while (curr != pivot)
    {
        if (curr->ticket.customerName < pivot->ticket.customerName)
        {
            if (*newHead == nullptr)
            {
                *newHead = curr;
            }
            prev = curr;
            curr = curr->next;
        }
        else
        {
            if (prev)
            {
                prev->next = curr->next;
            }
            LinkedListNode *temp = curr->next;
            curr->next = nullptr;
            tail->next = curr;
            tail = curr;
            curr = temp;
        }
    }

    if (*newHead == nullptr)
    {
        *newHead = pivot;
    }

    *newEnd = tail;

    return pivot;
}

// Recursive Quick Sort function
LinkedListNode *quickSortSBN(LinkedListNode *head, LinkedListNode *tail)
{
    if (!head || head == tail)
    {
        return head;
    }

    LinkedListNode *newHead = nullptr;
    LinkedListNode *newEnd = nullptr;

    LinkedListNode *pivot = partitionSBN(head, tail, &newHead, &newEnd);

    if (newHead != pivot)
    {
        LinkedListNode *temp = newHead;
        while (temp->next != pivot)
        {
            temp = temp->next;
        }
        temp->next = nullptr;

        newHead = quickSortSBN(newHead, temp);

        temp = get_tail(newHead);
        temp->next = pivot;
    }

    pivot->next = quickSortSBN(pivot->next, newEnd);

    return newHead;
}

// --------------------------------- Merge Sort ---------------------------------

// helper function for merge sort
LinkedListNode *splitListSBN(LinkedListNode *head)
{
    LinkedListNode *slow = head;
    LinkedListNode *fast = head->next;

    // get the middle of the list
    while (fast != nullptr && fast->next != nullptr)
    {
        slow = slow->next;
        fast = fast->next->next;
    }

    LinkedListNode *mid = slow->next;
    slow->next = nullptr;
    return mid;
}

// Helper function to merge two sorted lists
// SBN --> Sort By Name
// using SBN with every method to avoid conflicts in LinkedList.h file where functions from all the files will be called.
LinkedListNode *mergeSBN(LinkedListNode *left, LinkedListNode *right)
{
    if (!left)
    {
        return right;
    }
    if (!right)
    {
        return left;
    }
    LinkedListNode *result = nullptr;

    if (left->ticket.customerName <= right->ticket.customerName)
    {
        result = left;
        result->next = mergeSBN(left->next, right);
    }
    else
    {
        result = right;
        result->next = mergeSBN(left, right->next);
    }

    return result;
}

// Recursive merge sort function
LinkedListNode *mergeSortSBN(LinkedListNode *head)
{
    if (head == nullptr || head->next == nullptr)
    {
        return head;
    }

    LinkedListNode *mid = splitListSBN(head);

    LinkedListNode *left = mergeSortSBN(head);
    LinkedListNode *right = mergeSortSBN(mid);

    return mergeSBN(left, right);
}