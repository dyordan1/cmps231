#include <stdexcept>
// Don't write "using namespace std" in template headers,
// you pollute the includer's namespace usage.
// using namespace is fine in implementation files.

template <typename T>
class ArrayList
{
public:
    ArrayList()
    {
        for (int i = 0; i < ArrayList::CAPACITY; i++)
        {
            data[i] = 0;
        }
        count = 0;
    }

    // Add the value to the beginning of the list. Throw length_error if beyond capacity
    void prepend(T value)
    {
        if (count >= ArrayList::CAPACITY)
        {
            throw std::length_error("Array list has reached capacity and cannot be prepended.");
        }
        for (int i = count; i > 0; i--)
        {
            data[i] = data[i - 1];
        }
        data[0] = value;
        count++;
    }

    // Add the value to the end of the list. Throw length_error if beyond capacity
    void append(T value)
    {
        if (count >= ArrayList::CAPACITY)
        {
            throw std::length_error("Array list has reached capacity and cannot be appended.");
        }
        data[count++] = value;
    }

    // Return the value at the given index.  Throw out_of_range if outside the bounds of the data in array.
    T get(int index) const
    {
        if (index < 0)
        {
            throw std::out_of_range("Index must be 0 or greater.");
        }
        else if (index >= count)
        {
            throw std::out_of_range("Index is larger than maxium index with valid data");
        }
        return data[index];
    }
    
    T & operator [](int index) {
        if (index < 0)
        {
            throw std::out_of_range("Index must be 0 or greater.");
        }
        else if (index >= count)
        {
            throw std::out_of_range("Index is larger than maxium index with valid data");
        }
        return data[index];
    }

    // Return index where given value is found.  Return -1 if the value is not found.
    int find(T value) const
    {
        for (int i = 0; i < count; i++)
        {
            if (data[i] == value)
                return i;
        }
        return -1;
    }

    // Return the current length of the array (the part that has data!)
    int length() const
    {
        return count;
    }

    // Make sure you reference this const whenever dealing with capacity, so you can
    // change the capacity of the array list by altering just this line of code.
    static const int CAPACITY = 100;

private:
    // add any private members you think are necessary.
    T data[ArrayList::CAPACITY];
    int count;
};