/*==============================================================================
* Title: Linked list implementation concept 
*
* Author: Dawid Wesierski
* Language: C
* To Compile: Microsoft Visual Studio Community 2022 (64-bit) Version 17.2
* Version: 0.0.1.1
* Date: 30.05.2022
*
* ------------------------------------------------------------------------------
* 
* Description:
* this program shows the implementation of the linked list concept it works 
* similar to stack the memory is dynamicly allocated so but you can only get out
* one value  from the TOP of the stack 
*	
* 
*=============================================================================*/
#include "header.h"


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


//option 0
void print_help(void) 
{
	printf("---DESCRIPTION OF THE OPTIONS--- \n"
   "1 - Add value to the array \n"
   "This option makes you input 2 values - Vlan id and tpid (tpid should be \n"
   "one of the 3 allovable Tpid values - \"0x8100\", \"0x9100\", \"0x88a8\") \n"
   "\n"
   "2 - Delete Value from the array \n"
   "This option lets you delete value from the array. \n"
   "\n"
   "3 - Print the array \n "
   "This option prints every value that you have added to the array. \n"
   "\n"
   "4 - Delete the array and clean the memory \n "
   "This option lets you release the memory that was taken for this array and \n"
   "also deletes the whole array. \n");
}


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


//option 1
bool add_value_linked_vlan_list(struct linked_vlan_list** stack) 
{
	struct linked_vlan_list* auxiliary;
   auxiliary = (struct linked_vlan_list*)malloc(sizeof(struct linked_vlan_list));
	printf("---ADDING VALUES---\n");
	if (auxiliary!=NULL)
	{
		printf("1 - input Vlan ID\n");
		scanf("%hu", &auxiliary->vlan_id);
		printf("2 - input tpid\n");
		scanf("%s", auxiliary->tpid);
		if (check_is_data_correct(*auxiliary))
		{
			auxiliary->before = (*stack);
         auxiliary->next = NULL;
         if(*stack != NULL)
         {
            (*stack)->next = auxiliary;
         }
         (*stack) = auxiliary;
			return true; //means terminate without errors
		}
	}
	else
   {
		printf("---ERROR UNABLE TO ALLOCATE THE MEMORY FOR THE NEW VALUE---\n");
      free(auxiliary);
   }
	while (getchar() != '\n'); //clear buffer in case excesive input data 
	print_wrong_input_data_msg();
	return false;
}


//option 3
void print_values_linked_vlan_list(struct linked_vlan_list* stack)
{
	unsigned short counter = 1;
	if (stack != NULL)
   {
   printf("---PRINTING VALUES---\n");
   while (stack->next != NULL) //do while basicly 
   {
      printf("value %3hu\n", counter++);
      printf("%10s %3hu\n", "vlan id", stack->vlan_id);
      printf("%10s %3s\n", "tpid", stack->tpid);
      stack = stack->next;
   }
   printf("value %3hu\n", counter++);
   printf("%10s %3hu\n", "vlan id", stack->vlan_id);
   printf("%10s %3s\n", "tpid", stack->tpid);
   printf("\n");
   }
   else
   	printf("---NO VALUES TO PRINT---\n");
   
}


//option 2
bool delete_value_linked_vlan_list(
   struct linked_vlan_list** stack_root,
   struct linked_vlan_list** stack_leaf,
   int size)

{
   struct linked_vlan_list* stack = *stack_root;
   
   if (stack != NULL && size > 0)
   {
      printf("---DELETING VALUES---\n"
      "which value do you want to delete ?\n\n");
      print_values_linked_vlan_list(stack);
      printf("input the value number of the deleted value \n\n");
      unsigned int index_to_delete;

      scanf("%u",&index_to_delete);
      int i;
      if(index_to_delete<=size)
      {
         //here we are moving our auxiliary pointer to the number of the value 
         //we want to delete 
         for(i=1;(i<index_to_delete && stack && index_to_delete < size);i++)
            stack=stack->next;

      }
      else
         return false;

      /*
      *  we are doing somthing like this 
      *  
      *  BEFORE
      *  node1
      *     before   -> node0
      *     next     -> deletenode
      *  deltednode
      *     before   ->node1
      *     next     ->node2
      *  node2
      *     before   ->deletenode
      *     next     ->node2
      * 
      * AFTER
      *  node1
      *     before   -> node0
      *     next     -> node2
      *  deltednode
      *     --MEMORY FREE
      *  node2
      *     before   ->node1
      *     next     ->node2
      */

      if(size>1)
      {
         if(stack->before!=NULL)
            stack->before->next = stack->next; 
         else
         {
            stack->next->before = NULL;
            (*stack_root) = stack->next;
         }

         if(stack->next!=NULL)
            stack->next->before = stack->before;
         else
         {
            stack->before->next = NULL;
            (*stack_leaf) = stack->before;
         }
      }
      else
      {
         *stack_root = NULL;
         *stack_leaf = NULL;
      }

      free(stack);
      printf("---VALUE DELETED---\n");
      return true;
   }
   else
   {
         return false;
   }
}


//option 4
void delete_linked_vlan_list(struct linked_vlan_list* stack)
{
	if (stack != NULL)
	{
		while(stack->next != NULL)
		{
			struct linked_vlan_list* auxiliary = stack;
			stack = stack->next;
			free(auxiliary);
		}
		free(stack);
		printf("---MEMORY CLEASENED---\n");
	}
}


int main(void)
{
	struct linked_vlan_list *vlan_stack;

   //the first value dosn't contain enything other than before->null
	struct linked_vlan_list *vlan_stack_root; 

	vlan_stack_root = NULL;
	vlan_stack = NULL;

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
            if (!add_value_linked_vlan_list(&vlan_stack))
               printf("---ADDING FAILED---\n");
            else
            {
               number_of_nodes++;
               if (vlan_stack_root == NULL)
                  vlan_stack_root = vlan_stack; // setting the root
            }
				break;
			case 2:
				if (!delete_value_linked_vlan_list(&vlan_stack_root,&vlan_stack, number_of_nodes))
					printf("---NO VALUES TO DELETE---\n");
				else
					number_of_nodes--;
				break;
			case 3:
				print_values_linked_vlan_list(vlan_stack_root);
				break;
			case 4:
				delete_linked_vlan_list(vlan_stack_root);
				break;
			default:
				print_wrong_input_data_msg();
			}
		}
		else
		{
			//this will take the remaining character from buffer
			while ((buffer_eater = getchar()) != '\n' || buffer_eater != EOF);		
			print_wrong_input_data_msg();
		}
	}
	return 0;
}