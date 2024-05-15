add_library(
        Searcher
        Searcher.cpp
        Searcher.hpp
)

target_include_directories(Searcher PUBLIC ${PROJECT_SOURCE_DIR})

target_link_libraries(Searcher PRIVATE InvertedIndex)