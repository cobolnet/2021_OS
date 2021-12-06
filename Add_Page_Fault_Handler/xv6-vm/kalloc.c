// Physical memory allocator, intended to allocate
// memory for user processes, kernel stacks, page table pages,
// and pipe buffers. Allocates 4096-byte pages.

#include "types.h"
#include "defs.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "spinlock.h"

void freerange(void *vstart, void *vend);
extern char end[]; // first address after kernel loaded from ELF file
int numfreepages=0;
uint pgrefcount[PHYSTOP >> PGSHIFT]; // 20163080 [57344]

struct run {
  struct run *next;
};

struct {
  struct spinlock lock;
  int use_lock;
  struct run *freelist;
} kmem;

// Initialization happens in two phases.
// 1. main() calls kinit1() while still using entrypgdir to place just
// the pages mapped by entrypgdir on free list.
// 2. main() calls kinit2() with the rest of the physical pages
// after installing a full page table that maps them on all cores.
void
kinit1(void *vstart, void *vend)
{
  initlock(&kmem.lock, "kmem");
  kmem.use_lock = 0;
  freerange(vstart, vend);
}

void
kinit2(void *vstart, void *vend)
{
  freerange(vstart, vend);
  kmem.use_lock = 1;
}

void
freerange(void *vstart, void *vend)
{
  char *p;
  p = (char*)PGROUNDUP((uint)vstart);
  for(; p + PGSIZE <= (char*)vend; p += PGSIZE)
  {
    pgrefcount[V2P(p) >> PGSHIFT] = 0; // 20163080
    kfree(p);
  }
}

//PAGEBREAK: 21
// Free the page of physical memory pointed at by v,
// which normally should have been returned by a
// call to kalloc().  (The exception is when
// initializing the allocator; see kinit above.)
void
kfree(char *v)
{
  struct run *r;

  if((uint)v % PGSIZE || v < end || V2P(v) >= PHYSTOP)
    panic("kfree");

  if(kmem.use_lock)
    acquire(&kmem.lock);

  if (pgrefcount[V2P(v) >> PGSHIFT] > 0) // 20163080
  { // 20163080
    pgrefcount[V2P(v) >> PGSHIFT]--; // 20163080
  } // 20163080
  else if (pgrefcount[V2P(v) >> PGSHIFT] == 0) // 20163080
  { // 20163080
    // Fill with junk to catch dangling refs.
    memset(v, 1, PGSIZE); // 20163080
    numfreepages++; // 20163080
    r = (struct run*)v; // 20163080
    r->next = kmem.freelist; // 20163080
    kmem.freelist = r; // 20163080
  } // 20163080
  if(kmem.use_lock)
    release(&kmem.lock);
}

// Allocate one 4096-byte page of physical memory.
// Returns a pointer that the kernel can use.
// Returns 0 if the memory cannot be allocated.
char*
kalloc(void)
{
  struct run *r;

  if(kmem.use_lock)
    acquire(&kmem.lock);
  r = kmem.freelist;
  if(r)
  {
    kmem.freelist = r->next;
    pgrefcount[V2P((char*)r) >> PGSHIFT] = 1; // 20163080
    numfreepages--; // 20163080
  }
  if(kmem.use_lock)
    release(&kmem.lock);
  return (char*)r;
}

int freemem(){
  uint freepages;
  if(kmem.use_lock)
    acquire(&kmem.lock);
  freepages = numfreepages;
  if(kmem.use_lock)
    release(&kmem.lock);
  return freepages;
}

uint // 20163080
get_refcounter(uint pa) // 20163080
{ // 20163080
  uint ref; // 20163080
  if(kmem.use_lock) // 20163080
    acquire(&kmem.lock); // 20163080
  ref = pgrefcount[pa >> PGSHIFT]; // 20163080
  if(kmem.use_lock) // 20163080
    release(&kmem.lock); // 20163080
  return ref; // 20163080
} // 20163080

void // 20163080
dec_refcounter(uint pa) // 20163080
{ // 20163080
  if(kmem.use_lock) // 20163080
    acquire(&kmem.lock); // 20163080
  pgrefcount[pa >> PGSHIFT]--; // 20163080
  if(kmem.use_lock) // 20163080
    release(&kmem.lock); // 20163080
} // 20163080

void // 20163080
inc_refcounter(uint pa) // 20163080
{ // 20163080
  if(kmem.use_lock) // 20163080
    acquire(&kmem.lock); // 20163080
  pgrefcount[pa >> PGSHIFT]++; // 20163080
  if(kmem.use_lock) // 20163080
    release(&kmem.lock); // 20163080
} // 20163080
