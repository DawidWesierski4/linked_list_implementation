#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"

const char allowable_tpid_values[NUMBER_OF_TPID_VALUES][TPID_MAX_LENGHT] = {
    "0x8100", "0x9100", "0x88a8"
};


bool vlan_list_check_is_data_correct(int value_vlan_id, char *tpid)
{
    int i;

    if (value_vlan_id < 0 || value_vlan_id > 4096)
        return false;

    //iterating and checking if our tpid is in the allowable tpid values 
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
        return false;

    auxiliary->next = NULL;
    auxiliary->before = NULL;
    strcpy(auxiliary->tpid, tpid);
    auxiliary->vlan_id = value_vlan_id;

    if(*list != NULL)
    {
        if((*list)->next == NULL)
            auxiliary->next = NULL;
        else
            auxiliary->next = (*list)->next;

        auxiliary->before = (*list);

        (*list)->next = auxiliary;
    }

    (*list) = auxiliary;
    return true; //means terminate without errors
}


//deletes the value that the pointer is pointing to, also patches up the list
bool vlan_delete_value_linked_vlan_list(struct linked_vlan_list *list)
{
    if(list == NULL)
        return false;

    //case when there is only one value in linked vlan list
    if((list)->before == NULL && (list)->next == NULL)
    {
        free(list);
        return true;
    }

    if((list)->before)
        (list)->before->next = (list)->next;
    else
        (list)->next->before = NULL;

    if((list)->next)
        (list)->next->before = (list)->before;
    else
        (list)->before->next = NULL;

    free(list);
    return true;
}


//frees the memory from the pointer to the end to the list
void vlan_delete_linked_vlan_list(struct linked_vlan_list *list)
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