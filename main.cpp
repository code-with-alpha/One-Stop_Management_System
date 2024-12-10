#include <iostream>
#include <string>
#include <chrono>
#include "ticket.h"
#include "LinkedList.h"
#include "Queue.h"
#include "Stack.h"
#include "file_reader.h"
#include "agent.h"
#include "agent_manager.h"

using namespace std;
using namespace std::chrono;

void addTicket(LinkedList &ticketList, Queue &pendingQueue, AgentManager &agentManager);
void resolveTicket(LinkedList &ticketList, Stack &resolutionLog);
void removeTicket(LinkedList &ticketList, Queue &pendingQueue);
void searchTicket(LinkedList &ticketList);
void sortTickets(LinkedList &ticketList);
void addAgent(AgentManager &agentManager);
void displayReports(LinkedList &ticketList, Queue &pendingQueue, Stack &resolutionLog, AgentManager &agentManager);
void displayResolutionLog(Stack &resolutionLog);
inline void Developer();

string defaultSortingAlgorithm = "";
string defaultSearchingAlgorithm = "";
int Threshold;

void showMenu(const ConfigReader &config)
{
    int choice;
    LinkedList ticketList;     // Custom linked list for managing tickets
    Queue pendingQueue;        // Custom queue for managing pending tickets (FIFO)
    Stack resolutionLog;       // Stack for managing ticket resolution logs (LIFO)
    AgentManager agentManager; // Agent manager for managing agents

    defaultSortingAlgorithm = config.getDefaultSortingAlgorithm();
    defaultSearchingAlgorithm = config.getDefaultSearchingAlgorithm();
    Threshold = config.getThreshold();

    do
    {
        cout << "\n\t==============================================\n";
        cout << "\t\tOne-Stop Management System\n";
        cout << "\t==============================================\n";
        cout << "\n1. Add Ticket.\n";
        cout << "2. Resolve Ticket.\n";
        cout << "3. Remove Ticket.\n";
        cout << "4. Search Ticket.\n";
        cout << "5. Sort Tickets.\n";
        cout << "6. Add Agent.\n";
        cout << "7. Display Reports.\n";
        cout << "8. Developer\n";
        cout << "0. Exit.\n";
        cout << "\nEnter choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            addTicket(ticketList, pendingQueue, agentManager);
            break;
        case 2:
            resolveTicket(ticketList, resolutionLog);
            break;
        case 3:
            removeTicket(ticketList, pendingQueue);
            break;
        case 4:
            searchTicket(ticketList);
            break;
        case 5:
            sortTickets(ticketList);
            break;
        case 6:
            addAgent(agentManager);
            break;
        case 7:
            displayReports(ticketList, pendingQueue, resolutionLog, agentManager);
            break;
        case 8:
            Developer();
            break;
        case 0:
            cout << "===========================================\n";
            cout << "Humara System Hack Karne ke Liye Shukriya!\n\tAb aap ja sakte hain.\n";
            cout << "\t=====================\n\n";
            break;
        default:
            cout << "Invalid choice! Please try again.\n";
            break;
        }
    } while (choice != 0);
}

// methods to sort tickets based on user preference (based on priority, creation time or name)
void sortTickets(LinkedList &ticketList)
{
    int sortOption;
    int choice;

    cout << "\nUsing " << defaultSortingAlgorithm << " to sort the tickets." << endl;
    cout << "If You want to change, then choose from the following" << endl;
    cout << "1. Bubble Sort" << endl;
    cout << "2. Selection Sort" << endl;
    cout << "3. Quick Sort" << endl;
    cout << "4. Merge Sort" << endl;
    cout << "0. Use Default" << endl;
    cout << "Enter choice: ";
    cin >> choice;

    cout << "\nSort Based on ?\n";
    cout << "1. Priority\n";
    cout << "2. Creation Time\n";
    cout << "3. Customer Name\n";
    cout << "Enter choice: ";
    cin >> sortOption;

    if (sortOption == 1)
    {
        auto start_SBP = high_resolution_clock::now(); // recording starting time
        ticketList.sortByPriority(choice);
        auto stop_SBP = high_resolution_clock::now();                          // recording ending time
        auto duration_SBP = duration_cast<milliseconds>(stop_SBP - start_SBP); // calculating total time it takes (time complexity)

        cout << "\n- Tickets sorted based on Priority using ";
        if (choice == 0)
        {
            cout << "Insertion Sort.\n";
        }
        else if (choice == 1)
        {
            cout << "Bubble Sort.\n";
        }
        else if (choice == 2)
        {
            cout << "Selection Sort.\n";
        }
        else if (choice == 3)
        {
            cout << "Quick Sort.\n";
        }
        else if (choice == 4)
        {
            cout << "Merge Sort.\n";
        }
        cout << "- Time Taken to Sort Tickets by Priority: " << duration_SBP.count() << " milliseconds\n";
    }
    else if (sortOption == 2)
    {

        auto start_SBC = high_resolution_clock::now(); // recording starting time
        ticketList.sortByCreationTime(choice);
        auto stop_SBC = high_resolution_clock::now();                          // recording ending time
        auto duration_SBC = duration_cast<milliseconds>(stop_SBC - start_SBC); // calculating total time it takes (time complexity)

        cout << "\n- Tickets sorted based on Creation Time using ";
        if (choice == 0)
        {
            cout << "Insertion Sort.\n";
        }

        else if (choice == 1)
        {
            cout << "Bubble Sort.\n";
        }
        else if (choice == 2)
        {
            cout << "Selection Sort.\n";
        }
        else if (choice == 3)
        {
            cout << "Quick Sort.\n";
        }
        else if (choice == 4)
        {
            cout << "Merge Sort.\n";
        }
        else
        {
            cout << "Insertion Sort.\n";
        }

        cout << "- Time Taken to Sort Tickets by Creation Time: " << duration_SBC.count() << " milliseconds\n";
    }

    else if (sortOption == 3)
    {

        auto start_SBN = high_resolution_clock::now(); // recording starting time
        ticketList.sortByCustomerName(choice);
        auto stop_SBN = high_resolution_clock::now();                          // recording ending time
        auto duration_SBN = duration_cast<milliseconds>(stop_SBN - start_SBN); // calculating total time it takes (time complexity)

        cout << "\n- Tickets sorted based on Customer Name using ";
        if (choice == 0)
        {
            cout << "Insertion Sort.\n";
        }
        else if (choice == 1)
        {
            cout << "Bubble Sort.\n";
        }
        else if (choice == 2)
        {
            cout << "Selection Sort.\n";
        }
        else if (choice == 3)
        {
            cout << "Quick Sort.\n";
        }
        else if (choice == 4)
        {
            cout << "Merge Sort.\n";
        }
        cout << "- Time Taken to Sort Tickets by Priority: " << duration_SBN.count() << " milliseconds\n";
    }

    else
    {
        cout << "Invalid choice! Please select a valid sorting option.\n";
        return;
    }

    ticketList.displayAll();
}

// method to search for a particular ticket
void searchTicket(LinkedList &ticketList)
{
    int searchOption;
    int choice;

    cout << "\nUsing " << defaultSearchingAlgorithm << " to Search for the ticket." << endl;
    cout << "If You want to change, then choose from the following" << endl;
    cout << "1. Binary Search" << endl;
    cout << "2. Interpolation Search" << endl;
    cout << "Note: Interpolation Search is only available for searching by Ticket ID. for searching using interpolation search, the data should\nbe uniformly distributed. If not sure about that, use Linear or Binary Search!" << endl;
    cout << "0. Use Default\n"
         << endl;
    cout << "Enter choice: ";
    cin >> choice;

    cout << "\n------------\n";
    cout << "Search Based on ?:\n";
    cout << "1. Ticket ID\n";
    cout << "2. Customer Name\n";
    cout << "Enter choice: ";
    cin >> searchOption;

    if (searchOption == 1)
    {
        auto start_search = high_resolution_clock::now();

        int ticketID;
        cout << "\nEnter Ticket ID: ";
        cin >> ticketID;

        Ticket *ticket = ticketList.searchByID(ticketID, choice);
        if (ticket != nullptr)
        {
            cout << "\n-------------------\n";
            cout << "Ticket found!\n";
            cout << "ID: " << ticket->id << "\n";
            cout << "Customer: " << ticket->customerName << "\n";
            cout << "Priority: " << ticket->priority << "\n";
            cout << "Status: " << (ticket->isOpen ? "Open" : "Closed") << "\n";
        }
        else
        {
            cout << "\nTicket with ID \"" << ticketID << "\" not found.\n";
        }
        auto stop_search = high_resolution_clock::now();
        auto duration_search = duration_cast<milliseconds>(stop_search - start_search);
        cout << "- Time taken to search the ticket: " << duration_search.count() << " milliseconds\n";
        cout << "---------------------------------------\n";
    }
    else if (searchOption == 2)
    {
        auto start_search = high_resolution_clock::now();

        string name;
        cout << "\nEnter Customer Name: ";
        cin.ignore();
        getline(cin, name);

        Ticket *ticket = ticketList.searchByName(name, choice);
        if (ticket != nullptr)
        {
            cout << "\nTicket found!\n";
            cout << "-------------------\n";
            cout << "ID: " << ticket->id << "\n";
            cout << "Customer: " << ticket->customerName << "\n";
            cout << "Priority: " << ticket->priority << "\n";
            cout << "Status: " << (ticket->isOpen ? "Open" : "Closed") << "\n";
        }
        else
        {
            cout << "\nTicket with Customer name \"" << name << "\" not found.\n";
        }
        auto stop_search = high_resolution_clock::now();
        auto duration_search = duration_cast<milliseconds>(stop_search - start_search);
        cout << "- Time taken to search tickets: " << duration_search.count() << " milliseconds\n";
        cout << "---------------------------------------\n";
    }

    else
    {
        cout << "\nInvalid choice. Please select 1 or 2.\n";
    }
}

// method to add agents
void addAgent(AgentManager &agentManager)
{
    int id;
    string name;
    cout << "\n-----------\n";
    cout << "Enter Agent ID: ";
    cin >> id;
    cout << "Enter Agent Name: ";
    cin.ignore();
    getline(cin, name);

    auto start_addAgent = high_resolution_clock::now();
    if (agentManager.addAgent(id, name))
    {
        cout << "Agent added successfully!\n";
        auto stop_addAgent = high_resolution_clock::now();
        auto duration_addAgent = duration_cast<milliseconds>(stop_addAgent - start_addAgent);
        cout << "- Time taken to add an Agent: " << duration_addAgent.count() << " milliseconds\n";
    }
    cout << "--------------------------------\n";
}

// method to add tickets
void addTicket(LinkedList &ticketList, Queue &pendingQueue, AgentManager &agentManager)
{
    int id, priority;
    string name, desc;

    cout << "\n-----------\n";
    cout << "Enter Ticket ID: ";
    cin >> id;
    cout << "Enter Customer Name: ";
    cin.ignore();
    getline(cin, name);

    cout << "Enter Priority (1=High, 2=Medium, 3=Low): ";
    cin >> priority;
    cout << "Enter Description: ";
    cin.ignore();
    getline(cin, desc);

    auto start_newTicket = high_resolution_clock::now();
    Ticket newTicket(id, name, priority, desc);
    ticketList.add(newTicket);
    auto stop_newTicket = high_resolution_clock::now();

    auto duration_newTicket = duration_cast<milliseconds>(stop_newTicket - start_newTicket);
    cout << "Time Taken for adding a new Ticket: " << duration_newTicket.count() << " milliseconds" << endl;
    cout << "----------------------------------------\n";

    if (!agentManager.assignTicketToAgent(id))
    {
        pendingQueue.enqueue(newTicket);
        cout << "- Ticket with ID \"" << id << "\" added to pending queue.....\n";
    }
}

// mothod to resolve tickets and add that ticket to the resolution log (i.e. stack)
void resolveTicket(LinkedList &ticketList, Stack &resolutionLog)
{
    int ticketID;
    cout << "------------\n";
    cout << "\nEnter Ticket ID to resolve: ";
    cin >> ticketID;

    auto start_resolveTicket = high_resolution_clock::now();
    Ticket *ticket = ticketList.searchByID(ticketID, 0);
    if (ticket && ticket->isOpen)
    {
        ticket->isOpen = false;
        ticket->closeTime = time(nullptr);

        resolutionLog.push(*ticket);
        auto stop_resolveTicket = high_resolution_clock::now();
        auto duration_resolveTicket = duration_cast<milliseconds>(stop_resolveTicket - start_resolveTicket);

        cout << "Ticket with ID \"" << ticketID << "\" has been resolved and added to the resolution log.\n";
        cout << "Time taken to search and resolve a Ticket: " << duration_resolveTicket.count() << " milliseconds" << endl;
        cout << "-----------------------------------------------------------\n";
    }
    else if (ticket)
    {
        cout << "Ticket with ID \"" << ticketID << "\" is already resolved.\n";
        cout << "-----------------------------------------------------------\n";
    }
    else
    {
        cout << "Ticket with ID \"" << ticketID << "\" not found.\n";
        cout << "-----------------------------------------------------------\n";
    }
}

// method to display the resolved tickets
void displayResolutionLog(Stack &resolutionLog)
{
    cout << "\n-----------\n";
    cout << "Ticket Resolution Log:\n";
    if (resolutionLog.isEmpty())
    {
        cout << "No resolved tickets!\n";
        cout << "--------------------------\n";
    }
    else
    {
        resolutionLog.display();
    }
}

// method to display the pending tickets
void displayPendingQueue(Queue &pendingQueue)
{
    cout << "----------------\n";
    cout << "Pending Tickets:\n";
    if (pendingQueue.isEmpty())
    {
        cout << "- No Pending Tickets..!\n";
    }
    else
    {
        pendingQueue.display();
    }
}

// method to remove a particular ticket using ticket ID
void removeTicket(LinkedList &ticketList, Queue &pendingQueue)
{
    int ticketID;
    cout << "\nEnter Ticket ID to remove: ";
    cin >> ticketID;

    cout << "----------------\n";
    auto start_removeTicket = chrono::high_resolution_clock::now();
    if (ticketList.remove(ticketID))
    {
        cout << "- Ticket ID " << ticketID << " removed from the Ticket List.\n";

        // Also removing ticket from the pending queue if present
        Queue tempQueue;
        bool foundInPending = false;

        while (!pendingQueue.isEmpty())
        {
            Ticket t = pendingQueue.dequeue();
            if (t.id == ticketID)
            {
                foundInPending = true;
                cout << "- Ticket ID " << ticketID << " also removed from the Pending Queue.\n";
            }
            else
            {
                tempQueue.enqueue(t);
            }
        }

        // Restoring the remaining tickets back to pendingQueue
        while (!tempQueue.isEmpty())
        {
            pendingQueue.enqueue(tempQueue.dequeue());
        }

        if (!foundInPending)
        {
            cout << "- Ticket ID " << ticketID << " was not in the pending queue.\n";
        }
        auto stop_removeTicket = chrono::high_resolution_clock::now();
        auto duration_removeTicket = chrono::duration_cast<milliseconds>(stop_removeTicket - start_removeTicket);

        cout << "Time taken to search and remove the ticket: " << duration_removeTicket.count() << " milliseconds" << endl;
    }
    else
    {
        cout << "- Ticket ID " << ticketID << " not found in the ticket list.\n";
    }
    cout << "-----------------------------------------\n";
}

// method to Display all the Reports
void displayReports(LinkedList &ticketList, Queue &pendingQueue, Stack &resolutionLog, AgentManager &agentManager)
{
    int reportOption;
    cout << "-------------\n";
    cout << "\n1. Display All Tickets\n";
    cout << "2. Display Pending Tickets\n";
    cout << "3. Display Ticket Resolution Log\n";
    cout << "4. Display All Agents\n";
    cout << "Enter choice: ";

    cin >> reportOption;
    cout << "--------------------------\n";

    switch (reportOption)
    {
    case 1:
        ticketList.displayAll();
        break;
    case 2:
        displayPendingQueue(pendingQueue);
        break;
    case 3:
        displayResolutionLog(resolutionLog);
        break;
    case 4:
        agentManager.displayAllAgents();
        break;
    default:
        cout << "Invalid Input!\n";
        break;
    }
}

// method to Display Information About the Developer
inline void Developer()
{
    cout << "=====================" << endl;
    cout << "\tBrought To You by alpha" << endl;
    cout << "\n\tKirish Kumar\t23K-0641\n";
    cout << "Github: https://github.com/code-with-alpha\n";
    cout << "Linkedin: https://linkedin.com/in/krrishkumar\n";
    cout << "Youtube: https://youtube.com/@codewithalphadotcom\n";
    cout << "=======================================================\n";
}

// This is the entry point of the complete  One Stop Management System
int main()
{
    ConfigReader config;
    config.loadConfig("config.txt"); // Loading the configuration from config.txt
    showMenu(config);
    return 0;
}
