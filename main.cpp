#include <filesystem>
#include <fstream>
#include <iostream>
#include <cstring>
#include <stdlib.h>

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
        cout << "Move File from Directory  -> Move File   \n";
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
                cout << "Exists\n";
            }
            else
            {
                cout << "Not Exists\n";
            }
        }
        else if (choice == "View Files")
        {
            for (const auto &dirEntry : recursive_directory_iterator(current_path()))
                std::cout << dirEntry << std::endl;
        }
        else if (choice == "Create File")
        {
            string FileName, Data;
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
        else if (choice == "Move File")
        {
            string oldDir, newDir;
            cout << "\nEnter Old Directory : ";
            getline(cin, oldDir);
            cout << "\nEnter New Directory : ";
            getline(cin, newDir);
            error_code err;
            rename(oldDir, newDir, err);
            if (err)
            {
                perror("Error moving file\n");
            }
            else
            {
                cout << "File Moved Succesfully\n";
            }
        }
    } while (choice != "Exit");
}