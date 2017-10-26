//
// CS252: MyMalloc Project
//
// The current implementation gets memory from the OS
// every time memory is requested and never frees memory.
//
// You will implement the allocator as indicated in the handout.
// 
// Also you will need to add the necessary locking mechanisms to
// support multi-threaded programs.
//

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/mman.h>
#include <pthread.h>
#include <errno.h>
#include <stdbool.h>
#include "MyMalloc.h"

#define ALLOCATED 1
#define NOT_ALLOCATED 0
#define ARENA_SIZE 2097152

pthread_mutex_t mutex;

static bool verbose = false;

extern void atExitHandlerInC()
{
  if (verbose)
    print();
}

static void * getMemoryFromOS(size_t size)
{
  // Use sbrk() to get memory from OS
  _heapSize += size;
 
  void *mem = sbrk(size);

  if(!_initialized){
      _memStart = mem;
  }

  return mem;
}


/*
 * @brief retrieves a new 2MB chunk of memory from the OS
 * and adds "dummy" boundary tags
 * @param size of the request
 * @return a FreeObject pointer to the beginning of the chunk
 */
static FreeObject * getNewChunk(size_t size)
{
  void *mem = getMemoryFromOS(size);

  // establish fence posts
  BoundaryTag *fencePostHead = (BoundaryTag *)mem;
  setAllocated(fencePostHead, ALLOCATED);
  setSize(fencePostHead, 0);

  char *temp = (char *)mem + size - sizeof(BoundaryTag);
  BoundaryTag *fencePostFoot = (BoundaryTag *)temp;
  setAllocated(fencePostFoot, ALLOCATED);
  setSize(fencePostFoot, 0);
 
  return (FreeObject *)((char *)mem + sizeof(BoundaryTag));
}

/**
 * @brief If no blocks have been allocated, get more memory and 
 * set up the free list
 */
static void initialize()
{
  verbose = true;

  pthread_mutex_init(&mutex, NULL);

  // print statistics at exit
  atexit(atExitHandlerInC);

  FreeObject *firstChunk = getNewChunk(ARENA_SIZE);

  // initialize the list to point to the firstChunk
  _freeList = &_freeListSentinel;
  setSize(&firstChunk->boundary_tag, ARENA_SIZE - (2*sizeof(BoundaryTag))); // ~2MB
  firstChunk->boundary_tag._leftObjectSize = 0;
  setAllocated(&firstChunk->boundary_tag, NOT_ALLOCATED);

  // link list pointer hookups
  firstChunk->free_list_node._next = _freeList;
  firstChunk->free_list_node._prev = _freeList;
  _freeList->free_list_node._prev = firstChunk;
  _freeList->free_list_node._next = firstChunk;

  _initialized = 1;
}

/**
 * @brief TODO: PART 1
 * This function should perform allocation to the program appropriately,
 * giving pieces of memory that large enough to satisfy the request. 
 * Currently, it just sbrk's memory every time.
 *
 * @param size size of the request
 *
 * @return pointer to the first usable byte in memory for the requesting
 * program
 */
static void * allocateObject(size_t size)
{
  if(size == 0 || size > ARENA_SIZE){
	errno = ENOMEM;
  	return NULL;
  }
  

  // Make sure that allocator is initialized
  if (!_initialized)
    initialize();
  
  size_t roundedSize = (size + 7) & ~7;
  roundedSize += sizeof(BoundaryTag);
  if(roundedSize < 32){
  	roundedSize = 32;
  }
  if (roundedSize > ARENA_SIZE - (3 * sizeof(BoundaryTag))) {
    errno = ENOMEM;
    return NULL;
  }
  FreeObject *p = _freeList -> free_list_node._next;
  bool noFoundFlag = true;
  while(p != _freeList){
	noFoundFlag = false;
  	if(getSize(&(p -> boundary_tag)) >= roundedSize && getSize(&(p -> boundary_tag)) < roundedSize + sizeof(FreeObject) + 8){
		setAllocated(&(p -> boundary_tag), ALLOCATED);
		p -> free_list_node._next -> free_list_node._prev = p -> free_list_node._prev;
		p -> free_list_node._prev -> free_list_node._next = p -> free_list_node._next;
		pthread_mutex_unlock(&mutex);
		return (void *)(p + 1);
	}else if(getSize(&(p -> boundary_tag)) >= roundedSize + sizeof(FreeObject) + 8){
		char * temp = (char *) p + getSize(&(p -> boundary_tag)) - roundedSize;	
		FreeObject *newOb = (FreeObject *) temp;
		setSize(&(p -> boundary_tag), getSize(&(p -> boundary_tag)) - roundedSize);
		setSize(&(newOb -> boundary_tag), roundedSize);
		setAllocated(&(newOb -> boundary_tag), ALLOCATED);
		char *memOb = temp + sizeof(BoundaryTag);
		p = (FreeObject *) memOb;
	
		char *nBlock = temp + roundedSize;
		FreeObject *nextBlock = (FreeObject *) nBlock;
		if(nextBlock != NULL && isAllocated(&(nextBlock -> boundary_tag))){
			nextBlock -> boundary_tag._leftObjectSize = roundedSize;
		}

		pthread_mutex_unlock(&mutex);
	    return (void *)(p);
	}else{
		noFoundFlag = true;
	}
	p = p -> free_list_node._next;
  }
  if(noFoundFlag){
	FreeObject *firstChunk = getNewChunk(ARENA_SIZE);

    setSize(&firstChunk->boundary_tag, ARENA_SIZE - (2*sizeof(BoundaryTag))); // ~2MB
    firstChunk->boundary_tag._leftObjectSize = 0;
    setAllocated(&firstChunk->boundary_tag, NOT_ALLOCATED);

    FreeObject *newNode = _freeList -> free_list_node._next;
    firstChunk->free_list_node._next = newNode;
    firstChunk->free_list_node._prev = _freeList;
    _freeList->free_list_node._next = firstChunk;
	pthread_mutex_unlock(&mutex);

    return allocateObject(size);
  }
   return p;
 }

/**
 * @brief TODO: PART 2
 * This funtion takes a pointer to memory returned by the program, and
 * appropriately reinserts it back into the free list.
 * You will have to manage all coalescing as needed
 *
 * @param ptr
 */
static void freeObject(void *ptr)
{
  char *opPtr = (char *)ptr - sizeof(BoundaryTag);
  FreeObject *usablePtr = (FreeObject *) opPtr;
  
  char *lop = (char *)ptr - usablePtr -> boundary_tag._leftObjectSize - sizeof(BoundaryTag);
  FreeObject *leftOb = (FreeObject *) lop;

  char *rop = opPtr + getSize(&(usablePtr -> boundary_tag));
  FreeObject *rightOb = (FreeObject *) rop;
	
  bool rightColFlag = false;
  if(!isAllocated(&(rightOb -> boundary_tag)) && rightOb != NULL){
	setSize(&(usablePtr -> boundary_tag), getSize(&(usablePtr -> boundary_tag)) + getSize(&(rightOb -> boundary_tag)));
  	setAllocated(&(rightOb -> boundary_tag), NOT_ALLOCATED);
  	rightOb -> free_list_node._prev -> free_list_node._next = rightOb -> free_list_node._next;
	rightOb -> free_list_node._next -> free_list_node._prev = rightOb -> free_list_node._prev;
  	rightColFlag = true;
  }
  
  if(!isAllocated(&(leftOb -> boundary_tag)) && leftOb != NULL){
	setSize(&(leftOb -> boundary_tag), getSize(&(leftOb -> boundary_tag)) + getSize(&(usablePtr -> boundary_tag)));
	setAllocated(&(leftOb -> boundary_tag), NOT_ALLOCATED);
	if(rightColFlag){
	  FreeObject *tempNext = _freeList -> free_list_node._next;
	  _freeList -> free_list_node._next = leftOb;
	  leftOb -> free_list_node._next = tempNext;
	  leftOb -> free_list_node._prev = _freeList;
	  setAllocated(&(usablePtr -> boundary_tag), NOT_ALLOCATED);
	}
  	return;
  }
	FreeObject *tempNext = _freeList -> free_list_node._next;
    _freeList -> free_list_node._next = usablePtr;
    usablePtr -> free_list_node._next = tempNext;
    usablePtr -> free_list_node._prev = _freeList;
  setAllocated(&(usablePtr -> boundary_tag), NOT_ALLOCATED);
  return;
}

void print()
{
  printf("\n-------------------\n");

  printf("HeapSize:\t%zd bytes\n", _heapSize);
  printf("# mallocs:\t%d\n", _mallocCalls);
  printf("# reallocs:\t%d\n", _reallocCalls);
  printf("# callocs:\t%d\n", _callocCalls);
  printf("# frees:\t%d\n", _freeCalls);

  printf("\n-------------------\n");
}

void print_list()
{
    printf("FreeList: ");
    if (!_initialized) 
        initialize();
    FreeObject *ptr = _freeList->free_list_node._next;
    while (ptr != _freeList) {
        long offset = (long)ptr - (long)_memStart;
        printf("[offset:%ld,size:%zd]", offset, getSize(&ptr->boundary_tag));
        ptr = ptr->free_list_node._next;
        if (ptr != NULL)
            printf("->");
    }
    printf("\n");
}

void increaseMallocCalls() { _mallocCalls++; }

void increaseReallocCalls() { _reallocCalls++; }

void increaseCallocCalls() { _callocCalls++; }

void increaseFreeCalls() { _freeCalls++; }

//
// C interface
//

extern void * malloc(size_t size)
{
  pthread_mutex_lock(&mutex);
  increaseMallocCalls();
  
  return allocateObject(size);
}

extern void free(void *ptr)
{
  pthread_mutex_lock(&mutex);
  increaseFreeCalls();
  
  if (ptr == 0) {
    // No object to free
    pthread_mutex_unlock(&mutex);
    return;
  }
  
  freeObject(ptr);
}

extern void * realloc(void *ptr, size_t size)
{
  pthread_mutex_lock(&mutex);
  increaseReallocCalls();

  // Allocate new object
  void *newptr = allocateObject(size);

  // Copy old object only if ptr != 0
  if (ptr != 0) {

    // copy only the minimum number of bytes
    FreeObject *o = (FreeObject *)((char *) ptr - sizeof(BoundaryTag));
    size_t sizeToCopy = getSize(&o->boundary_tag);
    if (sizeToCopy > size) {
      sizeToCopy = size;
    }

    memcpy(newptr, ptr, sizeToCopy);

    //Free old object
    freeObject(ptr);
  }

  return newptr;
}

extern void * calloc(size_t nelem, size_t elsize)
{
  pthread_mutex_lock(&mutex);
  increaseCallocCalls();
    
  // calloc allocates and initializes
  size_t size = nelem * elsize;

  void *ptr = allocateObject(size);

  if (ptr) {
    // No error
    // Initialize chunk with 0s
    memset(ptr, 0, size);
  }

  return ptr;
}

