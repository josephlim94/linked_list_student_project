// linked_list_student_project.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <functional>
#include "StudentList.h"

void init_data(StudentList& list)
{
    /*Open file and verify validity*/
    std::ifstream parseFile("data.txt");
    if (!parseFile.good())
    {
        cerr << "ERROR: File is either corrupt or does not exist." << endl;
        exit(1); //Terminate program
    }

    // Read record and save all data
    Student test_node;
    //Loop over file line by line
    std::string line;
    while (std::getline(parseFile, line))
    {
        if (line.empty())
        {
            continue;
        }
        // First line is student name
        test_node.name = line;
        // Second line is ID
        if (std::getline(parseFile, line))
        {
            std::stringstream line_stream(line);
            line_stream >> test_node.ID;
        }
        else
        {
            break;
        }
        // Third line is GPA
        if (std::getline(parseFile, line))
        {
            std::stringstream line_stream(line);
            line_stream >> test_node.GPA;
        }
        else
        {
            break;
        }
        // Add to list if parsing is ok
        list.add(test_node);
    }
}

typedef std::function<bool (StudentList&, std::ifstream&, std::stringstream&)> command_function;
typedef std::map<std::string, command_function> command_map_t;

command_map_t command_map;

void compute_command(StudentList& list) {
    // Iterate through command list file
    // Parse text to get command
    // Compute
    /*Open file and verify validity*/
    std::ifstream parseFile("commands.txt");
    if (!parseFile.good())
    {
        cerr << "ERROR: File is either corrupt or does not exist." << endl;
        exit(1); //Terminate program
    }

    //Loop over file line by line
    std::string line;
    while (std::getline(parseFile, line))
    {
        std::stringstream line_stream(line);
        std::string command;
        if (line_stream >> command) {
            line_stream >> std::ws;
            auto pos = command_map.find(command);
            if (pos != command_map.end())
                pos->second(list, parseFile, line_stream);
        }
    }
}

void printReverse(Student* student_node, int counter)
{
    // Base case  
    if (student_node == NULL)
        return;

    // print the list after head node  
    printReverse(student_node->next, counter+1);

    // After everything else is printed, print head
    std::cout << counter << " - Student name=" << student_node->name << std::endl;
    std::cout << "Student ID=" << student_node->ID << std::endl;
    std::cout << "Student GPA=" << student_node->GPA << std::endl;
    if (counter != 1) std::cout << "-------------------------- - " << std::endl;
}

int main()
{
    // register commands
    command_map.insert(command_map_t::value_type("ADDSTUDENT", [](StudentList& student_list, std::ifstream& parseFile, std::stringstream& s) {
        Student test_node;
        std::string line;
        if (!getline(s, line)) return false;
        // First line is student name
        test_node.name = line;
        // Second line is ID
        if (std::getline(parseFile, line))
        {
            std::stringstream line_stream(line);
            line_stream >> test_node.ID;
        }
        else
        {
            return false;
        }
        // Third line is GPA
        if (std::getline(parseFile, line))
        {
            std::stringstream line_stream(line);
            line_stream >> test_node.GPA;
        }
        else
        {
            return false;
        }
        // Add to list if parsing is ok
        student_list.add(test_node);
        return true;
        }));

    command_map.insert(command_map_t::value_type("STUDENTINFO", [](StudentList& student_list, std::ifstream& parseFile, std::stringstream& s) {
        std::string line;
        // Get student ID
        int student_id;
        if (!getline(s, line)) return false;
        std::stringstream line_stream(line);
        line_stream >> student_id;
        // Find student info based on ID
        Student* student_node = student_list.head;
        while (student_node != nullptr)
        {
            if (student_node->ID == student_id)
            {
                std::cout << "Student data found!" << std::endl;
                std::cout << "Student name=" << student_node->name << std::endl;
                std::cout << "Student ID=" << student_node->ID << std::endl;
                std::cout << "Student GPA=" << student_node->GPA << std::endl;
            }
            student_node = student_node->next;
        }
        return true;
        }));

    command_map.insert(command_map_t::value_type("DELETESTUDENT", [](StudentList& student_list, std::ifstream& parseFile, std::stringstream& s) {
        std::string line;
        // Get student ID
        int student_id;
        if (!getline(s, line)) return false;
        std::stringstream line_stream(line);
        line_stream >> student_id;
        // Find student info based on ID
        Student* student_node = student_list.head;
        while (student_node != nullptr)
        {
            if (student_node->ID == student_id)
            {
                student_list.deleteNode(student_node);
                break;
            }
            student_node = student_node->next;
        }
        return true;
        }));

    command_map.insert(command_map_t::value_type("FINDLARGEST", [](StudentList& student_list, std::ifstream& parseFile, std::stringstream& s) {
        std::string line;
        double largest_GPA = 0;
        Student *student_with_largest_gpa = nullptr;
        Student* student_node = student_list.head;
        while (student_node != nullptr)
        {
            if (student_node->GPA > largest_GPA)
            {
                student_with_largest_gpa = student_node;
                largest_GPA = student_node->GPA;
            }
            student_node = student_node->next;
        }

        if (student_with_largest_gpa != nullptr)
        {
            std::cout << "Student with the largest GPA is:" << std::endl;
            std::cout << "Student name=" << student_with_largest_gpa->name << std::endl;
            std::cout << "Student ID=" << student_with_largest_gpa->ID << std::endl;
            std::cout << "Student GPA=" << student_with_largest_gpa->GPA << std::endl;
        }
        return true;
        }));

    command_map.insert(command_map_t::value_type("PRINTLIST", [](StudentList& student_list, std::ifstream& parseFile, std::stringstream& s) {
        std::string line;
        std::cout << "Will run PRINTLIST command." << std::endl;
        std::cout << "The list of students in the system are: " << std::endl;
        Student* student_node = student_list.head;
        int student_counter = 1;
        while (student_node != nullptr)
        {
            std::cout << student_counter << " - Student name=" << student_node->name << std::endl;
            std::cout << "Student ID=" << student_node->ID << std::endl;
            std::cout << "Student GPA=" << student_node->GPA << std::endl;
            student_node = student_node->next;
            student_counter++;
            if (student_node != nullptr) std::cout << "-------------------------- - " << std::endl;
        }
        return true;
        }));

    command_map.insert(command_map_t::value_type("REVERSEPRINTLIST", [](StudentList& student_list, std::ifstream& parseFile, std::stringstream& s) {
        std::string line;
        int counter = 1;
        std::cout << "Will run REVERSEPRINTLIST command.\n";
        //printReverse(student_list.head, counter);
        return true;
        }));

    StudentList list;
    init_data(list);
    compute_command(list);
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
