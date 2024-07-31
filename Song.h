#ifndef SONG_H
#define SONG_H
#include <string>
#include <iostream>

using namespace std;

class song {
public:
    string name;
    string genre;
    string artist;
    song();
    song(const string& name,const string& genre,const string& artist);};

class nodes {
public:
    song data;
    nodes* left;
    nodes* right;
    nodes(const song& song) {
        data=song,left=NULL,right=NULL;}};

class BST {
private:
    nodes* root;
    void insert(nodes*& node,const song& song);
    void display(nodes* node);
    nodes* sbname(nodes* node,const string& name);
    void sbgenre(nodes* node,const string& genre);
    void sbartist(nodes* node,const string& artist);
    void engine(nodes* node,const string usgenre[],int gcount,const string usartist[],int acount);

public:
    BST() {
         root=NULL;}
    void insert(const song& song);
    void display();
    nodes* sbname(const string& name);
    void sbgenre(const string& genre);
    void sbartist(const string& artist);
    bool exxsist(const string& name);
    void engine(const string usgenre[],int gcount,const string usartist[],int acount);};
#endif // SONG_H
