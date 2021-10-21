//----------------------------------------------------------------------
// FILE: array_list.h
// NAME: Jessica Robertson
// DATE CREATED: September 7, 2020
// DATE LAST MODIFIED: October 21, 2021
// DESC: Implements a resizable array version of the list
//       class. Elements are added by default to the last available
//       index in the array. 
//----------------------------------------------------------------------

#ifndef ARRAY_LIST_H
#define ARRAY_LIST_H

#include "list.h"

template<typename T>
class ArrayList : public List<T>
{
public:
  ArrayList();
  ArrayList(const ArrayList<T>& rhs);
  ~ArrayList();
  ArrayList& operator=(const ArrayList<T>& rhs);

  void add(const T& item);
  bool add(size_t index, const T& item);
  bool get(size_t index, T& return_item) const;
  bool set(size_t index, const T& new_item);
  bool remove(size_t index);
  size_t size() const;

private:
  T* items;
  size_t capacity;
  size_t length;

  // helper to resize items array
  void resize();
};

//This is the default constructor
template<typename T>
ArrayList<T>::ArrayList()
  : capacity(10), length(0)
{
  items = new T[capacity];
}

template<typename T>
ArrayList<T>::ArrayList(const ArrayList<T>& rhs)
  : capacity(10), length(0), items(nullptr)
{
  // defer to assignment operator
  *this = rhs;
}
  
//This is the deconstructor
template<typename T>
ArrayList<T>::~ArrayList() {
  delete [] items;
  items = nullptr;
  length = 0;
}

//this is the copy assignment operator
template<typename T>
ArrayList<T>& ArrayList<T>::operator=(const ArrayList<T>& rhs) {
 // check if left list is empty
    if(this == &rhs) {
        return *this;
    }
    delete [] items;
// copy the size and the capacity of the new list
    items = new T[rhs.capacity];
    while(length > 0) {
        remove(0);
    }
    T holder;
// traverse the list and copy each value	
    for(size_t i = 0; i < rhs.size(); i++){
        rhs.get(i, holder);
        add(holder);
    }
	return *this;
}

//this function adds an item to the end of the array, resizing if necessary
template<typename T>
void ArrayList<T>::add(const T& item) { 
	if (capacity <= length) {
		resize();
	}
	
	items[length] = item;
	length++;
}

//This function adds an item by index and moves the items over one
template<typename T>
bool ArrayList<T>::add(size_t index, const T& item) {
// check if list reached its capacity
    if(capacity <= (length+1)) {
        resize();
    }
// check if index is in range of the list
    if((index < 0) || (index > length) || (index > capacity)) {
        return false;
    }
    else {
// shift the list upwards
        for(size_t i = (length + 1); i > index; --i) {
             items[i] = items[i-1];
        }	
// update the index with the new value
       items[index] = item; 
       length++;
       return true;
    }	
}

//This function gets the item that the user is searching for using the index
template<typename T>
bool ArrayList<T>::get(size_t index, T& return_item) const {
// check if index is in range of the list
    if((index < 0) || (index >= length) || (index > capacity)) {
        return false;
    }
    else {
    // return the value of the index by reference
        return_item = items[index]; 
        return true;
    }
}

//This function sets a new value to an indexed point
template<typename T>
bool ArrayList<T>::set(size_t index, const T& new_item){
    // check if index is in range of the list
    if((index < 0) || (index >= length)) {
         return false;
    }
    // update the index with the new value
    else {
        items[index] = new_item;
        return true;
    }
}

//This function removes the index from the array
template<typename T>
bool ArrayList<T>::remove(size_t index) {
    // check if index is in range of the list
    if((index < 0) || (index >= length)) {
        return false; 
    }
    else {
        // shift the list down one to remove the value
        for(size_t i = index; i < length; i++) {
           items[i] = items[i+1];
        }
        //update the size of the list	
        length--;
         return true;
    }
}

//This function returns the size of the array
template<typename T>
size_t ArrayList<T>::size() const {
	return length;
}

//This function will resize the array if it's not large enough for what's needed
template<typename T> 
void ArrayList<T>::resize() {
    // double the size of the list
    T * temp = new T[(capacity*2)];
    // call copy and assignm function to copy value to new list
    capacity = capacity * 2;
    size_t i = 0;	
    while(i < length) {
        temp[i] = items[i];
        i++;
    }
    items = temp;
}

#endif