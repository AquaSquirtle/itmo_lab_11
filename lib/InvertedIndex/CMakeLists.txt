add_library(
        InvertedIndex
        InvertedIndex.hpp
        InvertedIndex.cpp
)

target_include_directories(InvertedIndex PUBLIC ${PROJECT_SOURCE_DIR}/lib/Information)

target_link_libraries(InvertedIndex PRIVATE Info)