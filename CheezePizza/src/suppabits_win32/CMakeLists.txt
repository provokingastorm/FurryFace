project( SUPPA_BITS_WIN32 )
cmake_minimum_required( VERSION 2.8 )

#------ sources ------
set( SUPPA_BITS_WIN32_SRC
	win32platform.h
	win32platform.cpp
    )

#------ additional includes ------
include_directories( ${SUPPA_BITS_SOURCE_DIR} )
include_directories( ${HGE_SOURCE_DIR}/include )
include_directories( ${DIRECTX_SDK_DIR}/include )

#------ link directories listed ------
link_directories( ${HGE_SOURCE_DIR}/linklib )
link_directories( ${DIRECTX_SDK_DIR}/lib ${DIRECTX_SDK_DIR}/lib/x64 ${DIRECTX_SDK_DIR}/lib/x86 )
link_libraries( hge )
link_libraries( hge-static )
link_libraries( suppabits )

#------ precompiled headers support (not done for now) ------
## if (MSVC)
##     set( PRECOMP_FILENAME "precompiled_headers" )
##     set_source_files_properties( ${PRECOMP_FILENAME}.cpp PROPERTIES COMPILE_FLAGS "/Yc${PRECOMP_FILENAME}.h" )
##     foreach( src_file ${HGEHELPERS_SRC} )
##         set_source_files_properties( ${src_file} PROPERTIES COMPILE_FLAGS "/Yu${PRECOMP_FILENAME}.h" )
##     endforeach( src_file ${HGEHELPERS_SRC} )
##     list( APPEND HGEHELPERS_SRC ${PRECOMP_FILENAME}.cpp ${PRECOMP_FILENAME}.h )
## endif (MSVC)

#------ target -----
add_library( suppabits_win32 STATIC ${SUPPA_BITS_WIN32_SRC} )