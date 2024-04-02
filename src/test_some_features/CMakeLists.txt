project(test_some_features)

aux_source_directory(. srcs)
include(CMakePrintHelpers)

# add_library(urlencode external/UrlEncoder/Encoder.cpp)
# target_include_directories(urlencode INTERFACE external/UrlEncoder)
# set_property(TARGET urlencode PROPERTY CXX_STANDARD 11)
function(one_file_one_project)
    foreach(src ${srcs})
        # set(OPENCV_BIN_INSTALL_PATH )
        get_filename_component(src_name ${src} NAME_WLE)
        set(sub_proj_name "${PROJECT_NAME}_${src_name}")
        add_executable(${sub_proj_name} ${src})

        if(WIN32)
            target_link_libraries(${sub_proj_name} PRIVATE wsock32 ws2_32 User32)
        endif()

        message("add project: ${sub_proj_name}")
        target_link_libraries(${sub_proj_name} PRIVATE fmt::fmt Boost::bind Boost::asio Boost::url Boost::beast toy::generic toy::cpperclip)
        target_link_libraries(${sub_proj_name} PRIVATE nlohmann_json::nlohmann_json)

        target_link_libraries(${sub_proj_name} PUBLIC Backward::Interface)

        if(NOT WIN32)
            target_link_libraries(${sub_proj_name} PUBLIC dw)
        endif()

        # target_include_directories(${sub_proj_name} PRIVATE
        # ${OPENCV_CONFIG_FILE_INCLUDE_DIR}
        # ${OPENCV_MODULE_opencv_core_LOCATION}/include
        # ${OPENCV_MODULE_opencv_highgui_LOCATION}/include
        # ${OPENCV_MODULE_opencv_imgcodecs_LOCATION}/include
        # )
        target_include_directories(${sub_proj_name} PRIVATE ${include_dir} ${clip_SOURCE_DIR})

        # target_include_directories(${sub_proj_name} PRIVATE ${EIGEN_INCLU})
        # target_link_libraries(${sub_proj_name} PRIVATE opencv_core opencv_highgui opencv_imgcodecs)
        target_link_libraries(${sub_proj_name} PRIVATE clip)

        # if(WIN32)
        #     add_custom_command(TARGET ${sub_proj_name} POST_BUILD
        #         COMMAND ${CMAKE_COMMAND}
        #         -DBINARY_DIR=${CMAKE_BINARY_DIR} -DDESTINATION="${EXECUTABLE_OUTPUT_PATH}" -P ${PROJECT_SOURCE_DIR}/CopyDLLS.cmake)
        # endif()

        cmake_print_properties(
            TARGETS ${sub_proj_name}
            PROPERTIES LINK_LIBRARIES INCLUDE_DIRECTORIES
        )

        # target_link_libraries(${sub_proj_name} PRIVATE Eigen3::Eigen)
    endforeach()
endfunction()

one_file_one_project()

# add_executable(test test.cpp)
# target_include_directories(test PRIVATE ${clip_SOURCE_DIR})
# target_link_libraries(test clip)