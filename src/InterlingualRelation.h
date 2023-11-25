//
// Created by Olcay Taner YILDIZ on 22.11.2023.
//

#ifndef WORDNET_INTERLINGUALRELATION_H
#define WORDNET_INTERLINGUALRELATION_H

#include "InterlingualDependencyType.h"

struct interlingual_relation{
    char* name;
    Interlingual_dependency_type dependency_type;
};

typedef struct interlingual_relation Interlingual_relation;

typedef Interlingual_relation *Interlingual_relation_ptr;

Interlingual_dependency_type get_interlingual_dependency_tag(const char* tag);

Interlingual_relation_ptr create_interlingual_relation(const char* name, const char* dependency_type);

void free_interlingual_relation(Interlingual_relation_ptr interlingual_relation);

char* get_interlingual_relation_type_as_string(Interlingual_dependency_type interlingual_dependency_type);

char* interlingual_relation_to_string(Interlingual_relation_ptr interlingual_relation);

#endif //WORDNET_INTERLINGUALRELATION_H
