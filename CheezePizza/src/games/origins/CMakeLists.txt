project( origins )
cmake_minimum_required( VERSION 2.8 )

#------ sources ------
set( ORIGINS_SRC
	originsgameconfig.cpp
	originsgameconfig.h
	originsgamesession.cpp
	originsgamesession.h
	originshud.cpp
	originshud.h
	originslinkrenderobject.cpp
	originslinkrenderobject.h
	originsplayer.cpp
	originsplayer.h
	originsplayerfactory.cpp
	originsplayerfactory.h
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


#------ target -----
add_executable( origins WIN32 ${ORIGINS_SRC} )

if( MSVC )
    SET_TARGET_PROPERTIES( origins PROPERTIES LINK_FLAGS "/NODEFAULTLIB:libci" )
endif()
