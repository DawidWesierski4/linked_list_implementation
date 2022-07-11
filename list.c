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
#include "list.h"


void print_wrong_input_data_msg(void)
{
     printf("---WRONG INPUT DATA TRY AGAIN---\n");
     printf("\n");
}


void print_menu(void)
{
    printf("\n"
    "---INPUT OPTION YOU WANT TO EXECUTE---\n"
    "0 - Help\n"
    "1 - Add value to the array \n"
    "2 - Delete value from the array \n"
    "3 - Display values from the array \n"
    "4 - Delete the whole array, release the memory and exit the program\n\n");
}


void print_help(void) 
{
     printf("---DESCRIPTION OF THE OPTIONS--- \n"
    "1 - Add value to the array \n"
    "This option makes you input 2 values - Vlan id and tpid (tpid should be \n"
    "one of the 3 allovable Tpid values - \"0x8100\", \"0x9100\", \"0x88a8\")\n"
    "\n"
    "2 - Delete Value from the array \n"
    "This option lets you delete value from the array. \n"
    "\n"
    "3 - Print the array \n "
    "This option prints every value that you have added to the array. \n"
    "\n"
    "4 - Delete the array and clean the memory \n "
    "This option lets you release the memory that was taken for this array \n"
    "and also deletes the whole array. \n");
}


int main(void)
{
     struct linked_vlan_list *vlan_list;

    //the first value dosn't contain enything other than before->null
     struct linked_vlan_list *vlan_list_root; 

     vlan_list_root = NULL;
     vlan_list = NULL;

     char buffer_eater; //this value is added to deal with c buffer 

     unsigned int number_of_nodes = 0;

     unsigned short int choice = 0;

     while(choice != 4)
     {
        print_menu();
        if (scanf("%hu", &choice))
        {
            switch (choice)
            {
            case 0:
                print_help();
                break;
            case 1:
                if (!add_value_linked_vlan_list(&vlan_list))
                    printf("---ADDING FAILED---\n");
            else
            {
                if (vlan_list_root == NULL)
                    vlan_list_root = vlan_list; // setting the root
            }
                    break;
            case 2:
                if (!delete_value_linked_vlan_list(&vlan_list_root,&vlan_list))
                    printf("---NO VALUES TO DELETE---\n");
                else
                    number_of_nodes--;
                break;
            case 3:
                print_values_linked_vlan_list(vlan_list_root);
                break;
            case 4:
                delete_linked_vlan_list(vlan_list_root);
                break;
            default:
                print_wrong_input_data_msg();
            }
        }
          else
        {
            //this will take the remaining character from buffer
            while ((buffer_eater = getchar()) != '\n' ||
                buffer_eater != EOF);
            print_wrong_input_data_msg();
        }
    }
    return 0;
}