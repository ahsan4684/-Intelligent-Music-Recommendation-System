/*Azzam Atiq 22i-9886
Ahsan Nazeef 22i-2157
*/

#include <iostream>
#include <fstream>
#include <sstream>
#include "Song.h"
#include "User.h"

using namespace std;

void search(BST& tree) {
    int choices;
    string ip;
    cout<<"Search by: 1. Name 2. Genre 3. Artist\nEnter choice: ";
    cin>>choices;
    cin.ignore();
    switch (choices) {
        case 1:
            cout<<"Enter the name of the song to search: ";
            getline(cin,ip);
            {nodes* result = tree.sbname(ip);
                if (result) {
                    cout<<"Song found: "<<endl;
                    cout<<"Name: "<<result->data.name<<", Genre: "<<result->data.genre<<", Artist: "<<result->data.artist<<endl;
                } else {
                    cout<<"Song not found."<<endl;}}
            break;
        case 2:
            cout<<"Enter the genre of the songs to search: ";
            getline(cin, ip);
            tree.sbgenre(ip);
            break;
        case 3:
            cout<<"Enter the artist of the songs to search: ";
            getline(cin,ip);
            tree.sbartist(ip);
            break;
        default:
            cout<<"Invalid option."<<endl;
            break;}}

void loadsong(BST& tree) {
    ifstream file("songs_list.txt");
    string l;
    while (getline(file,l)) {
        stringstream ss(l);
        string part,name,genre,artist;
        getline(ss,part,':'); 
        getline(ss,name,',');
        name = name.substr(1); 
        getline(ss,part,':'); 
        getline(ss,genre,',');
        genre = genre.substr(1); 
        getline(ss,part, ':');
        getline(ss,artist);
        artist=artist.substr(1);
        song song(name,genre,artist);
        tree.insert(song);}
    file.close();}

int main() {
    BST tree;
    loadsong(tree);
    usertable users;  
    while (true) {
        int choice;
        string username,password;
        cout<<"1. Login\n2. Signup\nEnter choice: ";
        cin>>choice;
        cin.ignore();  
        cout<<"Enter username: ";
        getline(cin,username);
        cout<<"Enter password: ";
        getline(cin,password);
        if(choice==1) {
            if(users.login(username,password)) {
                cout<<"Login successful!"<<endl;
                while (true) {
                    cout<<"1. Music Library\n2. Search a song\n3. Add song to playlist\n4. Mark song as favorite\n5. Display playlists\n6. Display favorite songs\n7. Recommend songs\n9. Log out\nEnter choice: ";
                    int mchoice;
                    cin>>mchoice;
                    cin.ignore();  
                    if(mchoice==1) {
                        tree.display();  
                    } else if (mchoice==2) {
                        search(tree);
                    } else if (mchoice==3) {
                        string pname, sname;
                        cout<<"Enter playlist name: ";
                        getline(cin,pname);
                        cout<<"Enter song name: ";
                        getline(cin,sname);
                        users.playlistt(username,pname,sname,tree);
                    } else if (mchoice==4) {
                        string sname;
                        cout<<"Enter song name: ";
                        getline(cin,sname);
                        users.favv(username,sname,tree);
                    } else if (mchoice==5) {
                        users.dispplaylist(username);
                    } else if (mchoice==6) {
                        users.dispfav(username);
                    } else if (mchoice == 7) {
                        users.engine(username, tree);
                    } else if (mchoice == 9) {
                        cout << "Logging out..." << endl;
                        break;
                    } }
                break; 
            } else {
                cout<<"Invalid username or password. try again."<<endl;   }
        } else if (choice==2) {
            if (users.signup(username,password)) {
                cout<<"Signup successful! You can now login."<<endl;
            } else {
                cout<<"Username already exists.  try again."<<endl;
            }
        } else {
            cout<<"Invalid choice.  try again."<<endl;}}}