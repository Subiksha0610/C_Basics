/*Exercise 8-8. Write a routine bfree(p,n) that will free any arbitrary block p of n characters 
into the free list maintained by malloc and free. By using bfree, a user can add a static or 
external array to the free list at any time. */
#include <stdio.h>
#include <stdlib.h>

typedef long Align;

union header {
    struct {
        union header *ptr;
        unsigned size;
    } s;
    Align x;
};

typedef union header Header;

static Header base;
static Header *freep = NULL;

void *mymalloc(unsigned nbytes) {
    Header *p, *prevp;
    unsigned nunits;

    if (nbytes == 0)
        return NULL;

    nunits = (nbytes + sizeof(Header) - 1) / sizeof(Header) + 1;

    if (freep == NULL) {
        base.s.ptr = freep = &base;
        base.s.size = 0;
    }

    prevp = freep;
    for (p = prevp->s.ptr; ; prevp = p, p = p->s.ptr) {
        if (p->s.size >= nunits) {
            if (p->s.size == nunits) {
                prevp->s.ptr = p->s.ptr;
            } else {
                p->s.size -= nunits;
                p += p->s.size;
                p->s.size = nunits;
            }
            freep = prevp;
            return (void *)(p + 1);
        }
        if (p == freep)
            return NULL;
    }
}

void myfree(void *ap) {
    Header *bp, *p;

    if (ap == NULL || freep == NULL)
        return;

    if ((unsigned long)ap % sizeof(Header) != 0)
        return;

    bp = (Header *)ap - 1;

    if (bp->s.size == 0)
        return;

    for (p = freep; !(bp > p && bp < p->s.ptr); p = p->s.ptr) {
        if (p >= p->s.ptr && (bp > p || bp < p->s.ptr))
            break;
        if (p->s.ptr == freep)
            return;
    }

    if (bp + bp->s.size == p->s.ptr) {
        bp->s.size += p->s.ptr->s.size;
        bp->s.ptr = p->s.ptr->s.ptr;
    } else {
        bp->s.ptr = p->s.ptr;
    }

    if (p + p->s.size == bp) {
        p->s.size += bp->s.size;
        p->s.ptr = bp->s.ptr;
    } else {
        p->s.ptr = bp;
    }

    freep = p;
}

void bfree(char *p, unsigned n) {
    Header *bp;
    unsigned nunits;

    if (p == NULL)
        return;

    if ((unsigned long)p % sizeof(Header) != 0)
        return;

    if (n < sizeof(Header))
        return;

    nunits = n / sizeof(Header);
    if (nunits < 2)
        return;

    if (freep == NULL) {
        base.s.ptr = freep = &base;
        base.s.size = 0;
    }

    bp = (Header *)p;
    bp->s.size = nunits;
    myfree((void *)(bp + 1));
}

int main(void) {
    static char buf[1000];

    bfree(buf, sizeof(buf));

    int *arr = (int *)mymalloc(10 * sizeof(int));
    if (arr == NULL) {
        printf("Allocation failed\n");
        return 1;
    }

    for (int i = 0; i < 10; i++) {
        arr[i] = i * 2;
        printf("arr[%d] = %d\n", i, arr[i]);
    }

    myfree(arr);
    myfree(arr);
    bfree(NULL, 100);
    bfree(buf + 1, 100);

    return 0;
}
/*output
arr[0] = 0
arr[1] = 2
arr[2] = 4
arr[3] = 6
arr[4] = 8
arr[5] = 10
arr[6] = 12
arr[7] = 14
arr[8] = 16
arr[9] = 18
*/