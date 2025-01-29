//
// Created by Olcay Taner YILDIZ on 25.11.2023.
//

#include "../src/WordNet.h"

void test_get_syn_set_with_id_single(Word_net_ptr turkish, char* id){
    if (get_syn_set_with_id(turkish, id) == NULL){
        printf("Error in synset with id %s\n", id);
    }
}

void test_get_syn_set_with_id(Word_net_ptr turkish) {
    test_get_syn_set_with_id_single(turkish, "TUR10-0000040");
    test_get_syn_set_with_id_single(turkish, "TUR10-0648550");
    test_get_syn_set_with_id_single(turkish, "TUR10-1034170");
    test_get_syn_set_with_id_single(turkish, "TUR10-1047180");
    test_get_syn_set_with_id_single(turkish, "TUR10-1196250");
}

void test_get_syn_set_with_literal_single(Word_net_ptr turkish, char* name, int sense){
    if (get_syn_set_with_literal(turkish, name, sense) == NULL){
        printf("Error in literal with name %s for sense %d\n", name, sense);
    }
}

void test_get_syn_set_with_literal(Word_net_ptr turkish){
    test_get_syn_set_with_literal_single(turkish, "sıradaki", 1);
    test_get_syn_set_with_literal_single(turkish, "Türkçesi", 2);
    test_get_syn_set_with_literal_single(turkish, "tropikal orman", 1);
    test_get_syn_set_with_literal_single(turkish, "mesut olmak", 1);
    test_get_syn_set_with_literal_single(turkish, "acı badem kurabiyesi", 1);
    test_get_syn_set_with_literal_single(turkish, "açık kapı siyaseti", 1);
    test_get_syn_set_with_literal_single(turkish, "bir baştan bir başa", 1);
    test_get_syn_set_with_literal_single(turkish, "eş zamanlı dil bilimi", 1);
    test_get_syn_set_with_literal_single(turkish, "bir iğne bir iplik olmak", 1);
    test_get_syn_set_with_literal_single(turkish, "yedi kat yerin dibine geçmek", 2);
    test_get_syn_set_with_literal_single(turkish, "kedi gibi dört ayak üzerine düşmek", 1);
    test_get_syn_set_with_literal_single(turkish, "bir kulağından girip öbür kulağından çıkmak", 1);
    test_get_syn_set_with_literal_single(turkish, "anasından emdiği süt burnundan fitil fitil gelmek", 1);
    test_get_syn_set_with_literal_single(turkish, "bir ayak üstünde kırk yalanın belini bükmek", 1);
}

void test_number_of_syn_sets_with_literal_single(Word_net_ptr turkish, char* name, int count){
    if (number_of_syn_sets_with_literal(turkish, name) != count){
        printf("Error in literal with name %s for count %d\n", name, count);
    }
}

void test_number_of_syn_sets_with_literal(Word_net_ptr turkish){
    test_number_of_syn_sets_with_literal_single(turkish, "yolcu etmek", 1);
    test_number_of_syn_sets_with_literal_single(turkish, "açık pembe", 2);
    test_number_of_syn_sets_with_literal_single(turkish, "bürokrasi", 3);
    test_number_of_syn_sets_with_literal_single(turkish, "bordür", 4);
    test_number_of_syn_sets_with_literal_single(turkish, "duygulanım", 5);
    test_number_of_syn_sets_with_literal_single(turkish, "sarsıntı", 6);
    test_number_of_syn_sets_with_literal_single(turkish, "kuvvetli", 7);
    test_number_of_syn_sets_with_literal_single(turkish, "merkez", 8);
    test_number_of_syn_sets_with_literal_single(turkish, "yüksek", 9);
    test_number_of_syn_sets_with_literal_single(turkish, "biçim", 10);
    test_number_of_syn_sets_with_literal_single(turkish, "yurt", 11);
    test_number_of_syn_sets_with_literal_single(turkish, "iğne", 12);
    test_number_of_syn_sets_with_literal_single(turkish, "kol", 13);
    test_number_of_syn_sets_with_literal_single(turkish, "alem", 14);
    test_number_of_syn_sets_with_literal_single(turkish, "taban", 15);
    test_number_of_syn_sets_with_literal_single(turkish, "yer", 16);
    test_number_of_syn_sets_with_literal_single(turkish, "ağır", 17);
    test_number_of_syn_sets_with_literal_single(turkish, "iş", 18);
    test_number_of_syn_sets_with_literal_single(turkish, "dökmek", 19);
    test_number_of_syn_sets_with_literal_single(turkish, "kaldırmak", 20);
    test_number_of_syn_sets_with_literal_single(turkish, "girmek", 21);
    test_number_of_syn_sets_with_literal_single(turkish, "gitmek", 22);
    test_number_of_syn_sets_with_literal_single(turkish, "vermek", 23);
    test_number_of_syn_sets_with_literal_single(turkish, "olmak", 24);
    test_number_of_syn_sets_with_literal_single(turkish, "bırakmak", 25);
    test_number_of_syn_sets_with_literal_single(turkish, "çıkarmak", 26);
    test_number_of_syn_sets_with_literal_single(turkish, "kesmek", 27);
    test_number_of_syn_sets_with_literal_single(turkish, "açmak", 28);
    test_number_of_syn_sets_with_literal_single(turkish, "düşmek", 33);
    test_number_of_syn_sets_with_literal_single(turkish, "atmak", 38);
    test_number_of_syn_sets_with_literal_single(turkish, "geçmek", 39);
    test_number_of_syn_sets_with_literal_single(turkish, "çekmek", 44);
    test_number_of_syn_sets_with_literal_single(turkish, "tutmak", 50);
    test_number_of_syn_sets_with_literal_single(turkish, "çıkmak", 59);
}

void test_get_syn_sets_with_part_of_speech_single(Word_net_ptr turkish, Pos pos, int count){
    Array_list_ptr list = get_syn_sets_with_part_of_speech(turkish, pos);
    if (list->size != count){
        printf("Error with pos %d with %d\n", pos, list->size);
    }
}

void test_get_syn_sets_with_part_of_speech(Word_net_ptr turkish){
    test_get_syn_sets_with_part_of_speech_single(turkish, NOUN_POS, 43882);
    test_get_syn_sets_with_part_of_speech_single(turkish, VERB_POS, 17773);
    test_get_syn_sets_with_part_of_speech_single(turkish, ADJECTIVE_POS, 12406);
    test_get_syn_sets_with_part_of_speech_single(turkish, ADVERB_POS, 2549);
    test_get_syn_sets_with_part_of_speech_single(turkish, INTERJECTION_POS, 1552);
    test_get_syn_sets_with_part_of_speech_single(turkish, PRONOUN_POS, 74);
    test_get_syn_sets_with_part_of_speech_single(turkish, CONJUNCTION_POS, 61);
    test_get_syn_sets_with_part_of_speech_single(turkish, PREPOSITION, 30);
}

void test_get_interlingual_single(Word_net_ptr turkish, char* id, int count){
    if (get_interlingual_of_word_net(turkish, id)->size != count){
        printf("Error in interlingual of %s with %d\n", id, count);
    }
}

void test_get_interlingual(Word_net_ptr turkish){
    test_get_interlingual_single(turkish, "ENG31-05674544-n", 1);
    test_get_interlingual_single(turkish, "ENG31-00220161-r", 2);
    test_get_interlingual_single(turkish, "ENG31-02294200-v", 3);
    test_get_interlingual_single(turkish, "ENG31-06205574-n", 4);
    test_get_interlingual_single(turkish, "ENG31-02687605-v", 5);
    test_get_interlingual_single(turkish, "ENG31-01099197-n", 6);
    test_get_interlingual_single(turkish, "ENG31-00587299-n", 7);
    test_get_interlingual_single(turkish, "ENG31-02214901-v", 9);
    test_get_interlingual_single(turkish, "ENG31-02733337-v", 10);
    test_get_interlingual_single(turkish, "ENG31-00149403-v", 19);
}

int main(){
    Word_net_ptr turkish = create_word_net();
    if (turkish->literal_list->count != 82276){
        printf("Error in literal list size %d\n", turkish->literal_list->count);
    }
    int literal_count = 0;
    Array_list_ptr list = get_syn_set_list(turkish);
    for (int i = 0; i < list->size; i++){
        Syn_set_ptr syn_set = array_list_get(list, i);
        literal_count += syn_set->synonym->literals->size;
    }
    free_array_list(list, NULL);
    if (literal_count != 110259){
        printf("Error in literal count %d", literal_count);
    }
    if (turkish->syn_set_list->count != 78327){
        printf("Error in synset list size %d", turkish->syn_set_list->count);
    }
    test_get_syn_set_with_id(turkish);
    test_get_syn_set_with_literal(turkish);
    test_number_of_syn_sets_with_literal(turkish);
    test_get_syn_sets_with_part_of_speech(turkish);
    test_get_interlingual(turkish);
    free_word_net(turkish);
}