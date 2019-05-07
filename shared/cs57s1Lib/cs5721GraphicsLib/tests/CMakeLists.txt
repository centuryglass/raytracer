include_directories(${CMAKE_SOURCE_DIR}/src)

IF(${Boost_THREAD_FOUND})
  ADD_EXECUTABLE (boostThreadExample
    boostThreadExample.cpp
    )
  TARGET_LINK_LIBRARIES(boostThreadExample sive-rtutil)
  TARGET_LINK_LIBRARIES(boostThreadExample ${Boost_THREAD_LIBRARIES})
  TARGET_LINK_LIBRARIES(boostThreadExample ${Boost_SYSTEM_LIBRARIES})
  
  TARGET_LINK_LIBRARIES(boostThreadExample pthread)
ENDIF()

# ADD_EXECUTABLE (cpp11ThreadExample
#   cpp11ThreadExample.cpp
#   )
# Need to add -std=c++0x
# TARGET_LINK_LIBRARIES(boostThreadExample sive-rtutil)

IF(${Boost_FOUND})

#  ADD_EXECUTABLE (boost_Timer
#    boost_Timer.cpp
#    )
#  TARGET_LINK_LIBRARIES(boost_Timer sive-rtutil)
#  TARGET_LINK_LIBRARIES(boost_Timer ${Boost_THREAD_LIBRARIES})
# TARGET_LINK_LIBRARIES(boost_Timer pthread)

ENDIF()

add_executable(test_Timer
  test_Timer.cpp
)
target_link_libraries(test_Timer sive-rtutil)

add_executable(test_pngWrite
  test_pngWrite.cpp
)
target_link_libraries(test_pngWrite sive-rtutil)
target_link_libraries(test_pngWrite ${Boost_PROGRAM_OPTIONS_LIBRARIES})
target_link_libraries(test_pngWrite ${PNG_LIBRARY})
target_link_libraries(test_pngWrite ${ZLIB_LIBRARY})

add_executable(test_fishEyeGen
  test_fishEyeGen.cpp
)
target_link_libraries(test_fishEyeGen sive-rtutil)
target_link_libraries(test_fishEyeGen ${Boost_PROGRAM_OPTIONS_LIBRARIES})
target_link_libraries(test_fishEyeGen ${PNG_LIBRARY})
target_link_libraries(test_fishEyeGen ${ZLIB_LIBRARY})

add_executable(test_Vector3D
  test_Vector3D.cpp
)
target_link_libraries(test_Vector3D sive-rtutil)

add_executable(test_XMLSceneParse
  test_XMLSceneParse.cpp
)
target_link_libraries(test_XMLSceneParse sive-rtutil)
target_link_libraries(test_XMLSceneParse ${Boost_PROGRAM_OPTIONS_LIBRARIES})
