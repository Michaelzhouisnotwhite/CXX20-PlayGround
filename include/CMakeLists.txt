project(include)
file(GLOB_RECURSE include_cpp *.cpp)
file(GLOB_RECURSE include_hpp *.hpp)

set(CPR_USE_SYSTEM_CURL ON CACHE BOOL "CPR_USE_SYSTEM_CURL")
# message("includes hpp: ${include_hpp}")
list(LENGTH include_cpp include_cpp_length)
if(include_cpp_length)
    message("PROJECT: ${PROJECT_NAME} includes name: ${include_cpp}")
    add_library(${PROJECT_NAME} ${include_cpp})
    target_link_libraries(${PROJECT_NAME} PRIVATE fmt::fmt)
    # include(FetchContent)
    # FetchContent_Declare(cpr GIT_REPOSITORY https://github.com/libcpr/cpr.git
    #                          GIT_TAG 0817715923c9705e68994eb52ef9df3f6845beba) # The commit hash for 1.10.x. Replace with the latest from: https://github.com/libcpr/cpr/releases
    # FetchContent_MakeAvailable(cpr)
    add_library(lib::include ALIAS ${PROJECT_NAME})
endif()

