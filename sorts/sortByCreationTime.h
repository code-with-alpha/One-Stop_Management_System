#include <iostream>
using namespace std;

LinkedListNode *_getTail(LinkedListNode *node)
{
    while (node != nullptr && node->next != nullptr)
    {
        node = node->next;
    }
    return node;
}

// --------------------------------- Bubble Sort ---------------------------------

void bubbleSortSBC(LinkedListNode *head)
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
            if (current->ticket.creationTime > current->next->ticket.creationTime)
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

void selectionSortSBC(LinkedListNode *head)
{
    if (head == nullptr || head->next == nullptr)
    {
        return;
    }

    LinkedListNode *sortedHead = head;
    while (sortedHead != nullptr)
    {
        LinkedListNode *minNode = sortedHead;
        LinkedListNode *current = sortedHead->next;

        while (current != nullptr)
        {
            if (current->ticket.creationTime < minNode->ticket.creationTime)
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

void insertionSortSBC(LinkedListNode *head)
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
        if (sorted == nullptr || sorted->ticket.creationTime > current->ticket.creationTime)
        {
            current->next = sorted;
            sorted = current;
        }
        else
        {
            LinkedListNode *sortedCurrent = sorted;
            while ((sortedCurrent->next != nullptr) && ((sortedCurrent->next->ticket.creationTime) <= (current->ticket.creationTime)))
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
LinkedListNode *partitionSBC(LinkedListNode *head, LinkedListNode *end, LinkedListNode **newHead, LinkedListNode **newEnd)
{
    LinkedListNode *pivot = end;
    LinkedListNode *prev = nullptr;
    LinkedListNode *curr = head;
    LinkedListNode *tail = pivot;

    *newHead = nullptr;

    while (curr != pivot)
    {
        if (curr->ticket.creationTime < pivot->ticket.creationTime)
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
LinkedListNode *quickSortSBC(LinkedListNode *head, LinkedListNode *end)
{
    if (!head || head == end)
    {
        return head;
    }

    LinkedListNode *newHead = nullptr;
    LinkedListNode *newEnd = nullptr;

    LinkedListNode *pivot = partitionSBC(head, end, &newHead, &newEnd);

    if (newHead != pivot)
    {
        LinkedListNode *temp = newHead;
        while (temp->next != pivot)
        {
            temp = temp->next;
        }
        temp->next = nullptr;

        newHead = quickSortSBC(newHead, temp);

        temp = _getTail(newHead);
        temp->next = pivot;
    }

    pivot->next = quickSortSBC(pivot->next, newEnd);

    return newHead;
}

// --------------------------------- Merge Sort ---------------------------------

// helper function for merge sort, to split the list into two halves
LinkedListNode *splitListSBC(LinkedListNode *head)
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
// SBC --> Sort By creationTime
// using SBC with every method to avoid conflicts in LinkedList.h file where functions from all the files will be called.
LinkedListNode *mergeSBC(LinkedListNode *left, LinkedListNode *right)
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

    if (left->ticket.creationTime <= right->ticket.creationTime)
    {
        result = left;
        result->next = mergeSBC(left->next, right);
    }
    else
    {
        result = right;
        result->next = mergeSBC(left, right->next);
    }

    return result;
}

// Recursive merge sort function
LinkedListNode *mergeSortSBC(LinkedListNode *head)
{
    if (head == nullptr || head->next == nullptr)
    {
        return head;
    }

    LinkedListNode *mid = splitListSBC(head);

    LinkedListNode *left = mergeSortSBC(head);
    LinkedListNode *right = mergeSortSBC(mid);

    return mergeSBC(left, right);
}