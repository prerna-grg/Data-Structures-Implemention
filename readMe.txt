******cStack.hpp*********

cStack uses an array of user defines size (default 100) to implement two stacks
stack1 starts build up from index 0 of the array
stack2 starts build up from index n-1 of the array
if top element of stack1 and stack2 are at consecutive index it considers the array to be full

1) cStack(int cap = 100)
--> Creates a cStack with default size 100 , if any argument is supplied the size will be changed as per the entered value
2) int redsize() const
--> return number of elements in the redStack
3) int bluesize() const
--> return number of elements in the blueStack
4) bool redempty() const
--> returns true if redstack is empty
5) bool blueempty() const
--> returns true if bluestack is empty
6) const E& redtop()
--> returns top element of the redstack , if red stack stack is empty it will print error terminate the code 
7) const E& bluetop()
--> returns top element of the bluestack , if blue stack stack is empty it will print error terminate the code
8) void redpush(const E& e)
--> pushes the element onto the red stack , if there is no space it will print overflow error
9) void bluepush(const E& e) 	
--> pushes the element onto the blue stack , if there is no space it will print overflow error
10) void redpop()
--> removes element from the top of red stack , if redstack is empty it will give error
11) void bluepop()
--> removes element from the top of red stack , if redstack is empty it will give error

TIME COMPLEXITY:
all the operations in cStack are O(1)




******deque.hpp*****

deque uses a cstack to create a double ended queue
any push/pop operation for front uses redStack
any push/pop operation for back uses blueStack
if any stack is empty while the other is non-empty it reorders the elements

1) Deque();	
--> creates a deque using cStack of size 100
2) int size() const
--> returns the number of items in the deque
3) bool empty() const	
--> return true if the deque is empty
4) const E& front() const
--> returns the first element , gives error if deque is empty
5) const E& back() const
--> returns the last element , gives error if deque is empty
6) void insertFront(const E& e)
--> inserts new element at the front
7) void insertBack(const E& e)
--> inserts new element at the back
8) void removeFront()
--> removes first element , error if deque is empty
9) void removeBack()
--> removes last element , error if deque is empty

TIME COMPLEXITY:
size() , front() , back() , insertFront() , insertBack() are all O(1)
removeFront() and removeBack() are O(n) 
PROOF:
for N remove operations:
first N/2 will be O(1)
next there will be N/2 ordering operations 
next N/4 operations will be O(1)
in this fashion
order will be 
O( (N/2+N/2+N/4+N/4.......)/N ) = O(N)




*****heap.hpp*****
1)Heap()
--> creates a node pointer of type E entered by the user
2) int size() const
--> returns number of elements in the heap
3) bool isEmpty() const
--> returns true if the queue is empty
4) void insert(const E& e)
--> insert element in the heap as well as heapifies
5) const E& min() const
--> returns minimum element of the heap , error if heap is empty
6) void removeMin()
--> remove minimum element from the heap , error if empty
7) Heap* mergeHeaps()
--> merges two heaps
8) void buildHeap(int A[], int size)
--> creates a heap from elements in the array

TIME COMPLEXITY:
size() , isEmpty() , min() , are all O(1)
insert() , removeMin() are order O(logn) as the node will be swapped logn times in worst case
mergeHeaps() is order n , it performs n operations to extract elements from the array and calls buildHeap

buildHeap assign the correct pointers in order n and heapifies which is order n as every element is heapified at most logh times where h is the height of that node , so integral sums down to n


