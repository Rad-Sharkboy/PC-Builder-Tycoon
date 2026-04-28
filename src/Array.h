#ifndef ARRAY_H
#define ARRAY_H

#include <iostream>
using namespace std;

const int MAX_CAPACITY = 100;

template <typename T>
class Array {
    T data[MAX_CAPACITY];
    int count;

public:
    Array(){count=0;}

    /*
      Appends 'item' to the next available slot.
      Silently rejects the item if the array is already full
      and prints a warning in the console.
    */
    void add(T item) {
        if(count < 100) {
            data[count++] = item;
            cout << "[Array] Item Added Successfully!" << endl;
            return;
        }
    
        cout << "[Array] Array is Full. Item NOT Added!" << endl;
        return;
    }

    /*
      Returns the item stored at 'index'.
      Returns a default-constructed T and prints an error if the index is out of bounds.
    */
    T get(int index) {
        if(index < 0 || index >= count) {
            cout <<"[Array] Index <"<<index<<"> is Out of Bounds!"<<endl;
            return T();
        }

        return data[index];
    }
    //Helper Function (extra)
    int size() {return count;}
};
#endif