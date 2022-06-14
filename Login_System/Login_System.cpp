#include <iostream>
#include <fstream>
#include <string>
#include <sys/types.h>
#include <sys/stat.h>
#if __cplusplus > 201402L // If the version of C++ is > than 14
    #include <experimental/filesystem>
    // It was still in the experimental:: namespace
    namespace fs = std::experimental::filesystem;
#else
    #include <filesystem>
    namespace fs = std::filesystem;
#endif

using namespace std;

int main(int argc, char * argv[])
{
    const unsigned int password_len = 15;
    struct stat info;
    char input;         //buffer for user inputs
    char data[password_len];      //buffer for reading password
    string name_buffer; //buffer for username input
    string pass_buffer; //buffer for password input
    string buffer;      //working buffer
    cout << "Login System 1.0" << endl;
    cout << "Login? (L)" << endl;
    cout << "Register? (R)" << endl;
    cin >> input;
    ofstream create;    //obj to create and write to credential files
    ifstream read;      //obj to read credential files
    //****************************************************************/
    //**********************Registration branch***********************/
    //****************************************************************/
    if (input == 'R' || input == 'r')
    {
        name_buffer.clear();    //empty buffer
        pass_buffer.clear();    //empty buffer
        system("cls");
        cout << "Choose a username: ";
        cin >> name_buffer;
        system("cls");
        cout << "Choose a password: ";
        cin >> pass_buffer;
        //Save credentials in file named name_buffer
        if (create.is_open())   //If stream is open close it
        {
            create.flush();
            create.close();
        }
        //Check if Credentials folder exists
        //If folder is not there make another one
        if (stat(".\\Credentials\\", &info) != 0)
        {
            fs::create_directory("Credentials");
        }
        //create path to credential file to be created
        buffer = ".\\Credentials\\";
        buffer.append(name_buffer);
        buffer.append(".cred");
        create.open(buffer.c_str(),ofstream::out);
        //Write password 
        create.write(pass_buffer.c_str(), pass_buffer.size());
        //Close stream
        create.flush();
        create.close();
        
        //Success
        system("cls");
        printf("User %s Registered!",name_buffer.c_str());
    }
    //****************************************************************/
    //*************************Login branch***************************/
    //****************************************************************/
    else if (input == 'L' || input == 'l')
    {
        name_buffer.clear();    //empty buffer
        pass_buffer.clear();    //empty buffer
        memset(data, 0, password_len);
        system("cls");
        cout << "Username: ";
        cin >> name_buffer;
        system("cls");
        cout << "Password: ";
        cin >> pass_buffer;
        //check if name file exists
        buffer = ".\\Credentials\\";
        buffer.append(name_buffer);
        buffer.append(".cred");
        //if username doent exist
        if (!(fs::exists(buffer.c_str())))
        {
            system("cls");
            cout << "Login Failed: Username does not exist" << endl;
        }
        else
        {
            //Validate password
            if (read.is_open())   //If stream is open close it
            {
                read.close();
            }
            read.open(buffer.c_str(), ifstream::in);    //open credential file
            //Get password
            read.read(data, password_len);
            //close stream
            read.close();
            //Validate password
            //If password is not valid
            if (strcmp(data, pass_buffer.c_str()))
            {
                system("cls");
                cout << "Login Failed: Incorrect Password" << endl;
            }
            else
            {
                system("cls");
                cout << "Logged in successfully" << endl;
            }
        }
    }
}