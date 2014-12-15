#ifndef TREE_H
#define TREE_H

#include "node.h"
//#include <string>
#include <QList>
#include <QFile>
#include <QQueue>

using namespace std;

class Tree
{

    QQueue<unsigned char> fila;
    QList<Node*>* list;
    Node* root;
    QString representation;
    QByteArray codes[256];
    QByteArray codeArray;
    char sizeTrash;

public:
    // Builder --------------------------------------
    Tree();

    // Gets -----------------------------------------
    Node* getRoot();
    QByteArray getCodification();
    QString getRepresentation() const;
    int getSizeTree();

    // Builders the tree -----------------------------
    void buildTree(int bytes[]);

    // Builders representation -----------------------
    void buildRepresentation(Node* base);


    // Encode ----------------------------------------
    void codification(Node* node,QString fileName);

    // Two firts bytes trash and tree's size --------
    QByteArray trashAndTreeSize();

    // rebuilder ------------------------------------
    void rebuilder(QByteArray rep);

    // Sets -----------------------------------------
    void setTrash(QByteArray byte);
    void setRepresentation();
    void setRoot(Node* node);

    // DELETE THIS -----------------------------------
    void show(Node *base, int height);
    void printCodes();



private:

    // Utilitárias  ---------------
    void bubbleSort();
    int position(Node* node) const;
    void encodeHelper(Node *node, QByteArray tmp);

};

#endif // TREE_H
