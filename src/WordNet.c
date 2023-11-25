//
// Created by Olcay Taner YILDIZ on 23.11.2023.
//

#include <XmlElement.h>
#include <XmlDocument.h>
#include <string.h>
#include <StringUtils.h>
#include <stdlib.h>
#include "WordNet.h"
#include "SynSet.h"
#include "InterlingualRelation.h"
#include <Dictionary/ExceptionalWord.h>

/**
 * ReadWordNetTask class extends SwingWorker class which is an abstract class to perform lengthy
 * GUI-interaction tasks in a background thread.
 */
void read_word_net(Word_net_ptr word_net, const char *file_name) {
    Xml_element_ptr root_node, syn_set_node, part_node, semantic_relation_node, type_node, to_node, literal_node, sense_node;
    Syn_set_ptr current_syn_set;
    Literal_ptr current_literal;
    Xml_document_ptr doc = create_xml_document(file_name);
    parse(doc);
    root_node = doc->root;
    syn_set_node = root_node->first_child;
    while (syn_set_node != NULL){
        part_node = syn_set_node->first_child;
        while (part_node != NULL){
            if (strcmp(part_node->name, "ID") == 0){
                current_syn_set = create_syn_set(part_node->pcData);
                add_syn_set(word_net, current_syn_set);
            } else {
                if (strcmp(part_node->name, "DEF") == 0){
                    set_definition(current_syn_set, part_node->pcData);
                } else {
                    if (strcmp(part_node->name, "EXAMPLE") == 0){
                        current_syn_set->example = str_copy(current_syn_set->example, part_node->pcData);
                    } else {
                        if (strcmp(part_node->name, "BCS") == 0) {
                            set_bcs(current_syn_set, atoi(part_node->pcData));
                        } else {
                            if (strcmp(part_node->name, "POS") == 0) {
                                switch (part_node->pcData[0]) {
                                    case 'a':
                                        current_syn_set->pos = ADJECTIVE_POS;
                                        break;
                                    case 'v':
                                        current_syn_set->pos =  VERB_POS;
                                        break;
                                    case 'b':
                                        current_syn_set->pos = ADVERB_POS;
                                        break;
                                    case 'n':
                                        current_syn_set->pos = NOUN_POS;
                                        break;
                                    case 'i':
                                        current_syn_set->pos = INTERJECTION_POS;
                                        break;
                                    case 'c':
                                        current_syn_set->pos = CONJUNCTION_POS;
                                        break;
                                    case 'p':
                                        current_syn_set->pos = PREPOSITION;
                                        break;
                                    case 'r':
                                        current_syn_set->pos = PRONOUN_POS;
                                        break;
                                }
                            } else {
                                if (strcmp(part_node->name, "SR") == 0){
                                    type_node = part_node->first_child;
                                    if (type_node != NULL && strcmp(type_node->name, "TYPE") == 0) {
                                        to_node = type_node->next_sibling;
                                        if (to_node != NULL && strcmp(to_node->name, "TO") == 0) {
                                            add_relation_to_syn_set(current_syn_set, create_semantic_relation(part_node->pcData, type_node->pcData, atoi(to_node->pcData)), SEMANTIC_RELATION);
                                        } else {
                                            add_relation_to_syn_set(current_syn_set, create_semantic_relation3(part_node->pcData, type_node->pcData), SEMANTIC_RELATION);
                                        }
                                    }
                                } else {
                                    if (strcmp(part_node->name, "ILR") == 0){
                                        type_node = part_node->first_child;
                                        if (type_node != NULL && strcmp(type_node->name, "TYPE") == 0) {
                                            char* interlingual_id = part_node->pcData;
                                            Array_list_ptr syn_set_list;
                                            if (hash_map_contains(word_net->interlingual_list, interlingual_id)){
                                                syn_set_list = hash_map_get(word_net->interlingual_list, interlingual_id);
                                            } else {
                                                syn_set_list = create_array_list();
                                            }
                                            array_list_add(syn_set_list, current_syn_set);
                                            hash_map_insert(word_net->interlingual_list, interlingual_id, syn_set_list);
                                            add_relation_to_syn_set(current_syn_set, create_interlingual_relation(interlingual_id, type_node->pcData), INTERLINGUAL_RELATION);
                                        }
                                    } else {
                                        if (strcmp(part_node->name, "SYNONYM") == 0) {
                                            literal_node = part_node->first_child;
                                            while (literal_node != NULL) {
                                                if (strcmp(literal_node->name, "LITERAL") == 0) {
                                                    sense_node = literal_node->first_child;
                                                    if (sense_node != NULL) {
                                                        if (strcmp(sense_node->name, "SENSE") == 0 && sense_node->pcData != NULL) {
                                                            current_literal = create_literal(literal_node->pcData, atoi(sense_node->pcData), current_syn_set->id);
                                                            semantic_relation_node = sense_node->next_sibling;
                                                            while (semantic_relation_node != NULL) {
                                                                if (strcmp(semantic_relation_node->name, "ORIGIN") == 0){
                                                                    current_literal->origin = str_copy(current_literal->origin, semantic_relation_node->pcData);
                                                                } else {
                                                                    if (strcmp(semantic_relation_node->name, "GROUP") == 0){
                                                                        current_literal->group_no = atoi(semantic_relation_node->pcData);
                                                                    } else {
                                                                        if (strcmp(semantic_relation_node->name, "SR") == 0) {
                                                                            type_node = semantic_relation_node->first_child;
                                                                            if (type_node != NULL && strcmp(type_node->name, "TYPE") == 0) {
                                                                                to_node = type_node->next_sibling;
                                                                                if (to_node != NULL && strcmp(to_node->name, "TO") == 0) {
                                                                                    add_relation_to_literal(current_literal, create_semantic_relation(semantic_relation_node->pcData, type_node->pcData, atoi(to_node->pcData)));
                                                                                } else {
                                                                                    add_relation_to_literal(current_literal, create_semantic_relation3(semantic_relation_node->pcData, type_node->pcData));
                                                                                }
                                                                            }
                                                                        }
                                                                    }
                                                                }
                                                                semantic_relation_node = semantic_relation_node->next_sibling;
                                                            }
                                                            add_literal_to_syn_set(current_syn_set, current_literal);
                                                            add_literal_to_literal_list(word_net, current_literal);
                                                        }
                                                    }
                                                }
                                                literal_node = literal_node->next_sibling;
                                            }
                                        } else {
                                            if (strcmp(part_node->name, "SNOTE") == 0) {
                                                current_syn_set->note = str_copy(current_syn_set->note, part_node->pcData);
                                            } else {
                                                if (strcmp(part_node->name, "WIKI") == 0) {
                                                    current_syn_set->wiki_page = str_copy(current_syn_set->wiki_page, part_node->pcData);
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
            part_node = part_node->next_sibling;
        }
        syn_set_node = syn_set_node->next_sibling;
    }
}

/**
 * Method constructs a DOM parser using the dtd/xml schema parser configuration and using this parser it
 * reads exceptions from file and puts to exceptionList HashMap.
 *
 * @param exceptionFileName exception file to be read
 */
void read_exception_file(Word_net_ptr word_net, const char *exception_file_name) {
    char* word_name, *root_form;
    Pos pos;
    Xml_element_ptr word_node, root_node;
    Xml_document_ptr doc = create_xml_document(exception_file_name);
    parse(doc);
    root_node = doc->root;
    word_node = root_node->first_child;
    while (word_node != NULL){
        if (has_attributes(word_node)){
            word_name = get_attribute_value(word_node, "name");
            root_form = get_attribute_value(word_node, "root");
            if (strcmp(get_attribute_value(word_node, "pos"), "Adj") == 0) {
                pos = ADJECTIVE_POS;
            } else {
                if (strcmp(get_attribute_value(word_node, "pos"), "Adv") == 0) {
                    pos = ADVERB_POS;
                } else {
                    if (strcmp(get_attribute_value(word_node, "pos"), "Noun") == 0) {
                        pos = NOUN_POS;
                    } else {
                        if (strcmp(get_attribute_value(word_node, "pos"), "Verb") == 0) {
                            pos = VERB_POS;
                        } else {
                            pos = NOUN_POS;
                        }
                    }
                }
            }
            hash_map_insert(word_net->exception_list, word_name, create_exceptional_word(word_name, root_form, pos));
        }
        word_node = word_node->next_sibling;
    }
}

/**
 * A constructor that initializes the SynSet list, literal list and schedules the {@code SwingWorker} for execution
 * on a <i>worker</i> thread.
 */
Word_net_ptr create_word_net() {
    Word_net_ptr result = malloc(sizeof(Word_net));
    result->interlingual_list = create_string_hash_map();
    result->exception_list = create_string_hash_map();
    result->literal_list = create_string_hash_map();
    result->syn_set_list = create_string_hash_map();
    read_word_net(result, "turkish_wordnet.xml");
    return result;
}

/**
 * Another constructor that initializes the SynSet list, literal list, reads exception,
 * and schedules the {@code SwingWorker} according to file with a specified name for execution on a <i>worker</i> thread.
 *
 * @param file_name resource to be read for the WordNet task
 */
Word_net_ptr create_word_net2(const char *file_name) {
    Word_net_ptr result = malloc(sizeof(Word_net));
    result->interlingual_list = create_string_hash_map();
    result->exception_list = create_string_hash_map();
    result->literal_list = create_string_hash_map();
    result->syn_set_list = create_string_hash_map();
    read_word_net(result, file_name);
    read_exception_file(result, "english_exception.xml");
    return result;
}

/**
 * Another constructor that initializes the SynSet list, literal list, reads exception file with a specified name,
 * sets the Locale of the programme with the specified locale, and schedules the {@code SwingWorker} according
 * to file with a specified name for execution on a <i>worker</i> thread.
 *
 * @param fileName          resource to be read for the WordNet task
 * @param exceptionFileName exception file to be read
 */
Word_net_ptr create_word_net3(const char *file_name, const char *exception_file_name) {
    Word_net_ptr result = malloc(sizeof(Word_net));
    result->interlingual_list = create_string_hash_map();
    result->exception_list = create_string_hash_map();
    result->literal_list = create_string_hash_map();
    result->syn_set_list = create_string_hash_map();
    read_word_net(result, file_name);
    read_exception_file(result, exception_file_name);
    return result;
}

/**
 * Adds a specified literal to the literal list.
 *
 * @param literal literal to be added
 */
void add_literal_to_literal_list(Word_net_ptr word_net, Literal_ptr literal) {
    Array_list_ptr literals;
    if (hash_map_contains(word_net->literal_list, literal->name)){
        literals = hash_map_get(word_net->literal_list, literal->name);
    } else {
        literals = create_array_list();
    }
    array_list_add(literals, literal);
    hash_map_insert(word_net->literal_list, literal->name, literals);
}

/**
 * Returns the values of the SynSet list.
 *
 * @return values of the SynSet list
 */
Array_list_ptr get_syn_set_list(const Word_net* word_net) {
    return value_list(word_net->syn_set_list);
}

/**
 * Returns the keys of the literal list.
 *
 * @return keys of the literal list
 */
Array_list_ptr get_literal_list(const Word_net* word_net) {
    return key_list(word_net->literal_list);
}

/**
 * Adds specified SynSet to the SynSet list.
 *
 * @param syn_set SynSet to be added
 */
void add_syn_set(Word_net_ptr word_net, Syn_set_ptr syn_set) {
    hash_map_insert(word_net->syn_set_list, syn_set->id, syn_set);
}

/**
 * Removes specified SynSet from the SynSet list.
 *
 * @param syn_set SynSet to be added
 */
void remove_syn_set(Word_net_ptr word_net, Syn_set_ptr syn_set) {
    hash_map_remove(word_net->syn_set_list, syn_set->id, (void (*)(void *)) free_syn_set);
}

/**
 * Returns SynSet with the specified SynSet ID.
 *
 * @param syn_set_id ID of the SynSet to be returned
 * @return SynSet with the specified SynSet ID
 */
Syn_set_ptr get_syn_set_with_id(const Word_net* word_net, const char *syn_set_id) {
    return hash_map_get(word_net->syn_set_list, syn_set_id);
}

/**
 * Returns SynSet with the specified literal and sense index.
 *
 * @param literal SynSet literal
 * @param sense   SynSet's corresponding sense index
 * @return SynSet with the specified literal and sense index
 */
Syn_set_ptr get_syn_set_with_literal(const Word_net *word_net, const char *literal, int sense) {
    Array_list_ptr literals;
    literals = hash_map_get(word_net->literal_list, literal);
    if (literals != NULL){
        for (int i = 0; i < literals->size; i++){
            Literal_ptr current = array_list_get(literals, i);
            if (current->sense == sense){
                return get_syn_set_with_id(word_net, current->syn_set_id);
            }
        }
    }
    return NULL;
}

/**
 * Returns the number of SynSets with a specified literal.
 *
 * @param literal literal to be searched in SynSets
 * @return the number of SynSets with a specified literal
 */
int number_of_syn_sets_with_literal(const Word_net *word_net, const char *literal) {
    if (hash_map_contains(word_net->literal_list, literal)){
        return ((Array_list_ptr)hash_map_get(word_net->literal_list, literal))->size;
    } else {
        return 0;
    }
}

/**
 * Returns a list of SynSets with a specified part of speech tag.
 *
 * @param pos part of speech tag to be searched in SynSets
 * @return a list of SynSets with a specified part of speech tag
 */
Array_list_ptr get_syn_sets_with_part_of_speech(const Word_net *word_net, Pos pos) {
    Array_list_ptr result = create_array_list();
    Array_list_ptr list = value_list(word_net->syn_set_list);
    for (int i = 0; i < list->size; i++){
        Syn_set_ptr syn_set = array_list_get(list, i);
        if (syn_set->pos == pos){
            array_list_add(result, syn_set);
        }
    }
    free_array_list(list, NULL);
    return result;
}

/**
 * Returns a list of literals with a specified literal String.
 *
 * @param literal literal String to be searched in literal list
 * @return a list of literals with a specified literal String
 */
Array_list_ptr get_literals_with_name(const Word_net *word_net, const char *literal) {
    if (hash_map_contains(word_net->literal_list, literal)){
        return hash_map_get(word_net->literal_list, literal);
    } else {
        return create_array_list();
    }
}

/**
 * Finds the SynSet with specified literal String and part of speech tag and adds to the given SynSet list.
 *
 * @param result  SynSet list to add the specified SynSet
 * @param literal literal String to be searched in literal list
 * @param pos     part of speech tag to be searched in SynSets
 */
void add_syn_sets_with_literal_to_list(const Word_net *word_net,
                                       Array_list_ptr result,
                                       const char *literal,
                                       Pos pos) {
    Array_list_ptr literals = hash_map_get(word_net->literal_list, literal);
    for (int i = 0; i < literals->size; i++){
        Literal_ptr current = array_list_get(literals, i);
        Syn_set_ptr syn_set = get_syn_set_with_id(word_net, current->syn_set_id);
        if (syn_set != NULL && syn_set->pos == pos){
            array_list_add(result, syn_set);
        }
    }
}

/**
 * Finds SynSets with specified literal String and adds to the newly created SynSet list.
 *
 * @param literal literal String to be searched in literal list
 * @return returns a list of SynSets with specified literal String
 */
Array_list_ptr get_syn_sets_with_literal(const Word_net *word_net, const char *literal) {
    Array_list_ptr result = create_array_list();
    if (hash_map_contains(word_net->literal_list, literal)){
        Array_list_ptr literals = hash_map_get(word_net->literal_list, literal);
        for (int i = 0; i < literals->size; i++){
            Literal_ptr current = array_list_get(literals, i);
            Syn_set_ptr syn_set = get_syn_set_with_id(word_net, current->syn_set_id);
            if (syn_set != NULL){
                array_list_add(result, syn_set);
            }
        }
    }
    return result;
}

/**
 * Adds the reverse relations to the SynSet.
 *
 * @param syn_set           SynSet to add the reverse relations
 * @param semantic_relation relation whose reverse will be added
 */
void add_reverse_relation(const Word_net *word_net,
                          const Syn_set *syn_set,
                          const Semantic_relation *semantic_relation) {
    Syn_set_ptr other_syn_set = get_syn_set_with_id(word_net, semantic_relation->name);
    if (other_syn_set != NULL){
        Semantic_relation_ptr other_relation = create_semantic_relation4(syn_set->id, reverse_semantic_relation(semantic_relation->relation_type));
        if (!contains_relation_in_syn_set(other_syn_set, other_relation, SEMANTIC_RELATION)){
            add_relation_to_syn_set(other_syn_set, other_relation, SEMANTIC_RELATION);
        }
    }
}

/**
 * Removes the reverse relations from the SynSet.
 *
 * @param syn_set           SynSet to remove the reverse relation
 * @param semantic_relation relation whose reverse will be removed
 */
void remove_reverse_relation(const Word_net *word_net,
                             const Syn_set *syn_set,
                             const Semantic_relation *semantic_relation) {
    Syn_set_ptr other_syn_set = get_syn_set_with_id(word_net, semantic_relation->name);
    if (other_syn_set != NULL){
        Semantic_relation_ptr other_relation = create_semantic_relation4(syn_set->id, reverse_semantic_relation(semantic_relation->relation_type));
        if (contains_relation_in_syn_set(other_syn_set, other_relation, SEMANTIC_RELATION)){
            remove_relation_from_syn_set(other_syn_set, other_relation);
        }
    }
}

/**
 * Loops through the SynSet list and adds the possible reverse relations.
 */
void equalize_semantic_relations(const Word_net *word_net) {
    Array_list_ptr list = get_syn_set_list(word_net);
    for (int i = 0; i < list->size; i++){
        Syn_set_ptr syn_set = array_list_get(list, i);
        for (int j = 0; j < syn_set->relations->size; j++){
            if (array_list_get_int(syn_set->relation_types, j) == SEMANTIC_RELATION){
                Semantic_relation_ptr relation = array_list_get(syn_set->relations, j);
                add_reverse_relation(word_net, syn_set, relation);
            }
        }
    }
    free_array_list(list, NULL);
}

/**
 * Sorts definitions of SynSets in SynSet list according to their lengths.
 */
void sort_definitions_of_word_net(const Word_net *word_net) {
    Array_list_ptr list = get_syn_set_list(word_net);
    for (int i = 0; i < list->size; i++){
        Syn_set_ptr syn_set = array_list_get(list, i);
        sort_definitions(syn_set);
    }
}

/**
 * Returns a list of SynSets with the interlingual relations of a specified SynSet ID.
 *
 * @param synSetId SynSet ID to be searched
 * @return a list of SynSets with the interlingual relations of a specified SynSet ID
 */
Array_list_ptr get_interlingual_of_word_net(const Word_net *word_net, const char *syn_set_id) {
    if (hash_map_contains(word_net->interlingual_list, syn_set_id)){
        return hash_map_get(word_net->interlingual_list, syn_set_id);
    } else {
        return create_array_list();
    }
}

/**
 * Creates a list of literals with a specified word, or possible words corresponding to morphological parse.
 *
 * @param word      literal String
 * @param parse     morphological parse to get possible words
 * @param meta_parse metamorphic parse to get possible words
 * @param fsm       finite state machine morphological analyzer to be used at getting possible words
 * @return a list of literal
 */
Array_list_ptr construct_literals(const Word_net *word_net,
                                  const char *word,
                                  const Morphological_parse *parse,
                                  const Metamorphic_parse *meta_parse,
                                  Fsm_morphological_analyzer_ptr fsm) {
    Array_list_ptr result = create_array_list();
    if (parse->inflectional_groups->size > 0){
        if (!is_parse_punctuation(parse) && !is_cardinal(parse) && !is_parse_real(parse)){
            Hash_set_ptr possible_words = get_possible_words(fsm, parse, meta_parse);
            Array_list_ptr list = hash_set_key_list(possible_words);
            for (int i = 0; i < list->size; i++){
                char* possible_word = array_list_get(list, i);
                Array_list_ptr added = get_literals_with_name(word_net, possible_word);
                array_list_add_all(result, added);
                free_array_list(added, NULL);
            }
            free_array_list(list, NULL);
            free_hash_set(possible_words, free);
        } else {
            Array_list_ptr added = get_literals_with_name(word_net, word);
            array_list_add_all(result, added);
            free_array_list(added, NULL);
        }
    } else {
        Array_list_ptr added = get_literals_with_name(word_net, word);
        array_list_add_all(result, added);
        free_array_list(added, NULL);
    }
    return result;
}

/**
 * Creates a list of SynSets with a specified word, or possible words corresponding to morphological parse.
 *
 * @param word      literal String  to get SynSets with
 * @param parse     morphological parse to get SynSets with proper literals
 * @param meta_parse metamorphic parse to get possible words
 * @param fsm       finite state machine morphological analyzer to be used at getting possible words
 * @return a list of SynSets
 */
Array_list_ptr construct_syn_sets(const Word_net *word_net,
                                  const char *word,
                                  const Morphological_parse *parse,
                                  const Metamorphic_parse *meta_parse,
                                  Fsm_morphological_analyzer_ptr fsm) {
    Array_list_ptr result = create_array_list();
    if (parse->inflectional_groups->size > 0){
        if (is_parse_proper_noun(parse)){
            array_list_add(result,get_syn_set_with_literal(word_net, "(özel isim)", 1));
        }
        if (is_parse_time(parse)){
            array_list_add(result,get_syn_set_with_literal(word_net,"(zaman)", 1));
        }
        if (is_parse_date(parse)){
            array_list_add(result,get_syn_set_with_literal(word_net,"(tarih)", 1));
        }
        if (is_hash_tag(parse)){
            array_list_add(result,get_syn_set_with_literal(word_net,"(hashtag)", 1));
        }
        if (is_email(parse)){
            array_list_add(result,get_syn_set_with_literal(word_net,"(eposta)", 1));
        }
        if (is_parse_ordinal(parse)){
            array_list_add(result,get_syn_set_with_literal(word_net,"(sayı sıra sıfatı)", 1));
        }
        if (is_parse_percent(parse)){
            array_list_add(result,get_syn_set_with_literal(word_net,"(yüzde)", 1));
        }
        if (is_parse_fraction(parse)){
            array_list_add(result,get_syn_set_with_literal(word_net,"(kesir sayı)", 1));
        }
        if (is_parse_range(parse)){
            array_list_add(result,get_syn_set_with_literal(word_net,"(sayı aralığı)", 1));
        }
        if (is_parse_real(parse)){
            array_list_add(result,get_syn_set_with_literal(word_net,"(reel sayı)", 1));
        }
        if (!is_parse_punctuation(parse) && !is_cardinal(parse) && !is_parse_real(parse)){
            Hash_set_ptr possible_words = get_possible_words(fsm, parse, meta_parse);
            Array_list_ptr list = hash_set_key_list(possible_words);
            for (int i = 0; i < list->size; i++){
                char* possible_word = array_list_get(list, i);
                Array_list_ptr syn_sets = get_syn_sets_with_literal(word_net, possible_word);
                if (syn_sets->size > 0){
                    for (int j = 0; j < syn_sets->size; j++){
                        Syn_set_ptr syn_set = array_list_get(syn_sets, j);
                        if (string_in_list(get_pos(parse), (char*[]) {"NOUN", "ADVERB", "VERB", "ADJ", "CONJ"}, 5)){
                            if (syn_set->pos == NOUN_POS){
                                if (strcmp(get_pos(parse), "NOUN") == 0 || strcmp(get_root_pos(parse), "NOUN") == 0){
                                    array_list_add(result, syn_set);
                                }
                            } else {
                                if (syn_set->pos == ADVERB_POS){
                                    if (strcmp(get_pos(parse), "ADVERB") == 0 || strcmp(get_root_pos(parse), "ADVERB") == 0){
                                        array_list_add(result, syn_set);
                                    }
                                } else {
                                    if (syn_set->pos == VERB_POS){
                                        if (strcmp(get_pos(parse), "VERB") == 0 || strcmp(get_root_pos(parse), "VERB") == 0){
                                            array_list_add(result, syn_set);
                                        }
                                    } else {
                                        if (syn_set->pos == ADJECTIVE_POS){
                                            if (strcmp(get_pos(parse), "ADJ") == 0 || strcmp(get_root_pos(parse), "ADJ") == 0){
                                                array_list_add(result, syn_set);
                                            }
                                        } else {
                                            if (syn_set->pos == CONJUNCTION_POS){
                                                if (strcmp(get_pos(parse), "CONJ") == 0 || strcmp(get_root_pos(parse), "CONJ") == 0){
                                                    array_list_add(result, syn_set);
                                                }
                                            } else {
                                                array_list_add(result, syn_set);
                                            }
                                        }
                                    }
                                }
                            }
                        } else {
                            array_list_add(result, syn_set);
                        }
                    }
                }
            }
            free_array_list(list, NULL);
            if (result->size == 0){
                list = hash_set_key_list(possible_words);
                for (int i = 0; i < list->size; i++){
                    char* possibleWord = array_list_get(list, i);
                    Array_list_ptr synSets = get_syn_sets_with_literal(word_net, possibleWord);
                    array_list_add_all(result, synSets);
                    free_array_list(synSets, NULL);
                }
                free_array_list(list, NULL);
            }
            free_hash_set(possible_words, free);
        } else {
            Array_list_ptr syn_sets = get_syn_sets_with_literal(word_net, word);
            array_list_add_all(result, syn_sets);
            free_array_list(syn_sets, NULL);
        }
        if (is_cardinal(parse) && result->size == 0){
            array_list_add(result,get_syn_set_with_literal(word_net,"(tam sayı)", 1));
        }
    } else {
        Array_list_ptr syn_sets = get_syn_sets_with_literal(word_net, word);
        array_list_add_all(result, syn_sets);
        free_array_list(syn_sets, NULL);
    }
    return result;
}

/**
 * Returns a list of literals using 3 possible words gathered with the specified morphological parses and metamorphic parses.
 *
 * @param parse1 morphological parse to get possible words
 * @param parse2 morphological parse to get possible words
 * @param parse3 morphological parse to get possible words
 * @param meta_parse1          metamorphic parse to get possible words
 * @param meta_parse2          metamorphic parse to get possible words
 * @param meta_parse3          metamorphic parse to get possible words
 * @param fsm                 finite state machine morphological analyzer to be used at getting possible words
 * @return a list of literals
 */
Array_list_ptr construct_idiom_literals_of_3(const Word_net *word_net,
                                             const Morphological_parse *parse1,
                                             const Morphological_parse *parse2,
                                             const Morphological_parse *parse3,
                                             const Metamorphic_parse *meta_parse1,
                                             const Metamorphic_parse *meta_parse2,
                                             const Metamorphic_parse *meta_parse3,
                                             Fsm_morphological_analyzer_ptr fsm) {
    Array_list_ptr result = create_array_list();
    Hash_set_ptr possible_words1 = get_possible_words(fsm, parse1, meta_parse1);
    Hash_set_ptr possible_words2 = get_possible_words(fsm, parse2, meta_parse2);
    Hash_set_ptr possible_words3 = get_possible_words(fsm, parse3, meta_parse3);
    Array_list_ptr list1 = hash_set_key_list(possible_words1);
    Array_list_ptr list2 = hash_set_key_list(possible_words2);
    Array_list_ptr list3 = hash_set_key_list(possible_words3);
    for (int i = 0; i < list1->size; i++){
        char* possible_word1 = array_list_get(list1, i);
        for (int j = 0; j < list2->size; j++){
            char* possible_word2 = array_list_get(list2, j);
            for (int k = 0; k < list3->size; k++) {
                char* possible_word3 = array_list_get(list3, j);
                String_ptr idiom = create_string4(possible_word1, " ", possible_word2);
                string_append(idiom, " ");
                string_append(idiom, possible_word3);
                Array_list_ptr literals = get_literals_with_name(word_net, idiom->s);
                free_string_ptr(idiom);
                array_list_add_all(result, literals);
                free_array_list(literals, NULL);
            }
        }
    }
    free_array_list(list1, NULL);
    free_array_list(list2, NULL);
    free_array_list(list3, NULL);
    free_hash_set(possible_words1, free);
    free_hash_set(possible_words2, free);
    free_hash_set(possible_words3, free);
    return result;
}

/**
 * Returns a list of SynSets using 3 possible words gathered with the specified morphological parses and metamorphic parses.
 *
 * @param parse1 morphological parse to get possible words
 * @param parse2 morphological parse to get possible words
 * @param parse3 morphological parse to get possible words
 * @param meta_parse1          metamorphic parse to get possible words
 * @param meta_parse2          metamorphic parse to get possible words
 * @param meta_parse3          metamorphic parse to get possible words
 * @param fsm                 finite state machine morphological analyzer to be used at getting possible words
 * @return a list of SynSets
 */
Array_list_ptr construct_idiom_syn_sets_of_3(const Word_net *word_net,
                                             const Morphological_parse *parse1,
                                             const Morphological_parse *parse2,
                                             const Morphological_parse *parse3,
                                             const Metamorphic_parse *meta_parse1,
                                             const Metamorphic_parse *meta_parse2,
                                             const Metamorphic_parse *meta_parse3,
                                             Fsm_morphological_analyzer_ptr fsm) {
    Array_list_ptr result = create_array_list();
    Hash_set_ptr possible_words1 = get_possible_words(fsm, parse1, meta_parse1);
    Hash_set_ptr possible_words2 = get_possible_words(fsm, parse2, meta_parse2);
    Hash_set_ptr possible_words3 = get_possible_words(fsm, parse3, meta_parse3);
    Array_list_ptr list1 = hash_set_key_list(possible_words1);
    Array_list_ptr list2 = hash_set_key_list(possible_words2);
    Array_list_ptr list3 = hash_set_key_list(possible_words3);
    for (int i = 0; i < list1->size; i++){
        char* possible_word1 = array_list_get(list1, i);
        for (int j = 0; j < list2->size; j++){
            char* possible_word2 = array_list_get(list2, j);
            for (int k = 0; k < list3->size; k++) {
                char* possible_word3 = array_list_get(list3, j);
                String_ptr idiom = create_string4(possible_word1, " ", possible_word2);
                string_append(idiom, " ");
                string_append(idiom, possible_word3);
                if (number_of_syn_sets_with_literal(word_net, idiom->s) > 0){
                    Array_list_ptr syn_sets = get_syn_sets_with_literal(word_net, idiom->s);
                    array_list_add_all(result, syn_sets);
                    free_array_list(syn_sets, NULL);
                }
                free_string_ptr(idiom);
            }
        }
    }
    free_array_list(list1, NULL);
    free_array_list(list2, NULL);
    free_array_list(list3, NULL);
    free_hash_set(possible_words1, free);
    free_hash_set(possible_words2, free);
    free_hash_set(possible_words3, free);
    return result;
}

/**
 * Returns a list of literals using 2 possible words gathered with the specified morphological parses and metamorphic parses.
 *
 * @param parse1 morphological parse to get possible words
 * @param parse2 morphological parse to get possible words
 * @param meta_parse1          metamorphic parse to get possible words
 * @param meta_parse2          metamorphic parse to get possible words
 * @param fsm                 finite state machine morphological analyzer to be used at getting possible words
 * @return a list of literals
 */
Array_list_ptr construct_idiom_literals_of_2(const Word_net *word_net,
                                             const Morphological_parse *parse1,
                                             const Morphological_parse *parse2,
                                             const Metamorphic_parse *meta_parse1,
                                             const Metamorphic_parse *meta_parse2,
                                             Fsm_morphological_analyzer_ptr fsm) {
    Array_list_ptr result = create_array_list();
    Hash_set_ptr possible_words1 = get_possible_words(fsm, parse1, meta_parse1);
    Hash_set_ptr possible_words2 = get_possible_words(fsm, parse2, meta_parse2);
    Array_list_ptr list1 = hash_set_key_list(possible_words1);
    Array_list_ptr list2 = hash_set_key_list(possible_words2);
    for (int i = 0; i < list1->size; i++){
        char* possible_word1 = array_list_get(list1, i);
        for (int j = 0; j < list2->size; j++){
            char* possible_word2 = array_list_get(list2, j);
            String_ptr idiom = create_string4(possible_word1, " ", possible_word2);
            Array_list_ptr literals = get_literals_with_name(word_net, idiom->s);
            free_string_ptr(idiom);
            array_list_add_all(result, literals);
            free_array_list(literals, NULL);
        }
    }
    free_array_list(list1, NULL);
    free_array_list(list2, NULL);
    free_hash_set(possible_words1, free);
    free_hash_set(possible_words2, free);
    return result;
}

/**
 * Returns a list of SynSets using 2 possible words gathered with the specified morphological parses and metamorphic parses.
 *
 * @param parse1 morphological parse to get possible words
 * @param parse2 morphological parse to get possible words
 * @param meta_parse1          metamorphic parse to get possible words
 * @param meta_parse2          metamorphic parse to get possible words
 * @param fsm                 finite state machine morphological analyzer to be used at getting possible words
 * @return a list of SynSets
 */
Array_list_ptr construct_idiom_syn_sets_of_2(const Word_net *word_net,
                                             const Morphological_parse *parse1,
                                             const Morphological_parse *parse2,
                                             const Metamorphic_parse *meta_parse1,
                                             const Metamorphic_parse *meta_parse2,
                                             Fsm_morphological_analyzer_ptr fsm) {
    Array_list_ptr result = create_array_list();
    Hash_set_ptr possible_words1 = get_possible_words(fsm, parse1, meta_parse1);
    Hash_set_ptr possible_words2 = get_possible_words(fsm, parse2, meta_parse2);
    Array_list_ptr list1 = hash_set_key_list(possible_words1);
    Array_list_ptr list2 = hash_set_key_list(possible_words2);
    for (int i = 0; i < list1->size; i++){
        char* possible_word1 = array_list_get(list1, i);
        for (int j = 0; j < list2->size; j++){
            char* possible_word2 = array_list_get(list2, j);
            String_ptr idiom = create_string4(possible_word1, " ", possible_word2);
            string_append(idiom, " ");
            if (number_of_syn_sets_with_literal(word_net, idiom->s) > 0){
                Array_list_ptr syn_sets = get_syn_sets_with_literal(word_net, idiom->s);
                array_list_add_all(result, syn_sets);
                free_array_list(syn_sets, NULL);
            }
            free_string_ptr(idiom);
        }
    }
    free_array_list(list1, NULL);
    free_array_list(list2, NULL);
    free_hash_set(possible_words1, free);
    free_hash_set(possible_words2, free);
    return result;
}

/**
 * Conduct common operations between similarity metrics.
 *
 * @param path_to_root_of_syn_set1 first list of Strings
 * @param path_to_root_of_syn_set2 second list of Strings
 * @return path length
 */
int find_path_length(const Array_list *path_to_root_of_syn_set1, const Array_list *path_to_root_of_syn_set2) {
    // There might not be a path between nodes, due to missing nodes. Keep track of that as well. Break when the LCS if found.
    for (int i = 0; i < path_to_root_of_syn_set1->size; i++) {
        int foundIndex = array_list_index_of(path_to_root_of_syn_set2,
                                             array_list_get(path_to_root_of_syn_set1, i),
                                             (int (*)(const void *, const void *)) compare_string);
        if (foundIndex != -1) {
            // Index of two lists - 1 is equal to path length. If there is not path, return -1
            return i + foundIndex - 1;
        }
    }
    return -1;
}

/**
 * Returns the depth of path.
 *
 * @param path_to_root_of_syn_set1 first list of Strings
 * @param path_to_root_of_syn_set2 second list of Strings
 * @return LCS depth
 */
int find_lcs_depth(const Array_list *path_to_root_of_syn_set1, const Array_list *path_to_root_of_syn_set2) {
    int result = -1;
    Hash_node_ptr tuple = find_lcs(path_to_root_of_syn_set1, path_to_root_of_syn_set2);
    if (tuple->key != NULL) {
        result = *(int*)tuple->value;
    }
    free_hash_node(tuple, free, free);
    return result;
}

/**
 * Returns the ID of LCS of path.
 *
 * @param path_to_root_of_syn_set1 first list of Strings
 * @param path_to_root_of_syn_set1 second list of Strings
 * @return LCS ID
 */
char* find_lcs_id(const Array_list *path_to_root_of_syn_set1, const Array_list *path_to_root_of_syn_set2) {
    Hash_node_ptr tuple = find_lcs(path_to_root_of_syn_set1, path_to_root_of_syn_set2);
    char* result = tuple->key;
    free_hash_node(tuple, NULL, free);
    return result;
}

/**
 * Returns depth and ID of the LCS.
 *
 * @param path_to_root_of_syn_set1 first list of Strings
 * @param path_to_root_of_syn_set2 second list of Strings
 * @return depth and ID of the LCS
 */
Hash_node_ptr find_lcs(const Array_list *path_to_root_of_syn_set1, const Array_list *path_to_root_of_syn_set2) {
    for (int i = 0; i < path_to_root_of_syn_set1->size; i++) {
        char* lcs_id = array_list_get(path_to_root_of_syn_set1, i);
        if (array_list_contains(path_to_root_of_syn_set2,
                                             lcs_id,
                                             (int (*)(const void *, const void *)) compare_string)){
            char* st1 = str_copy(st1, lcs_id);
            int* index = malloc(sizeof(int));
            *index = path_to_root_of_syn_set1->size - i + 1;
            return create_hash_node(st1, index);
        }
    }
    int* index = malloc(sizeof(int));
    *index = -1;
    return create_hash_node(NULL, index);
}

/**
 * Finds the path to the root node of a SynSets.
 *
 * @param syn_set SynSet whose root path will be found
 * @return list of String corresponding to nodes in the path
 */
Array_list_ptr find_path_to_root(const Word_net *word_net, Syn_set_ptr syn_set) {
    Array_list_ptr path_to_root = create_array_list();
    while (syn_set != NULL){
        char* st = str_copy(st, syn_set->id);
        array_list_add(path_to_root, st);
        syn_set = percolate_up(word_net, syn_set);
    }
    return path_to_root;
}

/**
 * Finds the parent of a node. It does not move until the root, instead it goes one level up.
 *
 * @param root SynSet whose root will be find
 * @return root SynSet
 */
Syn_set_ptr percolate_up(const Word_net *word_net, Syn_set_ptr root) {
    for (int i = 0; i < root->relation_types->size; i++) {
        int type = array_list_get_int(root->relation_types, i);
        if (type == SEMANTIC_RELATION) {
            Semantic_relation_ptr relation = array_list_get(root->relations, i);
            if (relation->relation_type == HYPERNYM) {
                root = get_syn_set_with_id(word_net, relation->name);
                // return even if one hypernym is found.
                return root;
            }
        }
    }
    return NULL;
}

/**
 * Changes ID of a specified SynSet with the specified new ID.
 *
 * @param s SynSet whose ID will be updated
 * @param new_id  new ID
 */
void change_syn_set_id(Word_net_ptr word_net, Syn_set_ptr s, char *new_id) {
    hash_map_remove(word_net->syn_set_list, s->id, NULL);
    free(s->id);
    s->id = str_copy(s->id, new_id);
    hash_map_insert(word_net->syn_set_list, s->id, s);
}

void free_word_net(Word_net_ptr word_net) {
    free_hash_map(word_net->syn_set_list, (void (*)(void *)) free_syn_set);
    Array_list_ptr list = key_list(word_net->literal_list);
    for (int i = 0; i < list->size; i++){
        Array_list_ptr list2 = hash_map_get(word_net->literal_list, array_list_get(list, i));
        if (list2 != NULL){
            free_array_list(list2, NULL);
        }
    }
    free_array_list(list, NULL);
    free_hash_map(word_net->literal_list, NULL);
    free_hash_map(word_net->exception_list, (void (*)(void *)) free_exceptional_word);
    list = key_list(word_net->interlingual_list);
    for (int i = 0; i < list->size; i++){
        Array_list_ptr list2 = hash_map_get(word_net->interlingual_list, array_list_get(list, i));
        free_array_list(list2, NULL);
    }
    free_array_list(list, NULL);
    free(word_net);
}
