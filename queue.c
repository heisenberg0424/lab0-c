#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "queue.h"

/* Create an empty queue */
struct list_head *q_new()
{
    struct list_head *head = malloc(sizeof(struct list_head));

    if (!head)
        return NULL;

    INIT_LIST_HEAD(head);
    return head;
}

void element_free(element_t *element)
{
    if (!element) {
        return;
    }
    free(element->value);
    free(element);
}

/* Free all storage used by queue */
void q_free(struct list_head *head)
{
    element_t *iter, *safe;
    list_for_each_entry_safe (iter, safe, head, list) {
        list_del(&iter->list);
        element_free(iter);
    }
    free(head);
}

/* Create new listed list element */
element_t *new_element(char *value)
{
    element_t *tmp = malloc(sizeof(element_t));
    if (!tmp) {
        return NULL;
    }

    int len = strlen(value) + 1;
    char *cpy = malloc(sizeof(char) * (len));
    if (!cpy) {
        free(tmp);
        return NULL;
    }

    memset(cpy, 0, len);
    memcpy(cpy, value, len);



    tmp->value = cpy;
    return tmp;
}

/* Insert an element at head of queue */
bool q_insert_head(struct list_head *head, char *s)
{
    if (!head) {
        return false;
    }

    element_t *tmp = new_element(s);

    if (!tmp) {
        return false;
    }

    list_add(&tmp->list, head);
    return true;
}

/* Insert an element at tail of queue */
bool q_insert_tail(struct list_head *head, char *s)
{
    if (!head) {
        return false;
    }

    element_t *tmp = new_element(s);

    if (!tmp) {
        return false;
    }

    list_add_tail(&tmp->list, head);
    return true;
}

/* Remove an element from head of queue */
element_t *q_remove_head(struct list_head *head, char *sp, size_t bufsize)
{
    if (!head || list_empty(head))
        return NULL;

    element_t *target = container_of(head->next, element_t, list);
    int len = strlen(target->value) + 1;

    if (sp && len < bufsize) {
        memcpy(sp, target->value, len);
    }

    list_del(&target->list);
    return target;
}

/* Remove an element from tail of queue */
element_t *q_remove_tail(struct list_head *head, char *sp, size_t bufsize)
{
    if (!head || list_empty(head))
        return NULL;

    element_t *target = container_of(head->prev, element_t, list);
    int len = strlen(target->value) + 1;

    if (sp && len < bufsize) {
        memcpy(sp, target->value, len);
    }

    list_del(&target->list);
    return target;
}

/* Return number of elements in queue */
int q_size(struct list_head *head)
{
    if (!head)
        return 0;

    int len = 0;
    struct list_head *li;

    list_for_each (li, head)
        len++;
    return len;
}

/* Delete the middle node in queue */
bool q_delete_mid(struct list_head *head)
{
    // https://leetcode.com/problems/delete-the-middle-node-of-a-linked-list/
    if (!head || list_empty(head))
        return false;

    struct list_head *slow, *fast;
    fast = head->prev;

    list_for_each (slow, head) {
        fast = fast->next->next;
        if (slow == head)
            break;
        if (fast->next == head || fast->next->next == head)
            break;
    }
    list_del(slow);
    element_free(container_of(slow, element_t, list));

    return true;
}

/* Delete all nodes that have duplicate string */
bool q_delete_dup(struct list_head *head)
{
    // https://leetcode.com/problems/remove-duplicates-from-sorted-list-ii/
    return true;
}

/* Swap every two adjacent nodes */
void q_swap(struct list_head *head)
{
    // https://leetcode.com/problems/swap-nodes-in-pairs/
}

/* Reverse elements in queue */
void q_reverse(struct list_head *head) {}

/* Reverse the nodes of the list k at a time */
void q_reverseK(struct list_head *head, int k)
{
    // https://leetcode.com/problems/reverse-nodes-in-k-group/
}

/* Sort elements of queue in ascending/descending order */
void q_sort(struct list_head *head, bool descend) {}

/* Remove every node which has a node with a strictly less value anywhere to
 * the right side of it */
int q_ascend(struct list_head *head)
{
    // https://leetcode.com/problems/remove-nodes-from-linked-list/
    return 0;
}

/* Remove every node which has a node with a strictly greater value anywhere to
 * the right side of it */
int q_descend(struct list_head *head)
{
    // https://leetcode.com/problems/remove-nodes-from-linked-list/
    return 0;
}

/* Merge all the queues into one sorted queue, which is in ascending/descending
 * order */
int q_merge(struct list_head *head, bool descend)
{
    // https://leetcode.com/problems/merge-k-sorted-lists/
    return 0;
}
