title: Hash Tables
---
class: center, middle, inverse
# Hashing and Hash Tables

---
# Some context...
We've been looking a lot at *search* - which means we are looking for a value, and we don't have a great idea of **where** it is in the container...

.callout[
Search is **not the same** as *lookup*.
]

- **Search** - You don't know where it is, you need to look for it
- **Lookup** - You know where it *should be*, now you just see if it is there.

The difference is subtle - but significant.  

---
# Lookup - defined.
Imagine you were assured that a series of numbers had the value of 0-99.
- In addition, you are told that memory consumption is not particularly important.
- ... and, that you will only need to tell whether a particular number is present, not how many times it is in your container.

.callout[
How could you arrange your container such that you could find whether a value is present in **O(1)** time?
]

---
# Value is the location...
In the example above, the value you are looking for **can only be found** at a specific index.
- The value at the index is `true`/`false`.
- We could change this to indicate *count* as well.

.info[
Of course, **this isn't a good generalized solution...**.  Why won't this work in all use-cases?
]

---
# Location *derived* from value
Let's say we have a container that stores **purchase transaction amounts**.  These numbers can range between $0.01 and $99.99 dollars.

We want to keep track of how many times a specific amount is seen in a list.

.callout[
How can we transform the value into a location, to create a lookup table?
]

---
# Location *derived* from value
Now let's say we need to keep track of purchases between $0.01 and $1,000,000.00...
- **This should be starting to concern you**... how many different "slots" are in our lookup table?
- **How likely is it that all amounts will be seen?**

--

.callout[
What if we used a modulus operator?
```
location = amount * 100 % 1000;
```
]

What sort of problems could arise?

---
# Hashing Functions
A hashing function takes an input value and outputs a hashed value.
- Presumably, the range of possible inputs is **larger** than the range of outputs.
- **Input** is sometimes called the **message**.
- **Output** is often called teh **hash** or **digest**.

--
- Example:  Using the % operator on a set of integers.
- Example:  Given a string, add up all the ASCII values to get an integer.
- Example:  Cryptographic hashes (ie. SHA)

---
# Collisions
Whenever two distinct values resolve to the **same** location, you have a *collision*.
- A hashing function should **limit** collisions - but it cannot avoid them entirely.

When a collision arises, we need to ensure that we can still find a place to add the value.
- We also must still be able to find both values when they are looked up!

---
# Collisions - the easy way
The easiest way to deal with collisions is to use a *list* for the hash table slot - **so you have a table of lists**.
- If multiple values hash to the same value (location), no problem - we just add them both to the list.
- When we do a lookup, we need to search the list associated with value's location.
- The table entries are often referred to as **buckets**.

.callout[
As long as our hashing function evenly distributes locations, we should be fine.
]

---
# Hashing Distributions
Sometimes are input values aren't evenly distributed - and this might end up producing poorly distributed hashed values.  **This would lead to collisions**.

**Example**:  Let's say each student ID number is XXXXYYYYZZZZ
- XXXX is the year the student was born.
- YYYY is a random 4 digit code
- ZZZZ is the year the student enrolled at Ramapo.

.callout[
If we used a hashing function that did a %1000, we'd be pretty disappointed... why?
]


This is a surprisingly common mistake, when dealing with "generated" IDs - the distribution of values is typically **not** normal.

---
# Alternatives to simple buckets
What is the search time now?
- Notice we call it search... not lookup!
- Could we improve it?

--
Options include:
- Expanding the table (reduce collisions)
- Using a search tree as the bucket.
- Linear probing
- Re-hashing

---
# Linear Probing
Keeping with a pure array (not a list), we can still deal with collisions:
- Given a value **v** to insert, we can hash to **k**.
- We can examine location **k** to see if anything is already there.
- If so, proceed to **k+1**, **k+2**, and so on - until we find an empty position.

.callout[
Notice that we are essentially creating a horizontal "bucket".
]

- How would we deal with inserting a value which hashes to (k+1) if we already used it?
- How do we deal with searching?
- How do we deal with deleting?

---
# Lab 5
Implement a Hash table using the bucket/chaining strategy, which stores **integers**.
- Create a "table size" that is **prime**, which helps distribute things nicely.  Use a `vector` of `vector`s... so each slot in the table is a `vector<int>` itself.
- Your hashing function should be to perform a modulus operation on the value, modding by the table size.
- Write some simple tests first!!!

---
# Conclusion
In most cases, *hash tables* offer extremely good lookup/search performance.
- The major caveat is how collisions are handled...
- There are a multitude of ways to resolve performance problems related to collisions - but none are free!
- In almost every case, you are sacrificing **space** for **time**.