/**
 * @file Vector.h
 * @brief This file contains the declaration of the Vector class template.
 */

#pragma once
#include <vector>
#include <algorithm>
#include <random>

/**
 * @class Vector
 * @brief  Manages an encapsulated STL vector within the class of Vector.
 * 
 * @author Wong Liang Jun
 * @version 1.0.2
 * @date 31/03/2024
 *
 */
template <class T>
class Vector {
    private:
        std::vector<T> m_array; // pointer to the heap

    public:
        /**
         * @brief Default constructor.
         *
         * Initializes a vector 
         * with the default size of 10.
         */
        Vector();

        /**
         * @brief Overloaded constructor.
         *
         * Initializes a vector with a given initial size.
         *
         * @param n Initial size of the vector.
         */
        Vector(int n);

        /**
         * @brief Get the current size of the vector.
         *
         * @return The number of elements in the vector.
         */
        int Size() const;

        /**
         * @brief Add an element to the end of the vector.
         *
         * @param item The item to be added.
         * @return True if the item was added successfully, false otherwise.
         */
        void Add(const T& item); 

        /**
         * @brief Remove the last element from the vector.
         */
        void Remove();

        /**
         * @brief Delete an element at the specified index.
         *
         * @param index The index of the element to be deleted.
         */
        void Delete(int index);

        /**
         * @brief Get the element at the specified index.
         *
         * @param index The index of the element to retrieve.
         */
        const T& getat(int index);

        /**
         * @brief Sets the element at the specified index.
         * 
         * Shifts existing data forwards, does not override. 
         * 
         * @param index The index of the element to set.
         * @param input The new value for the element.
         */
        void Insert(int index, const T& input);

        /**
         * @brief Modify the element at the specified index.
         * 
         * Replaces the data at the index specified.
         *
         * @param index The index of the element to modify.
         * @param input The new value for the element.
         */
        void Modify(int index, const T& input); 

        /**
         * @brief Remove all elements from the vector.
         */
        void Clear();

        /**
         * @brief Overloaded assignment operator.
         *
         * Assigns the contents of another vector to this vector.
         *
         * @param input The vector to copy from.
         * @return A reference to this vector.
         */
        Vector<T>& operator = (const Vector<T>& input);

        /**
         * @brief Overloaded access operator.
         *
         * Provides access to the element at the specified index.
         * 
         * Does not increase or decrease the size of the Vector.
         *
         * @param index The index of the element to access.
         * @return A reference to the element at the specified index.
         */
        T& operator[] (const int &index);

        /**
         * @brief Overloaded const access operator.
         *
         * Provides constant access to the element at the specified index.
         * 
         * Does not increase or decrease the size of the Vector.
         *
         * @param index The index of the element to access in the vector.
         * @return A const reference to the element at the specified index.
         */
        const T& operator[] (const int &index) const;

        /**
         * @brief Shuffle function 
         *
         * Provides the vector class to change the position of the data in the vector. 
         */
        void Shuffle();

}; 

// implementation

template <class T>
Vector<T>::Vector() {
    m_array = std::vector<T>();
}

template <class T>
Vector<T>::Vector(int n) {
    m_array = std::vector<T>(n);
}

template <class T>
int Vector<T>::Size() const {
    return m_array.size();
}

template <class T>
void Vector<T>::Add(const T& item) { // How push_back would work.
    m_array.push_back(item);
}

// template <class T>
// void Vector<T>::ReAlloc(int newCapacity) {
//     T* newBlock = new T[newCapacity];

//     if (newCapacity < m_size) {
//         m_size = newCapacity;
//     }

//     for (int i = 0; i< m_size; i++) {
//         newBlock[i] = m_array[i];
//     }
//     delete[] m_array;
//     m_array = newBlock;
//     m_capacity = newCapacity;
// }

template <class T>
const T& Vector<T>::getat(int index) {
    if (index >= 0 && index < Size()) {
        return m_array[index];
    } else {
        throw std::out_of_range("Index out of range");
    }
}

template <class T>
void Vector<T>::Insert(int index, const T& input) {
    if (index >= 0 && index <= Size()) {
        m_array.insert(m_array.begin() + index, input);
    } else {
        throw std::out_of_range("Index out of range");
    }
}

template <class T>
void Vector<T>::Remove() { // similar to popback
    if (!m_array.empty()) {
        m_array.pop_back();
    }
}

template <class T>
void Vector<T>::Modify(int index, const T& input) {
    if (index >= 0 && index < Size()) {
        m_array[index] = input;
    } else {
        throw std::out_of_range("Index out of range");
    }
}

template <class T>
void Vector<T>::Delete(int index) { 
    if (index >= 0 && index < Size()) {
        auto itr = m_array.begin() + index;
        m_array.erase(itr);
    }
}

template <class T>
void Vector<T>::Clear() { //clears the entire array.
    m_array.clear();
}

template <class T>
Vector<T>& Vector<T>::operator = (const Vector<T>& input) {
    if (this != &input) {
        m_array = input.m_array;
    }
    return *this;
}

template <class T>
T& Vector<T>::operator[] (const int & index) {
    if (index >= 0 && index < m_array.size()) {
        return m_array[index];
    } else {
        throw std::out_of_range("Index out of range");
    }
}

template <class T>
const T& Vector<T>::operator[] (const int & index) const {
    if (index >= 0 && index < m_array.size()) {
        return m_array[index];
    } else {
        throw std::out_of_range("Index out of range");
    }
}

template <class T>
void Vector<T>::Shuffle() {
    auto rng = std::default_random_engine {};
    std::shuffle(std::begin(m_array), std::end(m_array), rng);
}