//
// Created by Olcay Taner YILDIZ on 25.11.2023.
//

#include <stdlib.h>
#include <Memory/Memory.h>
#include "SimilarityPath.h"

double compute_similarity_similarity_path(Word_net_ptr word_net,
                                          Syn_set_ptr syn_set1,
                                          Syn_set_ptr syn_set2) {
    Array_list_ptr path_to_root_of_syn_set1 = find_path_to_root(word_net, syn_set1);
    Array_list_ptr path_to_root_of_syn_set2 = find_path_to_root(word_net, syn_set2);
    double max_depth = path_to_root_of_syn_set1->size > path_to_root_of_syn_set2->size ? path_to_root_of_syn_set1->size : path_to_root_of_syn_set2->size;
    int path_length = find_path_length(path_to_root_of_syn_set1, path_to_root_of_syn_set2);
    free_array_list(path_to_root_of_syn_set1, free_);
    free_array_list(path_to_root_of_syn_set2, free_);
    return 2 * max_depth - path_length;
}
