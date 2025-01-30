//
// Created by Olcay Taner YILDIZ on 22.11.2023.
//

#include <stdlib.h>
#include <string.h>
#include <FileUtils.h>
#include <StringUtils.h>
#include <Memory/Memory.h>
#include "Synonym.h"
#include "Literal.h"

/**
 * A constructor that creates a new array of literals.
 */
Synonym_ptr create_synonym() {
    Synonym_ptr result = malloc_(sizeof(Synonym), "create_synonym");
    result->literals = create_array_list();
    return result;
}

/**
 * Frees memory allocated to a synonym. Frees literals array list.
 * @param synonym Synonym to be deallocated.
 */
void free_synonym(Synonym_ptr synonym) {
    free_array_list(synonym->literals, (void (*)(void *)) free_literal);
    free_(synonym);
}

/**
 * Appends the specified Literal to the end of literals list.
 *
 * @param synonym Current synonym object
 * @param literal element to be appended to the list
 */
void add_literal_to_synonym(Synonym_ptr synonym, Literal_ptr literal) {
    array_list_add(synonym->literals, literal);
}

/**
 * Returns the element at the specified position in literals list.
 *
 * @param synonym Current synonym object
 * @param index index of the element to return
 * @return the element at the specified position in the list
 */
Literal_ptr get_literal(Synonym_ptr synonym, int index) {
    return array_list_get(synonym->literals, index);
}

/**
 * Returns the element with the specified name in literals list.
 *
 * @param synonym Current synonym object
 * @param name name of the element to return
 * @return the element with the specified name in the list
 */
Literal_ptr get_literal_with_name(Synonym_ptr synonym, const char *name) {
    for (int i = 0; i < synonym->literals->size; i++){
        Literal_ptr literal = array_list_get(synonym->literals, i);
        if (strcmp(literal->name, name) == 0){
            return literal;
        }
    }
    return NULL;
}

/**
 * Returns <tt>true</tt> if literals list contains the specified literal.
 *
 * @param synonym Current synonym object
 * @param literal element whose presence in the list is to be tested
 * @return <tt>true</tt> if the list contains the specified element
 */
bool contains_literal(Synonym_ptr synonym, const Literal *literal) {
    return array_list_contains(synonym->literals, literal, (int (*)(const void *, const void *)) compare_literal);
}

/**
 * Returns <tt>true</tt> if literals list contains the specified String literal.
 *
 * @param synonym Current synonym object
 * @param name element whose presence in the list is to be tested
 * @return<tt>true</tt> if the list contains the specified element
 */
bool contains_literal_with_name(Synonym_ptr synonym, const char *name) {
    for (int i = 0; i < synonym->literals->size; i++){
        Literal_ptr literal = array_list_get(synonym->literals, i);
        if (strcmp(literal->name, name) == 0){
            return true;
        }
    }
    return false;
}

/**
 * Removes the first occurrence of the specified element from literals list,
 * if it is present. If the list does not contain the element, it stays unchanged.
 *
 * @param synonym Current synonym object
 * @param literal element to be removed from the list, if present
 */
void remove_literal(Synonym_ptr synonym, const Literal *literal) {
    int index = array_list_index_of(synonym->literals, literal, (int (*)(const void *, const void *)) compare_literal);
    if (index != -1){
        array_list_remove(synonym->literals, index, (void (*)(void *)) free_literal);
    }
}

/**
 * Overridden toString method to print literals.
 *
 * @param synonym Current synonym object
 * @return concatenated literals
 */
char *synonym_to_string(const Synonym *synonym) {
    char tmp[MAX_LINE_LENGTH];
    sprintf(tmp, "%s", ((Literal_ptr) array_list_get(synonym->literals, 0))->name);
    for (int i = 1; i < synonym->literals->size; i++){
        sprintf(tmp, "%s %s", tmp, ((Literal_ptr) array_list_get(synonym->literals, i))->name);
    }
    return clone_string(tmp);
}
