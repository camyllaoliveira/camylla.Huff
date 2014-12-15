#include "node.h"


Node::Node()
{
    this->content = 0;
    this->left = this->right = 0;
    this->frequency = 0;
    this-> code.clear();
}

Node::Node(int frequency, unsigned char content = 0)
{
    this->content = content;
    this->frequency = frequency;
    this->left = this->right = 0;
}


Node *Node::getLeft()
{
    return this->left;
}

Node *Node::getRight()
{
    return this->right;
}

int Node::getFrequency()
{
    return this->frequency;
}

unsigned char Node::getContent()
{
    return this->content;
}

bool Node::isLeaf()
{
    return !(this->right && this->left);
}

QPair<Node *, int> Node::fromBArray(QByteArray rep, int pos)
{
    unsigned char ch = (unsigned char) rep.at(pos);
    if (ch == '#'){
        if (ch == '{')
        {
            pos++;
            ch = (unsigned char) rep.at(pos);
        }
        return QPair<Node*,int>(new Node(0,ch),pos);
    }
    QPair<Node*,int> pLeft = fromBArray(rep,pos+1);
    QPair<Node*,int> pRight = fromBArray(rep,pLeft.second+1);
    Node* node = new Node('#');
    node->setLeft(pLeft.first);
    node->setRight(pRight.first);

    return QPair<Node*,int>(node,pRight.second);

 }
void Node::printCode()
{
    for (int i = 0; i < code.size(); i++)
    {
        std::cout << code.at(i);
    }

    std::cout << std::endl;
}


QByteArray Node::getCode()
{
    return code;
}

void Node::setLeft(Node *newLeft)
{
    left = newLeft;
}

void Node::setRight(Node *newRight)
{
    right = newRight;
}

void Node::setCode(QByteArray code)
{
    this->code.append(code);
}

void Node::setFrequency(int frequency)
{
    this->frequency = frequency;
}

void Node::setContent(unsigned char content)
{
    this->content = content;
}





