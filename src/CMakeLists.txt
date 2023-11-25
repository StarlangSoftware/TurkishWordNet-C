cmake_minimum_required(VERSION 3.23)
project(WordNet C)

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_FLAGS "-O3")

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

add_library(WordNet src/CategoryType.h src/InterlingualDependencyType.h src/SemanticRelationType.h src/SemanticRelation.c src/SemanticRelation.h src/InterlingualRelation.c src/InterlingualRelation.h src/Literal.c src/Literal.h src/Synonym.c src/Synonym.h src/SynSet.c src/SynSet.h src/WordNet.c src/WordNet.h src/Similarity/JCN.c src/Similarity/JCN.h src/Similarity/LCH.c src/Similarity/LCH.h src/Similarity/Lin.c src/Similarity/Lin.h src/Similarity/Resnik.c src/Similarity/Resnik.h src/Similarity/SimilarityPath.c src/Similarity/SimilarityPath.h src/Similarity/WuPalmer.c src/Similarity/WuPalmer.h)
target_link_libraries(WordNet ${CONAN_LIBS})
