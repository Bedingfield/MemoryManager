/*
Program by Jonathan Bedingfield
2/17/20
Memory Manager
Currently using First-Fit
*/

//#ifndef mm
//#define mm

#include <iostream>
#include <sys/mman.h>
using namespace std;

typedef struct mmalloc_t
{
	int size;
	int magicNum;
} mmalloc_t;

typedef struct mmfree_t
{
	int size;
	mmfree_t* next;
} mmfree_t;

mmfree_t* head;//pointer to the first node in the linked list.  There will allways be at least one once we initilize
void* botLim;
void* topLim;
int freeHeaderSize;

void init_mem(int free_space_size)
{
	head = (mmfree_t*) mmap(NULL, free_space_size, PROT_READ|PROT_WRITE, MAP_ANON|MAP_PRIVATE, -1, 0);
	head->next = NULL;
	head->size = free_space_size - 16;
	botLim = (void*) head;
	topLim = (void*) (static_cast<void*>(head) + free_space_size);
}

void* mem_manager_malloc(int size)
{
	int adjustedSize = (size+16);//accomidates header
	mmfree_t* current = head;
	mmfree_t* trailing;
	mmalloc_t* allocated;
	trailing = NULL;
	
	cout << "request of " << size << endl;
	
	while(current != NULL && current->size < size)
	{
		trailing = current;//we use this to re link the list after a new allocation is made
		current = current->next;
	}
	if(current != NULL)//we found one
	{
		if(current->size == adjustedSize)//eat the whole node
		{
			if(trailing == NULL && current->next == NULL)//we are the only item in the list
			{
				head = NULL;
				allocated = (mmalloc_t*) current;
				allocated->size = size;
				allocated->magicNum = 1234567;
				return (void*) (static_cast<void*>(allocated) + 16);
			}
			if(current->next == NULL)//we are at the end of the list
			{
				trailing->next = NULL;
				allocated = (mmalloc_t*) current;
				allocated->size = size;
				allocated->magicNum = 1234567;
				return (void*) (static_cast<void*>(allocated) + 16);
			}
			if(trailing == NULL)//we are at the beginning of the list
			{
				head = current->next;
				allocated = (mmalloc_t*) current;
				allocated->size = size;
				allocated->magicNum = 1234567;
				return (void*) (static_cast<void*>(allocated) + 16);
			}
			else//we have a node before and a node after us
			{
				trailing->next = current->next;
				allocated = (mmalloc_t*) current;
				allocated->size = size;
				allocated->magicNum = 1234567;
				return (void*) (static_cast<void*>(allocated) + 16);
			}
		}
		else//it is not the same size,  we will need to be carefull here
		{
			if((current->size) > adjustedSize)//there is enough space
			{
				if(trailing == NULL && current->next == NULL)//we are the only item in the list
				{
					head = (mmfree_t*) (static_cast<void*>(current) + adjustedSize);
					
					//stamp a new header at current + adjustedSize
					head->size = (current->size - adjustedSize);
					head->next = NULL;
					allocated = (mmalloc_t*) current;
					allocated->size = size;
					allocated->magicNum = 1234567;
					return (void*) (static_cast<void*>(allocated) + 16);
				}
				if(current->next == NULL)//we are at the end of the list
				{
					trailing->next = (mmfree_t*) (static_cast<void*>(current) + adjustedSize);
					
					//stamp a new header at current + adjustedSize
					trailing->next->size = (current->size - adjustedSize);
					trailing->next->next = NULL;
					
					allocated = (mmalloc_t*) current;
					allocated->size = size;
					allocated->magicNum = 1234567;
					return (void*) (static_cast<void*>(allocated) + 16);
				}
				if(trailing == NULL)//we are at the beginning of the list
				{
					head = (mmfree_t*) (static_cast<void*>(current) + adjustedSize);
					
					//stamp a new header at current + adjustedSize
					head->size = (current->size - adjustedSize);
					head->next = current->next;
					
					allocated = (mmalloc_t*) current;
					allocated->size = size;
					allocated->magicNum = 1234567;
					return (void*) (static_cast<void*>(allocated) + 16);
				}
				else//we have a node before and a node after us
				{
					trailing->next = (mmfree_t*) (static_cast<void*>(current) + adjustedSize);
					
					//stamp a new header at current + adjustedSize
					trailing->next->size = (current->size - adjustedSize);
					trailing->next->next = current->next;
					
					allocated = (mmalloc_t*) current;
					allocated->size = size;
					allocated->magicNum = 1234567;
					return (void*) (static_cast<void*>(allocated) + 16);
				}
			}
			else//otherwise allocate the whole chunk (dont tell the user tho)
			{
				if(trailing == NULL && current->next == NULL)//we are the only item in the list
				{
					//cout << "asdfjkl;" << endl;
					head = NULL;
					allocated = (mmalloc_t*) current;
					allocated->size = current->size;
					allocated->magicNum = 1234567;
					return (void*) (static_cast<void*>(allocated) + 16);
				}
				if(current->next == NULL)//we are at the end of the list
				{
					trailing->next = NULL;
					allocated = (mmalloc_t*) current;
					allocated->size = current->size;
					allocated->magicNum = 1234567;
					return (void*) (static_cast<void*>(allocated) + 16);
				}
				if(trailing == NULL)//we are at the beginning of the list
				{
					head = current->next;
					allocated = (mmalloc_t*) current;
					allocated->size = current->size;
					allocated->magicNum = 1234567;
					return (void*) (static_cast<void*>(allocated) + 16);
				}
				else//we have a node before and a node after us
				{
					trailing->next = current->next;
					allocated = (mmalloc_t*) current;
					allocated->size = current->size;
					allocated->magicNum = 1234567;
					return (void*) (static_cast<void*>(allocated) + 16);
				}
			}
		}
	}
	else//we didnt
	{
		cout << "Did not find a space for item of size:  " << size << endl;
		return NULL;
	}
}

void coalesce()//merg the free list wherever possable
{
	mmfree_t* trailing;
	mmfree_t* current;
		
	if(head != NULL)
	{
		trailing = NULL;
		current = head;
		
		while(current != NULL)
		{
			trailing = current;
			current = current->next;
			
			if(current == (mmfree_t*) (static_cast<void*>(trailing) + trailing->size + 16))//trailing and current are consecutive spaces
			{
				trailing->next = current->next;
				trailing->size = (trailing->size + current->size + 16);
				
				trailing = NULL;
				current = head;
			}
		}
	}
}

void mem_manager_free(void* ptr)
{
	if(ptr > botLim && ptr < topLim)//check that the address given is valid
	{
		//extract the size of the space
		int size;
		mmalloc_t* allocated;
		mmfree_t* toInsert;
		mmfree_t* trailing;
		mmfree_t* current;
		
		allocated = (mmalloc_t*) ptr;
		allocated = (mmalloc_t*) (static_cast<void*>(allocated) - 16);//adjust the pointer
		size = allocated->size;//get the size
		
		//write the size of the space to the new header
		toInsert = (mmfree_t*) allocated;
		toInsert->size = size;//set the size
		toInsert->next = NULL;
		
		//now look for a location to insert into the list
		if(head == NULL)
		{
			head = toInsert;
		}
		else
		{
			current = head;
			trailing = NULL;
			while(current < toInsert && current != NULL)
			{
				trailing = current;
				current = current->next;
			}
			if(current == NULL)
			{
				trailing->next = toInsert;
			}
			if(trailing == NULL)
			{
				head = toInsert;
				toInsert->next = current;
			}
			else
			{
				trailing->next = toInsert;
				toInsert->next = current;
			}
		}
		coalesce();
	}
	else//error message if wanted
	{
		//cout << "Invalid address returned to FreeMemory" << endl;
	}
}

void traverse_free_list()
{
	if(head == NULL)
	{
		cout << "The Free list is empty" << endl << endl;
	}
	else
	{
		cout << "Traversal of the Free list" << endl << endl;
		mmfree_t* current = head;
		while(current != NULL)
		{
			cout << "Address: " << current << endl;
			cout << "Free Space: " << current->size << endl << endl;
			current = current->next;
		}
	}
}

//#endif