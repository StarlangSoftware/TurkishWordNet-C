//
// Created by Olcay Taner YILDIZ on 23.11.2023.
//

#ifndef WORDNET_WORDNET_H
#define WORDNET_WORDNET_H

#include <HashMap/HashMap.h>
#include <MorphologicalParse.h>
#include <MetamorphicParse.h>
#include <FsmMorphologicalAnalyzer.h>
#include "Literal.h"
#include "SynSet.h"

struct word_net {
    Hash_map_ptr syn_set_list;
    Hash_map_ptr literal_list;
    Hash_map_ptr exception_list;
    Hash_map_ptr interlingual_list;
};

typedef struct word_net Word_net;

typedef Word_net *Word_net_ptr;

void read_word_net(Word_net_ptr word_net, const char *file_name);

void read_exception_file(Word_net_ptr word_net, const char *exception_file_name);

Word_net_ptr create_word_net();

Word_net_ptr create_word_net2(const char *file_name);

Word_net_ptr create_word_net3(const char *file_name, const char *exception_file_name);

void free_word_net(Word_net_ptr word_net);

void add_literal_to_literal_list(Word_net_ptr word_net, Literal_ptr literal);

Array_list_ptr get_syn_set_list(const Word_net *word_net);

Array_list_ptr get_literal_list(const Word_net *word_net);

void add_syn_set(Word_net_ptr word_net, Syn_set_ptr syn_set);

void remove_syn_set(Word_net_ptr word_net, Syn_set_ptr syn_set);

Syn_set_ptr get_syn_set_with_id(const Word_net *word_net, const char *id);

Syn_set_ptr get_syn_set_with_literal(const Word_net *word_net, const char *literal, int sense);

int number_of_syn_sets_with_literal(const Word_net *word_net, const char *literal);

Array_list_ptr get_syn_sets_with_part_of_speech(const Word_net *word_net, Pos pos);

Array_list_ptr get_literals_with_name(const Word_net *word_net, const char *literal);

void add_syn_sets_with_literal_to_list(const Word_net *word_net,
                                       Array_list_ptr result,
                                       const char *literal,
                                       Pos pos);

Array_list_ptr get_syn_sets_with_literal(const Word_net *word_net, const char *literal);

void add_reverse_relation(const Word_net *word_net,
                          const Syn_set *syn_set,
                          const Semantic_relation *semantic_relation);

void remove_reverse_relation(const Word_net *word_net,
                             const Syn_set *syn_set,
                             const Semantic_relation *semantic_relation);

void equalize_semantic_relations(const Word_net *word_net);

Array_list_ptr construct_literals(const Word_net *word_net,
                                  const char *word,
                                  const Morphological_parse *parse,
                                  const Metamorphic_parse *meta_parse,
                                  Fsm_morphological_analyzer_ptr fsm);

Array_list_ptr construct_syn_sets(const Word_net *word_net,
                                  const char *word,
                                  const Morphological_parse *parse,
                                  const Metamorphic_parse *meta_parse,
                                  Fsm_morphological_analyzer_ptr fsm);

Array_list_ptr construct_idiom_literals_of_3(const Word_net *word_net,
                                             const Morphological_parse *parse1,
                                             const Morphological_parse *parse2,
                                             const Morphological_parse *parse3,
                                             const Metamorphic_parse *meta_parse1,
                                             const Metamorphic_parse *meta_parse2,
                                             const Metamorphic_parse *meta_parse3,
                                             Fsm_morphological_analyzer_ptr fsm);

Array_list_ptr construct_idiom_syn_sets_of_3(const Word_net *word_net,
                                             const Morphological_parse *parse1,
                                             const Morphological_parse *parse2,
                                             const Morphological_parse *parse3,
                                             const Metamorphic_parse *meta_parse1,
                                             const Metamorphic_parse *meta_parse2,
                                             const Metamorphic_parse *meta_parse3,
                                             Fsm_morphological_analyzer_ptr fsm);

Array_list_ptr construct_idiom_literals_of_2(const Word_net *word_net,
                                             const Morphological_parse *parse1,
                                             const Morphological_parse *parse2,
                                             const Metamorphic_parse *meta_parse1,
                                             const Metamorphic_parse *meta_parse2,
                                             Fsm_morphological_analyzer_ptr fsm);

Array_list_ptr construct_idiom_syn_sets_of_2(const Word_net *word_net,
                                             const Morphological_parse *parse1,
                                             const Morphological_parse *parse2,
                                             const Metamorphic_parse *meta_parse1,
                                             const Metamorphic_parse *meta_parse2,
                                             Fsm_morphological_analyzer_ptr fsm);

void sort_definitions_of_word_net(const Word_net *word_net);

Array_list_ptr get_interlingual_of_word_net(const Word_net *word_net, const char *syn_set_id);

int find_path_length(const Array_list* path_to_root_of_syn_set1, const Array_list* path_to_root_of_syn_set2);

int find_lcs_depth(const Array_list* path_to_root_of_syn_set1, const Array_list* path_to_root_of_syn_set2);

char* find_lcs_id(const Array_list* path_to_root_of_syn_set1, const Array_list* path_to_root_of_syn_set2);

Hash_node_ptr find_lcs(const Array_list* path_to_root_of_syn_set1, const Array_list* path_to_root_of_syn_set2);

Array_list_ptr find_path_to_root(const Word_net* word_net, Syn_set_ptr syn_set);

Syn_set_ptr percolate_up(const Word_net* word_net, Syn_set_ptr root);

void change_syn_set_id(Word_net_ptr word_net, Syn_set_ptr s, const char* new_id);

#endif //WORDNET_WORDNET_H
