/**
 ******************************************************************************
 * @file       daemon.c
 * @version    V1
 * @brief      API C source file of daemon.c
 *             Created on: 2013-2-26
 *             Author: daixuyi
 * @details    守护进程.
 * &copy       Copyrigth(C), 2013-2015.
 *
 ******************************************************************************
 **/

#include <types.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <debug.h>
#include <intLib.h>
#include <devLib.h>
#include <shell.h>

#define DM_MAX_NAME_LEN (8u)
#define DM_MAX_CHECK_TIME       (10u)       //喂狗间隔时间(s)


typedef struct soft_dog
{
	int32_t count;              /**<计数器*/
	char name[DM_MAX_NAME_LEN]; /**<任务名*/
	struct ListNode list_node;  /**<通用链表节点*/
}soft_dog_t;

static struct ListNode the_registed_list;
static TASK_ID DaemonTaskId = 0;

static uint32_t
soft_dog_init(void)
{
	/*初始化双向链表*/
	InitListHead(&the_registed_list);
	return 0;
}
static soft_dog_t* find_by_name(char_t* pname)
{
	soft_dog_t* pnode = NULL;
    struct ListNode* iter;

    LIST_FOR_EACH(iter, &the_registed_list)
    {
        /* 取得遍历到的对象 */
        pnode = MemToObj(iter, soft_dog_t, list_node);
        if (strncmp(pnode->name, pname, sizeof(pnode->name)) == 0)
        {
            return pnode;
        }
    }
	return NULL;
}
uint32_t regist_to_daemon(char *name)
{
	uint32_t fd;

	if(find_by_name(name) != NULL)
	{
		printf("err %s registered\n", name);
		return -1;
	}

	soft_dog_t* new = malloc(sizeof(struct soft_dog));
    if (new == NULL)
    {
        printf("dev_create out of mem! when creat name: %s.\n", name);
        return ERROR;
    }
	new->count = DM_MAX_CHECK_TIME;
	strncpy(new->name, name, DM_MAX_NAME_LEN);
	ListAddTail(&new->list_node, &the_registed_list);
	fd = (uint32_t)new;

	return fd;
}
/*how to release*/
uint32_t
feed_dog(uint32_t task_fd)
{

	soft_dog_t* pnode = (soft_dog_t*) task_fd;
	pnode->count = DM_MAX_CHECK_TIME;

	return 0;
}

void daemon_loop(void)
{
	soft_dog_t* pnode = NULL;
	struct ListNode* iter;
	while(1)
	{
		taskDelay(1);//时间多少？

		LIST_FOR_EACH(iter, &the_registed_list)
		{
			/* 取得遍历到的对象 */
			pnode = MemToObj(iter, soft_dog_t, list_node);
			if(pnode->count == 0)
			{
				printf("daemon reboot system...\n");
			}
			else if(pnode->count > 0)
			{
				pnode->count --;
			}

		}
	}
}

status_t daemon_init(void)
{
    if (DaemonTaskId != 0)
        return (ERROR); /* already called */
	soft_dog_init();
	DaemonTaskId = taskSpawn((const signed char * const )"DAEMON", 3, 1024,(OSFUNCPTR)daemon_loop, 0);

    D_ASSERT(DaemonTaskId != NULL);
    return (OK);
}

static void wdt_show(void)
{
	soft_dog_t* pnode = NULL;
    struct ListNode* iter;

	printf("Name");
	printf("\r\t\t\t");
	printf("RemainCounts\n");

    LIST_FOR_EACH(iter, &the_registed_list)
    {
        /* 取得遍历到的对象 */
        pnode = MemToObj(iter, soft_dog_t, list_node);
		printf("%s", pnode->name);
		printf("\r\t\t\t");
		printf("%d\n", pnode->count);
    }
}
int32_t do_wdt_show(cmd_tbl_t * cmdtp, uint32_t argc, const uint8_t *argv[])
{
	wdt_show();
    return 0;
}

SHELL_CMD(
    wdtshow, CFG_MAXARGS,        do_wdt_show,
    "wdtshow \r\t\t\t\t wdt show \n"
);
