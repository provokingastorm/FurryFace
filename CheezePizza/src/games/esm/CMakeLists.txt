project( esm )
cmake_minimum_required( VERSION 2.8 )

#------ sources ------
set( ESM_SRC
    esm.cpp
    )

#------ additional includes ------
include_directories( ${SUPPA_BITS_SOURCE_DIR} )
include_directories( ${HGE_SOURCE_DIR}/include )
include_directories( ${DIRECTX_SDK_DIR}/include )

#------ link directories listed ------
link_directories( ${HGE_SOURCE_DIR}/linklib )
link_directories( ${DIRECTX_SDK_DIR}/lib ${DIRECTX_SDK_DIR}/lib/x64 ${DIRECTX_SDK_DIR}/lib/x86 )
link_libraries( hge )
link_libraries( hge )
link_libraries( hge-static )
link_libraries( suppabits )
link_libraries( suppabits_win32 )


#------ target -----
add_executable( esm WIN32 ${ESM_SRC} )

if( MSVC )
    SET_TARGET_PROPERTIES( esm PROPERTIES LINK_FLAGS "/NODEFAULTLIB:libci" )
endif()
