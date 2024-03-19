set(the_description "data module")
as_add_module(data as_core as_io)
set(extra_libs "")

file(GLOB_RECURSE lib_hdrs_lib
    "${CMAKE_CURRENT_LIST_DIR}/include/*.hpp"
    "${CMAKE_CURRENT_LIST_DIR}/include/*.h"    
)

as_source_group("Include" DIRBASE "${CMAKE_CURRENT_LIST_DIR}/include" 
                FILES ${lib_hdrs_lib} )

as_glob_module_sources(HEADERS ${OpenCV_INCLUDE_DIRS} ${lib_hdrs_lib} ${EIGEN3_INCLUDE_DIRS})
as_module_include_directories(${OpenCV_INCLUDE_DIRS} ${the_module} ${lib_hdrs_lib} ${EIGEN3_INCLUDE_DIRS})
list(APPEND extra_libs ${OpenCV_LIBS})
as_create_module(${extra_libs})