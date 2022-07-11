/*==============================================================================
* Title: Linked list implementation concept 
*
* Author: Dawid Wesierski
* Language: C
* To Compile: gcc 11.2.0
* Version: 0.1.0.0
* Date: 08.07.2022
*
* ------------------------------------------------------------------------------
* 
* Description:
* this program shows the implementation of the linked list concept it works 
* similary to list the memory is dynamicly allocated you can print the value
*     
* 
*=============================================================================*/
#include "header.h"


//for linked_vlan_list its 0<vlan_id<4096 tpid from allowable_tpid array
bool check_is_data_correct(struct linked_vlan_list tested_value)
{
    if (tested_value.vlan_id < 0 || tested_value.vlan_id > 4096)
        return false;

    //iterating and checking our tpid is in the allowable tpid values 
    int i;

    for (i = 0; i < NUMBER_OF_TPID_VALUES; i++)
    {
        if (!strcmp(tested_value.tpid, allowable_tpid_values[i]))
        {
            printf("---DATA VALIDATION SUCCESSFUL---\n");
            return true;
        }
    }
    return false;
}


bool add_value_linked_vlan_list(struct linked_vlan_list **list) 
{
     struct linked_vlan_list *auxiliary;
    
    auxiliary = 
        (struct linked_vlan_list*)malloc(sizeof(struct linked_vlan_list));
    
     printf("---ADDING VALUES---\n");
    if (auxiliary!=NULL)
    {
        printf("1 - input Vlan ID\n");
        scanf("%hu", &auxiliary->vlan_id);
        printf("2 - input tpid\n");
        scanf("%s", auxiliary->tpid);
        if (check_is_data_correct(*auxiliary))
        {
            auxiliary->before = (*list);
            if((*list)->next == NULL)
                auxiliary->next = NULL;
            else
                auxiliary->next = (*list)->next;
            if(*list != NULL)
            {
                (*list)->next = auxiliary;
            }
            (*list) = auxiliary;
            return true; //means terminate without errors
        }
    }

    else
    {
        printf("---ERROR UNABLE TO ALLOCATE THE"
        " MEMORY FOR THE NEW VALUE---\n");
        free(auxiliary);
    }
    while (getchar() != '\n'); //clear buffer in case excesive input data 
    print_wrong_input_data_msg();
    return false;
}


void print_values_linked_vlan_list(struct linked_vlan_list* list)
{
    unsigned short counter = 1;
    if (list != NULL)
    {
        printf("---PRINTING VALUES---\n");
        do
        {
            printf("value %3hu\n", counter++);
            printf("%10s %3hu\n", "vlan id", list->vlan_id);
            printf("%10s %3s\n", "tpid", list->tpid);
            list = list->next;
        } while (list->next != NULL);
        printf("\n");
    }
    else
        printf("---NO VALUES TO PRINT---\n");
    
}


int count_and_print_values_linked_vlan_list(struct linked_vlan_list* list)
{
    unsigned short counter = 0;
    if (list != NULL)
    {
        do
        {
            printf("value %3hu\n", ++counter);
            printf("%10s %3hu\n", "vlan id", list->vlan_id);
            printf("%10s %3s\n", "tpid", list->tpid);
            list = list->next;
        }while (list->next != NULL);
    }
    else
        printf("---NO VALUES TO PRINT---\n");

    return counter;
}

//option 2
bool delete_value_linked_vlan_list(
    struct linked_vlan_list **list_root,
    struct linked_vlan_list **list_leaf)
{
    struct linked_vlan_list* list = *list_root;
    int size = 0;

    if (list != NULL)
    {
        printf("---DELETING VALUES---\n"
        "which value do you want to delete ?\n\n");
        size = count_and_print_values_linked_vlan_list(list);
        printf("input the value number of the deleted value \n\n");
        unsigned int index_to_delete;

        scanf("%u",&index_to_delete);
        int i;
        if(index_to_delete>0)
        {
            //here we are moving our auxiliary pointer to the number of the  
            //value we want to delete 
            for(i=1;(i<index_to_delete && list && index_to_delete < size);i++)
                list=list->next;

        }
        else
            return false;

        /*
        *  we are doing something like this 
        *  
        *  BEFORE
        *  node1
        *      before    -> node0
        *      next      -> deletenode
        *  deltednode
        *      before    ->node1
        *      next      ->node2
        *  node2
        *      before    ->deletenode
        *      next      ->node2
        * 
        * AFTER
        *  node1
        *      before    -> node0
        *      next      -> node2
        *  deltednode
        *      --MEMORY FREE
        *  node2
        *      before    ->node1
        *      next      ->node2
        */

        if(size > 1)
        {
            if(list->before != NULL)
                list->before->next = list->next; 
            else
            {
                list->next->before = NULL;
                (*list_root) = list->next;
            }

            if(list->next != NULL)
                list->next->before = list->before;
            else
            {
                list->before->next = NULL;
                (*list_leaf) = list->before;
            }
        }
        else
        {
            *list_root = NULL;
            *list_leaf = NULL;
        }

        free(list);
        printf("---VALUE DELETED---\n");
        return true;
    }
    else
    {
        return false;
    }
}


void delete_linked_vlan_list(struct linked_vlan_list *list)
{
    if (list != NULL)
    {
        while(list->next != NULL)
        {
            struct linked_vlan_list* auxiliary = list;
            list = list->next;
            free(auxiliary);
        }

        free(list);
        printf("---MEMORY CLEASENED---\n");
    }
}