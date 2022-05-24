/*===================================================================================
* Title: Linked list implementation concept 
*
* Author: Dawid WÄsierski
* Language: C
* To Compile: Microsoft Visual Studio Community 2022 (64-bit) Version 17.2
* Version: 0.0.0.1
* Date: 24.05.2022
*
* ----------------------------------------------------------------------------------
* Description:
* this program shows the implementation of the linked list concept it works similar
* to stack the memory is dynamicly allocated so but you can only get 
*
*==================================================================================*/
#include <stdio.h>

struct linked_vlan_list
{
	unsigned short int VLAN_ID;
	char* TPID;
	struct linked_list* next;
};

static char* allowable_tpid_values[] = {
	"0x8100", "0x9100", "0x88a8"
};


print_wrong_input_data_mssg(void)
{
	printf("-----------------------------------------------\n");
	printf("----------WRONG-INPUT-DATA-TRY-AGAIN-----------\n");
	printf("-----------------------------------------------\n");
}


void print_menu(void)
{
	printf("-----------------------------------------------\n");
	printf("------IMPUT-OPTION-YOU-WANT-TO-EXECUTE---------\n");
	printf("0-HELP \n");
	printf("1-ADD TO THE ARRAY \n");
	printf("2-DELETE FROM THE ARRAY \n");
	printf("3-PRINT THE ARRAY \n");
	printf("4-SORT ARRAY \n");
	printf("5-CLEAN ARRAY / EXIT \n");
	printf("-----------------------------------------------\n");
}

//option 0
void print_help(void) 
{
	printf("-----------------------------------------------\n");
	printf("----------DESCRIPTION-OF-THE-OPTIONS-----------\n");
	printf("1-ADD TO THE ARRAY \n");
	printf("This option make you turn in 2 values Vlan Id  \n");
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
	printf("-----------------------------------------------\n");
}


//option 1
void add_value_vlan_linked_list(struct vlan_linked_list* stack) 
{
	printf("-----here will be adding values alhorithm------\n");
}


//option 2
void delete_value_vlan_linked_list(struct vlan_linked_list* stack)
{
	printf("--------here will be deleteing algorithm-------\n");
}


//option 3
void print_value_vlan_linked_list(struct vlan_linked_list* stack)
{
	printf("--------here will be printing  algorithm-------\n");
}


//option 4
void sort_value_vlan_linked_list(struct vlan_linked_list* stack)
{
	printf("---------here will be sorting algorithm--------\n");
}


//option 5
void delete_vlan_linked_list(struct vlan_linked_list* stack)
{
	printf("-here will be algorithm for deleting / cleaining memory-\n");
}

int main(void)
{
	struct linked_vlan_list vlan_stack;
	unsigned short int choice = 0;

	while (choice != 5)
	{
		print_menu();
		if (scanf("%hu", choice))
		{
			switch (choice)
			{
			case 0:
				print_help();
				break;
			case 1:
				add_value_vlan_linked_list(&vlan_stack);
				break;
			case 2:
				delete_value_vlan_linked_list(&vlan_stack);
				break;
			case 3:
				print_values_vlan_linked_list(&vlan_stack);
				break;
			case 4:
				sort_values_vlan_linked_list(&vlan_stack);
				break;
			case 5:
				delete_vlan_linked_list(&vlan_stack);
				break;
			default:
				print_wrong_input_data_mssg();
			}
		}
		else
			print_wrong_input_data_mssg();
	}
	return 0;
}