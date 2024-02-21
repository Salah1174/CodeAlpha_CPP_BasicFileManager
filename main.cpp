#include <filesystem>
#include <fstream>
#include <iostream>
#include <cstring>

using namespace std;
using namespace std::filesystem;
using recursive_directory_iterator = std::filesystem::recursive_directory_iterator;

int main()
{
    string choice, DirLoc;
    do
    {
        cout << "\nCurrent Path : " << current_path();
        cout << "\nCreate Directory          -> Create Dir  \n";
        cout << "Navigate Directory        -> Navigate Dir\n";
        cout << "View Files in Directory   -> View Files  \n";
        cout << "Create Files in Directory -> Create File \n";
        cout << "Enter Required Operation : ";

        getline(cin, choice);
        if (choice == "Create Dir")
        {
            cout << "\nEnter Directory Location : ";
            getline(cin, DirLoc);
            if (create_directories(DirLoc))
            {
                cout << "Created\n";
            }
            else
            {
                cout << "Not Created\n";
            }
        }
        else if (choice == "Navigate Dir")
        {
            cout << "\nEnter Directory Location : ";
            getline(cin, DirLoc);
            directory_entry entry{DirLoc};
            if (entry.exists())
            {
                current_path(DirLoc);
                // cout << current_path() << endl;
                cout << "Exists\n";
            }
            else
            {
                cout << "Not Exists\n";
            }
        }
        else if (choice == "View Files")
        {
            // cout << "\nEnter Directory Location : ";
            // getline(cin, DirLoc);
            for (const auto &dirEntry : recursive_directory_iterator(current_path()))
                std::cout << dirEntry << std::endl;
        }
        else if (choice == "Create File")
        {
            string FileName, Data;
            // cout << "\nEnter Directory Location : ";
            // getline(cin, DirLoc);
            cout << "\nEnter File Name and Extension : ";
            getline(cin, FileName);

            path path(current_path());              
            path /= FileName;                       
            create_directories(path.parent_path()); 

            cout << "\nEnter file data : ";
            getline(cin, Data);
            ofstream ofs(path);
            ofs << Data;
            ofs.close();
        }
        // else if (choice == "Move File")
        // {
        //     std::ifstream in("from.txt", std::ios::in | std::ios::binary);
        //     std::ofstream out("to.txt", std::ios::out | std::ios::binary);
        //     out << in.rdbuf();
        //     std::remove("from.txt");

        //     // try
        //     // {
        //     //     std::filesystem::copy("from.txt", "to.txt");
        //     //     std::filesystem::remove("from.txt");
        //     // }
        //     // catch (std::filesystem::filesystem_error &e)
        //     // {
        //     //     std::cout << e.what() << '\n';
        //     // }
        // }

    } while (choice != "Exit");
}