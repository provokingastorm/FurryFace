project( SUPPA_BITS )
cmake_minimum_required( VERSION 2.8 )

#------ sources ------
set( SUPPA_BITS_SRC
    cheezepizza.h
	cheezepizzacore.cpp
    cheezepizzacore.h
	cheezepizzaengine.cpp
    cheezepizzaengine.h
	componentdata.h
	componentsystem.cpp
	componentsystem.h
	debugutilities.cpp
    debugutilities.h
	delegate.h
	enginesubsystem.cpp
    enginesubsystem.h
	gamesession.cpp
    gamesession.h
	hud.cpp
    hud.h
	icomponent.h
	inputconfig.cpp
    inputconfig.h
	inputsubsystem.cpp
    inputsubsystem.h
	iplatform.h
    irenderable.h
	localplayer.cpp
    localplayer.h
	messagepump.cpp
    messagepump.h
    messagetypes.h
	playerfactory.cpp
    playerfactory.h
	playersubsystem.cpp
	playersubsystem.h
    point.h
	scene2d.cpp
    scene2d.h
	scene2dobject.cpp
    scene2dobject.h
	sharedcomponents.cpp
	sharedcomponents.h
    sharedinputconfigs.cpp
    sharedinputconfigs.h
    sharedrenderables.cpp
    sharedrenderables.h
	tickable.cpp
    tickable.h
	ticklinkedlist.cpp
    ticklinkedlist.h
	vector2d.cpp
    vector2d.h
	world2d.cpp
    world2d.h
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