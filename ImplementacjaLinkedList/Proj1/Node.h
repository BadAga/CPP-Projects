#ifndef NODE _H
#define NODE _H

#include <iostream>
using namespace std;

template <class T>
class LinkedList;

template <class T>
class Node
{

    friend class LinkedList<T>;
    T data;  //przechowywana informacja
    Node<T>* prev; //wskaznik na wezê³ poprzedni
    Node<T>* next; //wska¿nik na wezel nastepny
public:
    Node();
    
    friend ostream& operator << (ostream& out, const Node<T>& node)
    {
        if (node.data == NULL)
        {

            out << "pusty weze³";
            return out;
        }
        out << node.data;
        return out;
    }

};
template<> class Node <string> //szblon szczegó³owy
{
    friend class LinkedList<string>;
    string data;
    Node<string>* prev;
    Node<string>* next;
public:
    Node();
   
    friend ostream& operator << (ostream& out, const Node<string>& node)
    {
        if (node.data == """")
        {
            out << "pusty weze³";
            return out;
        }
        out << node.data;
        return out;
    }
    
};
template <typename T>
Node<T>::Node()
{
    data = NULL;
    prev = nullptr;
    next = nullptr;
}
Node<string>::Node()
{
    data.assign("");
    prev = nullptr;
    next = nullptr;
}
#endif // NODE_H
