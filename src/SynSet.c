//
// Created by Olcay Taner YILDIZ on 22.11.2023.
//

#include <stdlib.h>
#include <StringUtils.h>
#include <FileUtils.h>
#include <Dictionary/Word.h>
#include <string.h>
#include "SynSet.h"
#include "InterlingualRelation.h"

/**
 * Constructor initialize SynSet ID, synonym and relations list.
 *
 * @param id Synset ID
 */
Syn_set_ptr create_syn_set(const char *id) {
    Syn_set_ptr result = malloc(sizeof(Syn_set));
    result->id = str_copy(result->id, id);
    result->definition = create_array_list();
    result->example = NULL;
    result->relations = create_array_list();
    result->relation_types = create_array_list();
    result->note = NULL;
    result->wiki_page = NULL;
    result->synonym = create_synonym();
    return result;
}

void free_syn_set(Syn_set_ptr syn_set) {
    for (int i = 0; i < syn_set->relation_types->size; i++){
        int type = array_list_get_int(syn_set->relation_types, i);
        if (type == SEMANTIC_RELATION){
            free_semantic_relation(array_list_get(syn_set->relations, i));
        } else {
            free_interlingual_relation(array_list_get(syn_set->relations, i));
        }
    }
    free(syn_set->relations);
    free_array_list(syn_set->relation_types, free);
    free_array_list(syn_set->definition, free);
    free(syn_set->id);
    free(syn_set->example);
    free(syn_set->note);
    free(syn_set->wiki_page);
    free_synonym(syn_set->synonym);
    free(syn_set);
}

/**
 * Mutator method for the SynSet ID.
 *
 * @param _id SynSet ID to be set
 */
void set_id(Syn_set_ptr syn_set, char *id) {
    for (int i = 0; i < syn_set->synonym->literals->size; i++){
        Literal_ptr literal = get_literal(syn_set->synonym, i);
        literal->syn_set_id = str_copy(literal->syn_set_id, id);
    }
    free(syn_set->id);
    syn_set->id = str_copy(syn_set->id, id);
}

/**
 * Mutator method for the _definition.
 *
 * @param _definition String _definition
 */
void set_definition(Syn_set_ptr syn_set, const char *definition) {
    if (definition != NULL){
        free_array_list(syn_set->definition, free);
        syn_set->definition = str_split(definition, '|');
    }
}

/**
 * Accessor for the definition.
 *
 * @return definition
 */
char *get_definition(const Syn_set* syn_set) {
    if (syn_set->definition->size > 0){
        return array_list_get(syn_set->definition, 0);
    }
    return NULL;
}

/**
 * Returns the first literal's name.
 *
 * @return the first literal's name.
 */
char *representative(const Syn_set* syn_set) {
    Literal_ptr literal = get_literal(syn_set->synonym, 0);
    return literal->name;
}

/**
 * Returns all the definitions in the list.
 *
 * @return all the definitions
 */
char *get_long_definition(const Syn_set* syn_set) {
    if (syn_set->definition->size > 0){
        char tmp[MAX_LINE_LENGTH];
        sprintf(tmp, "%s", (char*) array_list_get(syn_set->definition, 0));
        for (int i = 1; i < syn_set->definition->size; i++){
            sprintf(tmp, "%s|%s", tmp, (char*) array_list_get(syn_set->definition, i));
        }
        char* result = str_copy(result, tmp);
        return result;
    } else {
        return NULL;
    }
}

int compare_definitions(const char *definition1, const char *definition2) {
    int tmp1 = word_size(definition1);
    int tmp2 = word_size(definition2);
    return compare_int(&tmp1, &tmp2);
}

/**
 * Sorts definitions list according to their lengths.
 */
void sort_definitions(Syn_set_ptr syn_set) {
    array_list_sort(syn_set->definition, (int (*)(const void *, const void *)) compare_definitions);
}

/**
 * Accessor for the definition at specified index.
 *
 * @param index definition index to be accessed
 * @return definition at specified index
 */
char *get_definition_with_index(const Syn_set* syn_set, int index) {
    if (index < syn_set->definition->size && index >= 0){
        return array_list_get(syn_set->definition, index);
    } else {
        return NULL;
    }
}

/**
 * Returns number of definitions in the list.
 *
 * @return number of definitions in the list.
 */
int number_of_definitions(const Syn_set* syn_set) {
    return syn_set->definition->size;
}

/**
 * Mutator for the _bcs value which enables the connection with the BalkaNet.
 *
 * @param _bcs _bcs value
 */
void set_bcs(Syn_set_ptr syn_set, int bcs) {
    if (bcs >= 1 && bcs <= 3){
        syn_set->bcs = bcs;
    }
}

/**
 * Appends the specified Relation to the end of relations list.
 *
 * @param relation element to be appended to the list
 */
void add_relation_to_syn_set(Syn_set_ptr syn_set, void* relation, int type) {
    array_list_add(syn_set->relations, relation);
    array_list_add_int(syn_set->relation_types, type);
}

/**
 * Removes the first occurrence of the specified element from relations list,
 * if it is present. If the list does not contain the element, it stays unchanged.
 *
 * @param relation element to be removed from the list, if present
 */
void remove_relation_from_syn_set(Syn_set_ptr syn_set, void* _relation) {
    int index = -1, type;
    for (int i = 0; i < syn_set->relations->size; i++){
        type = array_list_get_int(syn_set->relation_types, i);
        if (type == SEMANTIC_RELATION){
            Semantic_relation_ptr relation1 = array_list_get(syn_set->relations, i);
            Semantic_relation_ptr relation2 = (Semantic_relation_ptr) _relation;
            if (strcmp(relation1->name, relation2->name) == 0){
                index = i;
                break;
            }
        } else {
            Interlingual_relation_ptr relation1 = array_list_get(syn_set->relations, i);
            Interlingual_relation_ptr relation2 = (Interlingual_relation_ptr) _relation;
            if (strcmp(relation1->name, relation2->name) == 0){
                index = i;
                break;
            }
        }
    }
    if (index != -1){
        if (type == SEMANTIC_RELATION){
            array_list_remove(syn_set->relations, index, (void (*)(void *)) free_semantic_relation);
        } else {
            array_list_remove(syn_set->relations, index, (void (*)(void *)) free_interlingual_relation);
        }
        array_list_remove(syn_set->relation_types, index, free);
    }
}

/**
 * Removes the first occurrence of the specified element from relations list according to relation name,
 * if it is present. If the list does not contain the element, it stays unchanged.
 *
 * @param name element to be removed from the list, if present
 */
void remove_relation_with_name(Syn_set_ptr syn_set, char *name) {
    int index = -1, type;
    for (int i = 0; i < syn_set->relations->size; i++){
        type = array_list_get_int(syn_set->relation_types, i);
        if (type == SEMANTIC_RELATION){
            Semantic_relation_ptr relation = array_list_get(syn_set->relations, i);
            if (strcmp(relation->name, name) == 0){
                index = i;
                break;
            }
        } else {
            Interlingual_relation_ptr relation = array_list_get(syn_set->relations, i);
            if (strcmp(relation->name, name) == 0){
                index = i;
                break;
            }
        }
    }
    if (index != -1){
        if (type == SEMANTIC_RELATION){
            array_list_remove(syn_set->relations, index, (void (*)(void *)) free_semantic_relation);
        } else {
            array_list_remove(syn_set->relations, index, (void (*)(void *)) free_interlingual_relation);
        }
        array_list_remove(syn_set->relation_types, index, free);
    }
}

/**
 * Returns the element at the specified position in relations list.
 *
 * @param index index of the element to return
 * @return the element at the specified position in the list
 */
void* get_relation(const Syn_set* syn_set, int index) {
    return array_list_get(syn_set->relations, index);
}

/**
 * Returns interlingual relations with the synonym interlingual dependencies.
 *
 * @return a list of SynSets that has interlingual relations in it
 */
Array_list_ptr get_interlingual_of_syn_set(const Syn_set* syn_set) {
    Array_list_ptr result = create_array_list();
    for (int i = 0; i < syn_set->relations->size; i++){
        int type = array_list_get_int(syn_set->relation_types, i);
        if (type == INTERLINGUAL_RELATION){
            Interlingual_relation_ptr relation = array_list_get(syn_set->relations, i);
            if (relation->dependency_type == SYNONYM){
                char* tmp = str_copy(tmp, relation->name);
                array_list_add(result, tmp);
            }
        }
    }
    return result;
}

/**
 * Returns the size of the relations list.
 *
 * @return the size of the relations list
 */
int relation_size(const Syn_set *syn_set) {
    return syn_set->relations->size;
}

/**
 * Adds a specified literal to the synonym.
 *
 * @param literal literal to be added
 */
void add_literal_to_syn_set(Syn_set_ptr syn_set, Literal_ptr literal) {
    add_literal_to_synonym(syn_set->synonym, literal);
}

/**
 * Compares literals of synonym and the specified SynSet, returns true if their have same literals.
 *
 * @param synSet SynSet to compare
 * @return true if SynSets have same literals, false otherwise
 */
bool contains_same_literal(const Syn_set* syn_set1, const Syn_set* syn_set2) {
    for (int i = 0; i < syn_set1->synonym->literals->size; i++){
        char* literal1 = get_literal(syn_set1->synonym, i)->name;
        for (int j = 0; j < syn_set2->synonym->literals->size; j++){
            char* literal2 = get_literal(syn_set2->synonym, j)->name;
            if (strcmp(literal1, literal2) == 0){
                return true;
            }
        }
    }
    return false;
}

/**
 * Returns <tt>true</tt> if relations list contains the specified relation.
 *
 * @param relation element whose presence in the list is to be tested
 * @return <tt>true</tt> if the list contains the specified element
 */
bool contains_relation_in_syn_set(const Syn_set *syn_set, void *relation, int type) {
    for (int i = 0; i < syn_set->relation_types->size; i++){
        if (array_list_get_int(syn_set->relation_types, i) == type){
            if (type == SEMANTIC_RELATION){
                Semantic_relation_ptr relation1 = array_list_get(syn_set->relations, i);
                Semantic_relation_ptr relation2 = (Semantic_relation_ptr) relation;
                if (strcmp(relation1->name, relation2->name) == 0){
                    return true;
                }
            } else {
                Interlingual_relation_ptr relation1 = array_list_get(syn_set->relations, i);
                Interlingual_relation_ptr relation2 = (Interlingual_relation_ptr) relation;
                if (strcmp(relation1->name, relation2->name) == 0){
                    return true;
                }
            }
        }
    }
    return false;
}

/**
 * Returns <tt>true</tt> if specified semantic relation type presents in the relations list.
 *
 * @param semanticRelationType element whose presence in the list is to be tested
 * @return <<tt>true</tt> if specified semantic relation type presents in the relations list
 */
bool contains_relation_type_in_syn_set(const Syn_set *syn_set, Semantic_relation_type relation_type) {
    for (int i = 0; i < syn_set->relation_types->size; i++){
        if (array_list_get_int(syn_set->relation_types, i) == SEMANTIC_RELATION){
            Semantic_relation_ptr relation = array_list_get(syn_set->relations, i);
            if (relation->relation_type == relation_type){
                return true;
            }
        }
    }
    return false;
}

/**
 * Overridden toString method to print the first definition or representative.
 *
 * @return print the first definition or representative.
 */
char *syn_set_to_string(const Syn_set *syn_set) {
    char* result = NULL;
    if (syn_set->definition->size > 0){
        result = str_copy(result, array_list_get(syn_set->definition, 0));
    } else {
        result = str_copy(result, representative(syn_set));
    }
    return result;
}
