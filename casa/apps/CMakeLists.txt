# Programs
foreach(prog casahdf5support)
    add_executable (${prog}  ${prog}.cc)
    target_link_libraries (${prog} casa_casa)
    if(DEFINED CMAKE_INSTALL_BINDIR)
        install(TARGETS ${prog} DESTINATION ${CMAKE_INSTALL_BINDIR})
    else()
        install(TARGETS ${prog} DESTINATION bin)
    endif()
endforeach()
# Scripts
##foreach(prog countcode)
##   install(PROGRAMS ${prog} DESTINATION bin)
##endforeach()
