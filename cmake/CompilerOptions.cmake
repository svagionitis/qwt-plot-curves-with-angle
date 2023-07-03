# Linker flags
set(LINKER_FLAGS "")

if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU" OR CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    if (ENABLE_ADDRESS_SANITIZER)
        add_compile_options(-fsanitize=address)
        add_link_options(-fsanitize=address)
    endif ()
elseif (MSVC)
    # Getting the following error
    # Error LNK2026 module unsafe for SAFESEH image. SLAPanelMinus CmdCtrlExamples\SLAPanelMinus\avcodec.lib(dlvvs00070.o)
    set(LINKER_FLAGS "/SAFESEH:NO")
endif ()

set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${LINKER_FLAGS}")
unset(LINKER_FLAGS)
