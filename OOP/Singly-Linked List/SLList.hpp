/*
 * Name: Mubasshir Karim
 * File: SLList.hpp
 * WSU ID: G498M939
 * Assignment: 7
 * Description: Single linked-list.
 */

 #ifndef SLLIST_HPP
 #define SLLIST_HPP

 template <class T> // It's a template class
 class SLList
 {
 public:
    SLList();       // Default Constructor
    SLList(T data); // Constructor that takes first item for list
                    // It shall not be possible to create copies or assign directly to the linked list
    ~SLList();      // Destructor
    class iterator;
    iterator begin(){return iterator(head);};   // begin()
    iterator end(){return iterator(nullptr);};  // end()

    bool empty();                       // A function called empty that lets you know if the list is empty or not
    int size() {return count;};         // A function called size that tells you how big the list is
    T front() {return *begin();};       // A function called front that returns the key value of the front node (return by value only)
    void push_back(T data);             // A function called push_back that adds a key to the end of the list
    iterator erase(iterator);           // A function called erase that takes as a parameter an iterator that indicates the Node to be erased.
			                            // It returns an iterator that indicates the position after the node that was erased
			                            // See the list class function of the same name at cplusplus.com
    void clear();                       // A function called clear that erases the list, but leaves the list object in a viable state
private:
    class Node  // Declare your Node class privately here
    {
    public:
        Node(T dat, Node* link)
        :   data(dat)
        ,   next(link)
        {};
        Node* getNext() const {return next;};
        const T& getData() const {return data;};
        void setData(const T& dat) {data = dat;};
        void setNext(Node* pointer) {next = pointer;};
    private:
        T data;
        Node* next;
    };
    // A pointer to the first node in the list
    Node* head;
    Node* tail;
    int count;
};

// Probably a good spot for the iterator class declaration
// It is contained within a template class
template<class T>
class SLList<T>::iterator
{
public:
    friend class SLList<T>;     // Constructor that takes a Node pointer
    iterator()
    : m(nullptr)
    {};
    iterator(Node* initial)
    :   m(initial)
    {};
    iterator operator ++()      // Overloaded postfix and prefix increment operators
    {
        m = m -> getNext();
        return *this;
    }
    iterator operator ++(int)   // Overloaded de-reference operator, returns by value only
    {
        iterator start(m);
        m = m -> getNext();
        return start;
    }
    bool operator == (const iterator& right) const      // Overloaded equality operator
    { return (m == right.m);}
    bool operator != (const iterator& right) const      // Overloaded inequality operator
    { return (m != right.m);}
    friend bool operator == (const Node* left, iterator right)
    {return (left == right.m);};
    const T& operator *() const {return m -> getData();};
private:
    Node* m;        // Node pointer (resource being managed by the iterator)
};

// Implementations of classes go here

template <class T>
SLList <T> :: SLList()
    :head(nullptr)
    ,tail(nullptr)
    , count(0)
    {};

template <class T>
SLList <T> :: SLList(T data)
{
    head = tail = new Node(data, nullptr);
    tail = tail -> getNext();
    count = 1;
};

template <class T>
SLList <T> :: ~SLList()
{
    clear();
}

template <class T>
bool SLList <T> :: empty()
{
    if (head == nullptr)
    {
        return true;
    }
    else
    {
        return false;
    }
};

template <class T>
void SLList <T> :: push_back(T data)
{
    if (empty())
    {
        head = tail = new Node(data, nullptr);
    }
    else
    {
        tail -> setNext(new Node(data, nullptr));
        tail = tail -> getNext();
    }
    count++;
}

template <class T>
typename SLList <T> :: iterator SLList <T> :: erase(iterator it)
{
    Node* prev = nullptr;
    Node* curr = head;

    while (curr != nullptr && (curr != it.m))
    {
        prev = curr;
        curr = curr -> getNext();
    }
    if (curr == it.m && curr != nullptr)
    {
        if (curr -> getNext() == nullptr)
            tail = prev;

        if (prev == nullptr)
        {
            head = curr -> getNext();
        }
        else
        {
            prev -> setNext(curr -> getNext());
        }
        delete curr;
        --count;
        if (prev == nullptr)
        {
            return head;
        }
        else
        {
            return prev -> getNext();
        }
    }
    else
    {
        return nullptr;
    }
}

template <class T>
void SLList <T> :: clear()
{
    for (auto it = begin(); it != end();)
    {
        it = erase(it);
    }
}

#endif
