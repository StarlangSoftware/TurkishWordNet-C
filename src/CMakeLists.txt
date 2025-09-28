cmake_minimum_required(VERSION 3.23)
project(WordNet)
set(CMAKE_C_STANDARD 17)
set(CMAKE_C_FLAGS "-O3")

find_package(morphological_analysis_c REQUIRED)

add_library(WordNet CategoryType.h InterlingualDependencyType.h SemanticRelationType.h SemanticRelation.c SemanticRelation.h InterlingualRelation.c InterlingualRelation.h Literal.c Literal.h Synonym.c Synonym.h SynSet.c SynSet.h WordNet.c WordNet.h Similarity/JCN.c Similarity/JCN.h Similarity/LCH.c Similarity/LCH.h Similarity/Lin.c Similarity/Lin.h Similarity/Resnik.c Similarity/Resnik.h Similarity/SimilarityPath.c Similarity/SimilarityPath.h Similarity/WuPalmer.c Similarity/WuPalmer.h)
target_link_libraries(WordNet morphological_analysis_c::morphological_analysis_c m)
