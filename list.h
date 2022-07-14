#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define NUMBER_OF_TPID_VALUES 3
#define TPID_MAX_LENGHT 7

struct linked_vlan_list
{
    struct linked_vlan_list *next;
    struct linked_vlan_list *before;
    char tpid[TPID_MAX_LENGHT];
    unsigned short int vlan_id;
};


//for linked_vlan_list its 0<vlan_id<4096 tpid from allowable_tpid array
bool vlan_list_check_is_data_correct(int value_vlan_id, char *tpid);


//this moves the pointer to the end of the list
struct linked_vlan_list* vlan_last_list_element (struct linked_vlan_list *list);

//adds the value AFTER the pointed value changes the pointer to the pointer to
//the new value 
bool vlan_add_value_linked_vlan_list(struct linked_vlan_list **list,
                                    int value_vlan_id, char *tpid);

//deletes the value that the pointer is pointing to, also patches up the list
bool vlan_delete_value_linked_vlan_list(struct linked_vlan_list *list);


//frees the memory from the pointer to the end to the list
void vlan_delete_linked_vlan_list(struct linked_vlan_list *list);