//
// Created by Olcay Taner YILDIZ on 25.11.2023.
//

#include <Memory/Memory.h>
#include "WuPalmer.h"

/**
 * Computes Wu-Palmer wordnet similarity metric between two synsets.
 * @param word_net WordNet for which similarity metrics will be calculated.
 * @param syn_set1 First synset
 * @param syn_set2 Second synset
 * @return Wu-Palmer wordnet similarity metric between two synsets
 */
double compute_similarity_wu_palmer(Word_net_ptr word_net,
                                    Syn_set_ptr syn_set1,
                                    Syn_set_ptr syn_set2) {
    Array_list_ptr path_to_root_of_syn_set1 = find_path_to_root(word_net, syn_set1);
    Array_list_ptr path_to_root_of_syn_set2 = find_path_to_root(word_net, syn_set2);
    int lcs_depth = find_lcs_depth(path_to_root_of_syn_set1, path_to_root_of_syn_set2);
    int size1 = path_to_root_of_syn_set1->size;
    int size2 = path_to_root_of_syn_set2->size;
    free_array_list(path_to_root_of_syn_set1, free_);
    free_array_list(path_to_root_of_syn_set2, free_);
    return (2.0 * lcs_depth) / (size1 + size2);
}
