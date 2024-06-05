//
// Created by Olcay Taner YILDIZ on 25.11.2023.
//

#include <stdlib.h>
#include <Memory/Memory.h>
#include "Lin.h"

/**
 * Computes Lin wordnet similarity metric between two synsets.
 * @param word_net WordNet for which similarity metrics will be calculated.
 * @param information_contents Information content hash map.
 * @param syn_set1 First synset
 * @param syn_set2 Second synset
 * @return Lin wordnet similarity metric between two synsets
 */
double compute_similarity_lin(Word_net_ptr word_net,
                              Hash_map_ptr information_contents,
                              Syn_set_ptr syn_set1,
                              Syn_set_ptr syn_set2) {
    Array_list_ptr path_to_root_of_syn_set1 = find_path_to_root(word_net, syn_set1);
    Array_list_ptr path_to_root_of_syn_set2 = find_path_to_root(word_net, syn_set2);
    char* lcs_id = find_lcs_id(path_to_root_of_syn_set1, path_to_root_of_syn_set2);
    free_array_list(path_to_root_of_syn_set1, free_);
    free_array_list(path_to_root_of_syn_set2, free_);
    double d1 = *(double*)hash_map_get(information_contents, syn_set1->id);
    double d2 = *(double*)hash_map_get(information_contents, syn_set2->id);
    double d_lcs = *(double*)hash_map_get(information_contents, lcs_id);
    free_(lcs_id);
    return (2 * d_lcs) / (d1 + d2);
}
