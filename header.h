#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define NUMBER_OF_TPID_VALUES 3
#define TPID_MAX_LENGHT 7

struct linked_vlan_list
{
    unsigned short int vlan_id;
    char tpid[TPID_MAX_LENGHT];
    struct linked_vlan_list* next;
    struct linked_vlan_list* before;
};

const char allowable_tpid_values[NUMBER_OF_TPID_VALUES][TPID_MAX_LENGHT] = {
    "0x8100", "0x9100", "0x88a8"
};