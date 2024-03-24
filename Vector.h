/**
 * @file Vector.h
 * @brief This file contains the declaration of the Vector class template.
 */

#pragma once

/**
 * @class Vector
 * @brief  Manages a simple Vector array with a size and capacity.
 * 
 * @author Wong Liang Jun
 * @version 1.0.1
 * @date 25/02/2024
 *
 * @todo Add something similar to the STL vector's emplace_back.
 *
 */
template <class T>
class Vector {
    private:
        T* m_array = nullptr; // pointer to the heap
        int m_size; // number of elements in the vector
        int m_capacity; // size of the array in the heap

        /**
         * @brief Reallocate the array to a new capacity.
         *
         * @param newCapacity The new capacity of the array.
         */
        void ReAlloc(int newCapacity);
        
        /**
         * @brief Copy constructor
         * @param rhs 
         * @return true if rhs has a value
        */ 
        bool Copy(const T& rhs);

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
         * @brief Destructor.
         *
         * Releases the memory allocated for the vector.
         */
        ~Vector(); //To release the memory 

        /**
         * @brief Get the current size of the vector.
         *
         * @return The number of elements in the vector.
         */
        int Size();

        /**
         * @brief Add an element to the end of the vector.
         *
         * @param item The item to be added.
         * @return True if the item was added successfully, false otherwise.
         */
        bool Add(const T& item); 

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
         * @return A reference to the element at the specified index.
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
        void setat(int index, const T& input);

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
        const Vector<T>& operator = (const Vector<T>& input);

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
        T& operator[] (int index);

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
        const T& operator[] (int index) const;

        /**
         * @brief Returns the pointer to the vector's array
         *
         * @return A pointer to the underlying array data.
         */
        T* Data();

        /**
         * @brief An overloaded data function for const pointer to vector's array. 
         *
         * @return m_array 
         */
        const T* Data() const;

}; 

// implementation

template <class T>
Vector<T>::Vector() {
    if (m_array != nullptr) {
        m_capacity = 10;
    }
    m_size = 0;
 
    m_array = new T[m_capacity];
}

template <class T>
Vector<T>::Vector(int n) {
    if (n <= 0) {
        std::cerr << "Inappropriate size into vector! Please try again." << std::endl;
        exit(-1);
    } else {
        m_capacity = n;
    }
    if (m_array != nullptr) {
        m_capacity = n;
    }
    m_size = 0;
    m_array = new T[m_capacity];
}

template <class T>
Vector<T>::~Vector() {
    if (m_array != nullptr) {
        delete[] m_array;
        m_array = nullptr;
    }
}

template <class T>
int Vector<T>::Size() {
    return m_size;
}

template <class T>
bool Vector<T>::Add(const T& item) { // How push_back would work.
    if (m_size >= m_capacity/2) {
        ReAlloc(m_capacity + m_capacity/2); // Increment the capacity of array by 1.5. 
    }
    if (m_size != m_capacity) {
        m_array[m_size] = item;
        m_size++;
        return true;
    }
    return false;
}

template <class T>
void Vector<T>::ReAlloc(int newCapacity) {
    T* newBlock = new T[newCapacity];

    if (newCapacity < m_size) {
        m_size = newCapacity;
    }

    for (int i = 0; i< m_size; i++) {
        newBlock[i] = m_array[i];
    }
    delete[] m_array;
    m_array = newBlock;
    m_capacity = newCapacity;
}

template <class T>
const T& Vector<T>::getat(int index) {
    if (index >= m_size) {
        std::cerr << "Index over limit!" <<std::endl;
        exit(-1);        
    }
    return m_array[index];
}

template <class T>
void Vector<T>::setat(int index, const T& input) {
    if (index >= m_capacity) {
        std::cerr << "Index over limit!" <<std::endl;
        exit(-1);
    }
    m_capacity = m_capacity +1;
    for (int i = m_capacity; i >= index; i-- ) {
        m_array[i+1] = m_array[i];
    }
    m_array[index] = input;
    m_size++;
    if (m_size > m_capacity/2) {
        ReAlloc(m_capacity + m_capacity/2);
    }
}

template <class T>
void Vector<T>::Remove() { // similar to popback
    if (m_size > 0) {
        m_size--;
        m_array[m_size].~T(); // removes one thing from the back
    }
}

template <class T>
void Vector<T>::Modify(int index, const T& input) {
    m_array[index] = input;
}

template <class T>
void Vector<T>::Delete(int index) { 
    if (m_size > 0) {
        for (int i = index; i < m_capacity; i++ ) {
            m_array[i] = m_array[i+1];// removes one thing at index
        } 
        m_size--;
    }
}

template <class T>
void Vector<T>::Clear() { //clears the entire array.
    delete[] m_array;
    m_array = nullptr;
    m_size = 0;
    m_capacity = 0;
}

template <class T>
const Vector<T>& Vector<T>::operator = (const Vector<T>& input) {

    if (this != input) {
        delete[] m_array;
        m_size = input.m_size;
        m_capacity = input.m_capacity;
        m_array = new T[m_size];
        Copy(input);
    }    
    return *this;
}

template <class T>
T& Vector<T>::operator[] (int index) {
    return m_array[index];
}

template <class T>
const T& Vector<T>::operator[] (int index) const {
    return m_array[index];
}

template <class T>
T* Vector<T>::Data() {
    return m_array;
}

template <class T>
const T* Vector<T>::Data() const {
    return m_array;
}

template <class T>
bool Vector<T>::Copy(const T& rhs) {
    if (rhs.m_array != nullptr) {
        m_array = rhs.m_array;
        return true;
    } else {
        return false;
    }

}