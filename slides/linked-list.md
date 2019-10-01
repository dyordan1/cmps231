title: Linked List
---
class: center, middle, inverse
# Linked List
Solving the contiguous allocation problem


---
# What problem?
- Why is contiguous allocation bad?
- Why is it good?

.callout[
There is no single answer - your use case will drive your choice, and it will vary.
]

---
# Non-contiguous?
With an array, if we know the address of the first element, we know the address of all the rest.

<img src='../images/array-addresses.png'/>

This is because all the elements are right next to eachother.  If we drop this requirement, then we
would need another way of knowing where *each* element is...

---
# Pointers to the rescue
What if we did this?

<img src='../images/list-of-pointers.png'/>

.callout[
Well, this sort of solves it, but now we have an array of pointers :(
]

---
# Pointers + Data
We need to store a pointer to **next** element with each element's data.
```c++
class node {
    public:
        int data;
        node * next;
}
```
Each element in the list is now of type **`Node`**.  We c an generalize this with template syntax, so we aren't stuck with `int`s.
```c++
template <typename T>
class node {
    public:
        T data;
        node<T> * next;
}
```
---
# A chain of `node`s
Now every `node` point's to the next node... so we are in good shape - *if we just knew where the first one was*.

<img src='../images/nodes.png'/>


---
# A chain of `node`s
Now every Node point's to the next node... so we are in good shape - *if we just knew where the first one was*.

<img src='../images/nodes-head.png'/>

.callout[
We can remember where the *first* `Node` is by holding a **pointer** to it.  
]

---
# A chain of `node`s
One more problem... what should the value of `next` be in that last `node`?

<img src='../images/nodes-head.png'/>

.callout[
We can remember where the *first* `Node` is by holding a **pointer** to it.  
]
---
# Encapsulation
**Remember**, we are trying to build a *general* container class.  
- Users of a container don't want to manage `node`s
- **Instead**, we will create a class that holds a pointer to the `head`, and eventually allows a user to do all the typical list operations - **blissfully unaware of what is about to come next!**.

```c++
class List {
    public: 
        List() {
            head = nullptr; // When we start, there is no first element.
        }
        ~List() { /* who wants to bet we have to clean up things here?*/ }
    private:
        node * head;
};
```

---
# Encapsulation
You might have notices that we made `node`s data members (`data` and `next`) **public**.
- You've been taught not to do this...
- However the user of a `List` object will **never** gain access to a `node` instance.
- The `List` object's public methods never return `nodes`, only data and iterators.

.callout[
There is nothing wrong with making `data` and `next` private, and providing accessors and mutators, but if the `List` is implemented correctly, not much is gained by doing this.
]
---
# List implementation
We can re-use the same test cases from the `vector` module, with some adjustments in method names..

Let's start with some easy methods:
- `is_empty` - return `true` if the list is empty.
- `push_front` - add something to the front.
- `front` - return data in first element (**throw if empty**)
- `pop_front` - remove the front of list (**throw if empty**)
- `size` - return number of elements in the list.

.callout[
**Distinct cases**:  Adding / removing from an empty list, a list with just one element, and a list with N > 1 elements.
]
---
# Memory (de)allocation
We are creating `node`s on the heap inside `List` - so we need to clean up!
- **`clear`** - public method to dispose of the list contents, **if user wants to do this!**.
- **`~List`** - destructor, can call `clear` itself.

.callout[
**Remember**, while it is OK to have a public method to perform de-allocation, we **never** rely on the user of the class to call it - we **always** clean up after ourselves within the destructor!
]
---
# List implementation (2)
Now let's add some capabilties:
- `push_back` - add something to the back.
- `pop_back` - remove the back of list (**throw if empty**)
- `back` - return data in last element (**throw if empty**)

.callout[
To do this efficiently, we'll want to keep track of where the `tail` of the list is.
]
---
# List implementation (3)
We had a `find` method, and a `get` method in our original `ArrayList`.
- Both of these methods involved a *location*.
- Integer indexes don't make as much sense as the used to... because they don't actually tell us where the element is in memory - only pointers do.
- We do *not* return pointers - we need to return something else, that abstracts the pointer and allows access to elements in a safe way.
.callout[
**Iterators** do just this!
]

---
# Iterator implementation
An iterator encapsulates a `node`.
- Given an iterator that points to a `node`:
 - We can increment the iterator to the next location
 - We can decrement the iterator to the previous location
 - We can access (read or write) the data at the given location.


---
# List implementation (3)
Now we can implement `get` and `find`.  We should also let users acquire an iterator:
 - Keeping with STL convention, let's provide a `begin` method to return iterator to first.

We can now traverse the list too!  We didn't overload it as completely as STL does, but at least we can call the `forward` and `is_valid` methods to move forward and stop as needed.

```c++
List<int> list;
list.push_back(5);
...
for (auto i = list.begin(); i.isValid(); i.forward()) {
    cout << i.value() << endl;
}
```

---
# List implementation (4)
Our last methods are for insert/remove from arbitrary locations.
- Again, we'll need to reference a location - an iterator.

```c++
// Add a number to the second element.
auto i = list.begin();
i.forward();            // yes, this is awkward, which is why we should
i.forward();            // override the +, +=, and ++ operator!
list.insert(i, 5);
// remove the 4th elemennt
i.forward();
i.forward();
list.remove(i);
```
.callout[
Let's think about what it takes to insert/remove from the middle of the list...
]

---
# Double-linked list
We can implement `insert` and `remove`, but it's a bit painful.
- A common alternative is to **enance** `node` to contain a `previous` pointer as well as `next`.
- This let's us easily gain a reference to **both** the `node`s neighbors.

```c++
template <typename T>
class node {
    public:
        T data;
        node<T> * next;
        node<T> * previous;
}
```

.callout[
We have to enhance the existing `List` so it sets `previous` correctly
]

---
# Iterator enhancments
- The iterator should be able to go backwards too now - `reverse`.
- In addition, we can give someone access to the `end` of the list by returning an iterator that points to `tail`

.callout[
**Warning:** STL returns an `iterator` that is "one past" the tail.  This is very useful, because it allows us to use the `end` iterator as a stopping point 
]

```c++
while (i < list.end()) {
    ...
}
```
.callout[
We aren't overloading all the operators, so we will stick with `end` pointing to `tail` - the last valid element.  

**However** keep this difference in mind when using STL!
]

---
# Back to insert / remove
- **`insert`** accept an iterator and a value, insert in front of iterator.
- **`remove`** accept an iterator and remove the element at that location.


.info[
In both cases, if the iterator is invalid, we should throw an exception.
]

---
# Some design flaws
Notice that you can't add at the end of the list with `insert`?  
- If we changed the behavior to add after the given iterator, then we couldn't add at front.
- Overloading < won't work as nicely as it does with STL containers, since when our iterator goes past the tail, and doesn't contain a previous reference.

.callout[
We've taken our design as far as we need to go for now - but you should understand that there is a lot of value in using STL - as the designers of the language have created excellent interfaces for you to use!
]