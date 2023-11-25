//
// Created by Olcay Taner YILDIZ on 25.11.2023.
//

#ifndef WORDNET_JCN_H
#define WORDNET_JCN_H

#include "../WordNet.h"

double compute_similarity_jcn(Word_net_ptr word_net,
                              Hash_map_ptr information_contents,
                              Syn_set_ptr syn_set1,
                              Syn_set_ptr syn_set2);

#endif //WORDNET_JCN_H
