project( tetrisgame )
cmake_minimum_required( VERSION 2.8 )

#------ sources ------
set( TETRIS_STATIC_SRC
	attractmode.cpp
	attractmode.h
    block.cpp
    block.h
	color.h
	compares.h
	creditroll.cpp
	creditroll.h
    defines.h
	fsmmachine.h
	fsmstate.h
	gamecontrol.cpp
	gamecontrol.h
	line.cpp
	line.h
	tetrisblock.cpp
	tetrisblock.h
	tetrisblockfactory.cpp
	tetrisblockfactory.h
	tetrisblocki.cpp
	tetrisblocki.h
	tetrisblockj.cpp
	tetrisblockj.h
	tetrisblockl.cpp
	tetrisblockl.h
	tetrisblocko.cpp
	tetrisblocko.h
	tetrisblockproxy.cpp
	tetrisblockproxy.h
	tetrisblockrotator.h
	tetrisblocks.cpp
	tetrisblocks.h
	tetrisblockt.cpp
	tetrisblockt.h
	tetrisblockz.cpp
	tetrisblockz.h
	tetrisgamesession.cpp
	tetrisgamesession.h
	tetrisgrid.cpp
	tetrisgrid.h
	tetrislaunch.cpp
	tetrishud.cpp
	tetrishud.h
	uncopyable.h
    )

#------ additional includes ------
include_directories( ${HGE_SOURCE_DIR}/include )

#------ link directories listed ------
link_directories( ${HGE_SOURCE_DIR}/linklib )
link_directories( ${DIRECTX_SDK_DIR}/lib ${DIRECTX_SDK_DIR}/lib/x64 ${DIRECTX_SDK_DIR}/lib/x86 )
link_libraries( hge )
link_libraries( hge-static )
link_libraries( suppabits )

#------ target -----
add_executable( tetrisgame WIN32 ${TETRIS_STATIC_SRC} )

if( MSVC )
    SET_TARGET_PROPERTIES( tetrisgame PROPERTIES LINK_FLAGS "/NODEFAULTLIB:libci" )
endif()
