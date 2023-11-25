//
// Created by Olcay Taner YILDIZ on 25.11.2023.
//

#ifndef WORDNET_LIN_H
#define WORDNET_LIN_H

#include "../WordNet.h"

double compute_similarity_lin(Word_net_ptr word_net,
                              Hash_map_ptr information_contents,
                              Syn_set_ptr syn_set1,
                              Syn_set_ptr syn_set2);

#endif //WORDNET_LIN_H
