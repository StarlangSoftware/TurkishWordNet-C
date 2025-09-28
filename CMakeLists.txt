cmake_minimum_required(VERSION 3.23)
project(WordNet)
set(CMAKE_C_STANDARD 17)
set(CMAKE_C_FLAGS "-O3")

find_package(morphological_analysis_c REQUIRED)

add_library(WordNet src/CategoryType.h src/InterlingualDependencyType.h src/SemanticRelationType.h src/SemanticRelation.c src/SemanticRelation.h src/InterlingualRelation.c src/InterlingualRelation.h src/Literal.c src/Literal.h src/Synonym.c src/Synonym.h src/SynSet.c src/SynSet.h src/WordNet.c src/WordNet.h src/Similarity/JCN.c src/Similarity/JCN.h src/Similarity/LCH.c src/Similarity/LCH.h src/Similarity/Lin.c src/Similarity/Lin.h src/Similarity/Resnik.c src/Similarity/Resnik.h src/Similarity/SimilarityPath.c src/Similarity/SimilarityPath.h src/Similarity/WuPalmer.c src/Similarity/WuPalmer.h)
target_link_libraries(WordNet morphological_analysis_c::morphological_analysis_c m)
add_executable(TestWordNet src/CategoryType.h src/InterlingualDependencyType.h src/SemanticRelationType.h src/SemanticRelation.c src/SemanticRelation.h src/InterlingualRelation.c src/InterlingualRelation.h src/Literal.c src/Literal.h src/Synonym.c src/Synonym.h src/SynSet.c src/SynSet.h src/WordNet.c src/WordNet.h src/Similarity/JCN.c src/Similarity/JCN.h src/Similarity/LCH.c src/Similarity/LCH.h src/Similarity/Lin.c src/Similarity/Lin.h src/Similarity/Resnik.c src/Similarity/Resnik.h src/Similarity/SimilarityPath.c src/Similarity/SimilarityPath.h src/Similarity/WuPalmer.c src/Similarity/WuPalmer.h Test/TestWordNet.c)
target_link_libraries(TestWordNet morphological_analysis_c::morphological_analysis_c m)
