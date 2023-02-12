project(lfuCache)

aux_source_directory(./src CPP_SOURCES)

add_executable(${PROJECT_NAME} ${CPP_SOURCES})

target_include_directories(${PROJECT_NAME}
                           PRIVATE ./include)

add_definitions(-DCACHE_VERSION=2)

install(TARGETS ${PROJECT_NAME}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
        COMPONENT ${PROJECT_NAME})
        