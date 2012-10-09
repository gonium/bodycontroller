# -*- mode: cmake; -*-

file(GLOB bodycontroller_hdrs *.h *.hpp)
install(FILES ${bodycontroller_hdrs} DESTINATION include/libbodycontroller)

configure_file(config.h.in ${CMAKE_BINARY_DIR}/libbodycontroller/config.h)
install(FILES ${CMAKE_BINARY_DIR}/libbodycontroller/config.h 
  DESTINATION include/libbodycontroller)

include_directories(${CMAKE_SOURCE_DIR}
                    ${CMAKE_CURRENT_BINARY_DIR}
                    ${Boost_INCLUDE_DIRS})
file(GLOB bodycontroller_src 
  *.cpp *.hpp 
)

# QT foo.
set(bodycontroller_hdr gui_main_window.hpp gl_widget.hpp)
set(bodycontroller_forms main_window.ui)
#set(bodycontroller_resources sprites.qrc)
QT4_WRAP_UI(bodycontroller_hdr_forms ${bodycontroller_forms})
QT4_WRAP_CPP(bodycontroller_hdr_moc ${bodycontroller_hdr} OPTIONS -DBOOST_TT_HAS_OPERATOR_HPP_INCLUDED)
#QT4_ADD_RESOURCES(bodycontroller_rcc_resources ${bodycontroller_resources})

#PROTOBUF_GENERATE_CPP(PROTO_SRCS PROTO_HDRS sequence.proto)

include_directories(
  ${CMAKE_SOURCE_DIR}
  ${Boost_INCLUDE_DIRS}
  ${CMAKE_BINARY_DIR}
  ${CMAKE_CURRENT_BINARY_DIR}
  )


ADD_LIBRARY(bodycontroller STATIC 
  ${bodycontroller_src} 
  ${PROTO_SRCS} ${PROTO_HDRS}
  ${bodycontroller_hdr_moc}
  ${bodycontroller_hdr_forms}
  ${bodycontroller_rcc_resources}
  )

target_link_libraries(bodycontroller
  ${Boost_LIBRARIES}
  ${PROTOBUF_LIBRARIES}
  ${QT_LIBRARIES}
  pthread
)

#if(BUILD_SHARED_LIBS)
# install(TARGETS bodycontroller LIBRARY DESTINATION lib)
  #else(BUILD_SHARED_LIBS)
   install(TARGETS bodycontroller ARCHIVE DESTINATION lib)
  #endif(BUILD_SHARED_LIBS)

