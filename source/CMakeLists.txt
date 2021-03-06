  project(CaesarIA-game)

# Find revision ID and hash of the sourcetree
include("${CMAKE_MODULE_PATH}/GenerateVersionHPP.cmake")

if(CMAKE_SIZEOF_VOID_P EQUAL 8)
    set(X64_BUILD 1)
endif()

if(X32_BUILD)
  set(X64_BUILD 0)
endif()

#select compiler
if (CMAKE_COMPILER_IS_CLANG)
  # using Clang
  add_definitions("-DGAME_COMPILER_NAME=\"clang\"")
elseif (CMAKE_COMPILER_IS_GNUCXX)
  # using GCC
  add_definitions("-DGAME_COMPILER_NAME=\"gcc\"")
elseif (MSVC)
  # using Visual Studio C++
  add_definitions("-DGAME_COMPILER_NAME=\"msvc\"")
endif()

aux_source_directory(. SRC_LIST)
file(GLOB INC_LIST "*.hpp")

include_directories(
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${DEP_SOURCE_DIR}
  ${STEAM_API_DIR}
  include
)

file(GLOB EVENTS_SOURCES_LIST "${CMAKE_CURRENT_SOURCE_DIR}/events/*.*")
file(GLOB CORE_SOURCES_LIST "${CMAKE_CURRENT_SOURCE_DIR}/core/*.*")
file(GLOB PATHWAY_SOURCES_LIST "${CMAKE_CURRENT_SOURCE_DIR}/pathway/*.*")
file(GLOB FONT_SOURCES_LIST "${CMAKE_CURRENT_SOURCE_DIR}/font/*.*")
file(GLOB GUI_SOURCES_LIST "${CMAKE_CURRENT_SOURCE_DIR}/gui/*.*")
file(GLOB GAME_SOURCES_LIST "${CMAKE_CURRENT_SOURCE_DIR}/game/*.*")
file(GLOB CITY_SOURCES_LIST "${CMAKE_CURRENT_SOURCE_DIR}/city/*.*")
file(GLOB GOOD_SOURCES_LIST "${CMAKE_CURRENT_SOURCE_DIR}/good/*.*")
file(GLOB VFS_SOURCES_LIST "${CMAKE_CURRENT_SOURCE_DIR}/vfs/*.*")
file(GLOB GFX_SOURCES_LIST "${CMAKE_CURRENT_SOURCE_DIR}/gfx/*.*")
file(GLOB SOUND_SOURCES_LIST "${CMAKE_CURRENT_SOURCE_DIR}/sound/*.*")
file(GLOB SOURCES_LIST "${CMAKE_CURRENT_SOURCE_DIR}/*.*")
file(GLOB ADV_INCLUDE_LIST "${CMAKE_CURRENT_SOURCE_DIR}/include/*")
file(GLOB OBJECTS_SOURCES_LIST "${CMAKE_CURRENT_SOURCE_DIR}/objects/*.*")
file(GLOB WALKER_SOURCES_LIST "${CMAKE_CURRENT_SOURCE_DIR}/walker/*.*")
file(GLOB WORLD_SOURCES_LIST "${CMAKE_CURRENT_SOURCE_DIR}/world/*.*")
file(GLOB GAME_MODELS_LIST "${GAME_CONFIG_DIR}/*.*")
file(GLOB GUI_MODELS_LIST "${GAME_CONFIG_DIR}/gui/*.*")
file(GLOB JSE_SOURCES_LIST "${CMAKE_CURRENT_SOURCE_DIR}/scripting/*.*")
file(GLOB SCRIPT_SYSTEM_LIST "${GAME_CONFIG_DIR}/system/*.*")
file(GLOB TUTORIAL_MODELS_LIST "${GAME_CONFIG_DIR}/tutorial/*.tutorial")
file(GLOB MISSIONS_LIST "${GAME_CONFIG_DIR}/missions/*.*")
file(GLOB HELP_LIST "${GAME_CONFIG_DIR}/help/*.*")
file(GLOB SCENES_LIST "${CMAKE_CURRENT_SOURCE_DIR}/scene/*.*")
file(GLOB THREAD_LIST "${CMAKE_CURRENT_SOURCE_DIR}/thread/*.*")
file(GLOB LAYERS_LIST "${CMAKE_CURRENT_SOURCE_DIR}/layers/*.*")
file(GLOB RELIGION_LIST "${CMAKE_CURRENT_SOURCE_DIR}/religion/*.*")
file(GLOB CHANGES_LIST "${GAME_CONFIG_DIR}/changes/*.*")
file(GLOB STEAM_SOURCES_LIST "${STEAM_API_DIR}/*.*")

add_executable(${PROJECT_NAME} ${SRC_LIST} ${INC_LIST}
               ${GAME_MODELS_LIST} ${GUI_MODELS_LIST} ${EVENTS_SOURCES_LIST}
               ${CORE_SOURCES_LIST} ${GUI_SOURCES_LIST} ${WALKER_SOURCES_LIST} ${FONT_SOURCES_LIST}
               ${OBJECTS_SOURCES_LIST} ${GAME_SOURCES_LIST} ${VFS_SOURCES_LIST}
               ${PATHWAY_SOURCES_LIST} ${CITY_SOURCES_LIST} ${GOOD_SOURCES_LIST}
               ${GFX_SOURCES_LIST} ${SOURCES_LIST} ${SOUND_SOURCES_LIST} ${WORLD_SOURCES_LIST}
               ${MISSIONS_LIST} ${TUTORIAL_MODELS_LIST} ${SCENES_LIST} ${RELIGION_LIST}
               ${STEAM_SOURCES_LIST} ${HELP_LIST} ${LAYERS_LIST} ${THREAD_LIST} ${CHANGES_LIST}
               ${SCRIPT_SYSTEM_LIST} ${JSE_SOURCES_LIST} ${PK_RESOURCES_LIST} ${ADV_INCLUDE_LIST})

include_directories(${SDL2MINI_INCLUDE_DIR})
target_link_libraries(${PROJECT_NAME} ${SDL2MINI_LIBRARY})

include_directories(${MIXER_INCLUDE_DIR})
target_link_libraries(${PROJECT_NAME} ${MIXER_LIBRARY})

include_directories(${PNG_INCLUDE_DIR})
target_link_libraries(${PROJECT_NAME} ${PNG_LIBRARY})

include_directories(${ZLIB_INCLUDE_DIR})
target_link_libraries(${PROJECT_NAME} ${ZLIB_LIBRARY})

include_directories(${LITEHTML_INCLUDE_DIR})
target_link_libraries(${PROJECT_NAME} ${LITEHTML_LIBRARY})

include_directories(${AES_INCLUDE_DIR})
target_link_libraries(${PROJECT_NAME} ${AES_LIBRARY})

include_directories(${BZIP_INCLUDE_DIR})
target_link_libraries(${PROJECT_NAME} ${BZIP_LIBRARY})

include_directories(${LZMA_INCLUDE_DIR})
target_link_libraries(${PROJECT_NAME} ${LZMA_LIBRARY})

include_directories(${SMK_INCLUDE_DIR})
target_link_libraries(${PROJECT_NAME} ${SMK_LIBRARY})

include_directories(${SDL2_TTF_INCLUDE_DIR})
target_link_libraries(${PROJECT_NAME} ${SDL2_TTF_LIBRARY})

target_link_libraries(${PROJECT_NAME} ${PICOC_LIBRARY})

if(BUILD_GL_FRAMEBUFFER)
add_definitions( -DGAME_USE_FRAMEBUFFER )
add_definitions( -DGAME_USE_SHADERS )
endif(BUILD_GL_FRAMEBUFFER)

######################## osx clang settings ##################################

if(APPLE)
  #include steam libraries
  if(USE_STEAM)
    target_link_libraries(${PROJECT_NAME} "${STEAM_API_DIR}/bin/osx32/libsteam_api.dylib")

    ADD_CUSTOM_COMMAND(
        TARGET ${PROJECT_NAME}
        POST_BUILD
        #COMMAND ${CMAKE_COMMAND} -E copy "${STEAM_API_DIR}/bin/osx32/libsdkencryptedappticket.dylib" "${WORK_DIR}/libsdkencryptedappticket.dylib"
        COMMAND ${CMAKE_COMMAND} -E copy "${STEAM_API_DIR}/bin/osx32/libsteam_api.dylib" "${WORK_DIR}/libsteam_api.dylib"
    )
  endif()

  # Enforce C++11
  set(USE_CPP11 ON)

  # Check for C++11 suport
  include(CheckCXXCompilerFlag)
  CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORTS_CXX11)

  set(GAME_BINARY_FILENAME "caesaria.macos")
  INCLUDE_DIRECTORIES ( /System/Library/Frameworks )
  FIND_LIBRARY(OpenGL_LIBRARY OpenGL)
  target_link_libraries(${PROJECT_NAME} ${OpenGL_LIBRARY} )

endif(APPLE)

######################## Win32 settings #################################

if(WIN32)
  if(MSVC)
    ########################## set visual studio virtual folders ###############
    source_group("events" FILES ${EVENTS_SOURCES_LIST})
    source_group("core" FILES ${CORE_SOURCES_LIST})
    source_group("pathway" FILES ${PATHWAY_SOURCES_LIST})
    source_group("gui" FILES ${GUI_SOURCES_LIST})
    source_group("game" FILES ${GAME_SOURCES_LIST})
    source_group("city" FILES ${CITY_SOURCES_LIST})
    source_group("good" FILES ${GOOD_SOURCES_LIST})
    source_group("vfs" FILES ${VFS_SOURCES_LIST})
    source_group("gfx" FILES ${GFX_SOURCES_LIST})
    source_group("sound" FILES ${SOUND_SOURCES_LIST})
    source_group("objects" FILES ${OBJECTS_SOURCES_LIST})
    source_group("walkers" FILES ${WALKER_SOURCES_LIST})
    source_group("world" FILES ${WORLD_SOURCES_LIST})
    source_group("models" FILES ${GUI_MODELS_LIST} ${GAME_MODELS_LIST})
    source_group("jse" FILES ${JSE_SOURCES_LIST})
    source_group("scripts" FILES ${SCRIPT_SYSTEM_LIST})
    source_group("tutorial" FILES ${TUTORIAL_MODELS_LIST})
    source_group("mission" FILES ${MISSIONS_LIST})
    source_group("help" FILES ${HELP_LIST})
    source_group("scenes" FILES ${SCENES_LIST})
    source_group("thread" FILES ${THREAD_LIST})
    source_group("layers" FILES ${LAYERS_LIST})
    source_group("religion" FILES ${RELIGION_LIST})
    source_group("changes" FILES ${CHANGES_LIST})
    source_group("steam" FILES ${STEAM_SOURCES_LIST})
    #############################################################################

    #set app run params
    set_target_properties (${PROJECT_NAME} PROPERTIES COMMAND_LINE_ARGUMENTS "-R ${CMAKE_CURRENT_SOURCE_DIR}")

    #avoid compiler warning
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /EHsc")

    set(COMPILER_SUPPORTS_CXX11 1)
  elseif(CMAKE_COMPILER_IS_GNUCXX)
    ####################### Win32 mingw settings ##################################
    #not show console window
    include(CheckCXXCompilerFlag)
    CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORTS_CXX11)
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -mwindows -static-libstdc++ -static-libgcc")
  endif()

   target_link_libraries(${PROJECT_NAME} "opengl32")
   target_link_libraries(${PROJECT_NAME} "winmm")
   target_link_libraries(${PROJECT_NAME} "imagehlp")

  #include steam libraries
  set(GAME_BINARY_FILENAME "caesaria")
  if(USE_STEAM)
    target_link_libraries(${PROJECT_NAME} "${STEAM_API_DIR}/bin/win/steam_api.lib")
    target_link_libraries(${PROJECT_NAME} "${STEAM_API_DIR}/helper/steam_helper.lib")

    ADD_CUSTOM_COMMAND(
        TARGET ${PROJECT_NAME}
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy "${STEAM_API_DIR}/bin/win/steam_api.dll" "${WORK_DIR}/steam_api.dll"
        COMMAND ${CMAKE_COMMAND} -E copy "${STEAM_API_DIR}/helper/steam_helper.dll" "${WORK_DIR}/steam_helper.dll"
    )
  endif()
endif(WIN32)

####################### linux gcc settings ######################################

if(UNIX AND NOT APPLE)
  #################### get locales ###############################
  message("Get locales from server")
  execute_process(COMMAND ${DEP_SOURCE_DIR}/localeconv/loadtable.py)
  set(RPATH ${GAME_CONFIG_DIR}/locale/caesar.)
  message("Move files to locale folder")
  execute_process(COMMAND mv ${CMAKE_BINARY_DIR}/2.csv ${RPATH}en)
  execute_process(COMMAND mv ${CMAKE_BINARY_DIR}/3.csv ${RPATH}de)
  execute_process(COMMAND mv ${CMAKE_BINARY_DIR}/4.csv ${RPATH}ru)
  execute_process(COMMAND mv ${CMAKE_BINARY_DIR}/5.csv ${RPATH}sv)
  execute_process(COMMAND mv ${CMAKE_BINARY_DIR}/6.csv ${RPATH}sp)
  execute_process(COMMAND mv ${CMAKE_BINARY_DIR}/7.csv ${RPATH}ro)
  execute_process(COMMAND mv ${CMAKE_BINARY_DIR}/8.csv ${RPATH}fr)
  execute_process(COMMAND mv ${CMAKE_BINARY_DIR}/9.csv ${RPATH}hu)
  execute_process(COMMAND mv ${CMAKE_BINARY_DIR}/10.csv ${RPATH}cs)
  execute_process(COMMAND mv ${CMAKE_BINARY_DIR}/11.csv ${RPATH}it)
  execute_process(COMMAND mv ${CMAKE_BINARY_DIR}/12.csv ${RPATH}nn)
  execute_process(COMMAND mv ${CMAKE_BINARY_DIR}/13.csv ${RPATH}pl)
  execute_process(COMMAND mv ${CMAKE_BINARY_DIR}/14.csv ${RPATH}ua)
  execute_process(COMMAND mv ${CMAKE_BINARY_DIR}/15.csv ${RPATH}fn)
  execute_process(COMMAND mv ${CMAKE_BINARY_DIR}/16.csv ${RPATH}pr)
  execute_process(COMMAND mv ${CMAKE_BINARY_DIR}/17.csv ${RPATH}sb)
  execute_process(COMMAND mv ${CMAKE_BINARY_DIR}/18.csv ${RPATH}bg)
  #################################################################

  set(GAME_BINARY_FILENAME "caesaria.linux")
  target_link_libraries(${PROJECT_NAME} "GL")
  target_link_libraries(${PROJECT_NAME} "dl")

  # set compiler options
  if(NOT CMAKE_BUILD_TYPE_RELEASE)
    message("CaesarIA-game: building in debug mode")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS_DEBUG} -Wall -Wno-unused-value -g")
    add_definitions(-DDEBUG)
  else()
    #release options strip bin
    message("CaesarIA-game: building in release mode")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -s")
  endif()

  if(X32_BUILD)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -m32")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -m32")
  endif()

  # Enforce C++11
  set(USE_CPP11 ON)

  # Check for C++11 suport
  include(CheckCXXCompilerFlag)
  CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORTS_CXX11)

  #include steam libraries
  if(USE_STEAM)
    if(X64_BUILD)
      target_link_libraries(${PROJECT_NAME} "${STEAM_API_DIR}/bin/linux64/libsteam_api.so")

      ADD_CUSTOM_COMMAND(
          TARGET ${PROJECT_NAME}
          POST_BUILD
          #COMMAND ${CMAKE_COMMAND} -E copy "${STEAM_API_DIR}/bin/linux64/libsdkencryptedappticket.so" "${WORK_DIR}/libsdkencryptedappticket.so"
          COMMAND ${CMAKE_COMMAND} -E copy "${STEAM_API_DIR}/bin/linux64/libsteam_api.so" "${WORK_DIR}/libsteam_api.so"
      )
    else()
      target_link_libraries(${PROJECT_NAME} "${STEAM_API_DIR}/bin/linux32/libsteam_api.so")

      ADD_CUSTOM_COMMAND(
          TARGET ${PROJECT_NAME}
          POST_BUILD
          #COMMAND ${CMAKE_COMMAND} -E copy "${STEAM_API_DIR}/bin/linux32/libsdkencryptedappticket.so" "${WORK_DIR}/libsdkencryptedappticket.so"
          COMMAND ${CMAKE_COMMAND} -E copy "${STEAM_API_DIR}/bin/linux32/libsteam_api.so" "${WORK_DIR}/libsteam_api.so"
     )
    endif()
  endif()
endif(UNIX AND NOT APPLE)

if(COMPILER_SUPPORTS_CXX11)
  if(NOT MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
  endif()

  message(STATUS "The compiler ${CMAKE_CXX_COMPILER} has no C++11 support.")
endif()

set_property(TARGET ${PROJECT_NAME} PROPERTY OUTPUT_NAME ${GAME_BINARY_FILENAME})
message( "C++ compiler is ${CMAKE_CXX_COMPILER_ID}" )
set(EXECUTABLE_OUTPUT_PATH ${WORK_DIR})

