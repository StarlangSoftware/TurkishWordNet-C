//
// Created by Olcay Taner YILDIZ on 22.11.2023.
//

#include <StringUtils.h>
#include <stdlib.h>
#include <FileUtils.h>
#include <Memory/Memory.h>
#include "InterlingualRelation.h"

static char *interlingual_dependency[14] = {"Hypernym", "Near_antonym", "Holo_member", "Holo_part", "Holo_portion",
                                            "Usage_domain", "Category_domain", "Be_in_state", "Subevent", "Verb_group",
                                            "Similar_to", "Also_see", "Causes", "SYNONYM"};

static Interlingual_dependency_type interlingual_dependency_types[14] = {HYPERNYM_ILR, NEAR_ANTONYM, HOLO_MEMBER, HOLO_PART,
                                                                         HOLO_PORTION,
                                                                         USAGE_DOMAIN, CATEGORY_DOMAIN, BE_IN_STATE,
                                                                         SUBEVENT, VERB_GROUP_ILR,
                                                                         SIMILAR_TO_ILR, ALSO_SEE_ILR, CAUSES, SYNONYM};

/**
 * Compares specified {@code String} tag with the tags in InterlingualDependencyType {@code Array}, ignoring case
 * considerations.
 *
 * @param tag String to compare
 * @return interlingual dependency type according to specified tag
 */
Interlingual_dependency_type get_interlingual_dependency_tag(const char *tag) {
    int index = string_index(tag, interlingual_dependency, 14);
    if (index != -1){
        return interlingual_dependency_types[index];
    }
    return ALSO_SEE_ILR;
}

/**
 * InterlingualRelation method sets its relation with the specified String name, then gets the InterlingualDependencyType
 * according to specified String dependencyType.
 *
 * @param name           relation name
 * @param dependencyType interlingual dependency type
 */
Interlingual_relation_ptr create_interlingual_relation(const char *name, const char *dependency_type) {
    Interlingual_relation_ptr result = malloc_(sizeof(Interlingual_relation), "create_interlingual_relation");
    result->name = str_copy(result->name, name);
    result->dependency_type = get_interlingual_dependency_tag(dependency_type);
    return result;
}

void free_interlingual_relation(Interlingual_relation_ptr interlingual_relation) {
    free_(interlingual_relation->name);
    free_(interlingual_relation);
}

/**
 * Method to retrieve interlingual dependency type as {@code String}.
 *
 * @return String interlingual dependency type
 */
char *get_interlingual_relation_type_as_string(Interlingual_dependency_type interlingual_dependency_type) {
    for (int i = 0; i < 14; i++){
        if (interlingual_dependency_types[i] == interlingual_dependency_type){
            return interlingual_dependency[i];
        }
    }
    return NULL;
}

char *interlingual_relation_to_string(Interlingual_relation_ptr interlingual_relation) {
    char tmp[MAX_LINE_LENGTH];
    sprintf(tmp, "%s->%s", get_interlingual_relation_type_as_string(interlingual_relation->dependency_type), interlingual_relation->name);
    return clone_string(tmp);
}
