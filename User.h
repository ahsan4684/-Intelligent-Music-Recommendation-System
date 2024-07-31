#include <string>
#include "Song.h"
using namespace std;

class nodeu {
public:
    string sname;
    nodeu* next;
    nodeu(const string& sname):sname(sname),next(NULL) {}};

class nodepl {
public:
    string namepla;
    nodeu* songs;
    nodepl* next;
    nodepl(const string& namepla):namepla(namepla),songs(NULL),next(NULL){}};

class nodein {
public:
    string username;
    string password;
    nodeu* favs;
    nodepl* plist;
    nodein* next;
    nodein(const string& username, const string& password):username(username),password(password),favs(NULL),plist(NULL),next(NULL){}};

class usertable {
private:
    nodein** table;
    int size;
    bool dchan;
    int hashing(const string& key);
    void loadu();
    void saveu();
    void loadp();
    void savep();
public:
    usertable(int size=201);
    bool login(const string& username,const string& password);
    bool signup(const string& username,const string& password);
    void playlistt(const string& username,const string& namepla,const string& sname,BST& tree);
    void favv(const string& username,const string& sname,BST& tree);
    void dispplaylist(const string& username);
    void dispfav(const string& username);
    void engine(const string& username,BST& tree);};

