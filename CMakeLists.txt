cmake_minimum_required(VERSION 3.5)
project(ethzasl_apriltag2 VERSION 1.0.0)

if (NOT WIN32)
    add_definitions("-fPIC -O3")
endif()
find_package(Threads)
find_package(OpenCV REQUIRED)
find_package(Eigen3 REQUIRED)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)


if ("!${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
  # The clang compiler (on osx) is somehow much more strict
  # than the compilers on ubuntu and so this does not seem
  # possible on OSX just yet.
  add_definitions( -Werror )
endif()

#############
# LIBRARIES #
#############
file(GLOB SOURCE_FILES "src/*.cc")
add_library(${PROJECT_NAME} STATIC ${SOURCE_FILES})
target_link_libraries(${PROJECT_NAME} Eigen3::Eigen ${OpenCV_LIBS})
target_include_directories(${PROJECT_NAME} PUBLIC
                           $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
                           $<INSTALL_INTERFACE:include>)
install(TARGETS ${PROJECT_NAME}
        EXPORT ${PROJECT_NAME}Targets
        ARCHIVE DESTINATION lib
        LIBRARY DESTINATION lib
        RUNTIME DESTINATION bin)

install(
    DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/include/
    DESTINATION include
    FILES_MATCHING PATTERN "*.h" PATTERN "*.hpp"
)

# install(
#     EXPORT ${PROJECT_NAME}Targets
#     FILE ${PROJECT_NAME}Targets.cmake
#     NAMESPACE ${PROJECT_NAME}::
#     DESTINATION share/cmake/${PROJECT_NAME}
# )

include(CMakePackageConfigHelpers)

configure_package_config_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/cmake/Config.cmake.in
    ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake
    INSTALL_DESTINATION share/cmake/${PROJECT_NAME}
)

# Version file
write_basic_package_version_file(
    ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY SameMajorVersion
)

# Install config + version files
install(
    FILES
        ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake
        ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake
    DESTINATION share/cmake/${PROJECT_NAME}
)

# Install exported targets file
install(
    EXPORT ${PROJECT_NAME}Targets
    FILE ${PROJECT_NAME}Targets.cmake
    NAMESPACE ${PROJECT_NAME}::
    DESTINATION share/cmake/${PROJECT_NAME}
)

############
# EXAMPLES #
############
#demo
#if(NOT APPLE)
#  add_executable(apriltags_demo src/example/apriltags_demo.cpp src/example/Serial.cpp)
#  target_link_libraries(apriltags_demo ${PROJECT_NAME} v4l2)
#endif()


