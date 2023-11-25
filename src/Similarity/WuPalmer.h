//
// Created by Olcay Taner YILDIZ on 25.11.2023.
//

#ifndef WORDNET_WUPALMER_H
#define WORDNET_WUPALMER_H

#include "../WordNet.h"

double compute_similarity_wu_palmer(Word_net_ptr word_net,
                                    Syn_set_ptr syn_set1,
                                    Syn_set_ptr syn_set2);

#endif //WORDNET_WUPALMER_H
