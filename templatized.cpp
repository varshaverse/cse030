#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <ostream>
#include <stdexcept>

template <typename T>
struct Link {
    T data;
    Link* next;

    Link() : data(T()), next(nullptr) {}

    Link(const T& data) : data(data), next(nullptr) {}
};

template <typename T>
class LinkedList {
    Link<T>* front;
    Link<T>* back;
    int size;

public:
    LinkedList() : front(nullptr), back(nullptr), size(0) {}

    void append(const T& value) {
        if (front == nullptr) {
            // Appending to an empty list
            front = new Link<T>(value);
            back = front;
        } else {
            // Appending to list with elements
            Link<T>* temp = new Link<T>(value);
            back->next = temp;
            back = temp;
        }
        size++;
    }

    T& operator[](int index) {
        if (index < 0 || index >= size) {
            throw std::logic_error("Index out of bounds");
        }
        Link<T>* temp = front;
        for (int i = 0; i < index; i++) {
            temp = temp->next;
        }
        return temp->data;
    }

    void prepend(const T& value) {
        if (front == nullptr) {
            // Prepending to an empty list
            front = new Link<T>(value);
            back = front;
        } else {
            // Prepending to a list with elements
            Link<T>* temp = new Link<T>(value);
            temp->next = front;
            front = temp;
        }
        size++;
    }
T removeFirst() {
    if (front == nullptr) { // front has nothing
        throw std::logic_error("List is empty");
    }
    T removedValue = front->data; // points value to the front
    Link<T>* firstNode = front;
    front = front->next;
    size--;
    delete firstNode;

    if (front == nullptr) {
        // The list empty, update back 
        back = nullptr;
    }

    return removedValue;
}
T removeLast() {
    if (front == nullptr) {
        throw std::logic_error("List is empty");
    }
    
    T removedValue;
    if (front == back) {
        //one element in the list
        removedValue = front->data;
        delete front;
        front = back = nullptr;
    } else {
        //multiple elements in the list
        Link<T>* current = front;
        while (current->next != back) {
            current = current->next;
        }
        removedValue = back->data;
        delete back;
        back = current;
        back->next = nullptr;
    }

    size--;

    return removedValue;
}


    friend std::ostream& operator<<(std::ostream& os, const LinkedList<T>& list) {
        Link<T>* curr = list.front;
        while (curr != nullptr) {
            os << curr->data;
            if (curr->next != nullptr) os << ", ";
            curr = curr->next;
        }

        return os;
    }

    // The following 2 friend declarations must be present so the unit tests can run
    friend struct TestTemplates;
    friend struct TestRemoveMethods;

    ~LinkedList() {
        while (front != nullptr) {
            Link<T>* temp = front;
            front = front->next;
            delete temp;
        }
    }
};

#endif
