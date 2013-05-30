/* Needs list.h */

typedef struct shared_deq {
    LIST_ELEMENT;
    struct semaphore sem;
} shared_deq_t;


#define DEFINE_SHARED_DEQ(name)         \
    struct shared_deq name = {          \
        ._list = INIT_LIST(name._list), \
        .sem = INIT_SEMAPHORE,          \
    };


#define sdeq_empty(sdeq) (list_empty(&(sdeq)->_list))

#define sdeq_add(sdeq, s) __sdeq_add(sdeq, &(s->_list))


#define sdeq_entry(sdeq, type) container_of(sdeq, type, _list)

static inline void __sdeq_add(shared_deq_t *sdeq, list_t *l) {
    acquire(&sdeq->sem);
    list_add(l, &sdeq->_list);
    release(&sdeq->sem);
}

static inline list_t *sdeq_pop(shared_deq_t *sdeq) {
    list_t *ret;
    acquire(&sdeq->sem);
    ret = list_pop(&sdeq->_list);
    release(&sdeq->sem);
    return ret;
}

/* NOT INHERENTLY THREADSAFE */
#define for_each_in_sdeq(curr, sdeq, member) for_each(curr, &sdeq._list, member)

