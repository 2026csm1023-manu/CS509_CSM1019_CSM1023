#include <iostream>
#include <cstdlib>

using namespace std;

void run_assignment(string folder, string executable)
{
    string command = "cd " + folder + " && " + executable;
    system(command.c_str());
}

int main()
{
    int choice;

    while(true)
    {
        cout << "\nSelect Assignment\n";
        cout << "1. Assignment 1\n";
        cout << "2. Assignment 2\n";
        cout << "3. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        if(choice == 1)
        {
            run_assignment("assignment1", "assignment1.exe");
        }
        else if(choice == 2)
        {
            run_assignment("assignment2", "assignment2.exe");
        }
        else if(choice == 3)
        {
            break;
        }
        else
        {
            cout << "Invalid choice\n";
        }
    }

    return 0;
}