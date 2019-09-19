title: Classes:  Review
---
class: center, middle, inverse
# Classes / Objects
A Review

---
# Data vs. Types
- We've seen arrays used simply as collections
- We've also seen arrays used to hold *histograms* - which is **entirely different!**.

We are approaching the definition of a **type** - which is data **plus** expected behaviors.
- An array has no real behavior
- A collection **does**
  - Insert, find, remove
- A histogram **does**
  - sample

---
# Abstract Data Types (ADT)
An important part of programming is **abstraction** - the ability for us to layer functionality such that the **implementation** detail is not always in our face!

- For a collection, we just want to call `insert`, we don't so much care about the bounds checking...
- For a histogram, we just want to call `sample`, we don't much care about how it's computed later!

.callout[Object-oriented programming languages allow programmers to create ADTs using `classes`]

---
# A simple class:  `Rational`
C++ is good at storing basic numbers - `int` and `float` and all their variants.

*However*, what about storing 1/3?  The best we can do is 0.333... with 64-bit precision.

Mostly this is OK - but sometimes we have programs that have thousands of computations, and each one depends on the previous.  Small rounding errors, *over a great number of iterations* adds up!

**Solution** - a new data type - `Rational`.
- A rational number has a numerator and denominator
- A rational number controls it's state - for example, setting it to 2/6 should automatically reduce to 1/3.
- A rational number can prevent invalid state - for example, 1/0 is no good.

---
# Encapsulation
To "control it's own state", the Rational class must protect it's `numerator` and `denominator` from being accessed directly.
- Whenever numerator and denominator are change, `Rational` needs to **know**!
 - It will check denominator isn't zero, and also reduce.

- Recall that member variables (and methods) can be marked `public`, `protected`, or `private`

```c++
class Rational {
    private:
        int numerator;
        int denominator;
}
```

---
# Accessors and Mutators
.split-left[
```cpp
int Rational::get_numerator() const
{
    return this->numerator;
}

int Rational::get_denominator() const
{
    return this->denominator;
}


```
]

.split-right[
```c++
void Rational::set_numerator(int value)
{
    this->numerator = value;
    this->reduce();
}
void Rational::set_denominator(int value)
{
    this->denominator = value;
    this->reduce();
}
```
]

.info[`reduce` is a **private** method for reducing the fraction - see code for details]
 
--
.callout[What about checking for denominator equal to 0?]

---
# Exceptions
What do we do when some foolish person calls `set_denominator` with 0?
1. Do nothing?
2. Print a stern warning?
3. Burn the whole program down?

---
# Exceptions
What do we do when some foolish person calls `set_denominator` with 0?
1. Do nothing?  
    - **Silent errors are terrible**
2. Print a stern warning? 
    - **There's a good change no one is reading your printout!**
3. Burn the whole program down?

--
.callout[Believe it or not, the third option is probably best!]

--

```c++
void set_denominator(int value) {
    if ( value == 0) {
        throw domain_error("Denominator cannot be set to 0");
    }
    this->denominator = value;
    this->reduce();
}
```

---
# Exception Handling

We will see more about exceptions later, but C++ has a rich set of exceptions available to us. Exceptions are defined in `stdexcept`... 
see [docs](https://en.cppreference.com/w/cpp/error/exception) for detail

The beauty of exceptions is that you can force the **caller** to handle the problem - which is appropriate, because the caller knows why the function / method was called in the first place, and should know better how to handle it!

```cpp
try {
    rational.set_denominator(input)
} catch( domain_error & e) {
    cerr << e.what() << endl;
}
```
.callout[Of course, a better written program would have checked the input in the first place - but it's not always possible]

---
# Access modifiers
What is the const doing at the end of this declaration?

```cpp
void get_denominator() const {
    return this.denominator;
}
```
--
A `const` in this location tells the caller (and the compiler) that calling this method **cannot change the state of the object**.

---
# Constructor
```c++
Rational(int n, int d) : numerator(n), denominator(d)
{
    if (this->denominator == 0)
    {
        throw std::domain_error("Denominator cannot be 0 in a rational number");
    }
    this->reduce();
}
```
.callout[Conveniently, although you can't return anything from a constructor, you can still throw an exception!]

Notice the member variable initialization stategy - you may not have seen this style before...

---
# Copy Constructor
Well... do we need one?
- The C++ compiler creates a copy contructor for us if we don't supply one.
- The default copy constructor simply copies member variables.
- If you have dynamic memory (pointers) you probably need to create your own.
- ... we'll see more on copy constructors later.

.callout[For similar reasons, we don't need a **destructor** with this class]


---
# Operations
We can create behaviors on the objects through additional member functions

```c++
Rational Rational ::add(const Rational &other) const
{
    int n = numerator * other.get_denominator() +
            denominator * other.get_numerator();
    int d = denominator * other.get_denominator();
    return Rational(n, d); // reduces
}

Rational Rational ::subtract(const Rational &other) const
{
    int n = numerator * other.get_denominator() -
            denominator * other.get_numerator();
    int d = denominator * other.get_denominator();
    return Rational(n, d); // reduces
}
```

---
# Overloading
Instead of using awkward functions, we can leverage operators in an intuitive way.
```c++
Rational operator+(const Rational &r1, const Rational &r2)
{
    return r1.add(r2);
}
Rational operator-(const Rational &r1, const Rational &r2)
{
    return r1.subtract(r2);
}
```
.callout[There is a lot more we can do with overloads, and we'll revisit some of the details later]

---
# Historgram:  As a class
Now we have the tools to create a `Histogram` class.
- It's constructor will initialize internal data
- It will contain a `sample` method to take in input
- It can have a `count` method to report frequency of a particular value

.callout[
We'll mostly borrow code from earlier, but now we have a nicer abstraction.
]

---
# Lab 2
Let's build a list class.
- It's constructor will allocate an array - whose max size is 100.
- It supports the following methods:
    - `prepend` and `append` - which adds a value to the *front* and *end*.
      - Throw `length_error` if size would exceed 100
    - `get` - which returns the value at a particular index.  The `get` method should prevent invalid indexes from being accessed.
      - Throw `out_of_range` error if index is invalid
    - `find` - returns the index where a value can be found, or -1 if it doesn't exist.
    - `length` - returns the current length of the list