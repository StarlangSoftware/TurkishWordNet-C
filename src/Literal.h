//
// Created by Olcay Taner YILDIZ on 22.11.2023.
//

#ifndef WORDNET_LITERAL_H
#define WORDNET_LITERAL_H

#include <ArrayList.h>
#include "SemanticRelation.h"

struct literal{
    char* name;
    int sense;
    char* syn_set_id;
    char* origin;
    int group_no;
    Array_list_ptr relations;
};

typedef struct literal Literal;

typedef Literal *Literal_ptr;

Literal_ptr create_literal(const char* name, int sense, const char* syn_set_id);

void free_literal(Literal_ptr literal);

void add_relation_to_literal(Literal_ptr literal, Semantic_relation_ptr relation);

void remove_relation_from_literal(Literal_ptr literal, Semantic_relation_ptr relation);

bool contains_relation_in_literal(const Literal* literal, const Semantic_relation* relation);

bool contains_relation_type_in_literal(const Literal* literal, Semantic_relation_type semantic_relation_type);

Semantic_relation_ptr get_semantic_relation(const Literal* literal, int index);

char* literal_to_string(const Literal* literal);

int compare_literal(const Literal* literal1, const Literal* literal2);

#endif //WORDNET_LITERAL_H
