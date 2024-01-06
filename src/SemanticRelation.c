//
// Created by Olcay Taner YILDIZ on 22.11.2023.
//

#include <StringUtils.h>
#include <stdlib.h>
#include <FileUtils.h>
#include <Memory/Memory.h>
#include "SemanticRelation.h"

static char *semantic_dependency[25] = {"ANTONYM", "HYPERNYM",
                                        "INSTANCE_HYPERNYM", "HYPONYM", "INSTANCE_HYPONYM", "MEMBER_HOLONYM",
                                        "SUBSTANCE_HOLONYM",
                                        "PART_HOLONYM", "MEMBER_MERONYM", "SUBSTANCE_MERONYM", "PART_MERONYM",
                                        "ATTRIBUTE",
                                        "DERIVATION_RELATED", "DOMAIN_TOPIC", "MEMBER_TOPIC", "DOMAIN_REGION",
                                        "MEMBER_REGION",
                                        "DOMAIN_USAGE", "MEMBER_USAGE", "ENTAILMENT", "CAUSE", "ALSO_SEE",
                                        "VERB_GROUP", "SIMILAR_TO", "PARTICIPLE_OF_VERB"};

static Semantic_relation_type semantic_dependency_tags[25] = {ANTONYM, HYPERNYM,
                                                              INSTANCE_HYPERNYM, HYPONYM, INSTANCE_HYPONYM,
                                                              MEMBER_HOLONYM, SUBSTANCE_HOLONYM,
                                                              PART_HOLONYM, MEMBER_MERONYM, SUBSTANCE_MERONYM,
                                                              PART_MERONYM, ATTRIBUTE,
                                                              DERIVATION_RELATED, DOMAIN_TOPIC, MEMBER_TOPIC,
                                                              DOMAIN_REGION, MEMBER_REGION,
                                                              DOMAIN_USAGE, MEMBER_USAGE, ENTAILMENT, CAUSE, ALSO_SEE,
                                                              VERB_GROUP, SIMILAR_TO, PARTICIPLE_OF_VERB};

Semantic_relation_type get_semantic_tag(const char *tag) {
    int index = string_index(tag, semantic_dependency, 25);
    if (index != -1){
        return semantic_dependency_tags[index];
    }
    return ALSO_SEE;
}

/**
 * A constructor to initialize relation type and the relation name.
 *
 * @param name         name of the relation
 * @param relationType String semantic dependency tag
 */
Semantic_relation_ptr create_semantic_relation(const char *name, const char *relation_type, int to_index) {
    Semantic_relation_ptr result = malloc_(sizeof(Semantic_relation), "create_semantic_relation");
    result->name = str_copy(result->name, name);
    result->relation_type = get_semantic_tag(relation_type);
    result->to_index = to_index;
    return result;
}

/**
 * Another constructor that initializes relation type, relation name, and the index.
 *
 * @param name         name of the relation
 * @param relationType String semantic dependency tag
 * @param toIndex      index of the relation
 */
Semantic_relation_ptr create_semantic_relation2(const char *name, Semantic_relation_type relation_type, int to_index) {
    Semantic_relation_ptr result = malloc_(sizeof(Semantic_relation), "create_semantic_relation2");
    result->name = str_copy(result->name, name);
    result->relation_type = relation_type;
    result->to_index = to_index;
    return result;
}

/**
 * Returns the reverse of a specific semantic relation type.
 *
 * @param semanticRelationType semantic relation type to be reversed
 * @return reversed version of the semantic relation type
 */
Semantic_relation_type reverse_semantic_relation(Semantic_relation_type semantic_relation_type) {
    switch (semantic_relation_type){
        case HYPERNYM:
            return HYPONYM;
        case HYPONYM:
            return HYPERNYM;
        case ANTONYM:
            return ANTONYM;
        case INSTANCE_HYPERNYM:
            return INSTANCE_HYPONYM;
        case INSTANCE_HYPONYM:
            return INSTANCE_HYPERNYM;
        case MEMBER_HOLONYM:
            return MEMBER_MERONYM;
        case MEMBER_MERONYM:
            return MEMBER_HOLONYM;
        case PART_MERONYM:
            return PART_HOLONYM;
        case PART_HOLONYM:
            return PART_MERONYM;
        case SUBSTANCE_MERONYM:
            return SUBSTANCE_HOLONYM;
        case SUBSTANCE_HOLONYM:
            return SUBSTANCE_MERONYM;
        case DOMAIN_TOPIC:
            return MEMBER_TOPIC;
        case MEMBER_TOPIC:
            return DOMAIN_TOPIC;
        case DOMAIN_REGION:
            return MEMBER_REGION;
        case MEMBER_REGION:
            return DOMAIN_REGION;
        case DOMAIN_USAGE:
            return MEMBER_USAGE;
        case MEMBER_USAGE:
            return DOMAIN_USAGE;
        case DERIVATION_RELATED:
            return DERIVATION_RELATED;
        default:
            return ALSO_SEE;
    }
}

/**
 * Accessor method to retrieve the semantic relation type as a String.
 *
 * @return String semantic relation type
 */
char *get_semantic_relation_type_as_string(Semantic_relation_type semantic_relation_type) {
    for (int i = 0; i < 25; i++){
        if (semantic_dependency_tags[i] == semantic_relation_type){
            return semantic_dependency[i];
        }
    }
    return NULL;
}

/**
 * Overridden toString method to print semantic relation types and names.
 *
 * @return semantic relation types and names
 */
char *semantic_relation_to_string(Semantic_relation_ptr semantic_relation) {
    char tmp[MAX_LINE_LENGTH];
    sprintf(tmp, "%s->%s", get_semantic_relation_type_as_string(semantic_relation->relation_type), semantic_relation->name);
    return clone_string(tmp);
}

void free_semantic_relation(Semantic_relation_ptr semantic_relation) {
    free_(semantic_relation->name);
    free_(semantic_relation);
}

int compare_relation(const Semantic_relation *relation1, const Semantic_relation *relation2) {
    return compare_string(relation1->name, relation2->name);
}

Semantic_relation_ptr create_semantic_relation3(const char *name, const char *relation_type) {
    return create_semantic_relation(name, relation_type, 0);
}

Semantic_relation_ptr create_semantic_relation4(const char *name, Semantic_relation_type relation_type) {
    return create_semantic_relation2(name, relation_type, 0);
}
