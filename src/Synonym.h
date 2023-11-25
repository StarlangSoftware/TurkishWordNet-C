//
// Created by Olcay Taner YILDIZ on 22.11.2023.
//

#ifndef WORDNET_SYNONYM_H
#define WORDNET_SYNONYM_H

#include <ArrayList.h>
#include "Literal.h"

struct synonym{
    Array_list_ptr literals;
};

typedef struct synonym Synonym;

typedef Synonym *Synonym_ptr;

Synonym_ptr create_synonym();

void free_synonym(Synonym_ptr synonym);

void add_literal_to_synonym(Synonym_ptr synonym, Literal_ptr literal);

Literal_ptr get_literal(Synonym_ptr synonym, int index);

Literal_ptr get_literal_with_name(Synonym_ptr synonym, const char* name);

bool contains_literal(Synonym_ptr synonym, const Literal* literal);

bool contains_literal_with_name(Synonym_ptr synonym, const char* name);

void remove_literal(Synonym_ptr synonym, const Literal* literal);

char* synonym_to_string(const Synonym* synonym);

#endif //WORDNET_SYNONYM_H
