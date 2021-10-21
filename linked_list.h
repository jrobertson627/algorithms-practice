//----------------------------------------------------------------------
// FILE: linked_list.h
// NAME: Jessica Robertson
// DATE CREATED: September 7, 2020
// DATE MODIFIED: October 21, 2021
// DESC: Implements a linked list version of the list class. Elements
//       are added by default to the end of the list via a tail pointer.
//----------------------------------------------------------------------


#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include "list.h"

template<typename T>
class LinkedList : public List<T>
{
public:
  LinkedList();
  LinkedList(const LinkedList<T>& rhs);
  ~LinkedList();
  LinkedList& operator=(const LinkedList<T>& rhs);

  void add(const T& item);
  bool add(size_t index, const T& item);
  bool get(size_t index, T& return_item) const;
  bool set(size_t index, const T& new_item);
  bool remove(size_t index);
  size_t size() const;

private:
  struct Node {
    T value;
    Node* next;
  };
  Node* head;
  Node* tail;
  size_t length;

  // helper to delete linked list
  void make_empty();
};

//This is the default constructor
template<typename T>
LinkedList<T>::LinkedList()
  : head(nullptr), tail(nullptr), length(0) {
}

//This is the copy constructor
template<typename T>
LinkedList<T>::LinkedList(const LinkedList<T>& rhs)
  : head(nullptr), tail(nullptr), length(0) {
  // defer to assignment operator
  *this = rhs;
}

//This is the deconstructor
template<typename T>
LinkedList<T>::~LinkedList() {
	make_empty();
}

//This is the copy assignment operator
template<typename T>
LinkedList<T>& LinkedList<T>::operator=(const LinkedList<T>& rhs) {
	Node * currNode = nullptr;
	Node * prevNode = nullptr;

	if (this != &rhs){
	  make_empty();
	}

	length = rhs.length;

	if (rhs.head == nullptr) {
	  	head = nullptr;
	  }
	  
	else {
		  	head = nullptr;
		  	currNode = rhs.head;
		  	prevNode = nullptr;
	  	  
		while (currNode != nullptr) {
			Node * newNode = new Node;
			newNode->value = currNode->value;
			if (head == nullptr) {
				head = newNode; 
				prevNode = newNode;
			}
			prevNode->next = newNode;
			prevNode = newNode;

			if (currNode->next == nullptr) {
				newNode->next = nullptr;
			}

			currNode = currNode->next;

			}
		tail = prevNode;
	}	
   return *this;
}

//This function adds an item to the end of the list by making the tail point to the new Node and 
//making the new node the tail
template<typename T>
void LinkedList<T>::add(const T& item) { 
	Node * newNode = new Node;
	newNode->next = nullptr;
	newNode->value = item;

	if (head == nullptr) {
		head = newNode;
		tail = newNode;
	}
	else {
		tail->next = newNode;
		tail = newNode;
	}
	length++;
}

//This function adds an item into the middle or front of the list
template<typename T>
bool LinkedList<T>::add(size_t index, const T& item) { 
	if (index < 0 || index > length) {
		return false;
	}

	else {
		Node * newNode = new Node;
		newNode->value = item;
		newNode->next = nullptr;

		if (index == 0) {
			if (!head) {
				head = newNode;
			}
			else {
				newNode->next = head;
				head = newNode;
			}
			tail = newNode;
			length++;
			return true;
		}
		else {
			size_t i = 0;
			Node* currNode = head;
			Node* prevNode = nullptr;
			while (currNode) {
				if (index == i) {
					prevNode->next = newNode;
					newNode->next = currNode;
					length++;
					return true;
				}
				prevNode = currNode;
				currNode = currNode->next;
				i++;
			}
		}

		tail->next = newNode;
		tail = newNode;
		length++;
	}
	return true;
}

//This function gets the item that the user has indexed
template<typename T>
bool LinkedList<T>::get(size_t index, T& return_item) const { 
	Node * currNode = head;
	size_t i = 0;
	if (head == nullptr) {
		return false;
	}
	else if (index == 0) {
		return_item = head->value;
		return true;
	}
	else {
		while (i != index) {
			if (currNode->next == nullptr) {
				return false;
			}
			currNode = currNode->next;
			i++;
		}
		return_item = currNode->value;
		return true;
	}
	return false;
}

//This function sets the index with a new value
template<typename T>
bool LinkedList<T>::set(size_t index, const T& new_item) { 
	Node * currNode = head;
	size_t i = 0;
	if (head == nullptr) {
		return false;
	}
	else {
		while (i != index) {
			if (currNode->next == nullptr) {
				return false;
			}
			currNode = currNode->next;
			i++;
		}
		currNode->value = new_item;
		return true;
	}
	return false;
}

//This function removes an index from the list and redoes the links
template<typename T>
bool LinkedList<T>::remove(size_t index) { 
	Node * currNode = head;
	Node * tempNode = nullptr;
	
	if (head == nullptr) {
		return false;
	}	
	
	else if (index == 0) {
		if (head->next == nullptr) {
			delete currNode;
			head = nullptr;
			tail = nullptr;
			length = 0;
			return true;
		}
		else {
			tempNode = currNode->next;
			delete currNode;
			head = tempNode;
			length--;
			return true;
		}
		
	}
	
	else {
		size_t i = 0;
		while (currNode != nullptr) {
			if (i == index) {
				tempNode->next = currNode->next;
				delete currNode;
				length--;
				if (tempNode->next == nullptr) {
					tail = tempNode;
				}
				return true;
			}
			else {
				tempNode = currNode;
				currNode = currNode->next;
				i++;
			}
		}
	}
	return false;
}

//This function returns the size of the linked list
template<typename T>
size_t LinkedList<T>::size() const { 
	return length;
}

//This function deletes the list
template<typename T>
void LinkedList<T>::make_empty() { 
	Node * currNode = head;
	Node * nextNode = nullptr;
	
	while (currNode != nullptr) {
		nextNode = currNode->next;
		delete currNode;
		currNode = nextNode;
	}
	head = nullptr;
	tail = nullptr;
	length = 0;
}


#endif