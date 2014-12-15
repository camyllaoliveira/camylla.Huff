#ifndef ARRAYLIST_H
#define ARRAYLIST_H

#include "node.h"
#include <QDebug>
#include <algorithm>

using namespace std;

class ArrayList
{
    Node** aList;
    int maxSize;
    int sizeList;
    int current;

public:

    ArrayList();
    ~ArrayList();
    void clear();
    void append(Node* it);
    void insert(Node* it);
    Node* remove();
    void moveToStart();
    void moveToEnd();
    void prev();
    void next();
    int lenght() const;
    int currPos() const;
    void moveToPos(int pos);
    Node* getContent();
    Node** getAList();
    void order();
    void show();

};

#endif // ARRAYLIST_H
