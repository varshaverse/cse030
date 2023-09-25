#ifndef SORTED_LIST_H
#define SORTED_LIST_H

#include "ArrayList.h"

template <typename T>
class SortedList : public ArrayList<T> {
public:
    void append(T value) {

        if(this->count >= this->capacity){
            this->inflate(); //making more space so it appends to the array
        }

        int i = this->count;

        while (i > 0 && value < this->arr[i - 1]) {// shifting to the right
            this->arr[i] = this->arr[i-1];
            i--;
        }
        this->arr[i] = value; // count goes up
        this->count++;
    }


    bool search(T value) const {
        int left = 0;
        int right = this->count - 1;

        while (left <= right){
            int mid = (left + right) / 2;

            if (this->arr[mid] == value){
                return true;
            }
            else{
                if (this->arr[mid] > value){
                    right = mid - 1;
                }
                else {
                    // numbers[mid] < value
                    left = mid + 1;
                }
            }
        }
        return false;
    }

    // This needs to be here because of the unit tests
    friend struct TestSortedList;

};

#endif
