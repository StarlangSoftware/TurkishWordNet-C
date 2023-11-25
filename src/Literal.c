//
// Created by Olcay Taner YILDIZ on 22.11.2023.
//

#include <stdlib.h>
#include <StringUtils.h>
#include <FileUtils.h>
#include "Literal.h"
#include "SemanticRelation.h"

/**
 * A constructor that initializes name, sense, SynSet ID and the relations.
 *
 * @param name     name of a literal
 * @param sense    index of sense
 * @param synSetId ID of the SynSet
 */
Literal_ptr create_literal(const char *name, int sense, const char *syn_set_id) {
    Literal_ptr result = malloc(sizeof(Literal));
    result->name = str_copy(result->name, name);
    result->sense = sense;
    result->syn_set_id = str_copy(result->syn_set_id, syn_set_id);
    result->origin = NULL;
    result->group_no = 0;
    result->relations = create_array_list();
    return result;
}

void free_literal(Literal_ptr literal) {
    free(literal->origin);
    free_array_list(literal->relations, (void (*)(void *)) free_semantic_relation);
    free(literal->name);
    free(literal->syn_set_id);
    free(literal);
}

/**
 * Appends the specified Relation to the end of relations list.
 *
 * @param relation element to be appended to the list
 */
void add_relation_to_literal(Literal_ptr literal, Semantic_relation_ptr relation) {
    array_list_add(literal->relations, relation);
}

/**
 * Removes the first occurrence of the specified element from relations list,
 * if it is present. If the list does not contain the element, it stays unchanged.
 *
 * @param relation element to be removed from the list, if present
 */
void remove_relation_from_literal(Literal_ptr literal, Semantic_relation_ptr relation) {
    int index = array_list_index_of(literal->relations, relation,
                                    (int (*)(const void *, const void *)) compare_relation);
    if (index != -1){
        array_list_remove(literal->relations, index, (void (*)(void *)) free_semantic_relation);
    }
}

/**
 * Returns <tt>true</tt> if relations list contains the specified relation.
 *
 * @param relation element whose presence in the list is to be tested
 * @return <tt>true</tt> if the list contains the specified element
 */
bool contains_relation_in_literal(const Literal* literal, const Semantic_relation* relation) {
    return array_list_contains(literal->relations, relation, (int (*)(const void *, const void *)) compare_relation);
}

/**
 * Returns <tt>true</tt> if specified semantic relation type presents in the relations list.
 *
 * @param semantic_relation_type element whose presence in the list is to be tested
 * @return <<tt>true</tt> if specified semantic relation type presents in the relations list
 */
bool contains_relation_type_in_literal(const Literal *literal, Semantic_relation_type semantic_relation_type) {
    for (int i = 0; i < literal->relations->size; i++){
        Semantic_relation_ptr relation = array_list_get(literal->relations, i);
        if (relation->relation_type == semantic_relation_type){
            return true;
        }
    }
    return false;
}

/**
 * Returns the element at the specified position in relations list.
 *
 * @param index index of the element to return
 * @return the element at the specified position in the list
 */
Semantic_relation_ptr get_semantic_relation(const Literal *literal, int index) {
    return array_list_get(literal->relations, index);
}

/**
 * Overridden to_string method to print names and sense of literals.
 *
 * @return concatenated names and senses of literals
 */
char *literal_to_string(const Literal *literal) {
    char tmp[MAX_LINE_LENGTH];
    sprintf(tmp, "%s %d", literal->name, literal->sense);
    char* result = str_concat(result, tmp);
    return result;
}

int compare_literal(const Literal *literal1, const Literal *literal2) {
    int result = compare_string(literal1->name, literal2->name);
    if (result == 0){
        result = compare_int(&(literal1->sense), &(literal2->sense));
    }
    return result;
}
