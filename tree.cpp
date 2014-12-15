#include "tree.h"

Tree::Tree()
{
    root = new Node();
    list = new QList<Node*>();

}

Node *Tree::getRoot()
{
    return root;
}

QByteArray Tree::getCodification()
{
    return codeArray;
}

void Tree::buildTree(int bytes[])
{

    for(int i = 0; i < 256; i++){
        if(bytes[i]){
            Node* tmp = new Node(bytes[i],i);
            list->append(tmp);
        }
    }

    bubbleSort();

    while(list->size() > 1){
        Node* tmp = new Node();
        tmp->setFrequency(list->at(0)->getFrequency()+list->at(1)->getFrequency());
        tmp->setLeft(list->at(0));
        tmp->setRight(list->at(1));
        list->pop_front();
        list->pop_front();
        list->insert(position(tmp),tmp);
    }
    root = list->at(0);
}

void Tree::bubbleSort()
{

    for (int i = 0; i < list->size(); i++){
        for (int j = i+1; j < list->size(); ++j){
            if (list->at(i)->getFrequency() > list->at(j)->getFrequency()){
                list->swap(i,j);

            } else if ( list->at(i)->getFrequency() == list->at(j)->getFrequency()){

                if(list->at(i)->getContent() > list->at(j)->getContent()){
                    list->swap(i,j);
                }
            }

        }
    }
}

void Tree::buildRepresentation(Node *base)
{
    if(base->isLeaf()){
        if(base->getContent() == '#'
                || base->getContent() == '{'){
            representation += '{';
        }
        representation += (char) base->getContent();
    } else {
        representation += '#';
        buildRepresentation(base->getLeft());
        buildRepresentation(base->getRight());
    }

}

QString Tree::getRepresentation() const
{
    return representation;
}

int Tree::position(Node *node) const
{
    int i;
    for(i = 0; i < list->size(); ++i){
        if(node->getFrequency() < list->at(i)->getFrequency()){
            break;
        }
    }
    return i;
}

int Tree::getSizeTree()
{
    return representation.size();
}

void Tree::encodeHelper(Node *node, QByteArray tmp){
    if (node->isLeaf()){
        node->setCode(tmp);
        codes[(unsigned char) node->getContent()] = node->getCode();
        tmp.clear();
    } else {
        tmp.append((char) 0);
        encodeHelper(node->getLeft(),tmp);
        tmp.remove(tmp.size()-1,1);
        tmp.append(1);
        encodeHelper(node->getRight(),tmp);
    }
}

void Tree::codification(Node *node, QString fileName)
{
    // Encode the nodes -------------------------------
    QByteArray tmp;
    encodeHelper(node,tmp);

    // Codes to codeArray -----------------------------
    QFile file(fileName);
    if(!file.open(QIODevice::ReadOnly))
        qDebug() << "The file cannot be read.";

    while(!file.atEnd())
    {
        unsigned char c;
        QByteArray line = file.readLine(1024);
        for (int i = 0; i < line.size(); ++i)
        {
            c = line.at(i);
            codeArray.append(codes[c]);
        }
    }

    // Encode the file ---------------------------------
    QByteArray ret;
    int des = 0;
    unsigned char ch1 = 0, ch2 = 0;

    int trash = 8 - (codeArray.size() % 8);
    sizeTrash = trash;

    for (int i = 0, des = 0; i < codeArray.size(); ++i)
    {
        ch1 = (codeArray.at(i) << (7 - des));
        ch2 |= ch1;
        ++des;
        if (des == 8)
        {
            ret.append(ch2);
            ch2 = 0;
            des = 0;
        }
    }

    if (des < 7)
        ret.append(ch2);
    codeArray.clear();
    codeArray.append(ret);

}

QByteArray Tree::trashAndTreeSize()
{
    QByteArray ret;

    // Trash's size to 2 firts bits -------
    char ch = 0;
    for (int i = 7; i > 4; i--)
    {
        ch |= (sizeTrash << i);
    }
    qDebug() << (int) sizeTrash;

    if (representation.size() > 255)
    {
        QByteArray tmp;
        int des = 3;
        char aux;
        tmp.append(representation.size());
        for(int i = 0; i < tmp.size(); i++)
        {
            aux = tmp.at(i);
            ch |= (aux << (7 - des));
            des++;
            if (des == 8)
            {
                ret.append(ch);
                des = 0;
                ch = 0;
            }
        }
        if (des < 7)
            ret.append(ch);

    } else {
        ret.clear();
        ret.append((unsigned char)ch).append(representation.size());
        qDebug() << "Ret:" << ret.toHex();
    }

    return ret;
}

void Tree::rebuilder(QByteArray rep)
{

    for (int i = 0; i < rep.size(); i++)
    {
        fila.append(rep.at(i));
        qDebug() << "no byte" << rep.at(i);
    }

    for (int i = 0; i < fila.size(); i++)
    {
        qDebug() << fila.at(i);
    }

}


void Tree::setTrash(QByteArray byte)
{
    char ch = 224; // 1110 0000
    char aux = 0;

    // "And" 3 firts bits -------------------

    aux = byte.at(0);
    ch &= aux;
    aux = 7;
    ch = (ch >> 5);
    ch &= aux;

    sizeTrash = ch;

}

void Tree::setRoot(Node *node)
{
    root = node;
}

void Tree::show(Node *base, int height) {
    if(base == 0) {
        return;
    }
    show(base->getRight(), height+1);
    if(base->getContent() != 0)
        qDebug() << qPrintable(QString("  ").repeated(height)) << (char)base->getContent();
    else
        qDebug() << qPrintable(QString("  ").repeated(height)) << base->getFrequency();
    show(base->getLeft(), height+1);
}

void Tree::printCodes()
{
    for (int i = 0; i < 255; i++)
    {
        qDebug() << "-> " << codes[i];
    }
}

