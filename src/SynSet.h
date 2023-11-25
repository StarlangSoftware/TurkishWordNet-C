//
// Created by Olcay Taner YILDIZ on 22.11.2023.
//

#ifndef WORDNET_SYNSET_H
#define WORDNET_SYNSET_H

#include <ArrayList.h>
#include "Dictionary/Pos.h"
#include "Synonym.h"

static int SEMANTIC_RELATION = 0;

static int INTERLINGUAL_RELATION = 1;

struct syn_set{
    char* id;
    Pos pos;
    Array_list_ptr definition;
    char* example;
    Synonym_ptr synonym;
    Array_list_ptr relations;
    Array_list_ptr relation_types;
    char* note;
    char* wiki_page;
    int bcs;
};

typedef struct syn_set Syn_set;

typedef Syn_set *Syn_set_ptr;

Syn_set_ptr create_syn_set(const char* id);

void free_syn_set(Syn_set_ptr syn_set);

void set_id(Syn_set_ptr syn_set, char* id);

void set_definition(Syn_set_ptr syn_set, const char* definition);

char* get_definition(const Syn_set* syn_set);

char* representative(const Syn_set* syn_set);

char* get_long_definition(const Syn_set* syn_set);

int compare_definitions(const char* definition1, const char* definition2);

void sort_definitions(Syn_set_ptr syn_set);

char* get_definition_with_index(const Syn_set* syn_set, int index);

int number_of_definitions(const Syn_set* syn_set);

void set_bcs(Syn_set_ptr syn_set, int bcs);

void add_relation_to_syn_set(Syn_set_ptr syn_set, void* relation, int type);

void remove_relation_from_syn_set(Syn_set_ptr syn_set, void* _relation);

void remove_relation_with_name(Syn_set_ptr syn_set, char* name);

void* get_relation(const Syn_set* syn_set, int index);

Array_list_ptr get_interlingual_of_syn_set(const Syn_set* syn_set);

int relation_size(const Syn_set* syn_set);

void add_literal_to_syn_set(Syn_set_ptr syn_set, Literal_ptr literal);

bool contains_same_literal(const Syn_set* syn_set1, const Syn_set* syn_set2);

bool contains_relation_in_syn_set(const Syn_set* syn_set, void* relation, int type);

bool contains_relation_type_in_syn_set(const Syn_set* syn_set, Semantic_relation_type relation_type);

char* syn_set_to_string(const Syn_set* syn_set);

#endif //WORDNET_SYNSET_H
