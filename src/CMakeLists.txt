# -*- mode: cmake; -*-
set(bc-gui_src bodycontroller.cpp)

include_directories(${CMAKE_SOURCE_DIR}
                    ${CMAKE_CURRENT_SOURCE_DIR} 
                    ${Boost_INCLUDE_DIRS})

add_executable(bc-gui
  ${bc-gui_src}
  ${SAMPLE_MOC_SRCS}
  ${SAMPLE_RC_SRCS}
  ${SAMPLE_UI_HDRS} 
  )

target_link_libraries(bc-gui
  bodycontroller 
  ${Boost_LIBRARIES}
  ${QT_LIBRARIES}
  ${OPENGL_LIBRARIES} 
  ${GLUT_LIBRARY}
  )

# sensor programs to the install target
INSTALL(PROGRAMS 
  ${CMAKE_CURRENT_BINARY_DIR}/bc-gui
  DESTINATION bin)

