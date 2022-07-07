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
   "4 - Delete the whole array, release the memory and exit the program\n");
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
   for (int i = 0; i < NUMBER_OF_TPID_VALUES; i++)
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
         (*stack)->next = auxiliary;
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

//option 2
bool delete_value_linked_vlan_list(struct linked_vlan_list** stack)
{
	if (*stack != NULL)
	{
		if ((*stack)->next != NULL)
		{
			struct linked_vlan_list* auxiliary = *stack;
			*stack = (*stack)->next;
			free(auxiliary);
			printf("---VALUE DELETED--\n");
		}
		else
		{
			free(*stack);
			*stack = NULL;
			printf("---ARRAY IS EMPTY---");
		}
		return true;
	}
	return false;
}


//option 3
bool print_values_linked_vlan_list(struct linked_vlan_list* stack)
{
	unsigned short counter = 1;
	if (stack == NULL)
		return false;
	else
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
		return true;
	}
}

/* THIS IS OPTIONAL SORT ALGORITHM 

//returns true when vlan 1 > vlan 2 (they are compared based on ID if the ID 
//are the same they are compared based on the tpid)
short int compare_vlan(struct linked_vlan_list vlan1, 
   struct linked_vlan_list vlan2)
{
	if (vlan1.vlan_id > vlan2.vlan_id)
		return 1;
	else if (vlan1.vlan_id == vlan2.vlan_id)
	{
		//this part is comparing by tpid
		if (strcmp(vlan1.tpid, vlan2.tpid) < 1)
			return -1;
		else if (strcmp(vlan1.tpid, vlan2.tpid) == 0)
			return 0;
		else
			return 1;
	}
	else
		return -1;
}




void swap_vlan(struct linked_vlan_list* vlan1, struct linked_vlan_list* vlan2)
{
	struct linked_vlan_list* auxiliary = 
   (struct linked_vlan_list*)malloc(sizeof(struct linked_vlan_list));
	if (auxiliary != NULL)
	{
		*auxiliary = *vlan1;
		vlan1->vlan_id = vlan2->vlan_id;
		strcpy(vlan1->tpid, vlan2->tpid);

		vlan2->vlan_id = auxiliary->vlan_id;
		strcpy(vlan2->tpid, auxiliary->tpid);
	}
}


bool sort_values_linked_vlan_list(struct linked_vlan_list* stack,
unsigned int number_of_nodes)
{
	struct linked_vlan_list* auxiliary;
	if (stack != NULL)
	{
		for (unsigned int i = 0; i < number_of_nodes-1; i++)
		{
			auxiliary = stack;
			for (unsigned int j = 0; j < number_of_nodes - i - 1; j++)
			{
					if (compare_vlan(*auxiliary, *auxiliary->next) > 0)
						swap_vlan(auxiliary, auxiliary->next);
				auxiliary =auxiliary->next;
			}
		}
		return true;
	}
	return false;
}
*/


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
	struct linked_vlan_list* vlan_stack, *vlan_stack_root;

	vlan_stack = NULL;
	char buffer_eater; //this value is added to deal with c buffer 

	unsigned int number_of_nodes = 0;

	unsigned short int choice = 0;

	while (choice != 4)
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
				if (vlan_stack == NULL)
               {
				   vlan_stack = (struct linked_vlan_list*)malloc(sizeof(struct linked_vlan_list));
               vlan_stack->before = NULL;
               vlan_stack->next = NULL;
               vlan_stack_root = vlan_stack;
               }
            if (vlan_stack != NULL &&!add_value_linked_vlan_list(&vlan_stack))
               printf("---ADDING FAILED---\n");
            else
               number_of_nodes++;
				break;
			case 2:
				if (!delete_value_linked_vlan_list(&vlan_stack))
					printf("---NO VALUES TO DELETE---\n");
				else
					number_of_nodes--;
				break;
			case 3:
				if (!print_values_linked_vlan_list(vlan_stack_root->next))
					printf("---NO VALUES TO PRINT---\n");
				break;
			case 4:
				delete_linked_vlan_list(vlan_stack);
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