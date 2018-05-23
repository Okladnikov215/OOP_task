#pragma once
#include <cassert>

template <class T> class ContainerIter;


template <typename T> struct Elem
{
	Elem(T data) : data(data), next(nullptr){}
	T data;
	Elem *next;
};


template <class T>
class Container 
{
private:
	unsigned int size;
	Elem<T> *head;
	Elem<T> *tail;

	//for the iterator implementation purposes
	Elem<T> *pastTheTail=new Elem<T>(0); 
	friend class ContainerIter<T>;
	typedef ContainerIter<T> iterator;
	typedef ContainerIter<const T> Citerator;

public:
	iterator begin()
	{ 
		return iterator(*this->head); 
	}

	iterator begin() const
	{
		return iterator(*this->head);
	}

	iterator end() 
	{ 
		return iterator(*this->pastTheTail);
	}

	iterator end() const
	{
		return iterator(*this->pastTheTail);
	}

	Container()
		: size(0)
		, head(nullptr)
		, tail(nullptr)
	{}

	Container(T data)
	{
		Elem<T> *temp = new Elem<T>(data);
		temp->next = pastTheTail;
		head = temp;
		tail = temp;
	}

	void pushFront(T data)
	{
		Elem<T> *e = new Elem<T>(data);
		e->next = head;
		head = e;
		return;
	}


	void pushBack(T)
	{

	}

	void delFront()
	{

	}

	void delBack()
	{

	}

	T getFirst() const
	{
		if (isEmpty())
		{
			throw EmptyContainerException();
		}
		return first->value;
	}

	T getLast() const
	{
		if (isEmpty())
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

	void empty()
	{
		while (!isEmpty())
		{
			removeFirst();
		}
	}

};

template < class T >
class ContainerIter
{
private:
	Elem<T> & ContainerElement;
public:
	ContainerIter(Container<T> &ñ)
		: ContainerElement(ñ.begin())
	{}

	ContainerIter(Elem<T> &e)
		: ContainerElement(e)
	{}

	bool operator!= (ContainerIter<T>& o)
	{
		if (&(o.ContainerElement)!=nullptr)
		{
			if (ContainerElement.data != o.ContainerElement.data)
				return true;
			else
				if (ContainerElement.next != o.ContainerElement.next)
					return true;
			return false;
		}
		else
		{
		}
	}

	T & operator*() { return ContainerElement; }

	template<typename T>
	ContainerIter<T> & operator++() 
	{ 
			if (ContainerElement.next)
				ContainerElement = *(ContainerElement.next);
			return *this;

	}



};