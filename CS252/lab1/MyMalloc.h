//
// CS252: MyMalloc header file
//
// The various variables, functions, and structs associated
// with the allocator are defined here.

// Header of an object. Used both when the object is allocated and freed

typedef struct BoundaryTag {
  size_t _objectSizeAndAlloc; // Real size of the object (the last bit is used to
                              // check if the object is allocated
  size_t _leftObjectSize;     // Real size of the previous contiguous chunk in memory
} BoundaryTag;

struct FreeObject;

typedef struct FreeListNode {
  struct FreeObject * _next;  // Points to the next object in the freelist (if free)
  struct FreeObject * _prev;  // Points to the previous object
} FreeListNode;

typedef struct FreeObject {   // Header used by objects that are free
                              // NOTE: ALLOCATED OBJECTS JUST HAVE A BOUNDARY TAG
  BoundaryTag boundary_tag; 
  FreeListNode free_list_node;
} FreeObject;

#define getSize(obj)     (((obj)->_objectSizeAndAlloc) & ~1)
#define setSize(obj, size) \
  ((obj)->_objectSizeAndAlloc = (size) | isAllocated(obj))

#define isAllocated(obj) (((obj)->_objectSizeAndAlloc) & 1)
#define setAllocated(obj, alloc) \
  ((obj)->_objectSizeAndAlloc = (alloc) | getSize(obj))

//STATE of the allocator
// Size of the heap
size_t _heapSize;

// initial memory pool
void * _memStart;

// True if heap has been initialized
int _initialized;

// # malloc calls
int _mallocCalls;

// # free calls
int _freeCalls;

// # realloc calls
int _reallocCalls;

// # realloc calls
int _callocCalls;

// Free list
FreeObject * _freeList;
FreeObject _freeListSentinel;

//FUNCTIONS
//Prints the heap size and other information about the allocator
void print();
void print_list();
