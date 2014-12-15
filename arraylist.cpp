#include "arraylist.h"

ArrayList::ArrayList(int size)
{
    maxSize = 256;
    sizeList = current = size;
    aList = new Node* [maxSize];
}

ArrayList::~ArrayList()
{
    delete []aList;
}

void ArrayList::clear()
{
    delete []aList;
    sizeList = current = 0;
    aList = new Node* [maxSize];

}

void ArrayList::append(Node *it)
{
    Q_ASSERT_X(sizeList < maxSize,"ArrayList::append","List capacity exceeded");
    for(int i = sizeList; i > current; i--)
        aList[i] = aList[i-1];

    aList[current] = it;
    sizeList++;
}

void ArrayList::insert(Node *it)
{
    Q_ASSERT_X(sizeList < maxSize,"ArrayList::insert","List capacity exceeded");
    aList[sizeList++] = it;
}

Node *ArrayList::remove()
{
    Q_ASSERT_X((current >= 0) && (current < sizeList),"ArrayList::remove","No element");
    Node* it = aList[current];
    for(int i = current; i < sizeList-1; i++)
        aList[i] = aList[i+1];
    sizeList--;
    return it;
}

void ArrayList::moveToStart()
{
    current = 0;
}

void ArrayList::moveToEnd()
{
    current = sizeList;
}

void ArrayList::prev()
{
    if (current != 0)
        current--;
}

void ArrayList::next()
{
    if (current < sizeList)
        current++;
}

int ArrayList::lenght() const
{
    return sizeList;
}

int ArrayList::currPos() const
{
    return current;
}

void ArrayList::moveToPos(int pos)
{
    Q_ASSERT_X((pos >= 0) && (pos <= sizeList),"ArrayList::moveToPos","Pos out of range");
    current = pos;
}

Node *ArrayList::getContent()
{
    Q_ASSERT_X((current >= 0) && (current < sizeList),"ArrayList::getContent","No current element");
    return aList[current];
}

Node **ArrayList::getAList()
{
    return aList;
}

void ArrayList::order()
{
    int i, j;
    for (i = sizeList - 1; i > 0; i--){
        for (j = 0; j < i; j++){
            // I critério: Frequência -----------
            if(aList[j]->getFrequence() > aList[j+1]->getFrequence()){
                swap(aList[j],aList[j+1]);
            } else if (aList[j]->getFrequence() == aList[j+1]->getFrequence()){
                // II critério: o nó a esquerda tem filhos ------------
                if(aList[j]->isLeaf() &&
                        aList[j+1]->isLeaf() == false){
                    swap(aList[j],aList[j+1]);
                } else if (aList[j]->isLeaf() && aList[j+1]->isLeaf()){
                    // III criterio: o conteudo do nó -------------
                    if(aList[j]->getContent() > aList[j+1]->getContent()){
                        swap(aList[j],aList[j+1]);
                    }                }
            }
        }
    }
}

void ArrayList::show()
{
    for(int i = 0;i < sizeList; i++)
    {
        qDebug() << aList[i]->getContent() << "|" << aList[i]->getFrequence();
    }

}
