#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#define number_of_tpid_values 3

struct linked_vlan_list
{
	unsigned short int VLAN_ID;
	char TPID[7];
	struct linked_list* next;
};

const char allowable_tpid_values[number_of_tpid_values][7] = {
	"0x8100", "0x9100", "0x88a8"
};