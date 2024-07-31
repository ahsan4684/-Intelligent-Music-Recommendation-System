#include "User.h"
#include "Song.h"
#include <fstream>
#include <iostream>
#include<sstream>
#include<string>

usertable::usertable(int size):size(size),dchan(false) {
    table = new nodein*[size]();
    for (int i=0;i<size;++i) {
        table[i]=NULL;}
    loadu();
    loadp();}

int usertable::hashing(const string& key) {
    long long hash=5381;
    for (int i=0;i <key.length();++i) {
        hash=(hash*33) + key[i];}
    return hash % size;}

void usertable::loadu() {
    ifstream file("users.txt");
    if (!file) {
        cout << "Failed to open users.txt " << endl;
        return;}
    string line, username, password;
    while (getline(file, line)) {
        istringstream ss(line);
        if (getline(ss, username,',')&&getline(ss,password)) {
            signup(username, password);}}
    file.close();}

void usertable::saveu() {
    if (!dchan) return;
    ofstream file("users.txt",ios::trunc);
    if (!file){
        cout<<"Failed to open users.txt"<<endl;
        return;}
    for (int i=0;i<size;++i) {
        nodein* current=table[i];
        while (current!=NULL) {
            file<<current->username<<","<<current->password<<endl;
            current=current->next;}}
    file.close();
    dchan = false;}

void usertable::loadp() {
    ifstream file("playlist.txt");
    if (!file) {
        cout<<"Failed to open playlist.txt"<<endl;
        return;}
    string line,username,namepla,sname;
    nodein* ccuser=NULL;
    while (getline(file,line)){
        if (line.empty()) continue;
        if (line[0]!=' ') {
            ccuser=NULL;
            for (int i=0;i<size;++i) {
                nodein* current=table[i];
                while (current!=NULL) {
                    if (current->username==line) {
                        ccuser=current;
                        break;}
                    current=current->next;}
                if (ccuser) break;
            }
        } else if (line[1]!= ' '){
            namepla=line.substr(1);
            nodepl* nplayy=new nodepl(namepla);
            nplayy->next=ccuser->plist;
            ccuser->plist=nplayy;
        } else {
            sname=line.substr(2);
            nodeu* nnsong=new nodeu(sname);
            if (namepla.empty()) {
                nnsong->next=ccuser->favs;
                ccuser->favs=nnsong;
            } else {
                nodepl* ccplay=ccuser->plist;
                while (ccplay&&ccplay->namepla!=namepla) {
                    ccplay=ccplay->next;}
                if (ccplay) {
                    nnsong->next=ccplay->songs;
                    ccplay->songs=nnsong;}}}}
    file.close();}

void usertable::savep() {
    ofstream file("playlist.txt", ios::trunc);
    if (!file) {
        cout<<"Failed to open playlist.txt"<<endl;
        return;}
    for (int i=0;i<size;++i) {
        nodein* current=table[i];
        while (current!=NULL) {
            file<<current->username<<endl;
            nodepl* ccplay=current->plist;
            while (ccplay!=NULL) {
                file<<" "<<ccplay->namepla<<endl;
                nodeu* csongg=ccplay->songs;
                while (csongg!=NULL) {
                    file<<"  "<<csongg->sname<<endl;
                    csongg=csongg->next;}
                ccplay=ccplay->next;}
            nodeu* cufavv=current->favs;
            while (cufavv!=NULL) {
                file<<"  "<<cufavv->sname<<endl;
                cufavv=cufavv->next;}
            current=current->next;}}
    file.close();}

bool usertable::login(const string& username, const string& password) {
    int index=hashing(username);
    nodein* current=table[index];
    while (current!=NULL) {
        if (current->username==username&&current->password==password) {
            return true;}
        current=current->next;}
    return false;}

bool usertable::signup(const string& username, const string& password) {
    int index=hashing(username);
    nodein* current=table[index];
    while (current!=NULL) {
        if (current->username==username) {
            return false;}
        current=current->next;}
    nodein* nuserr=new nodein(username,password);
    nuserr->next=table[index];
    table[index]=nuserr;
    dchan=true;
    saveu();
    return true;}

void usertable::playlistt(const string& username, const string& namepla, const string& sname, BST& tree) {
    if (!tree.exxsist(sname)) {
        cout<<"song does not exist "<<endl;
        return;}
    int index=hashing(username);
    nodein* current=table[index];
    while (current!=NULL) {
        if (current->username==username) {
            nodepl* ccplay=current->plist;
            while (ccplay!=NULL) {
                if (ccplay->namepla==namepla) {
                    nodeu* csongg=ccplay->songs;
                    while (csongg!=NULL) {
                        if (csongg->sname==sname) {
                            cout<<"song already exists in the playlist."<<endl;
                            return;}
                        csongg=csongg->next;}
                    break;}
                ccplay=ccplay->next;}
            if (!ccplay) {
                ccplay=new nodepl(namepla);
                ccplay->next=current->plist;
                current->plist=ccplay;}
            nodeu* nnsong=new nodeu(sname);
            nnsong->next=ccplay->songs;
            ccplay->songs=nnsong;
            dchan=true;
            savep();
            return;}
        current=current->next;}}

void usertable::favv(const string& username, const string& sname, BST& tree) {
    if (!tree.exxsist(sname)) {
        cout<<"song does not exist "<<endl;
        return;}
    int index=hashing(username);
    nodein* current=table[index];
    while (current != NULL) {
        if (current->username == username) {
            nodeu* cufavv = current->favs;
            while (cufavv != NULL) {
                if (cufavv->sname == sname) {
                    cout<<"song already exists "<<endl;
                    return;}
                cufavv=cufavv->next;        }
            nodeu* nnsong=new nodeu(sname);
            nnsong->next=current->favs;
            current->favs=nnsong;
            dchan=true;
            savep();
            return;}
        current=current->next;}}

void usertable::dispplaylist(const string& username) {
    int index=hashing(username);
    nodein* current=table[index];
    while (current!=NULL) {
        if (current->username==username) {
            nodepl* ccplay=current->plist;
            while (ccplay!=NULL) {
                cout<<"Playlist: "<<ccplay->namepla<<endl;
                nodeu* csongg=ccplay->songs;
                while (csongg!=NULL) {
                    cout<<"  "<<csongg->sname<<endl;
                    csongg=csongg->next;}
                ccplay=ccplay->next;}
            return;}
        current=current->next;}}

void usertable::dispfav(const string& username) {
    int index=hashing(username);
    nodein* current=table[index];
    while (current!=NULL) {
        if (current->username==username) {
            cout<<"Favorite Songs:"<<endl;
            nodeu* cufavv=current->favs;
            while (cufavv!=NULL) {
                cout<<"  "<<cufavv->sname<<endl;
                cufavv=cufavv->next;}
            return;}
        current=current->next;}}

void usertable::engine(const string& username, BST& tree) {
    int index = hashing(username);
    nodein* ccuser = table[index];
    while (ccuser!=NULL) {
        if (ccuser->username==username) {
            string usgenre[100];
            string usartist[100];
            int gcount = 0;
            int acount = 0;
            nodepl* ccplay=ccuser->plist;
            while (ccplay!=NULL) {
                nodeu* csongg=ccplay->songs;
                while (csongg!=NULL) {
                    nodes* nodes=tree.sbname(csongg->sname);
                    if (nodes) {
                        bool exx1 = false;
                        for (int i=0;i<gcount;++i) {
                            if (usgenre[i]==nodes->data.genre) {
                                exx1=true;
                                break;}}
                        if (!exx1) {
                            usgenre[gcount++]=nodes->data.genre;}
                        bool exx2=false;
                        for (int i=0;i<acount;++i) {
                            if (usartist[i]==nodes->data.artist) {
                                exx2=true;
                                break;}}
                        if (!exx2) {
                            usartist[acount++]=nodes->data.artist;}}
                    csongg=csongg->next;}
                ccplay=ccplay->next;}
            nodeu* cufavv=ccuser->favs;
            while (cufavv!=NULL) {
                nodes* nodes=tree.sbname(cufavv->sname);
                if (nodes) {
                    bool exx1=false;
                    for (int i=0;i<gcount;++i) {
                        if (usgenre[i]==nodes->data.genre) {
                            exx1=true;
                            break;}}
                    if (!exx1) {
                        usgenre[gcount++]=nodes->data.genre;}
                    bool exx2=false;
                    for (int i=0;i<acount;++i) {
                        if (usartist[i]==nodes->data.artist) {
                            exx2 = true;
                            break;}}
                    if (!exx2) {
                        usartist[acount++]=nodes->data.artist;}}
                cufavv=cufavv->next;}
            cout<<"Recommended Songs:"<<endl;
            tree.engine(usgenre,gcount,usartist,acount);
            return;}
        ccuser=ccuser->next;}}