#include <iostream>
using namespace std;

LinkedListNode *GetTail(LinkedListNode *node)
{
    while (node != nullptr && node->next != nullptr)
    {
        node = node->next;
    }
    return node;
}

// --------------------------------- Bubble Sort ---------------------------------

void bubbleSortSBP(LinkedListNode *head)
{
    if (head == nullptr || head->next == nullptr)
    {
        return;
    }

    bool swapped;
    LinkedListNode *current;
    LinkedListNode *last = nullptr;

    // Loop until no more swaps are needed
    do
    {
        swapped = false;
        current = head;

        // Traverse the list until the last unsorted element
        while (current->next != last)
        {
            if (current->ticket.priority > current->next->ticket.priority)
            {
                // Swap the data of the nodes
                swap(current->ticket, current->next->ticket);
                swapped = true;
            }
            current = current->next;
        }
        last = current; // Update the last sorted position
    } while (swapped);
}

// --------------------------------- Selection Sort ---------------------------------

void selectionSortSBP(LinkedListNode *head)
{
    if (head == nullptr || head->next == nullptr)
    {
        return;
    }

    LinkedListNode *sortedHead = head; // Start from the head of the list
    while (sortedHead != nullptr)
    {
        // Find the node with the minimum priority in the unsorted part of the list
        LinkedListNode *minNode = sortedHead;
        LinkedListNode *current = sortedHead->next;

        while (current != nullptr)
        {
            if (current->ticket.priority < minNode->ticket.priority)
            {
                minNode = current;
            }
            current = current->next;
        }

        // Swap the data of the nodes to place the minimum node at it's correct position
        if (minNode != sortedHead)
        {
            swap(sortedHead->ticket, minNode->ticket);
        }

        // Move sortedHead one step forward in the list
        sortedHead = sortedHead->next;
    }
}

// --------------------------------- Insertion Sort ---------------------------------

void insertionSortSBP(LinkedListNode *head)
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
        if (sorted == nullptr || sorted->ticket.priority > current->ticket.priority)
        {
            current->next = sorted;
            sorted = current;
        }
        else
        {
            LinkedListNode *sortedCurrent = sorted;
            while ((sortedCurrent->next != nullptr) && ((sortedCurrent->next->ticket.priority) <= (current->ticket.priority)))
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
LinkedListNode *partitionSBP(LinkedListNode *head, LinkedListNode *end, LinkedListNode **newHead, LinkedListNode **newEnd)
{
    LinkedListNode *pivot = end;
    LinkedListNode *prev = nullptr;
    LinkedListNode *curr = head;
    LinkedListNode *tail = pivot;

    *newHead = nullptr;

    while (curr != pivot)
    {
        if (curr->ticket.priority < pivot->ticket.priority)
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
LinkedListNode *quickSortSBP(LinkedListNode *head, LinkedListNode *tail)
{
    if (!head || head == tail)
    {
        return head;
    }

    LinkedListNode *newHead = nullptr;
    LinkedListNode *newEnd = nullptr;

    LinkedListNode *pivot = partitionSBP(head, tail, &newHead, &newEnd);

    if (newHead != pivot)
    {
        LinkedListNode *temp = newHead;
        while (temp->next != pivot)
        {
            temp = temp->next;
        }
        temp->next = nullptr;

        newHead = quickSortSBP(newHead, temp);

        temp = GetTail(newHead);
        temp->next = pivot;
    }

    pivot->next = quickSortSBP(pivot->next, newEnd);

    return newHead;
}

// --------------------------------- Merge Sort ---------------------------------

// helper function for merge sort, to split the list into two halves
LinkedListNode *splitListSBP(LinkedListNode *head)
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
// SBP --> Sort By Priority
// using SBP with every method to avoid conflicts in LinkedList.h file where functions from all the files will be called.
LinkedListNode *mergeSBP(LinkedListNode *left, LinkedListNode *right)
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

    if (left->ticket.priority <= right->ticket.priority)
    {
        result = left;
        result->next = mergeSBP(left->next, right);
    }
    else
    {
        result = right;
        result->next = mergeSBP(left, right->next);
    }

    return result;
}

// Recursive merge sort function
LinkedListNode *mergeSortSBP(LinkedListNode *head)
{
    if (head == nullptr || head->next == nullptr)
    {
        return head;
    }

    // Split the list
    LinkedListNode *mid = splitListSBP(head);

    // Sort each half recursively
    LinkedListNode *left = mergeSortSBP(head);
    LinkedListNode *right = mergeSortSBP(mid);

    // Merge the sorted halves
    return mergeSBP(left, right);
}