include(FetchContent)

FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG release-1.12.1
)

# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(
        ttest
        test.cpp
)

target_link_libraries(
        ttest
        GTest::gtest_main
)

target_include_directories(ttest PUBLIC ${PROJECT_SOURCE_DIR})
target_link_libraries(ttest table InvertedIndex Searcher)

include(GoogleTest)

gtest_discover_tests(ttest)