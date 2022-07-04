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
#include "Header.h"


void print_wrong_input_data_mssg(void)
{
	printf("----------WRONG-INPUT-DATA-TRY-AGAIN-----------\n");
	printf("\n");
}


void print_menu(void)
{
	printf("\n");
	printf("------IMPUT-OPTION-YOU-WANT-TO-EXECUTE---------\n");
	printf("0-HELP \n");
	printf("1-ADD TO THE ARRAY \n");
	printf("2-DELETE FROM THE ARRAY \n");
	printf("3-PRINT THE ARRAY \n");
	printf("4-SORT ARRAY \n");
	printf("5-CLEAN ARRAY / EXIT \n");
	printf("\n");
}


//option 0
void print_help(void) 
{
	printf("\n");
	printf("----------DESCRIPTION-OF-THE-OPTIONS-----------\n");                                 
	printf("1-ADD TO THE ARRAY \n");
	printf("This option makes you innput 2 values - Vlan Id  \n");
	printf("and TPID (TPID should be one of the 3 values   \n");
	printf("\"0x8100\", \"0x9100\", \"0x88a8\"\n");
	printf("\n");
	printf("2-DELETE FROM THE ARRAY \n");
	printf("this option delets the last added value to \n");
	printf("the array, you can only delete the last value\n");
	printf("\n");
	printf("3-PRINT THE ARRAY \n");
	printf("this function prints every value in the array \n");
	printf("from the newest to the oldest\n");
	printf("\n");
	printf("4-SORT ARRAY \n");
	printf("this functions sorts the inputed array in \n");
	printf("ascending order if the ID is the same the \n");
	printf("second criteria to for sorting is TPID value\n");
	printf("(also in ascending order\n");
	printf("\n");
	printf("5-CLEAN ARRAY / EXIT \n");
	printf("releses the memory ocupied by the program then \n");
	printf("exicts from the program\n");
	printf("\n");
}


//for linked_vlan_list its 0<VLAN_ID<4096 TPID from allowable_tpid array
bool check_is_data_correct(struct linked_vlan_list tested_value)
{
	if (tested_value.VLAN_ID >= 0 &&
		tested_value.VLAN_ID <= 4096)
	{
		//iterating and checking our TPID is in the allowable tpid values 
		for (int i = 0; i < number_of_tpid_values; i++)
		{
			if (!strcmp(tested_value.TPID, allowable_tpid_values[i]))
			{
				printf("-------------DATA-VALIDATION-SUCESFOUL-------------\n");
				return 0;
			}
		}
	}
	return 1;
}



//option 1
bool add_value_linked_vlan_list(struct linked_vlan_list** stack) 
{
	struct linked_vlan_list* auxiliary;
	auxiliary = (struct linked_vlan_list*)malloc(sizeof(struct linked_vlan_list));
	printf("-----------------ADDING-VALUES-----------------\n");
	if (auxiliary!=NULL)
	{
		printf("1 - input Vlan ID\n");
		scanf("%hu", &auxiliary->VLAN_ID);
		printf("2 - input TPID\n");
		scanf("%s", auxiliary->TPID);
		if (!check_is_data_correct(*auxiliary))
		{
			auxiliary->next = (*stack);
			(*stack) = auxiliary;
			return true; //means terminate without errors
		}
	}
	else
		printf("------ERROR DURING ALLOCATION OF THE MEMORY FOR NEW VALUE--------\n");
	while (getchar() != '\n'); //clear buffer in case excesive input data 
	print_wrong_input_data_mssg();
	return false;
}


//option 1
bool init_linked_vlan_list(struct linked_vlan_list** stack)
{
	*stack = (struct linked_vlan_list*)malloc(sizeof(struct linked_vlan_list));
	printf("-----------------ADDING-VALUES-----------------\n");
	if (*stack != NULL)
	{
		printf("1 - input Vlan ID\n");
		scanf("%hu", &(*stack)->VLAN_ID);
		printf("2 - input TPID\n");
		scanf("%s", (*stack)->TPID);
		(*stack)->next = NULL;
		if (!check_is_data_correct(*(*stack)))
			return true; 
	}
	else
		printf("-ERROR DURING INITIALIZATION ALLOCATION OF THE MEMORY FAILED-\n");
	while (getchar() != '\n'); //clear buffer in case excesive input data 
	*stack = NULL;
	print_wrong_input_data_mssg();
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
			printf("-----------------VALUE-DELETED---------------\n");
		}
		else
		{
			free(*stack);
			*stack = NULL;
			printf("-----------------ARRAY-EMPTY---------------");
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
		printf("-----------------PRINTING-VALUES---------------\n");
		while (stack->next != NULL) //do while basicly 
		{
			printf("value %3hu\n", counter++);
			printf("%10s %3hu\n", "vlan id", stack->VLAN_ID);
			printf("%10s %3s\n", "TPID", stack->TPID);
			stack = stack->next;
		}
		printf("value %3hu\n", counter++);
		printf("%10s %3hu\n", "vlan id", stack->VLAN_ID);
		printf("%10s %3s\n", "TPID", stack->TPID);
		printf("\n");
		return true;
	}
}


//returns true when vlan 1 > vlan 2 (they are compared based on ID if the ID 
//are the same they are compared based on the TPID)
short int compare_vlan(struct linked_vlan_list vlan1, 
   struct linked_vlan_list vlan2)
{
	if (vlan1.VLAN_ID > vlan2.VLAN_ID)
		return 1;
	else if (vlan1.VLAN_ID == vlan2.VLAN_ID)
	{
		//this part is comparing by TPID
		if (strcmp(vlan1.TPID, vlan2.TPID) < 1)
			return -1;
		else if (strcmp(vlan1.TPID, vlan2.TPID) == 0)
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
		vlan1->VLAN_ID = vlan2->VLAN_ID;
		strcpy(vlan1->TPID, vlan2->TPID);

		vlan2->VLAN_ID = auxiliary->VLAN_ID;
		strcpy(vlan2->TPID, auxiliary->TPID);
	}
}


//option 4 (sorted by bubble sort)
bool sort_values_linked_vlan_list(struct linked_vlan_list* stack,unsigned int number_of_nodes)
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


//option 5
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
		printf("--------------MEMORY-CLEASENED------------\n");
	}
}


int main(void)
{
	struct linked_vlan_list* vlan_stack;
	vlan_stack = NULL;
	char buffer_eater; //this value is added to deal with c buffer 
	unsigned int number_of_nodes = 0;
	unsigned short int choice = 0;
	while (choice != 5)
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
					if (!init_linked_vlan_list(&vlan_stack))
						printf("--------------INITIALIZATION-FAILED------------\n");
					else
						number_of_nodes = 1;
				}
				else
				{
					if (!add_value_linked_vlan_list(&vlan_stack))
						printf("-----------------ADDING-FAILED-----------------\n");
					else
						number_of_nodes++;
				}
				break;
			case 2:
				if (!delete_value_linked_vlan_list(&vlan_stack))
					printf("------------------NO-VALUES-TO-DELETE----------------\n");
				else
					number_of_nodes--;
				break;
			case 3:
				if (!print_values_linked_vlan_list(vlan_stack))
					printf("------------------NO-VALUES-TO-PRINT----------------\n");
				break;
			case 4:
				if (!sort_values_linked_vlan_list(vlan_stack,number_of_nodes))
					printf("------------------NO-VALUES-TO-SORT----------------\n");
				break;
			case 5:
				delete_linked_vlan_list(vlan_stack);
				break;
			default:
				print_wrong_input_data_mssg();
			}
		}
		else
		{
			//this will take the remaining character from buffer
			while ((buffer_eater = getchar()) != '\n' || buffer_eater != EOF);		
			print_wrong_input_data_mssg();
		}
	}
	return 0;
}