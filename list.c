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
#include "list.h"


void print_menu(void)
{
    printf("\n"
    "---INPUT OPTION YOU WANT TO EXECUTE---\n"
    "0 - Help\n"
    "1 - Add value to theg array \n"
    "2 - Delete value from the array \n"
    "3 - Display values from the array \n"
    "4 - Delete the whole array\n"
    "5 - Delete the whole array, release the memory and exit the program\n\n");
}


void print_help(void) 
{
    printf("---DESCRIPTION OF THE OPTIONS--- \n"
    "1 - Add value to the array \n"
    "This option makes you input 2 values - Vlan id and tpid (tpid should be \n"
    "one of the 3 allowable Tpid values - \"0x8100\", \"0x9100\", \"0x88a8\")\n"
    "\n"
    "2 - Delete Value from the array \n"
    "This option lets you delete value from the array. \n"
    "\n"
    "3 - Print the array \n "
    "This option prints every value that you have added to the array. \n"
    "\n"
    "4 - Delete the array and clean the memory \n "
    "This option lets you release the memory that was taken for this array \n"
    "and also deletes the whole array. \n"
    "5 - Exit the program (it also releses all the memory taken \n"
    "by the program\n");
}


void print_values_linked_vlan_list(struct linked_vlan_list *list)
{
    if (list == NULL)
    {
        printf("---NO VALUES TO PRINT---\n");
        return;
    }

    printf("---PRINTING VALUES---\n");
    do
    {
        printf("\n%10s %3hu\n", "vlan id", list->vlan_id);
        printf("%10s %3s\n", "tpid", list->tpid);
        list = list->next;
    } while (list != NULL);
}


bool delete_value_linked_vlan_list(struct linked_vlan_list **list_root,
                                    struct linked_vlan_list **list_leaf)
{
    if (*list_root == NULL)
    {
        printf("---LIST IS EMPTY---\n");
        return false;
    }

    struct linked_vlan_list *list = *list_root;
    struct linked_vlan_list *aux;
    int id_to_delete;
    bool value_found = false;

    printf("---DELETING VALUES---\n"
    "which value do you want to delete ?\n\n");
    print_values_linked_vlan_list(list);
    printf("\nValue: ");
    scanf("%u",&id_to_delete);
    printf("\n");

    if (id_to_delete < 0 || id_to_delete > 4096)
    {
        printf("---ERROR INDEX EXCEEDS ALLOWABLE VALUES---\n\n");
        return false;
    }

    while (list != NULL)
    {
        if (list->vlan_id != id_to_delete)
        {
            (list) = (list)->next;
            continue;
        }

        if(list->before == NULL)
            *list_root = list->next;

        if(list->next == NULL)
            *list_leaf = list->before;

        aux = list->next;
        if (vlan_delete_value_linked_vlan_list(list))
        {
            value_found = true;
            list = aux;
            continue;
        }

        //if the value of the root was changed and deleting the first value
        //failed then we need to move the root back or leaf up
        if(!(*list_root)->before)
            (*list_root)=(*list_root)->before;

        if(!(*list_leaf)->next)
            (*list_leaf) = (*list_leaf)->next;

        printf("---FAILED TO DELETE THE VALUE---");
        return false;
    }

    if(value_found)
    {
        printf("---VALUES DELETED---\n");
        return true;
    }
    else
    {
        printf("---VALUE WITH THIS ID NOT FOUND---\n");
        return false;
    }

}


bool add_value_linked_vlan_list(struct linked_vlan_list **list)
{
    short unsigned int value_vlan_id;
    char tpid[TPID_MAX_LENGHT];

    printf("---ADDING VALUES---\n");
    printf("1 - input Vlan ID\n");
    scanf("%hu", &value_vlan_id);
    printf("2 - input tpid\n");
    scanf("%s", tpid);

    if (!vlan_list_check_is_data_correct(value_vlan_id,tpid))
    {
        printf("\n---ERROR INCORECT ID OR VLAN VALUE---\n");
        return false;
    }

    if(!vlan_add_value_linked_vlan_list(list,value_vlan_id,tpid))
    {
        printf("\n---ERROR ADDING THE VALUE FAILED---\n");
        return false;
    }

    printf("---VALUE ADDED---\n");
    return true; //means terminate without errors
}


bool function_choice(unsigned short int choice,
                    struct linked_vlan_list **vlan_list,
                    struct linked_vlan_list **vlan_list_root)
{
    switch (choice)
    {
        case 0:
            print_help();
            break;
        case 1:
            if (!add_value_linked_vlan_list(vlan_list))
                printf("---ADDING FAILED---\n");
            else
            {
                if (*vlan_list_root == NULL) 
                    *vlan_list_root = *vlan_list; // setting the root
            }
            break;
        case 2:
            if (!delete_value_linked_vlan_list(vlan_list_root, vlan_list))
                printf("---DELETING FAILED---\n");
            break;
        case 3:
            print_values_linked_vlan_list(*vlan_list_root);
            break;
        case 4:
            vlan_delete_linked_vlan_list(*vlan_list_root);
            *vlan_list_root = NULL;
            *vlan_list = NULL;
            break;
        case 5:
            vlan_delete_linked_vlan_list(*vlan_list_root);
            return false; //exiting
        default:
            printf("---ERROR WRONG INPUT OPTION TRY AGAIN---\n");
    }
    return true;
}


int main(void)
{
    struct linked_vlan_list *vlan_list;
    struct linked_vlan_list *vlan_list_root;
    unsigned short int choice;
    char buffer_eater; //this value is added to deal with c buffer

    vlan_list_root = NULL;
    vlan_list = NULL;
    choice = 0;

    while (true)
    {
        print_menu();
        if (!scanf("%hu", &choice))
        {
            printf("---ERROR WHILE READING THE INPUT OPTION TRY AGAIN---\n\n");
            while ((buffer_eater = getchar()) != '\n' || buffer_eater != EOF);
        }

        if(!function_choice(choice, &vlan_list, &vlan_list_root))
        {
            printf("\n---EXITING---\n");
            break;
        }
    }

    return 0;
}