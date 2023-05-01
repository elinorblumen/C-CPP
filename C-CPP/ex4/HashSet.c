
#include "HashSet.h"
#include <stdlib.h>
#include "Node.h"
#include <string.h>

/**
 * @def HASH_SET_MINIMAL_CAPACITY
 * The minimal capacity of the hash set.
 * It means, the minimal number of <b> Nodes </b> the hash set has.
 */
#define HASH_SET_MINIMAL_CAPACITY 1
/**
 * @def HASH_SET_INITIAL_SIZE
 * The initial size of the hash set.
 * It means, the initial number of inserted nodes the hash set contains.
 */
#define HASH_SET_INITIAL_SIZE 0
/**
 * @def HASH_SET_INITIAL_CAP
 * The initial capacity of the hash set.
 * It means, the initial number of <b> Nodes </b> the hash set has.
 */
#define HASH_SET_INITIAL_CAP 16


/**
* Helper function that checks that non of the hash-set
    * functions are NULL
* @param hash_set the hash-set to be checked
* @return 1 if all functions are valid, 0 otherwise
*/
int check_hash_set_functions(HashSet* hash_set);

/**
 * Allocates dynamically new hash set.
 * @param hash_func a function which "hashes" keys.
 * @param value_cpy a function which copies Values.
 * @param value_cmp a function which compares Values.
 * @param value_free a function which frees Values.
 * @return pointer to dynamically allocated HashSet.
 * @if_fail return NULL or if one of the function pointers is null.
 */
HashSet *hash_set_alloc(
    HashFunc hash_func, HashSetValueCpy value_cpy,
    HashSetValueCmp value_cmp, HashSetValueFree value_free)
{
    if((hash_func)&&(value_cpy)&&(value_cmp)&&(value_free)){
            HashSet *hash_set = malloc (sizeof (HashSet));
        if(hash_set){
            hash_set->NodesList = malloc (HASH_SET_INITIAL_CAP*sizeof (Node*));
            if(!hash_set->NodesList){
                    free(hash_set);
                    return NULL;
                }
            for(int i = 0; i < HASH_SET_INITIAL_CAP; i++){
                hash_set->NodesList[i] = node_alloc (value_cpy, value_cmp, value_free);
                if(!hash_set->NodesList[i]){
                    for(int j = 0; j < i; j++){
                        free(hash_set->NodesList[i]);
                    }
                    free(hash_set->NodesList);
                    free(hash_set);
                        return NULL;
                }
            }
            hash_set->size = HASH_SET_INITIAL_SIZE;
            hash_set->capacity = HASH_SET_INITIAL_CAP;
            hash_set->hash_func = hash_func;
            hash_set->value_cpy = value_cpy;
            hash_set->value_cmp = value_cmp;
            hash_set->value_free = value_free;
            return hash_set;
        }
    }
    return NULL;
}

/**
 * Allocates dynamically new hash set with given size and capacity.
 * @param capacity new capacity
 * @param size new size
 * @param hash_func a function which "hashes" keys.
 * @param value_cpy a function which copies Values.
 * @param value_cmp a function which compares Values.
 * @param value_free a function which frees Values.
 * @return pointer to dynamically allocated HashSet.
 * @if_fail return NULL or if one of the function pointers is null.
 */
void hash_set_re_alloc(HashSet *old_hash_set,
                       unsigned int new_cap){
    HashSet * new_hash_set = hash_set_alloc(old_hash_set->hash_func,
                                            old_hash_set->value_cpy,
                                            old_hash_set->value_cmp,
                                            old_hash_set->value_free);
    if(!new_hash_set){
            return;
    }
    Node ** new_nodes_array = malloc(new_cap*sizeof(void *));
    if(!new_nodes_array){
            hash_set_free(&new_hash_set);
            return;
        }
    for(unsigned int i = 0; i < new_cap; i++){
        new_nodes_array[i] = node_alloc (new_hash_set->value_cpy,new_hash_set->value_cmp,
                                         new_hash_set->value_free);
        if(!new_nodes_array[i]){
            for(unsigned int j = 0; j < i; j++){
                    free(new_nodes_array[i]);
                }
            free(new_nodes_array);
            free(new_hash_set);
            return;
        }
    }
    for(int i = 0; i < HASH_SET_INITIAL_CAP; i++){
        free(new_hash_set->NodesList[i]);
    }
    free(new_hash_set->NodesList);
    new_hash_set->NodesList = new_nodes_array;
    new_hash_set->capacity = new_cap;
    for (size_t i = 0; i < old_hash_set->capacity; i++) {
            Node *curr_node = old_hash_set->NodesList[i];
            if (curr_node !=NULL) {
                    hash_set_insert (new_hash_set, curr_node->data);
                    node_free(&curr_node);
                }
        }
    free(old_hash_set->NodesList);
    memcpy(old_hash_set,new_hash_set,sizeof(HashSet));
    free(new_hash_set);
}

/**
 * Frees the hash set and all its elements.
 * @param p_hash_set pointer to pointer to a hash_set.
 */
void hash_set_free(HashSet **p_hash_set){

    if((p_hash_set) && (*p_hash_set)){
        if((*p_hash_set)->NodesList){
            for(size_t i = 0; i < (*p_hash_set)->capacity ; ++i){
                if(((*p_hash_set)->NodesList)[i]){
                        node_free (&(((*p_hash_set)->NodesList)[i]));
                }
            }
            free(((*p_hash_set)->NodesList));
        }
    free(*p_hash_set);
    *p_hash_set = NULL;
    }
}

/**
 * Inserts a new Value to the hash set.
 * The function inserts *new*, *copied*, *dynamically allocated* Value,
 * @param hash_set the hash set where we want to insert the new element
 * @param value a Value we would like to add to the hashset
 * @return returns 1 for successful insertion, 0 otherwise.
 */
int hash_set_insert(HashSet *hash_set, Value value){

    if(hash_set && value && check_hash_set_functions (hash_set)){
        if(hash_set_contains_value (hash_set, value)){
                return 0;
        }
        size_t hash_index;
        if((hash_set->capacity) > HASH_SET_MINIMAL_CAPACITY){
            hash_index = (hash_set->hash_func(value)) &
                ((hash_set->capacity)-1);
        }
        else{hash_index = 0;}
        for (unsigned int i = 0; i < hash_set->capacity; ++i){
            int probing = ((hash_index + (i+(i*i))/2) & ((hash_set->capacity)-1));
            Node *curr_node = hash_set->NodesList[probing];
            if(curr_node == NULL){
                hash_set->NodesList[probing] = node_alloc(hash_set->value_cpy,
                                            hash_set->value_cmp,
                                            hash_set->value_free);
                if(!hash_set->NodesList[probing]) {return 0;}
                set_node_data (hash_set->NodesList[probing], value);
                ++((hash_set->NodesList)[hash_index]->hashCount);
                ++(hash_set->size);
                if(hash_set_get_load_factor (hash_set) >=
                   HASH_SET_MAX_LOAD_FACTOR){
                        hash_set_re_alloc (hash_set,
                                           (hash_set->capacity)*
                                           HASH_SET_GROWTH_FACTOR);
                    }
                return 1;
            }
            if((hash_set->NodesList)[probing]!= NULL){
                if(((hash_set->NodesList)[probing]->data) == NULL){
                    set_node_data ((hash_set->NodesList)[probing], value);
                    ++((hash_set->NodesList)[hash_index]->hashCount);
                    ++(hash_set->size);
                    if(hash_set_get_load_factor (hash_set) >=
                       HASH_SET_MAX_LOAD_FACTOR){
                        hash_set_re_alloc (hash_set,
                                           (hash_set->capacity)*
                                               HASH_SET_GROWTH_FACTOR);
                    }
                        return 1;
                }
            }
        }
    }
    return 0;
}

/**
 * The function checks if the given value exists in the hash set.
 * @param hash_set a hash set.
 * @param value the value to be checked.
 * @return 1 if the value is in the hash set, 0 otherwise.
 */
int hash_set_contains_value(HashSet *hash_set, Value value){
    if(hash_set && value && check_hash_set_functions (hash_set) &&
    hash_set->NodesList){
        for (unsigned int i = 0; i < hash_set->capacity; i++){
            if(hash_set->NodesList[i]){
                int check = check_node ((hash_set->NodesList)[i], value);
                if (check == 1){
                        return check;
                    }
            }

        }
    }

    return 0;
}

/**
 * The function erases a Value.
 * @param hash_set a hash set.
 * @param value the value to be erased from the hashtable
 * @return 1 if the erasing was done successfully, 0 otherwise.
 */
int hash_set_erase(HashSet *hash_set, Value value){
    if(hash_set && value && hash_set->NodesList &&
        check_hash_set_functions (hash_set)){
        unsigned int hash_index;
        if((hash_set->capacity) > HASH_SET_MINIMAL_CAPACITY){
                hash_index = (hash_set->hash_func(value)) &
                             ((hash_set->capacity)-1);
            }
        else{hash_index = 0;}
        if((hash_set->NodesList)[hash_index] == NULL){
            if(get_hash_count ((hash_set->NodesList)[hash_index]) == 0){
                    return 0;
                }
        }
        for (unsigned int i = 0; i < hash_set->capacity; ++i){
            int probing = (hash_index + (i+(i*i))/2) & ((hash_set->capacity)-1);
            if(((hash_set->NodesList)[probing]) != NULL){
                int check = ((hash_set->NodesList)[probing])->elem_cmp_func(
                    (hash_set->NodesList)[probing]->data, value);
                if (check == 1){
                    clear_node ((hash_set->NodesList)[probing]);
                    --(((hash_set->NodesList)[hash_index])->hashCount);
                    --(hash_set->size);
                    if(hash_set_get_load_factor(hash_set) <= HASH_SET_MIN_LOAD_FACTOR){
                        if(hash_set->capacity > HASH_SET_MINIMAL_CAPACITY){
                             hash_set_re_alloc (
                                hash_set,
                                ((hash_set->capacity) / HASH_SET_GROWTH_FACTOR));
                        }
                    }
                    return 1;
                }
            }
        }
    }
    return 0;
}

/**
 * This function returns the load factor of the hash set.
 * @param hash_set a hash set.
 * @return the hash set's load factor, -1 if the function failed.
 */
double hash_set_get_load_factor(HashSet *hash_set)
{
    if(hash_set)
        {
            return ((double)(hash_set->size))/((double)hash_set->capacity);
        }
    return -1;

}

/**
 * This function deletes all the values in the hash set.
 * @param hash_set a hash set to be cleared.
 */
void hash_set_clear(HashSet *hash_set){

    if(hash_set && check_hash_set_functions (hash_set) &&
    hash_set->NodesList){
        for(unsigned int i = 0; i < hash_set->capacity; ++i){
            Node *curr_node = hash_set->NodesList[i];
            if(curr_node){
                curr_node->hashCount = 0;
                if(curr_node->data){
                    hash_set->value_free(&(curr_node->data));
                    curr_node->data = NULL;
                }
            }
        }
        hash_set->size = 0;
    }
}

/**
 * This function gets the element in the hashset hashed to the indexed value
 * @param hash_set the hashset
 * @param value the index of the node in the hashtable that
 * we would like to have its value
 * @return the element in the hashset hashed to the indexed value
 * NULL in case of an error or an empty node or an unexpected value
 */
Value hash_set_at(HashSet *hash_set, int value){
    if(hash_set && (value < (int)hash_set->capacity) &&
    (value >= HASH_SET_INITIAL_SIZE && hash_set->NodesList)){
        if(hash_set->NodesList[value] && hash_set->NodesList[value]->data){
                return hash_set->NodesList[value]->data;
        }
    }
    return NULL;
}

/**
 * Helper function that checks that non of the hash-set
 * functions are NULL
 * @param hash_set the hash-set to be checked
 * @return 1 if all functions are valid, 0 otherwise
 */
int check_hash_set_functions(HashSet* hash_set){
    if(hash_set){

        if(hash_set->hash_func &&
        hash_set->value_cmp && hash_set->value_cpy){
                return 1;
        }
    }
    return 0;
}



