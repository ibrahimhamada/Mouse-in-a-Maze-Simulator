#ifndef ARRAY_STACK_
#define ARRAY_STACK_

#include "StackADT.h"

struct node {
	int x;
	int y;
	int dir = 0;
	int status = -1;
};

template<typename T>
class ArrayStack : public StackADT<node>
{
private:
	T* items;		// Array of stack items
	int      top;                   // Index to top of stack
	const int STACK_SIZE;

public:

	ArrayStack() :STACK_SIZE(30)	
	{
		items = new T[STACK_SIZE];
		top = -1;
	}

	ArrayStack(int MaxSize) : STACK_SIZE(MaxSize)
	{
		items = new T[STACK_SIZE];
		top = -1;
	}  

	bool isEmpty() const
	{
		return top == -1;
	}  

	bool push(const T& newEntry)
	{
		if (top == STACK_SIZE - 1) return false;	

		top++;
		items[top] = newEntry;
		return true;
	}  

	bool pop(T& TopEntry)
	{
		if (isEmpty()) return false;

		TopEntry = items[top];
		top--;
		return true;
	} 

	bool peek(T& TopEntry) const
	{
		if (isEmpty()) return false;

		TopEntry = items[top];
		return true;
	}  

	~ArrayStack()
	{
		delete[]items;
	}

	ArrayStack(const ArrayStack<T>& S) :STACK_SIZE(S.STACK_SIZE)
	{
		items = new T[STACK_SIZE];
		for (int i = 0; i <= S.top; i++)
			items[i] = S.items[i];
		top = S.top;
	}


}; 
#endif
