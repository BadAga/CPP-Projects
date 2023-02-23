#ifndef LINKEDLIST _H
#define LINKEDLIST _H

#include "Node.h";
#include <iostream>

using namespace std;

template <class T>
class LinkedList
{
private:
    Node<T>* head;
    Node<T>* tail;
    bool is_empty; //informacja czy lista jest pusta
public:
    LinkedList();
    LinkedList(const LinkedList& other);
    ~LinkedList();
    void push_back(T value);
    void display_list()const;
    void push_front(T value);
    void pop_back();
    void pop_front();
    int size() const;
    void insert_after(T value, int pos); //pos to pozycja po ktorej ma sie znalezc nowy wezel
    void delete_at(int pos); //pos to doklada pozycja ktora usuwamy
    bool search(T key);    //zwraca informacje czy w liscie znajduje sie wezel z "data" takim samym co klucz
    void clear();  //usuwa wszystie elementy listy
    Node<T>& operator [](int pos);
    void copy(const LinkedList<T>& to_copy); 
    
};

template<class T>
LinkedList<T>::LinkedList() : head(nullptr), tail(nullptr), is_empty(true) {}

template<class T>
inline LinkedList<T>::LinkedList(const LinkedList& other)
{

    if (other.is_empty)  //jesli lista ktora chcemy skopiowac jest pusta to tworzymy zwykla pusta lista
    {
        is_empty = other.is_empty;
        head = nullptr;
        tail = nullptr;
    }
    else //jeœli nie to iterujemy po calej liscie other i dodajemy kolejne wezly z tymi samymi informacjami co w liscie other
    {
        is_empty = 1; //na poczatku lista jest pusta; po wykonaniu sie pierwszego push_back is_empty bedzie false
        Node<T>* temp = other.head;
        for (int i = 0; i < other.size(); i++) 
        {
            T info;
            info = temp->data;
            this->push_back(info);
            temp = temp->next;
        }
    }
    cout << "Konstruktor kopiujacy LL" << endl;
}

template<class T>
LinkedList<T>::~LinkedList()
{
    Node<T>* tmp = nullptr;
    while (head)
    {
        tmp = head;
        head = head->next;
        delete tmp;
    }
    head = nullptr;
    cout << "destruktor LL" << endl;
}

template<class T>
inline void LinkedList<T>::push_back(T value)
{
    Node<T>* node = new Node<T>;
    node->data = value; 
    if (is_empty == false) //jesli lista nie jest pusta 
    {
        tail->next = node;
        node->prev = tail;
        tail = node;
    }
    else //jesli lista do ktorej wstawiamy jest juz pusta to wstawiany wezel jest g³owa listy i ogonem listy
    {
        head = tail = node;
    }
    is_empty = false;
}

template<class T>
void LinkedList<T>::display_list()const
{
    Node<T>* node = head;
    if (is_empty)
    {
        cout << "Lista jest pusta" << endl;
    }
    else
    {
        while (node != nullptr)
        {
            cout << *node << "  ";
            node = node->next;
        }
    }
    cout << endl;
}

template<class T>
void LinkedList<T>::push_front(T value)
{
    Node<T>* node = new Node<T>;
    node->data = value;
    if (is_empty) //jesli lista do ktorej wstawiamy jest juz pusta to wstawiany wezel jest g³owa listy i ogonem listy
    {
        head = tail = node;
        is_empty = false;
    }
    else 
    {
        node->next = head;
        head->prev = node;
        head = node;
    }

}

template<class T>
inline void LinkedList<T>::pop_back()
{

    if (!is_empty) //jesli lista nie jest pusta
    {
        Node<T>* del_node = tail;
        tail = tail->prev; //od tego momentu tail jest przedostatnim elementem wsgledem wczesniejszego ulozenia
        if (tail == nullptr) //jezeli aktualny tail jest nullptr to lista by³ jadnoelementowa to musimy glowe wskazac na nullptr (tail juz wskazuje na nullptr)
        {
            head = nullptr;
        }
        else
        {
            tail->next = nullptr; //jesli lista nie byla jednoelementowa to next nowego tail trzeba wskazac w bezpieczne miejsce
        }
        if (del_node)
        {
            delete del_node; //usuwamy wezel do usuniecia i jego wskaznik ustawiamy na nullptr
            del_node = nullptr;
        }
        if ((head == nullptr) && (tail == nullptr))
        {
            is_empty = true; // na koniec trzeba zadbac by informacja o is_empty jest poprawna
        }
    }
    else
    {
        cout << "Lista jest pusta. Pop back nie wykonal sie" << endl;
    }

}

template<class T>
inline void LinkedList<T>::pop_front()
{
    if (!is_empty)
    {
        Node<T>* del_node = head;
        head = head->next;
        if (head == nullptr) // jest to jednoelementowa lista
        {
            tail == nullptr; //trzeba tail ustawic na nullptr
            is_empty = true;
        }
        else
        {
            head->prev = nullptr; 
        }
        if (del_node)
        {
            delete del_node;  //usuwamy wezel do usuniecia i jego wskaznik ustawiamy na nullptr
            del_node = nullptr;
        }
        if ((head == nullptr) && (tail == nullptr))
        {
            is_empty = true; // na koniec trzeba zadbac by informacja o is_empty jest poprawna
        }
    }
    else
    {
        cout << "Lista jest pusta. Pop front nie wykonal sie" << endl;
    }
}

template<class T>
inline int LinkedList<T>::size()const
{
    int counter = 0;
    Node<T>* node = head;
    if (is_empty)
    {
        return 0;
    }
    else
    {
        while (node != nullptr)
        {
            counter++;
            node = node->next;
        }
    }
    return counter;
}

template<class T>
void LinkedList<T>::insert_after(T value, int pos)
{
    if (is_empty && (pos == 0)) //wstawianie na pierwsza pozycje pustej listy
    {
        Node<T>* node = new Node<T>;
        node->data = value;
        head = tail = node;
        is_empty = false;
    }
    else
    {
        if ((this->size() <= pos) || (pos < 0)) //gdy podana pozycja jest poza zakresem mozliwych pozycji
        {
            cout << "ta pozycja nie jest osiagalna; maksymalna pozycja to: " << this->size() - 1 << endl;
        }
        else
        {
            Node<T>* temp_node = head;
            int counter = 0;
            while (counter != pos) //iterujemy do momentu znalezienia odowiedniego wezla
            {
                temp_node = temp_node->next;
                counter++;
            }
            if (temp_node->next == nullptr)//jesli wskaznik next znalezionego wezla to nullptr; to oznacza ze tempnode==tail
            {
                Node<T>* node = new Node<T>;
                node->data = value;
                tail->next = node;
                node->prev = tail;
                tail = node;


            }
            else //w innym przypadku trzeba wstawic pomiedzy dwa istniejace juz wezly
            {
                Node<T>* to_insert = new Node<T>;
                to_insert->data = value;
                to_insert->prev = temp_node; 
                temp_node->next->prev = to_insert;
                to_insert->next = temp_node->next;
                temp_node->next = to_insert;
            }
        }
    }
}

template<class T>
inline void LinkedList<T>::delete_at(int pos)
{
    if (is_empty)
    {
        cout << "KOM: Lista jest pusta. Delete at nie wykonal sie" << endl;
    }
    else
    {
        if ((pos < 0) || this->size() <= pos)
        {
            cout << "KOM: ta pozycja nie jest osiagalna; maksymalna pozycja to : " << this->size() - 1 << endl;
        }
        else //pozycja znajduje sie w prawidlowym zakresie
        {
            Node<T>* temp_node = head;
            int counter = 0;
            while (counter != pos)//iterujemy do momentu znaleznia odpowiedniego miejsca
            {
                temp_node = temp_node->next;
                counter++;
            }
            if (temp_node->next == nullptr) //usuwamy z koñca
            {
                this->pop_back();
            }
            else if (temp_node->prev == nullptr)//usuwamy z pocz¹tku
            {
                this->pop_front();
            }
            else
            {
                temp_node->next->prev = temp_node->prev;
                temp_node->prev->next = temp_node->next;
                temp_node->next = nullptr;
                temp_node->prev = nullptr;
                delete temp_node;
                temp_node = nullptr;

            }
        }
    }
}

template<class T>
bool LinkedList<T>::search(T key)
{

    if (is_empty)
    {
        cout << "KOM: Lista jest pusta. Find first nie wykona³o siê" << endl;
        return 0;
    }
    else
    {
        Node<T>* temp = head;
        bool found = 0;
        for (int i = 0; i < this->size(); i++) 
        {
            if (temp->data == key)
            {
                found == 1;
                cout << "KOM: klucz: " << key << " znaleziono w liscie" << endl;
                return 1;
            }
            else
            {
                temp = temp->next;
            }
        }
        if (!found)
        {
            cout << "KOM: nie znaleziono elementu" << endl;
            return 0;
        }
    }
}

template<class T>
inline void LinkedList<T>::clear()
{
    Node<T>* tmp = nullptr; 
    while (head) //dopoki head nie jest nullptr
    {
        tmp = head;
        head = head->next;
        delete tmp;
    }
    head = nullptr;
    tail = nullptr;
    is_empty = true;
    cout << "KOM: Lista zostala wyczyszczona" << endl;
}

template<class T>
inline Node<T>& LinkedList<T>::operator[](int pos)
{
    Node<T>* temp_node = head;
    int counter = 0;
    while (counter != pos)
    {
        temp_node = temp_node->next;
        counter++;
    }
    return *temp_node;
}

template<class T>
inline void LinkedList<T>::copy(const LinkedList<T>& to_copy)
{
    if (to_copy.is_empty == 1)
    {
        this->clear();
        is_empty = 1;
    }
    else
    {

        if (is_empty == 0)
        {
            this->clear();
        }

        Node<T>* temp = to_copy.head;
        for (int i = 0; i < to_copy.size(); i++)
        {
            T info;
            info = temp->data;
            this->push_back(info);
            temp = temp->next;
        }
        is_empty = 0;
    }

}


#endif // !LINKEDLIST _H


