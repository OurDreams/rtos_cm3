/**
 ******************************************************************************
 * @file       list.h
 * @version    V0.0.1
 * @brief      list模块.
 * @details    提供统一的链表操作方法.
 *
 ******************************************************************************
 */
#ifndef __LIST_H__
#define __LIST_H__

struct ListNode
{
	struct ListNode *pNextNode;
	struct ListNode *pPrevNode;
};

#define LIST_FOR_EACH(iter, pHead) \
	for (iter = (pHead)->pNextNode; iter != (pHead); iter = iter->pNextNode)

#define MemToObj(ptr, type, member) \
    (type *)((char *)ptr - (char *)(&((type *)0)->member))

extern void InitListHead(struct ListNode *pHead);
extern void ListAddHead(struct ListNode *pNew, struct ListNode *pHead);
extern void ListAddTail(struct ListNode *pNew, struct ListNode *pHead);
extern void ListDelNode(struct ListNode *pNode);
extern int ListIsEmpty(const struct ListNode *pHead);

#endif /* __LIST_H__ */
