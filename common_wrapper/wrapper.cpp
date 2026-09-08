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
        cout << "3. Assignment 3\n";
        cout << "4. Assignment 4\n";
        cout << "5. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        if(choice == 1)
        {
            run_assignment("..\\assignment1", "assignment1.exe");
        }
        else if(choice == 2)
        {
            run_assignment("..\\assignment2", "assignment2.exe");
        }
        else if(choice == 3)
        {
            run_assignment("..\\assignment3", "assignment3.exe");
        }
        else if(choice == 4)
        {
            run_assignment("..\\assignment4", "assignment4.exe");
        }
        else if(choice == 5)
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
