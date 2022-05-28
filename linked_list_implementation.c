/*===================================================================================
* Title: Linked list implementation concept 
*
* Author: Dawid Wesierski
* Language: C
* To Compile: Microsoft Visual Studio Community 2022 (64-bit) Version 17.2
* Version: 0.0.0.2
* Date: 24.05.2022
*
* ----------------------------------------------------------------------------------
* 
* Description:
* this program shows the implementation of the linked list concept it works similar
* to stack the memory is dynamicly allocated so but you can only get 
* 
*==================================================================================*/
#include "Header.h"

print_wrong_input_data_mssg(void)
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
	if (tested_value.VLAN_ID >= 0 ||
		tested_value.VLAN_ID <= 4096)
	{
		//iterating and checking our TPID is in the allowable tpid values 
		for (int i = 0; i < number_of_tpid_values; i++)
		{
			if (!strcmp(tested_value.TPID, allowable_tpid_values[i]))
			{
				printf("---------DATA-VALIDATION-SUCESFOUL-------------\n");
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
		scanf_s("%hu", &auxiliary->VLAN_ID);
		printf("2 - input TPID\n");
		scanf_s("%s", auxiliary->TPID, 7);
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
		scanf_s("%hu", &(*stack)->VLAN_ID);
		printf("2 - input TPID\n");
		scanf_s("%s", (*stack)->TPID, 7);
		(*stack)->next = NULL;
		if (!check_is_data_correct(*(*stack)))
			return true; //
	}
	else
		printf("------ERROR DURING INITIALIZATION ALLOCATION OF THE MEMORY FAILED--------\n");
	while (getchar() != '\n'); //clear buffer in case excesive input data 
	*stack = NULL;
	print_wrong_input_data_mssg();
	return false;
}


//option 2
void delete_value_linked_vlan_list(struct linked_vlan_list* stack)
{
	printf("--------here will be deleteing algorithm-------\n");
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
		while (stack->next != NULL)
		{
			printf("value %hu", counter++);
			printf("%10s %hu\n", "vlan id", stack->VLAN_ID);
			printf("%10s %s\n", "vlan id", stack->TPID);
			stack = stack->next;
		}
		printf("value %hu", counter++);
		printf("%10s %hu\n", "vlan id", stack->VLAN_ID);
		printf("%10s %s\n", "vlan id", stack->TPID);
		printf("\n");
		return true;
	}
}


//option 4
bool sort_values_linked_vlan_list(struct linked_vlan_list* stack)
{
	printf("---------here will be sorting algorithm--------\n");
	return 0;
}


//option 5
void delete_linked_vlan_list(struct linked_vlan_list* stack)
{
	printf("-here will be algorithm for deleting / cleaining memory-\n");
}

int main(void)
{
	struct linked_vlan_list* vlan_stack;
	vlan_stack = NULL;
	char buffer_eater = NULL; //this value is added to deal with c buffer 
	unsigned short int choice = 0;
	while (choice != 5)
	{
		print_menu();
		if (scanf_s("%hu", &choice))
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
				}
				else
				{
					if (!add_value_linked_vlan_list(&vlan_stack))
						printf("-----------------ADDING-FAILED-----------------\n");
				}
				break;
			case 2:
				delete_value_linked_vlan_list(&vlan_stack);
				break;
			case 3:
				if (!print_values_linked_vlan_list(vlan_stack))
					printf("------------------NO-VALUES-TO-PRINT----------------\n");
				break;
			case 4:
				if (!sort_values_linked_vlan_list(vlan_stack))
					printf("------------------NO-VALUES-TO-PRINT----------------\n");
				break;
			case 5:
				delete_linked_vlan_list(&vlan_stack);
				break;
			default:
				print_wrong_input_data_mssg();
			}
		}
		else
		{
			while ((buffer_eater = getchar()) != '\n' && buffer_eater != EOF);		//this will take the remaining character from buffer
			print_wrong_input_data_mssg();
		}
	}
	return 0;
}