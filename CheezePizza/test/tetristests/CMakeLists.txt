project( TETRIS_TESTS )
cmake_minimum_required( VERSION 2.8 )

#------ sources ------
set( TETRIS_TESTS_SRC
    tetristests.cpp
    )

#------ additional includes ------
include_directories( ${HGE_SOURCE_DIR}/test/unittestpp )
#include_directories( ${HGE_SOURCE_DIR}/test/unittestpp/win32 )

#------ link directories listed ------
link_directories( ${HGE_SOURCE_DIR}/linklib )
link_directories( ${DIRECTX_SDK_DIR}/lib ${DIRECTX_SDK_DIR}/lib/x64 ${DIRECTX_SDK_DIR}/lib/x86 )
link_libraries( hge-static unittestpp )


#------ target -----
add_library( tetris_tests STATIC ${TETRIS_TESTS_SRC} )
