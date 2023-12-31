//
// Created by Olcay Taner YILDIZ on 21.11.2023.
//

#ifndef WORDNET_SEMANTICRELATIONTYPE_H
#define WORDNET_SEMANTICRELATIONTYPE_H

enum semantic_relation_type{
    ANTONYM, HYPERNYM,
    INSTANCE_HYPERNYM, HYPONYM, INSTANCE_HYPONYM, MEMBER_HOLONYM, SUBSTANCE_HOLONYM,
    PART_HOLONYM, MEMBER_MERONYM, SUBSTANCE_MERONYM, PART_MERONYM, ATTRIBUTE,
    DERIVATION_RELATED, DOMAIN_TOPIC, MEMBER_TOPIC, DOMAIN_REGION, MEMBER_REGION,
    DOMAIN_USAGE, MEMBER_USAGE, ENTAILMENT, CAUSE, ALSO_SEE,
    VERB_GROUP, SIMILAR_TO, PARTICIPLE_OF_VERB
};

typedef enum semantic_relation_type Semantic_relation_type;

#endif //WORDNET_SEMANTICRELATIONTYPE_H
