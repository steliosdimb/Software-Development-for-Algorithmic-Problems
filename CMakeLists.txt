# Created by the script cgal_create_CMakeLists
# This is the CMake script for compiling a set of CGAL applications.

cmake_minimum_required(VERSION 3.1...3.23)

project( PROJECT )


# CGAL and its components
find_package( CGAL QUIET COMPONENTS  )

if ( NOT CGAL_FOUND )

  message(STATUS "This project requires the CGAL library, and will not be compiled.")
  return()  

endif()


# Boost and its components
find_package( Boost REQUIRED )

if ( NOT Boost_FOUND )

  message(STATUS "This project requires the Boost library, and will not be compiled.")

  return()  

endif()

# include for local directory
add_subdirectory(include)
list(APPEND EXTRA_LIBS Polygon_functions)
# include for local package



# ############################

add_executable( PROJECT PROJECT.cpp )

add_to_cached_list( CGAL_EXECUTABLE_TARGETS PROJECT )

# Link the executable to CGAL and third-party libraries
target_link_libraries(PROJECT PRIVATE CGAL::CGAL ${EXTRA_LIBS})






