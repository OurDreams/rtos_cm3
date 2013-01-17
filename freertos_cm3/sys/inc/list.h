#pragma once

struct ListNode {
	struct ListNode *pNextNode, *pPrevNode;
};

static void InitListHead(struct ListNode *pHead)
{
	pHead->pNextNode = pHead;
	pHead->pPrevNode = pHead;
}

static void __list_add(struct ListNode *pNew,
			struct ListNode *pPrev,
			struct ListNode *pNext)
{
	pNext->pPrevNode = pNew;
	pNew->pNextNode  = pNext;
	pNew->pPrevNode  = pPrev;
	pPrev->pNextNode = pNew;
}

static void ListAddHead(struct ListNode *pNew, struct ListNode *pHead)
{
	__list_add(pNew, pHead, pHead->pNextNode);
}

static void ListAddTail(struct ListNode *pNew, struct ListNode *pHead)
{
	__list_add(pNew, pHead->pPrevNode, pHead);
}

static void __list_del(struct ListNode *pPrev, struct ListNode *pNext)
{
	pNext->pPrevNode = pPrev;
	pPrev->pNextNode = pNext;
}

static void ListDelNode(struct ListNode *pNode)
{
	__list_del(pNode->pPrevNode, pNode->pNextNode);
}


static inline int ListIsEmpty(const struct ListNode *pHead)
{
	return pHead->pNextNode == pHead;
}

#define LIST_FOR_EACH(iter, pHead) \
	for (iter = (pHead)->pNextNode; iter != (pHead); iter = iter->pNextNode)


/////////////////

struct list_head {
	struct list_head *next, *prev;
};

#define LIST_HEAD_INIT(name) { &(name), &(name) }

#define LIST_HEAD(name) \
	struct list_head name = LIST_HEAD_INIT(name)

static inline void INIT_LIST_HEAD(struct list_head *list)
{
	list->next = list;
	list->prev = list;
}

static inline void _list_add(struct list_head *new,
				  struct list_head *prev,
				  struct list_head *next)
{
	next->prev = new;
	new->next = next;
	new->prev = prev;
	prev->next = new;
}

static inline void list_add(struct list_head *new, struct list_head *head)
{
	_list_add(new, head, head->next);
}


static inline void list_add_tail(struct list_head *new, struct list_head *head)
{
	_list_add(new, head->prev, head);
}

static inline void _list_del(struct list_head * prev, struct list_head * next)
{
	next->prev = prev;
	prev->next = next;
}

static inline void list_del(struct list_head *entry)
{
	_list_del(entry->prev, entry->next);
//	entry->next = LIST_POISON1;
//	entry->prev = LIST_POISON2;
}


#define list_for_each(pos, head) \
	for (pos = (head)->next; pos != (head); pos = pos->next)
