//
// Created by Olcay Taner YILDIZ on 25.11.2023.
//

#include <stdlib.h>
#include "Resnik.h"

double compute_similarity_resnik(Word_net_ptr word_net,
                                 Hash_map_ptr information_contents,
                                 Syn_set_ptr syn_set1,
                                 Syn_set_ptr syn_set2) {
    Array_list_ptr path_to_root_of_syn_set1 = find_path_to_root(word_net, syn_set1);
    Array_list_ptr path_to_root_of_syn_set2 = find_path_to_root(word_net, syn_set2);
    char* lcs_id = find_lcs_id(path_to_root_of_syn_set1, path_to_root_of_syn_set2);
    free_array_list(path_to_root_of_syn_set1, free);
    free_array_list(path_to_root_of_syn_set2, free);
    double d_lcs = *(double*)hash_map_get(information_contents, lcs_id);
    free(lcs_id);
    return d_lcs;
}
