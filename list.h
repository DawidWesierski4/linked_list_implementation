#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define NUMBER_OF_TPID_VALUES 3
#define TPID_MAX_LENGHT 7

struct linked_vlan_list
{
    struct linked_vlan_list* next;
    struct linked_vlan_list* before;
    char tpid[TPID_MAX_LENGHT];
    unsigned short int vlan_id;
};

const char allowable_tpid_values[NUMBER_OF_TPID_VALUES][TPID_MAX_LENGHT] = {
    "0x8100", "0x9100", "0x88a8"
};


//for linked_vlan_list its 0<vlan_id<4096 tpid from allowable_tpid array
bool list_check_is_data_correct(int value_vlan_id, char* tpid)
{
    int i;

    if (value_vlan_id < 0 || value_vlan_id > 4096)
        return false;

    //iterating and checking our tpid is in the allowable tpid values 
    for (i = 0; i < NUMBER_OF_TPID_VALUES; i++)
    {
        if (!strcmp(tpid, allowable_tpid_values[i]))
            return true;
    }
    return false;
}


//this moves the pointer to the end of the list
struct linked_vlan_list* vlan_last_list_element (struct linked_vlan_list *list)
{
    if (!list)
        return NULL;

    while (list->next)
        list = list->next;

    return list;
}

//adds the value AFTER the pointed value changes the pointer to the pointer to
//the new value 
bool vlan_add_value_linked_vlan_list(struct linked_vlan_list **list,
                                    int value_vlan_id, char *tpid) 
{
    struct linked_vlan_list *auxiliary;

    auxiliary = 
        (struct linked_vlan_list*) malloc(sizeof(struct linked_vlan_list));

    if(!auxiliary)
    {
        printf("---ERROR ALOCATION OF THE MEMORY FAILED---\n");
        return false;
    }

    auxiliary->before = (*list);
    strcpy(auxiliary->tpid,tpid);
    auxiliary->vlan_id = value_vlan_id;

    if(*list != NULL)
    {
        if((*list) -> next == NULL)
            auxiliary->next = NULL;
        else
            auxiliary->next = (*list)->next;

        auxiliary->before = (*list);

        (*list)->next = auxiliary;
    }

    (*list) = auxiliary;
    return true; //means terminate without errors
}


//option 2
bool vlan_delete_value_linked_vlan_list(struct linked_vlan_list **list)
{
    if(*list == NULL)
        return false;

    if((*list)->before == NULL && (*list)->next == NULL)
    {
        free(*list);
        *list = NULL;
        return true;
    }

    if((*list)->before)
        (*list)->before->next = (*list)->next;

    if((*list)->next)
        (*list)->next->before = (*list)->before;
    
    free(*list);
    return true;
}


//frees the memory from the pointer to the end to the list
void delete_linked_vlan_list(struct linked_vlan_list *list)
{
    if (list == NULL)
        return;

    struct linked_vlan_list *auxiliary;

    if(list->before)
        list->before->next = NULL;

    while (list != NULL)
    {
        auxiliary = list;
        list = list->next;
        free(auxiliary);
    }
}