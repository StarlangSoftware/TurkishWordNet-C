//
// Created by Olcay Taner YILDIZ on 25.11.2023.
//

#include <stdlib.h>
#include <math.h>
#include <Memory/Memory.h>
#include "LCH.h"

/**
 * Computes LCH wordnet similarity metric between two synsets.
 * @param word_net WordNet for which similarity metrics will be calculated.
 * @param syn_set1 First synset
 * @param syn_set2 Second synset
 * @return LCH wordnet similarity metric between two synsets
 */
double compute_similarity_lch(Word_net_ptr word_net,
                              Syn_set_ptr syn_set1,
                              Syn_set_ptr syn_set2) {
    Array_list_ptr path_to_root_of_syn_set1 = find_path_to_root(word_net, syn_set1);
    Array_list_ptr path_to_root_of_syn_set2 = find_path_to_root(word_net, syn_set2);
    double max_depth = path_to_root_of_syn_set1->size > path_to_root_of_syn_set2->size ? path_to_root_of_syn_set1->size : path_to_root_of_syn_set2->size;
    int path_length = find_path_length(path_to_root_of_syn_set1, path_to_root_of_syn_set2);
    free_array_list(path_to_root_of_syn_set1, free_);
    free_array_list(path_to_root_of_syn_set2, free_);
    return -log(path_length / (2 * max_depth));
}
