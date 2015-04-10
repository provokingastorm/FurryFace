project( SUPPA_BITS )
cmake_minimum_required( VERSION 2.8 )

#------ sources ------
set( SUPPA_BITS_SRC
	cheezepizzacore.cpp
	cheezepizzaengine.cpp
	debugutilities.cpp
	enginesubsystem.cpp
	gamesession.cpp
	hud.cpp
	inputconfig.cpp
	inputsubsystem.cpp
	launch.cpp
	localplayer.cpp
	playerfactory.cpp
	scene2d.cpp
	scene2dmanager.cpp
	scene2dobject.cpp
    sharedrenderables.cpp
	tickable.cpp
	vector2d.cpp
    )

#------ additional includes ------
include_directories( ${HGE_SOURCE_DIR}/include )

#------ link directories listed ------
link_directories( ${HGE_SOURCE_DIR}/linklib )
link_libraries( hgehelpers hge-static )

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
add_library( suppabits STATIC ${SUPPA_BITS_SRC} )