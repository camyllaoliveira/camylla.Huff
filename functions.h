#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <QFile>
#include <QDebug>
#include "tree.h"

void countBytes(QString fileName, int bytes[])
{

    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly))
    {
        qDebug() << "countBytes: The file cannot be read";
        return;
    }

    while(!file.atEnd())
    {
        QByteArray line = file.readLine(1024);
        for (int i = 0; i < line.size(); ++i){
            ++bytes[(unsigned char) line.at(i)];
        }
    }

    file.close();
}

void compress(QString fileName, QString newFileName, Tree* tree)
{
    QFile file(newFileName);
    file.open(QIODevice::WriteOnly);

    // Name's size --------------------------------------
    char ch = 0;
    char aux = 0;
    int des = 0;
    QByteArray tmp;
    tmp.append(fileName.size());

    for(int i = 0; i < tmp.size(); i++)
    {
        aux = tmp.at(i);
        ch |= (aux << (7 - des));
        des++;
        if (des == 8)
        {
            des = 0;
            tmp.append(ch);
            ch = 0;
        }
    }

    // Writes to new file ----------------------------------
    QByteArray toFile;

    // Trash and Tree's size -------------------------------
    toFile.append(tree->trashAndTreeSize());
    toFile.append(tmp);
    toFile.append(fileName);
    toFile.append(tree->getRepresentation());

    file.write(toFile);
    file.write(tree->getCodification());
    file.close();

}

void decompress(QString fileName)
{
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly))
    {
        qDebug() << "decompress: The file cannot be decompress.";
    }

    Tree* tree = new Tree();

    // Trash and tree's size --------------------------------------
    QByteArray b;
    b = file.read(1);
    // trash ------------------------------------------------------
    tree->setTrash(b);

    // tree --------------------------------------------------------
    b.append(file.read(1));
    int sizetree = 0;
    char aux = b.at(0);
    char ch = 31;
    ch &= aux;
    sizetree += ch;
    aux = 0;
    aux = b.at(1);
    ch = 0;
    ch |= aux;
    sizetree += ch;

    // the name's file ---------------------------------------------
    b.append(file.read(1));
    int name = b.at(2);
    b.append(file.read(name));
    QString thename;
    for (int i = 3; i < 3 + name; i++)
    {
        thename.append(b.at(i));
    }

    // the representation -------------------------------------------
    b.clear();
    b.append(file.read(sizetree));
    for (int i = 0; i < b.size(); i++);

    tree->rebuilder(b);
    tree->show(tree->getRoot(),0);

}



#endif // FUNCTIONS_H
