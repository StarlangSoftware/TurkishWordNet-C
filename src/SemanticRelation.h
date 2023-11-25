//
// Created by Olcay Taner YILDIZ on 22.11.2023.
//

#ifndef WORDNET_SEMANTICRELATION_H
#define WORDNET_SEMANTICRELATION_H

#include "SemanticRelationType.h"

struct semantic_relation{
    char* name;
    Semantic_relation_type relation_type;
    int to_index;
};

typedef struct semantic_relation Semantic_relation;

typedef Semantic_relation *Semantic_relation_ptr;

Semantic_relation_type get_semantic_tag(const char* tag);

Semantic_relation_ptr create_semantic_relation(const char* name,
                                               const char* relation_type,
                                               int to_index);

Semantic_relation_ptr create_semantic_relation2(const char* name,
                                                Semantic_relation_type relation_type,
                                                int to_index);

Semantic_relation_ptr create_semantic_relation3(const char* name, const char* relation_type);

Semantic_relation_ptr create_semantic_relation4(const char* name,
                                                Semantic_relation_type relation_type);

Semantic_relation_type reverse_semantic_relation(Semantic_relation_type semantic_relation_type);

char* get_semantic_relation_type_as_string(Semantic_relation_type semantic_relation_type);

char* semantic_relation_to_string(Semantic_relation_ptr semantic_relation);

void free_semantic_relation(Semantic_relation_ptr semantic_relation);

int compare_relation(const Semantic_relation* relation1, const Semantic_relation* relation2);

#endif //WORDNET_SEMANTICRELATION_H
