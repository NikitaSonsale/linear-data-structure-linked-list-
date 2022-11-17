#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

/* #defines */
#define TRUE			1
#define FALSE 			0
#define SUCCESS 		1
#define FAILURE 		0
#define LIST_EMPTY 		2
#define LIST_DATA_NOT_FOUND 	3

/* typedefs */

typedef int data_t;
typedef struct node node_t;
typedef node_t list_t;
typedef int status_t;
typedef int bool;
typedef int len_t;

/* structure */

struct node
{
	data_t data;
	struct node *prev;
	struct node *next;
};

/* declarations of interface routines */
list_t *create_list(void);
status_t insert_beg(list_t *p_list, data_t new_data);
status_t insert_end(list_t *p_list, data_t new_data);
status_t insert_after(list_t *p_list, data_t ex_data, data_t new_data);
status_t insert_before(list_t *p_list, data_t ex_data, data_t new_data);

status_t get_beg(list_t *p_list, data_t *p_data);
status_t get_end(list_t *p_list, data_t *p_data);
status_t pop_beg(list_t *p_list, data_t *p_data);
status_t pop_end(list_t *p_list, data_t *p_data);

status_t remove_beg(list_t *p_list);
status_t remove_end(list_t *p_list);
status_t remove_data(list_t *p_list, data_t data_remove);

len_t get_length(list_t *p_list);
bool get_repeat_count(list_t *p_list, data_t search_data);
bool contains(list_t *p_list, data_t search_data);
void show_list(list_t *p_list, const char *msg);
status_t destroy_list(list_t **p_list);

list_t *concat_list(list_t *p_list1, list_t *p_list2);
list_t *merge_list(list_t *p_list1, list_t *p_list2);
list_t *get_reversed_list(list_t *p_list);

status_t list_to_array(list_t *p_list, data_t **pp_array, size_t *p_size);
list_t *array_to_list(data_t *p_array, int size);

status_t append_list(list_t *p_list1, list_t *p_list2);
status_t reverse_list(list_t *p_list);

/* daclarations of auxillary routines */
node_t *get_list_node(data_t new_data);
void generic_insert(node_t *p_beg, node_t *p_mid, node_t *p_end);
void generic_delete(node_t *delete_node);
bool is_list_empty(list_t *p_list);
node_t *locate_node(list_t *p_list, data_t search_data);
void *xmalloc(size_t size_in_bytes);
/* client area */

int main()
{
	list_t *p_list = NULL;
	status_t s;
	data_t data;
	list_t *p_list1 = NULL;
        list_t *p_list2 = NULL;
        list_t *p_concat_list = NULL;
        list_t *p_merge_list = NULL;
        list_t *p_reversed_list = NULL;


	p_list = create_list();

	printf("INSERT ROUTINES\n\n\n");

	for(data = 0; data < 6; data++)
	{
		s = insert_beg(p_list, data);
		assert(s == SUCCESS);
	}
	show_list(p_list, "AFTER INSERT BEGINING");

	printf("\n");
	for(data = 10; data < 50; data = data + 10)
        {
                s = insert_end(p_list, data);
                assert(s == SUCCESS);
        }
        show_list(p_list, "AFTER INSERT END");

	s = insert_after(p_list, 4, 100);
	assert(s == SUCCESS);

	s = insert_before(p_list, 30, 200);
	assert(s == SUCCESS);
     
	printf("\n");
	show_list(p_list, "AFTER INSERT AFTER AND BEFORE");

	printf("\n\nREMOVE ROUTINES\n\n\n");

	s = remove_beg(p_list);
	assert(s == SUCCESS);

	s = remove_end(p_list);
	assert(s == SUCCESS);

	show_list(p_list, "AFTER REMOVE BEG AND REMOVE END");

	printf("\n");
	s = remove_data(p_list, 3);
	show_list(p_list, "AFTER REMOVING DATA 3");

	printf("\n\nGET ROUTINES\n\n\n");

	s = get_beg(p_list, &data);
	assert(s == SUCCESS);
	printf("STARTING DATA OF LIST : %d\n", data);

	s = get_end(p_list, &data);
	assert(s == SUCCESS);
        printf("LAST DATA OF LIST : %d\n", data);

	printf("\n\nPOP ROUTINES\n\n\n");

	s = pop_beg(p_list, &data);
        assert(s == SUCCESS);
        printf("POPPED STARTING DATA : %d\n", data);
	show_list(p_list, "AFTER POP BEG");

	printf("\n");
        s = pop_end(p_list, &data);
        assert(s == SUCCESS);
        printf("POPPED LAST DATA : %d\n", data);
	show_list(p_list, "AFTER POP END");


	printf("\n\nGET LENGTH ,CONTAINS AND GET REPEAT COUNT ROUTINES\n\n\n");

	len_t length;
	length = get_length(p_list);
	printf("LENGTH OF LIST IS : %d\n", length);

	if(contains(p_list, 20) == TRUE)
		puts("20 is present in the list");
		
	int count;
	count = get_repeat_count(p_list, 200);
	printf("There are %d entries of 200 in the list\n", count);


	printf("\n\nInterlist ROUTINES\n\n\n");


	p_list1 = create_list();
        p_list2 = create_list();

        for(data = 5; data <= 95; data += 10)
        {
                insert_end(p_list1, data);
                insert_end(p_list2, data+5);
        }

        show_list(p_list1, "List1:");
	printf("\n");
        show_list(p_list2, "List2:");

        p_concat_list = concat_list(p_list1, p_list2);
	printf("\n");
        show_list(p_concat_list, "concat_list");

	printf("\n");
	p_merge_list = merge_list(p_list1, p_list2);
        show_list(p_merge_list, "merge_list");
	
	printf("\n");
	p_reversed_list = get_reversed_list(p_list);
        show_list(p_reversed_list, "reversed_list");


	 printf("\n\nARRAY TO LIST AND LIST TO ARRAY\n\n\n");


        data_t *p_array = NULL;
        size_t p_size;

        s = list_to_array(p_list, &p_array, &p_size);
        assert(s == SUCCESS);
        int i;
        puts("LIST TO ARRAY :");
        for(i = 0; i < p_size; i++)
        {
                printf("p_array[%d] : %d\n", i, p_array[i]);
        }

        list_t *p_new_list = NULL;
        data_t p_array1[] = {10, 20, 30, 40, 50};

        int size = 5;
        p_new_list = array_to_list(p_array1, size);
        assert(p_new_list != NULL);
	printf("\n");
        show_list(p_new_list, "ARRAY TO LIST : ");

	printf("\n\nAPPEND AND REVERSE ROUTINE WITHOUT CREATING NEW LIST\n\n\n");


	show_list(p_list2, "List2 before undergoing reversal:");
	printf("\n");

        s = reverse_list(p_list2);
        assert(s == SUCCESS);
        show_list(p_list2, "Reversed List2:");


	printf("\n");

        s = append_list(p_list1, p_list2);
        assert(s == SUCCESS);
        show_list(p_list1, "list2 IS APPENDED BEHIND list1 :");

	printf("\n");

         s = destroy_list(&p_list);
        assert(s == SUCCESS && p_list == NULL);

        puts("list is destroyed");


	return 0;
}

/* definations of functions */

list_t *create_list(void)
{
	node_t *p_new_node = NULL;
	p_new_node = get_list_node(-1);
	p_new_node->next = p_new_node;
	p_new_node->prev = p_new_node;

	return(p_new_node);
}

status_t insert_beg(list_t *p_list, data_t new_data)
{
	generic_insert(p_list, get_list_node(new_data), p_list->next);
	return(SUCCESS);
}

status_t insert_end(list_t *p_list, data_t new_data)
{
	generic_insert(p_list->prev, get_list_node(new_data), p_list);
	return(SUCCESS);
}

status_t insert_after(list_t *p_list, data_t ex_data, data_t new_data)
{
	node_t *p_ex_node = locate_node(p_list, ex_data);
	if(p_ex_node == NULL)
		return(LIST_DATA_NOT_FOUND);
	generic_insert(p_ex_node, get_list_node(new_data), p_ex_node->next);
	return(SUCCESS);
}

status_t insert_before(list_t *p_list, data_t ex_data, data_t new_data)
{
	node_t *p_ex_node = locate_node(p_list, ex_data);
        if(p_ex_node == NULL)
                return(LIST_DATA_NOT_FOUND);
        generic_insert(p_ex_node->prev, get_list_node(new_data), p_ex_node);
        return(SUCCESS);
}

status_t get_beg(list_t *p_list, data_t *p_data)
{
	if(is_list_empty(p_list) == TRUE)
		return (LIST_EMPTY);
	*p_data = p_list->next->data;
	return(SUCCESS);
}

status_t get_end(list_t *p_list, data_t *p_data)
{
	if(is_list_empty(p_list) == TRUE)
                return (LIST_EMPTY);
        *p_data = p_list->prev->data;
        return(SUCCESS);
}

status_t pop_beg(list_t *p_list, data_t *p_data)
{
	if(is_list_empty(p_list) == TRUE)
                return (LIST_EMPTY);

        *p_data = p_list->next->data;
	generic_delete(p_list->next);
        return(SUCCESS);

}

status_t pop_end(list_t *p_list, data_t *p_data)
{
	if(is_list_empty(p_list) == TRUE)
                return (LIST_EMPTY);

        *p_data = p_list->prev->data;
	generic_delete(p_list->prev);
        return(SUCCESS);
}

status_t remove_beg(list_t *p_list)
{
	if(is_list_empty(p_list) == TRUE)
		return (LIST_EMPTY);
	generic_delete(p_list->next);
	return(SUCCESS);
}

status_t remove_end(list_t *p_list)
{
	if(is_list_empty(p_list) == TRUE)
                return (LIST_EMPTY);
        generic_delete(p_list->prev);
        return(SUCCESS);
}

status_t remove_data(list_t *p_list, data_t data_remove)
{
	node_t *p_delete_node = locate_node(p_list, data_remove);
	if(p_delete_node == NULL)
		return(LIST_DATA_NOT_FOUND);
	generic_delete(p_delete_node);
	return(SUCCESS);
}

len_t get_length(list_t *p_list)
{
	len_t length;
	node_t *p_run;
	for(p_run = p_list->next, length = 0; p_run != p_list; p_run = p_run->next, ++length)
	{
	}
	return(length);
}

int get_repeat_count(list_t *p_list, data_t search_data)
{
	int count = 0;
	node_t *p_run;
	for(p_run = p_list->next; p_run != p_list; p_run = p_run->next)	
	{
		if(p_run->data == search_data)
		{
			++count;
		}
	}
	return(count);
}

bool contains(list_t *p_list, data_t search_data)
{
	return(locate_node(p_list, search_data) != NULL);
}

bool is_list_empty(list_t *p_list)
{
	return(p_list->next == p_list && p_list->prev == p_list);
}

void show_list(list_t *p_list, const char *msg)
{
	node_t *p_run = NULL;
	puts(msg);
	printf("[START]<->");
	for(p_run = p_list->next; p_run != p_list; p_run = p_run->next)
	{
		printf("[%d]<->", p_run->data);
	}
	puts("[END]");
}

status_t destroy_list(list_t **pp_list)
{
        list_t *p_list = *pp_list;
        node_t *p_run, *p_run_next;
        for(p_run = p_list->next; p_run != p_list; p_run = p_run_next)
        {
                p_run_next = p_run->next;
                free(p_run);
        }
        free(p_list);
        
        *pp_list = NULL;
        return(SUCCESS);
}


list_t *concat_list(list_t *p_list1, list_t *p_list2)
{
        list_t *p_new_list = create_list();
        node_t *p_run;
        for(p_run = p_list1->next; p_run != p_list1; p_run = p_run->next)
        {
                insert_end(p_new_list, p_run->data);
        }
        for(p_run = p_list2->next; p_run != p_list2; p_run = p_run->next)
        {
                insert_end(p_new_list, p_run->data);
        }
        return(p_new_list);
}

list_t *merge_list(list_t *p_list1, list_t *p_list2)
{
        list_t *p_merge_list = create_list();
        node_t *p_run1 = p_list1->next;
        node_t *p_run2 = p_list2->next;

        while(TRUE)
        {
                if(p_run1 == p_list1)
                {
                        while(p_run2 != p_list2)
                        {
                                insert_end(p_merge_list, p_run2->data);
                                p_run2 = p_run2->next;
                        }
                        break;
                }
                if(p_run2 == p_list2)
                {
                        while(p_run1 != p_list1)
                        {
                                insert_end(p_merge_list, p_run1->data);
                                p_run1 = p_run1->next;
                        }
                        break;
                }

                if(p_run1->data <= p_run2->data)
                {
                        insert_end(p_merge_list, p_run1->data);
                        p_run1 = p_run1->next;
                }
                else
                {
                        insert_end(p_merge_list, p_run2->data);
                       p_run2 = p_run2->next;
                }
        }
        return(p_merge_list);
}

list_t *get_reversed_list(list_t *p_list)
{
        list_t *p_reversed_list = create_list();
        node_t *p_run = p_list->prev;
        while(p_run != p_list)
        {
                insert_end(p_reversed_list, p_run->data);
                p_run = p_run->prev;
        }
        return(p_reversed_list);
}

status_t list_to_array(list_t *p_list, data_t **pp_array, size_t *p_size)
{
        data_t *p_array = NULL;
        len_t list_len = get_length(p_list);
        node_t *p_run;
        int i;
        p_array = (data_t*)xmalloc(list_len * sizeof(data_t));
        for(p_run = p_list->next, i = 0; p_run != p_list; p_run = p_run->next, i++)
        {
                p_array[i] = p_run->data;
        }

        if(list_len != 0)
        {
                *pp_array = p_array;
                *p_size = list_len;
        }
        return(SUCCESS);
}

list_t *array_to_list(data_t *p_array, int size)
{
        list_t *p_new_list = create_list();
        int i;
        for(i = 0; i < size; i++)
        {
                insert_end(p_new_list, p_array[i]);
        }
        return(p_new_list);
}
			
status_t append_list(list_t *p_list1, list_t *p_list2)
{
        if(is_list_empty(p_list2) == TRUE)
                return(SUCCESS);

        p_list1->prev->next = p_list2->next;
        p_list2->next->prev = p_list1->prev;
        p_list1->prev = p_list2->prev;
        p_list2->prev->next = p_list1;
        free(p_list2);
        return(SUCCESS);
}

status_t reverse_list(list_t *p_list)
{
        node_t *p_run, *p_run_prev, *p_prev_orig;
        p_prev_orig = p_list->prev;
        for(p_run = p_list->prev->prev; p_run != p_list; p_run = p_run_prev)
        {
                p_run_prev = p_run->prev;
                generic_insert(p_list->prev, p_run, p_list);
        }
        p_prev_orig->prev = p_list;
        p_list->next = p_prev_orig;
        return (SUCCESS);
}
                                                                                   



node_t *locate_node(list_t *p_list, data_t search_data)
{
	node_t *p_run = NULL;
	for(p_run = p_list->next; p_run != p_list; p_run = p_run->next)
	{
		if(p_run->data == search_data)
			return(p_run);
	}
	return(NULL);
}

void generic_insert(node_t *p_beg, node_t *p_mid, node_t *p_end)
{
	p_mid->next = p_end;
	p_mid->prev = p_beg;
	p_beg->next = p_mid;
	p_end->prev = p_mid;
}

void generic_delete(node_t *delete_node)
{
	delete_node->prev->next = delete_node->next;
	delete_node->next->prev = delete_node->prev;
	free(delete_node);
}

node_t *get_list_node(data_t new_data)
{
	node_t *p_node = NULL;
	p_node = (node_t*)xmalloc(sizeof(node_t));
	p_node->data = new_data;
	p_node->prev = NULL;
	p_node->next = NULL;
	return(p_node);
}

void *xmalloc(size_t size_in_bytes)
{
	void *p = NULL;
	p = malloc(size_in_bytes);
	assert(p != NULL);
	return(p);
}

