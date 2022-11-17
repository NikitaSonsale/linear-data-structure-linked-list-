#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define TRUE 1
#define FALSE 0
#define SUCCESS 1
#define FAILURE 0
#define LIST_DATA_NOT_FOUND 2
#define LIST_IS_EMPTY 3

/* typedefs */
typedef int data_t;
typedef struct node node_t;
typedef node_t list_t;
typedef int status_t;
typedef int len_t;
typedef int bool;

/* Structure */
struct node
{
	data_t data;
	struct node *prev;
	struct node *next;
};

/* declarations of routines */
list_t *create_list();

status_t insert_beg(list_t *p_list, data_t new_data);
status_t insert_end(list_t *p_list, data_t new_data);
status_t insert_after(list_t *p_list, data_t ex_data, data_t new_data);
status_t insert_before(list_t *p_list, data_t ex_data, data_t new_data);

status_t get_beg(list_t *p_list, data_t *p_beg_data);
status_t get_end(list_t *p_list, data_t *p_end_data);
status_t pop_beg(list_t *p_list, data_t *p_beg_data);
status_t pop_end(list_t *p_list, data_t *p_end_data);

status_t remove_beg(list_t *p_list);
status_t remove_end(list_t *p_list);
status_t remove_data(list_t *p_list, data_t delete_data);

status_t is_list_empty(list_t *p_list);
len_t get_length(list_t *p_list);
bool contains(list_t *p_list, data_t s_data);
void show(list_t *p_list, const char *msg);

list_t *concate(list_t *p_list_1, list_t *p_list_2);
list_t *merge(list_t *p_list_1, list_t *p_list_2);
list_t *get_reversed_list(list_t *p_list);

status_t append(list_t *p_list_1, list_t *p_list_2);
status_t reverse_list(list_t *p_list);

void list_to_array(list_t *p_list, data_t **p_array, data_t *p_size);
list_t *array_to_list(data_t *p_array, size_t size);
status_t destroy_list(list_t **pp_list);

void generic_insert(node_t *p_beg, node_t *p_mid, node_t *p_end);
void generic_delete(node_t *delete_node);
node_t *search_node(list_t *p_list, data_t search_data);
node_t *get_list_node(data_t new_data);
void get_last_node(list_t *p_list, node_t **pp_last_node);

void *xmalloc(size_t size_in_bytes);

/* client */

int main()
{
	list_t *p_list;
	list_t* p_list1 = NULL;
	list_t* p_list2 = NULL;
	list_t* concated_list = NULL;
	list_t* merged_list = NULL;
	list_t* reversed_list = NULL;
	status_t s;
	status_t status;
	len_t length;

	p_list = create_list();

	puts("\n\n \t\t\tAFTER CREATING LIST \n\n");

	show(p_list, "after creating list");

	puts("\n\n \t\t\tINSERT ROUTINES \n\n");
	data_t data;
	for(data = 0; data < 5; data++)
	{
		s = insert_beg(p_list, data);
		assert(s == SUCCESS);
	}

	show(p_list, "after insert beg");


	for(data = 5; data < 10; data++)
        {
                s = insert_end(p_list, data);
                assert(s == SUCCESS);
        }
	puts("\n");
	show(p_list, "after insert end");

	s = insert_after(p_list, 3, 100);
	assert(s == SUCCESS);

	s = insert_before(p_list, 7, 200);
	assert(s == SUCCESS);

	puts("\n");
	show(p_list, "after insert_after and insert_before");

	printf("\n\t\t\tGET ROUTINES\n\n");

	status = get_beg(p_list, &data);
	assert(status);
	printf("Start data = %d\n", data);

	status = get_end(p_list, &data);
	assert(status);
	printf("End data = %d\n", data);

	printf("\n\t\t\tPOP ROUTINES\n\n");

	status = pop_beg(p_list, &data);
	assert(status);
	printf("Start data = %d\n", data);
	show(p_list, "After pop_start:");

	status = pop_end(p_list, &data);
	assert(status);
	puts("\n");
	printf("End data = %d\n", data);
	show(p_list, "After pop_end:");

	puts("\n\n \t\t\tREMOVE ROUTINES \n\n");

	s = remove_beg(p_list);
	assert(s == SUCCESS);
        show(p_list, "after removing beg");
	
	s = remove_end(p_list);
	assert(s == SUCCESS);
	puts("\n");
	show(p_list, "after removing end");

	status = remove_data(p_list, 0);
	assert(status);
	puts("\n");
	show(p_list, "After remove_data:");

	printf("\n\t\t\tLENGTH AND CONTAINS ROUTINES\n\n");

	length = get_length(p_list);
	printf("length of linked list : %d\n", length);

	printf("contains routine : ");
	if(contains(p_list, 100) == TRUE)
		printf("GIVEN DATA IS PRESENT IN THE LINKED LIST\n");
	else
		printf("GIVEN DATA IS NOT PRESENT IN THE LINKED LIST\n");

	printf("\n\t\t\tCONCATE, MERGE AND REVERSE ROUTINES\n\n");

	p_list1 = create_list();
    	p_list2 = create_list();

    	for(data = 5; data <= 55; data += 10)
    	{
        	insert_end(p_list1, data);
        	insert_end(p_list2, data+5);
    	}

    	show(p_list1, "List1:");
	puts("\n");
    	show(p_list2, "List2:");

	concated_list = concate(p_list1, p_list2);
	puts("\n");
	show(concated_list, "LIST AFTER CONCATINATION");

	merged_list = merge(p_list1, p_list2);
	puts("\n");
	show(merged_list, "LIST AFTER MERGING");

	reversed_list = get_reversed_list(p_list1);
	puts("\n");
	show(reversed_list, "LIST AFTER REVERSING");

        printf("\n\t\t\tAPPEND AND REVERSE INPLACE ROUTINES\n\n");

	status = append(p_list1, p_list2);
	assert(status);
	show(p_list1, "AFTER APPEND");

	status = reverse_list(p_list1);
	assert(status);
	puts("\n");
	show(p_list1, "AFTER REVERSE INPLACE");

        printf("\n\t\t\tARRAY TO LIST AND LIST TO ARRAY ROUTINES\n\n");

	data_t *p_array = NULL;
        data_t p_size;

	list_to_array(p_list, &p_array, &p_size);
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
	puts("\n");
	show(p_new_list, "ARRAY TO LIST : ");

        printf("\n\t\t\tDESTROYING ALL LISTS\n\n");

	status = destroy_list(&p_list);
     	assert(status == SUCCESS && p_list == NULL);

	status = destroy_list(&p_list1);
        assert(status == SUCCESS && p_list1 == NULL);

	status = destroy_list(&p_list2);
        assert(status == SUCCESS && p_list2 == NULL);

	status = destroy_list(&concated_list);
        assert(status == SUCCESS && concated_list == NULL);

	status = destroy_list(&merged_list);
        assert(status == SUCCESS && merged_list == NULL);

	status = destroy_list(&reversed_list);
        assert(status == SUCCESS && reversed_list == NULL);

	status = destroy_list(&p_new_list);
        assert(status == SUCCESS && p_new_list == NULL);

	printf("ALL LISTS ARE DESTROYED\n\n");
	return 0;
}

/* definations of routines */
list_t *create_list()
{
	return(get_list_node(-1));
}

status_t insert_beg(list_t *p_list, data_t new_data)
{
	generic_insert(p_list, get_list_node(new_data), p_list->next);
	return(SUCCESS);
}

status_t insert_end(list_t *p_list, data_t new_data)
{
	node_t *p_run = NULL;
	p_run = p_list;
	while(p_run->next != NULL)
	{
		p_run = p_run->next;
	}
	generic_insert(p_run, get_list_node(new_data), NULL);
	return(SUCCESS);
}

status_t insert_after(list_t *p_list, data_t ex_data, data_t new_data)
{
	node_t *p_existing_node = search_node(p_list, ex_data);
	if(p_existing_node == NULL)
		return(LIST_DATA_NOT_FOUND);

	generic_insert(p_existing_node, get_list_node(new_data), p_existing_node->next);
	return(SUCCESS);
}

status_t insert_before(list_t *p_list, data_t ex_data, data_t new_data)
{
	node_t *p_existing_node = search_node(p_list, ex_data);
        if(p_existing_node == NULL)
                return(LIST_DATA_NOT_FOUND);

        generic_insert(p_existing_node->prev, get_list_node(new_data), p_existing_node);
        return(SUCCESS);
}

status_t get_beg(list_t *p_list, data_t *p_beg_data)
{
	if(is_list_empty(p_list) == TRUE)
                return(LIST_IS_EMPTY);
	*p_beg_data = p_list->next->data;
	return SUCCESS;
}

status_t get_end(list_t *p_list, data_t *p_end_data)
{
	node_t *last_node = NULL;
	if(is_list_empty(p_list) == TRUE)
                return(LIST_IS_EMPTY);

	get_last_node(p_list, &last_node);
        *p_end_data = last_node->data;
        return SUCCESS;
}

status_t pop_beg(list_t *p_list, data_t *p_beg_data)
{
	if(is_list_empty(p_list) == TRUE)
                return(LIST_IS_EMPTY);
	*p_beg_data = p_list->next->data;
        generic_delete(p_list->next);
        return SUCCESS;
}

status_t pop_end(list_t *p_list, data_t *p_end_data)
{
	node_t *p_last_node = NULL;
	if(is_list_empty(p_list) == TRUE)
                return(LIST_IS_EMPTY);

	get_last_node(p_list, &p_last_node);
	*p_end_data = p_last_node->data;
	generic_delete(p_last_node);
	return SUCCESS;
}

status_t remove_beg(list_t *p_list)
{
	if(is_list_empty(p_list) == TRUE)
		return(LIST_IS_EMPTY);
	generic_delete(p_list->next);
	return SUCCESS;
}

status_t remove_end(list_t *p_list)
{
	node_t *p_run = NULL;
	if(is_list_empty(p_list) == TRUE)
		return(LIST_IS_EMPTY);
	p_run = p_list;
	while(p_run->next != NULL)
		p_run = p_run->next;
	generic_delete(p_run);
	return SUCCESS;
}

status_t remove_data(list_t *p_list, data_t delete_data)
{
	node_t *p_node = search_node(p_list, delete_data);
	if(p_node == NULL)
		return(LIST_DATA_NOT_FOUND);
	generic_delete(p_node);
	return SUCCESS;
}

status_t is_list_empty(list_t *p_list)
{
	return(p_list->next == NULL && p_list->prev == NULL);
}

len_t get_length(list_t *p_list)
{
	node_t *p_run = NULL;
	len_t length = 0;
	p_run = p_list->next;
	while(p_run != NULL)
	{
		length++;
		p_run = p_run->next;
	}
	return length;
}

bool contains(list_t *p_list, data_t s_data)
{
	node_t *p_node = NULL;
	p_node = search_node(p_list, s_data);
	if(p_node == NULL)
		return FALSE;
	return TRUE;
}

void show(list_t *p_list, const char *msg)
{
    struct node* p_run = NULL; 

    if(msg)
        puts(msg); 

    printf("[BEG]<->"); 

    p_run = p_list->next; 
    while(p_run != NULL)
    {
        printf("[%d]<->", p_run->data); 
        p_run = p_run->next; 
    }
    puts("[END]"); 
}

list_t *concate(list_t *p_list_1, list_t *p_list_2)
{
	list_t *p_new_list;
	node_t *p_run = NULL;

	p_new_list = create_list();
	for(p_run = p_list_1->next; p_run != NULL; p_run = p_run->next)
		insert_end(p_new_list, p_run->data);
	for(p_run = p_list_2->next; p_run != NULL; p_run = p_run->next)
		insert_end(p_new_list, p_run->data);

	return p_new_list;
}

list_t *merge(list_t *p_list_1, list_t *p_list_2)
{
	list_t *p_merge_list;
	node_t *p_run1, *p_run2;

	p_run1 = p_list_1->next;
	p_run2 = p_list_2->next;

	p_merge_list = create_list();

	while(TRUE)
	{
		if(p_run1 == NULL)
		{
			while(p_run2 != NULL)
			{
				insert_end(p_merge_list, p_run2->data);
				p_run2 = p_run2->next;
			}
			break;
		}

		if(p_run2 == NULL)
		{
			while(p_run1 != NULL)
			{
				insert_end(p_merge_list, p_run1->data);
				p_run1 = p_run1->next;
			}
			break;
		}

		if(p_run1->data <=  p_run2->data)
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

	return p_merge_list;

}

list_t *get_reversed_list(list_t *p_list)
{
	list_t *p_reverse_list;
	node_t *p_run = NULL;

	p_reverse_list = create_list();

	for(p_run = p_list->next; p_run != NULL; p_run = p_run->next)
	{
		insert_beg(p_reverse_list, p_run->data);
	}

	return p_reverse_list;
}

status_t append(list_t *p_list_1, list_t *p_list_2)
{
	node_t *p_last_node_of_p_list_1 = NULL;

	get_last_node(p_list_1, &p_last_node_of_p_list_1);

	p_last_node_of_p_list_1->next = p_list_2->next;
	free(p_list_2);
	return SUCCESS;
}

status_t reverse_list(list_t *p_list)
{
	node_t* p_run = NULL; 
	node_t* p_run_next = NULL; 
	
	if (p_list->next == NULL || p_list->next->next == NULL)
		return (SUCCESS); 
	
	p_run = p_list->next->next;
	p_list->next->next = NULL; 
	while (p_run != NULL)
	{
		p_run_next = p_run->next; 
		generic_insert(p_list, p_run, p_list->next); 
		p_run = p_run_next; 
	}

	return (SUCCESS); 
}

void list_to_array(list_t *p_list, data_t **pp_array, data_t *p_size)
{
	data_t *p_array = NULL;
	len_t length = get_length(p_list);
	node_t *p_run = NULL;
	int i;

	p_array = (data_t*)xmalloc(length * sizeof(data_t));

	for (p_run = p_list->next, i = 0; p_run != NULL; p_run = p_run->next, ++i)
	{
		p_array[i] = p_run->data;
	}

	if(length != 0)
	{
		*pp_array = p_array;
		*p_size = length;
	}	

}

list_t *array_to_list(data_t *p_array, size_t size)
{
	list_t *p_new_list = create_list();
	int i;
	for(i = 0; i < size; i++)
	{
		insert_end(p_new_list, p_array[i]);
	}
	return(p_new_list);
}

status_t destroy_list(list_t **pp_list)
{
	list_t *p_list = *pp_list;
	node_t *p_run, *p_run_next;
	for(p_run = p_list->next; p_run != NULL; p_run = p_run_next)
	{
		p_run_next = p_run->next;
		free(p_run);
	}
	free(p_list);
	*pp_list = NULL;
	return(SUCCESS);
}

void get_last_node(list_t *p_list, node_t **pp_last_node)
{
	node_t *p_run = NULL;
	p_run = p_list;
	while(p_run->next != NULL)
		p_run = p_run->next;
	*pp_last_node = p_run;
}

void generic_insert(node_t *p_beg, node_t *p_mid, node_t *p_end)
{
	p_mid->next = p_end;
	p_mid->prev = p_beg;

	if(p_beg != NULL)
		p_beg->next = p_mid;

	if(p_end != NULL)
		p_end->prev = p_mid;
}

void generic_delete(node_t *p_delete_node)
{
	if(p_delete_node->prev != NULL)
		p_delete_node->prev->next = p_delete_node->next;
	if(p_delete_node->next != NULL)
		p_delete_node->next->prev = p_delete_node->prev;
	free(p_delete_node);
}

node_t *search_node(list_t *p_list, data_t search_data)
{
	node_t *p_run = NULL;
	for(p_run = p_list->next; p_run != NULL; p_run = p_run->next)
	{
		if(p_run->data == search_data)
			return p_run;
	}
	return NULL;
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
	return p;
}

