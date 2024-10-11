#pragma once
#ifndef HEADER_H
#define HEADER_H

#include <iostream>
#include <cstring>

using namespace std;

/**
 * @brief Class representing a set of strings separated by commas.
 *
 * This class implements operations on sets, such as addition,
 * removal, union, intersection, and difference of sets.
 */
class MyString {
public:
    /**
     * @brief Default constructor. Initializes an empty set.
     */
    MyString();

    /**
     * @brief Parameterized constructor.
     * @param str A string representing set elements separated by commas.
     */
    MyString(const char* str);

    /**
     * @brief Destructor. Frees the memory allocated for the string.
     */
    ~MyString();

    /**
     * @brief Copy constructor.
     * @param other Another set object to copy from.
     */
    MyString(const MyString& other);

    /**
     * @brief Move constructor.
     * @param other Another set object to move from.
     */
    MyString(MyString&& other);

    /**
     * @brief Assignment operator.
     * @param other Another set object to assign.
     * @return Reference to the current object.
     */
    MyString& operator =(const MyString& other);

    /**
     * @brief Equality operator.
     * @param other Another set object to compare.
     * @return true if the sets are equal, false otherwise.
     */
    bool operator ==(const MyString& other) const;

    /**
     * @brief Inequality operator.
     * @param other Another set object to compare.
     * @return true if the sets are not equal, false otherwise.
     */
    bool operator !=(const MyString& other) const;

    /**
     * @brief Adds an element to the set.
     * @param el The element to add.
     */
    void Add(const char* el);

    /**
     * @brief Union operator.
     * @param other Another set object to union with.
     * @return A new object representing the union of two sets.
     */
    MyString operator +(const MyString& other) const;

    /**
     * @brief Intersection operator.
     * @param other Another set object to intersect with.
     * @return A new object representing the intersection of two sets.
     */
    MyString operator *(const MyString& other) const;

    /**
     * @brief Difference operator.
     * @param other Another set object for the difference.
     * @return A new object representing the difference between two sets.
     */
    MyString operator -(const MyString& other) const;

    /**
     * @brief Removes an element from the set.
     * @param el The element to remove.
     */
    void Remove(const char* el);

    /**
     * @brief Checks if an element is in the set.
     * @param el The element to check.
     * @return true if the element is present, false otherwise.
     */
    bool isInSet(const char* el) const;

    /**
     * @brief Returns the number of elements in the set.
     * @return The number of elements in the set.
     */
    int Cardinality() const;

    /**
     * @brief Prints a subset based on a bitmask.
     * @param n The bitmask used to determine the subset.
     */
    void PrintSubset(int n) const;

    /**
     * @brief Gets an element of the set by index.
     * @param index The index of the element.
     * @return A pointer to the element as a string.
     */
    const char* GetElement(int index) const;

    /**
     * @brief Prints all subsets of the set.
     */
    void PrintPowerSet() const;

    /**
     * @brief Prints the set.
     */
    void Print() const;

    /**
     * @brief Checks if the set is empty.
     * @return true if the set is empty, false otherwise.
     */
    bool IsEmpty();

private:
    char* str; //< Pointer to the string representing the set.
    int length; //< Length of the string.
};

#endif