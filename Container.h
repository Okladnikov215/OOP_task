#pragma once

#include <assert.h>
#include <functional>

template <typename T> class Node
{
public:
    Node(T value)
            : value(value)
            , prev(nullptr)
            , next(nullptr)
    {}

    T value;
    Node<T> * prev;
    Node<T> * next;
};

class EmptyContainerException : public std::logic_error
{
public:
    EmptyContainerException()
    : std::logic_error("Empty Container Error")
    {}
};

template <typename T> class Container
{
public:
    Container()
        : size(0)
        , first(nullptr)
        , last(nullptr)
    {}

    Container(Container const & origin) : Container()
    {
        *this = origin;
    }

    Container & operator =(Container const & origin) {
        if (this == &origin)
        {
            return *this;
        }
        clean();
        origin.forEach(
                [this] (T const & elem) {addLast(elem);}
        );
        return *this;
    }

    ~Container()
    {
        clean();
    }

    void addFirst(T const & value)
    {
        Node<T> * newNode = new Node<T>(value);
        if(isEmpty())
        {
            assert(last == nullptr);
            last = newNode;
        }
        else
        {
            first->prev = newNode;
        }
        newNode->next = first;
        first = newNode;

        ++size;
    }

    void addLast(T const & value)
    {
        Node<T> * newNode = new Node<T>(value);

        if(isEmpty())
        {
            assert(first == nullptr);
            first = newNode;
        }
        else
        {
            last->next = newNode;
        }
        newNode->prev = last;
        last = newNode;

        ++size;
    }

    void removeFirst()
    {
        if(isEmpty())
        {
            throw EmptyContainerException();
        }

        Node<T> * toRemove;
        toRemove = first;
        first = toRemove->next;
        if(first != nullptr)
        {
            first->prev = nullptr;
        }
        else
        {
            last = nullptr;
        }
        delete toRemove;

        --size;
    }

    void removeLast()
    {
        if(isEmpty())
        {
            throw EmptyContainerException();
        }

        Node<T> * toRemove;
        toRemove = last;
        last = toRemove->prev;
        if(last != nullptr)
        {
            last->next = nullptr;
        }
        else
        {
            first = nullptr;
        }
        delete toRemove;

        --size;
    }

    T getFirst() const
    {
        if(isEmpty())
        {
            throw EmptyContainerException();
        }
        return first->value;
    }

    T getLast() const
    {
        if(isEmpty())
        {
            throw EmptyContainerException();
        }
        return last->value;
    }

    unsigned int getSize() const
    {
        return size;
    }

    bool isEmpty() const
    {
        return (this->getSize() == 0);
    }

    void clean()
    {
        while(!isEmpty())
        {
            removeFirst();
        }
    }

    void forEach(std::function<void(T &)> func)
    {
        Node<T> * elem = first;

        while(elem != nullptr)
        {
            func(elem->value);
            elem = elem->next;
        }
    }

    void forEach(std::function<void(T const &)> func) const
    {
        Node<T> * elem = first;

        while(elem != nullptr)
        {
            func(elem->value);
            elem = elem->next;
        }
    }

private:
    unsigned int size;
    Node<T> * first;
    Node<T> * last;
};