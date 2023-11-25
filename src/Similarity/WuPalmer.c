//
// Created by Olcay Taner YILDIZ on 25.11.2023.
//

#include <stdlib.h>
#include "WuPalmer.h"

double compute_similarity_wu_palmer(Word_net_ptr word_net,
                                    Syn_set_ptr syn_set1,
                                    Syn_set_ptr syn_set2) {
    Array_list_ptr path_to_root_of_syn_set1 = find_path_to_root(word_net, syn_set1);
    Array_list_ptr path_to_root_of_syn_set2 = find_path_to_root(word_net, syn_set2);
    int lcs_depth = find_lcs_depth(path_to_root_of_syn_set1, path_to_root_of_syn_set2);
    int size1 = path_to_root_of_syn_set1->size;
    int size2 = path_to_root_of_syn_set2->size;
    free_array_list(path_to_root_of_syn_set1, free);
    free_array_list(path_to_root_of_syn_set2, free);
    return (2.0 * lcs_depth) / (size1 + size2);
}
