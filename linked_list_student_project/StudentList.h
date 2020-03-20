
#include <iostream>
#include "Student.h"

using namespace std;

#pragma once
class StudentList
{
public:
	Student* head;
	Student* tail;
	StudentList() {
		head = nullptr;
		tail = nullptr;
	}

    void add(Student node)
    {
        // Create new node
        Student* tmp = new Student;
        // Copy node data
        tmp->name = node.name;
        tmp->ID = node.ID;
        tmp->GPA = node.GPA;
        // Set next node as null
        tmp->next = nullptr;

        if (head == nullptr)
        {
            head = tmp;
            tail = tmp;
        }
        else
        {
            tail->next = tmp;
            tail = tail->next;
        }
    }

    void deleteNode(Student* node)
    {
        // When node to be deleted is head node  
        if (head == node)
        {
            if (head->next == NULL)
            {
                std::cout << "There is only one node." <<
                    " The list can't be made empty " << std::endl;
                return;
            }

            /* Copy the data of next node to head */
            head->name = head->next->name;
            head->ID = head->next->ID;
            head->GPA = head->next->GPA;

            // store address of next node
            node = head->next;

            // Remove the link of next node  
            head->next = head->next->next;

            // free memory  
            delete node;

            return;
        }

        // When not first node, follow  
        // the normal deletion process  

        // find the previous node  
        Student* prev = head;
        while (prev->next != nullptr && prev->next != node)
            prev = prev->next;

        // Check if node really exists in Linked List  
        if (prev->next == nullptr)
        {
            std::cout << "\nGiven node is not present in Linked List" << std::endl;
            return;
        }

        // Remove node from Linked List  
        prev->next = prev->next->next;

        // Free memory  
        delete node;

        return;
    }

};

