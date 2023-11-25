//
// Created by Olcay Taner YILDIZ on 25.11.2023.
//

#ifndef WORDNET_LCH_H
#define WORDNET_LCH_H

#include "../WordNet.h"
#include "../SynSet.h"

double compute_similarity_lch(Word_net_ptr word_net,
                              Syn_set_ptr syn_set1,
                              Syn_set_ptr syn_set2);

#endif //WORDNET_LCH_H
