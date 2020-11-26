#ifndef MY_HEAP_
#define MY_HEAP_
#include <iostream> 
using namespace std;
template<class ItemType>
class myHeap {
private:
   // Start with a small default size
   static const int DEFAULT_CAPACITY = 24;
   ItemType *items;

   int itemCount; // Current count of heap items
   int maxItems;  // Maximum capacity of the heap

   // Returns the array index of the left child (if exists).
   int getLeftChildIndex(const int nodeIndex) const;
   
   // Returns the array index of the right child (if exists).
   int getRightChildIndex(int nodeIndex) const;
   
   // Returns the array index of the parent node.
   int getParentIndex(int nodeIndex) const;
   
   // Tests whether this node is a leaf.
   bool isLeaf(int nodeIndex) const;
   
   // Converts a semiheap to a heap.
   void heapRebuild(int nodeIndex);
   
   // Creates a heap from an unordered array.
   void heapCreate();
   
public:
   myHeap();
   myHeap(const ItemType someArray[], const int arraySize);
   ~myHeap();
   
   // HeapInterface Public Methods:
   bool isEmpty() const;
   int getNumberOfNodes() const;
   
   ItemType peekTop() const;
   bool add(const ItemType& newData);
   bool remove();
   void clear();

};

template<class ItemType>
int myHeap<ItemType>::getLeftChildIndex(const int nodeIndex) const {
   return (2 * nodeIndex) + 1;
}

template<class ItemType>
int myHeap<ItemType>::getParentIndex(const int nodeIndex) const {
   return (nodeIndex - 1) / 2;
}

template<class ItemType>
int myHeap<ItemType>::getRightChildIndex(const int nodeIndex) const {
   return (2 * nodeIndex) + 2;
}

template<class ItemType>
void myHeap<ItemType>::heapRebuild(const int subTreeNodeIndex) {

    int largest = subTreeNodeIndex; // Initialize largest as root 
    int leftChild = getLeftChildIndex(subTreeNodeIndex); // Stores left child node
    int rightChild = getRightChildIndex(subTreeNodeIndex); // Stores right child node
    int size = itemCount; // assigns size of items array
 
    // Checks to see if leftChild is less than the size and if the left child is greater than the largest node.
    if (leftChild < size && items[leftChild] > items[largest])
        // If true than make left child node the largest.
        largest = leftChild; 

    // Checks to see if rightChild is less than the size and if the right child is greater than the largest node.
    if (rightChild < size && items[rightChild] > items[largest])
        // If true than make right child node the largest.
        largest = rightChild;
    
    // Checks to see if the largest node is not the sub tree node
    if (largest != subTreeNodeIndex) {
        // if true then swap the largest node with the sub tree node.
        swap(items[subTreeNodeIndex], items[largest]);
         
        // rebuild the heap
        heapRebuild(largest);
    }
}

template<class ItemType>
void myHeap<ItemType>::heapCreate() {
   for (int index = itemCount / 2; index >= 0; index--) {
      heapRebuild(index);  
   }
}

// Constructor that accepts an existing array
template<class ItemType>
myHeap<ItemType>::
myHeap(const ItemType someArray[], const int arraySize):
             itemCount(arraySize), maxItems(2 * arraySize) {

    items = new  ItemType[arraySize]; //creates new items array.

    // Transfers specified array into items.
    for (int i = 0; i < arraySize; i++)
    {
        items[i] = someArray[i];
    }

    // Create Heap
    heapCreate();
}

// Default constructor
template<class ItemType>
myHeap<ItemType>::myHeap(): itemCount(0),
        maxItems(DEFAULT_CAPACITY) {
   items = new ItemType[DEFAULT_CAPACITY];
}

// Default destructor
template<class ItemType>
myHeap<ItemType>::~myHeap() {
        delete items; 
}

// Return whether the heap is empty
template<class ItemType>
bool myHeap<ItemType>::isEmpty() const {
   return itemCount == 0;
}

// Return the total number of nodes
template<class ItemType>
int myHeap<ItemType>::getNumberOfNodes() const {
   return itemCount;
}

// Remove the root of the heap and rebuild it
template<class ItemType>
bool myHeap<ItemType>::remove() {
    bool empty = isEmpty();
    if (!empty) {

        int lastElement = items[itemCount - 1]; // Assigns the lastElement

        items[0] = lastElement; // Makes the last element the first one.

        itemCount--; // Decrements itemCount.

        heapCreate(); // Create new heap.
    }
    return empty;
}

// Clear all items (note we do not resize the array here).
template<class ItemType>
void myHeap<ItemType>::clear() {
   itemCount = 0;
}

// Return the value at the root of the heap
template<class ItemType>
ItemType myHeap<ItemType>::peekTop() const {
   return items[0];
}

// Add a new item to the heap
template<class ItemType>
bool myHeap<ItemType>::add(const ItemType& newData) {
    bool hasRoomToAdd = (itemCount < maxItems);
    if (hasRoomToAdd) { 
        
        int n = itemCount + 1; // Assigns index to size of items + 1

        items[n - 1] = newData; // Puts new data the the last element in heap.

        heapCreate(); // Creates heap.

        itemCount++; // Increments count.
        }
    return hasRoomToAdd;
}
#endif /* !MY_HEAP_ */
