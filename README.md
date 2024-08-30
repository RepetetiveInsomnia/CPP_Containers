# CPP_Containers

Implementation of the containers.h. library.

### Introduction

As part of the project I made my own library that implements the basic standard C++ container classes: `list`, `map`, `queue`, `set`, `stack` and `vector`. Implementations provide a full set of standard methods and attributes for element handling, container capacity checking and iteration. As a bonus, I also implemented several other container classes from the C++ container library that are not as commonly used, but differ in their implementation details.

## Information

Each type of containers should provide the user with the following methods:

- standard constructors (default constructor, copy constructor, move constructor, constructor with initialization list, see materials);

- methods for accessing container elements (e.g. accessing an element with the index i);

- methods for checking if a container is full (e.g. the number of elements in the container, check if the container is empty);

- methods for changing the container (removing and adding new elements, cleaning the container);

- methods for dealing with the container iterator.

Iterators provide access to container elements. The specific type of iterator will be different for each container. This is due to the different way of organising object sets in container classes, as well as the actual implementation of the container. Iterators are implemented to work in a similar way to a pointer to an array element in C. So this approach to iterators allows you to interact with any container in the same way. Containers provide iterators via the `begin()` and `end()` methods, which point to the first and next after last elements of the container respectively.

Iterator `iter` has the following operations:

- `*iter`: gets the element pointed to by the iterator;

- `++iter`: moves the iterator forward to the next element;

- `--iter`: moves the iterator backwards to the previous element;

- `iter1 == iter2`: two iterators are equal if they point to the same element;

- `iter1 != iter2`: two iterators are not equal if they point to different elements.

In addition to the special organisation of objects and the provision of the necessary methods, the implementation of container classes requires the templating of objects.

Template classes or class templates are used when you want to create a class that depends on additional external parameters, which can be other classes or data types. For example, if you need to create a list class, you don't want to have to rewrite the list implementation for all possible element types. It would be nice to write one class with one parameter and get several specific list classes at once (character, integer, floating-point, user-defined type lists, etc.).
In C++, containers are part of the Standard Template Library (STL) for this very reason, along with iterators and some algorithms.

There are two main types of containers: sequence and associative containers. To find an element in sequence containers (`list`, `vector`, `array`, `stack`, `queue`), you have to look through the container one by one, while in associative containers (`map`, `set`, `multiset`) you just need to look through the key associated with the value.


## Implementation

List of classes: `list`, `map`, `queue`, `set`, `stack`, `vector`.

Additional list of classes to be implemented additionally: `array`, `multiset`.

### Implementation of the `insert_many` method.

I completed the classes with the appropriate methods, according to the table:

| Modifiers      | Definition                                      | Containers |
|----------------|-------------------------------------------------| -------------------------------------------|
| `iterator insert_many(const_iterator pos, Args&&... args)`          | Inserts new elements into the container directly before `pos`.  | List, Vector. |
| `void insert_many_back(Args&&... args)`          | Appends new elements to the end of the container.  | List, Vector, Queue. |
| `void insert_many_front(Args&&... args)`          | Appends new elements to the top of the container.  | List, Stack. |
| `vector<std::pair<iterator,bool>> insert_many(Args&&... args)`          | Inserts new elements into the container.  | Map, Set, Multiset. |

