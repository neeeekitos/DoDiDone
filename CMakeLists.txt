cmake_minimum_required(VERSION 3.13)
project(e-chess VERSION 0.1)

set(CMAKE_CXX_STANDARD 17)

# Recursive CMake search for header and source files, and also libs
file(GLOB_RECURSE sources      "src/*.cpp")
file(GLOB_RECURSE headers      "include/*.h")
file(GLOB_RECURSE sources_test src/test/*.cpp)

find_package(SFML 2.5.1 COMPONENTS system window graphics network audio)


# setting output directories to store our executables
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build)

# Adds an executable target called <name> to be built from the source files listed
add_executable(e-chess ${sources} ${headers})
target_link_libraries(e-chess sfml-graphics sfml-window sfml-system sfml-audio)
###############################################################################
## dependencies ###############################################################
###############################################################################

# this defines the variables Boost_LIBRARIES that contain all library names
# that we need to link to
#[[find_package(Boost 1.36.0 COMPONENTS filesystem system REQUIRED)

target_link_libraries(example PUBLIC
        ${Boost_LIBRARIES}
        # here you can add any library dependencies
        )]]
###############################################################################
## testing ####################################################################
###############################################################################

# this is for our testing framework
# we don't add REQUIRED because it's just for testing
find_package(GTest)

if(GTEST_FOUND)
    add_executable(unit_tests ${sources_test} ${sources})

    # we add this define to prevent collision with the main
    # this might be better solved by not adding the source with the main to the
    # testing target
    target_compile_definitions(unit_tests PUBLIC UNIT_TESTS)

    # this allows us to use our executable as a link library
    # therefore we can inherit all compiler options and library dependencies
    set_target_properties(example PROPERTIES ENABLE_EXPORTS on)

    target_link_libraries(unit_tests PUBLIC
            ${GTEST_BOTH_LIBRARIES}
            example
            )

    target_include_directories(unit_tests PUBLIC
            ${GTEST_INCLUDE_DIRS} # doesn't do anything on Linux
            )
endif()

###############################################################################
## packaging ##################################################################
###############################################################################

# all install commands get the same destination. this allows us to use paths
# relative to the executable.
install(TARGETS e-chess DESTINATION build)
# this is basically a repeat of the file copy instruction that copies the
# resources in the build directory, but here we tell cmake that we want it
# in the package
#install(DIRECTORY resources DESTINATION example_destination)

# now comes everything we need, to create a package
# there are a lot more variables you can set, and some
# you need to set for some package types, but we want to
# be minimal here
set(CPACK_PACKAGE_NAME "e-chess")
set(CPACK_PACKAGE_VERSION "0.1")

# we don't want to split our program up into several things
set(CPACK_MONOLITHIC_INSTALL 1)


#[[ This must be last.

    CPack is a packaging system for software distributions.
    It can be used to generate:

    - Linux RPM, deb, and gzip packages (for both binaries and source code).
    - NSIS files (for Microsoft Windows).
    - macOS packages.]]
include(CPack)
