#include <stdexcept>
#include <iostream>

template <typename T>
class node
{
public:
    node(node<T> *next, node<T> *prev, T data = 0)
    {
        // Fill this in.
    }
    node<T> *next;
    node<T> *prev;
    T data;
};

template <typename T>
class iterator;

// You will likely benefit from referencing 10-linked-list/ while implementing
// this class.
template <typename T>
class CircularList
{
public:
    CircularList()
    {
        // Fill this in
    }
    ~CircularList()
    {
        // Fill this in
    }

    iterator<T> begin() const
    {
        // Fill this in
    }

    // A circle has no end() :)

    bool is_empty() const
    {
        // Fill this in
    }

    void clear()
    {
        // Fill this in
    }

    // Insert in front of the given iterator.
    void insert(iterator<T> pos, T value)
    {
        // Fill this in
    }

    void push(T value)
    {
        // Fill this in
    }

    // Remove the value pointed at by the given iterator.
    void remove(iterator<T> pos)
    {
        // Fill this in
    }

    // We choose to omit pop() in favor of remove() with an iterator above - a
    // circular linked list is unlikely to need to pop the arbitrary head.

    iterator<T> find(const T &value)
    {
        // Fill this in
    }

    // We will choose to omit any front/back methods - we encourage the use of
    // find and iterators for our cicular list.

    int size() const
    {
        // Fill this in
    }

private:
    node<T> *head;

    int length;

    // Ok you get this one for free :)
    void debug_printout()
    {
        std::cerr << "---------------------------" << std::endl;
        std::cerr << "Debug print of list:  size = " << size() << std::endl;

        auto current = head;
        if (current != nullptr)
        {
            do
            {
                std::cerr << current << ":  " << current->prev << " <= " << current->data << " => " << current->next << std::endl;
                current = current->next;
            } while (current != head);
        }
    }
};

template <typename T>
bool operator!=(const iterator<T> &i1, const iterator<T> &i2)
{
    return i1.target != i2.target;
}
template <typename T>
bool operator==(const iterator<T> &i1, const iterator<T> &i2)
{
    return i1.target == i2.target;
}

// The iterator is already done for you - no modifications are neccessary.
// I know it's scary, but maybe still try to read through it :)
template <typename T>
class iterator
{
public:
    void forward()
    {
        if (!valid())
        {
            throw std::out_of_range("Cannot call next on invalid iterator");
        }
        target = target->next;
    }
    void back()
    {
        if (!valid())
        {
            throw std::underflow_error("Cannot call back on invalid iterator");
        }
        target = target->prev;
    }
    T &data()
    {
        if (!valid())
        {
            throw std::out_of_range("Cannot call data on invalid iterator");
        }
        return target->data;
    }
    bool valid()
    {
        return target != nullptr;
    }
    ~iterator<T>()
    {
    }

    // Dereference operator is just a convenience - calls out to data()
    T &operator*()
    {
        return data();
    }

private:
    // This is important... notice that the
    // constructor is private.  This means
    // normal user code just can't create an
    // iterator.  But List is a friend, so it can.
    // This is a classic Factory pattern - the List
    // class is the only onen that can build an iterator
    // for you.
    // If we were building a library of containers, we
    // might need to use a base class as friend, so iterator
    // could be re-used across subclasses.
    iterator<T>(node<T> *target) : target(target)
    {
    }

    node<T> *target;
    friend class CircularList<T>;

    // Operators are defined outside of classes, but this needs access to our
    // private target pointer.
    friend bool operator!=<>(const iterator<T> &i1, const iterator<T> &i2);
    friend bool operator==<>(const iterator<T> &i1, const iterator<T> &i2);
};