#include "Song.h"
#include <iostream>

using namespace std;

song::song() {}

song::song(const string& name,const string& genre,const string& artist):name(name),genre(genre),artist(artist) {}
void BST::insert(nodes*& node, const song& song) {
    if (!node){
        node=new nodes(song);
    } else if(song.name<node->data.name) {
        insert(node->left,song);
    } else {
        insert(node->right,song);}}

void BST::display(nodes* node) {
    if (node) {
        display(node->left);
        cout<<"Name: "<<node->data.name<<", Genre: "<<node->data.genre<<", Artist: "<<node->data.artist<<endl;
        display(node->right);}}

nodes* BST::sbname(nodes* node, const string& name) {
    if (!node)
     return NULL;
    if (name==node->data.name) 
    return node;
    else if (name<node->data.name) 
    return sbname(node->left, name);
    else return sbname(node->right,name);}

void BST::insert(const song& song) {
    insert(root, song);}

void BST::display() {
    display(root);}

nodes* BST::sbname(const string& name) {
    return sbname(root,name);}


void BST::sbgenre(nodes* node,const string& genre) {
    if (node) {
        sbgenre(node->left, genre);
        if (node->data.genre==genre) {
            cout<<"Name: "<<node->data.name<<", Genre: "<<node->data.genre<<", Artist: "<<node->data.artist<<endl;}
        sbgenre(node->right,genre);}}

void BST::sbartist(nodes* node,const string& artist) {
    if (node) {
        sbartist(node->left,artist);
        if (node->data.artist==artist) {
            cout<<"Name: "<<node->data.name<<", Genre: "<<node->data.genre<<", Artist: "<<node->data.artist<<endl;}
        sbartist(node->right,artist);}}

void BST::sbgenre(const string& genre) {
    sbgenre(root, genre);}

void BST::sbartist(const string& artist) {
    sbartist(root, artist);}

bool BST::exxsist(const string& name) {
    return sbname(name) != NULL;}

void BST::engine(nodes* node,const string usgenre[],int gcount,const string usartist[],int acount) {
    if (node) {
        engine(node->left,usgenre,gcount,usartist,acount);
        bool rc=false;
        for (int i=0;i<gcount;i++) {
            if (node->data.genre==usgenre[i]) {
                rc=true;
                break;}}
        for (int i=0;i<acount;i++) {
            if (node->data.artist==usartist[i]) {
                rc=true;
                break;}}
        if (rc) {
            cout<<"Name: "<<node->data.name<<", Genre: "<<node->data.genre<<", Artist: "<<node->data.artist<<endl;}
        engine(node->right,usgenre,gcount,usartist,acount);}}

void BST::engine(const string usgenre[],int gcount,const string usartist[],int acount) {
    engine(root,usgenre,gcount,usartist,acount);}