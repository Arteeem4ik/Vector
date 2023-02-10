You are required to implement a generic Vector class with a single generic parameter, the type of elements to store.
When implementing, it is possible (and even necessary) to use generalized algorithms from the STL (std::copy, std::fill, etc.), but
you can't use standard containers. The correctness of the multiplicative array expansion scheme will be checked with
coefficient 2. In the basic version, manual control over the lifetime of objects is not required (see additional task). Class
must support the following functionality:

Default constructor - creates an empty array;
Explicit constructor from number - creates an array of the specified size filled with objects constructed by default;
Constructor that takes a size and a value (in that order) - collects an array of extracted sizes filled with
significant expenses;
Template constructor that takes a pair of iterators - creates a copy of the passed range;

Important: the declaration of this constructor must be of the form
template <class Iterator, class = std::enable_if_t<std::is_base_of_v<std::forward_iterator_tag, typename std::iterator_traits<Iterator>::iterator_category>>>
Vector(Iterator first, Iterator last)
This makes the constructor available only when there are two Forward iterators as input.

Constructor from std::initializer_list;

Rule of five;
Methods Size, Capacity, Empty;

Const and non-constant index access operator []. Non-const should allow you to change the received
element;

Const and non-constant index access operator []. Non-const should allow you to change the received
element;

Methods Front () and Back () - access to the first and last elements (also two versions each).

Data() method - returns a pointer to the beginning of the array.

Swap(other) method - swaps content with another array other;

Resize(new_size) method - resizes to new_size. If the capacity does not allow storing so many elements, then
a new buffer with capacity new_size is allocated. Missing elements are constructed by default.

Resize(new_size, value) method - the same as Resize(new_size), but in the case of new_size > size fills in the missing
elements with the value value.

Reserve(new_cap) method - changes capacity to max(new_cap, current capacity). The size does not change.
ShrinkToFit() method - reduces capacity to size.

The Clear() method - sets the size to 0, while the allocated memory is NOT cleared.

Methods PushBack(const T&) and PushBack(T&&) - adds a new element to the end of the array.

PopBack() method - removes the last element.

Comparison operators (<, >, <=, >=, ==, !=) specifying the lexicographic order.

Also implement support for iterators and methods for working with them: begin(), end(), cbegin(), cend(), rbegin(), rend(),
crbegin(), crend(). begin()-end(), rbegin()-rend() should have two versions returning const and non-const
iterators.
Inside the Vector class, define the member types ValueType, Pointer, ConstPointer, Reference, ConstReference,
SizeType, Iterator, ConstIterator.# Vector
