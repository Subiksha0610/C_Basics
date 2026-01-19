#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

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

    if (nbytes == 0 || nbytes > UINT_MAX - sizeof(Header))
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

    if (ap == NULL)
        return;

    if (freep == NULL)
        return;

    if ((unsigned long)ap % sizeof(Header) != 0)
        return;

    bp = (Header *)ap - 1;

    if (bp->s.size == 0 || bp->s.size > UINT_MAX / sizeof(Header))
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

int main(void) {
    int *arr = (int *) mymalloc(5 * sizeof(int));
    if (arr == NULL)
        return 1;

    for (int i = 0; i < 5; i++) {
        arr[i] = i * 10;
        printf("arr[%d] = %d\n", i, arr[i]);
    }

    myfree(arr);
    myfree(arr);
    myfree(NULL);

    return 0;
}
