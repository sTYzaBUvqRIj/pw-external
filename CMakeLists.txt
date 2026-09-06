cmake_minimum_required(VERSION 3.15)
project(PWEXT)

file(GLOB SRC_FILES
    "src/*.c*"
    "src/*/*.c*"
    
    "vendor/*/*.c*"
)

add_executable(PWEXT
    ${SRC_FILES}
)

set_target_properties(PWEXT PROPERTIES
    CXX_STANDARD 20
    CXX_STANDARD_REQUIRED YES
)

target_include_directories(PWEXT PRIVATE
    src
    vendor
)

target_link_directories(PWEXT PRIVATE)

target_compile_definitions(PWEXT PRIVATE
    $<$<CONFIG:Debug>:_DEBUG>
    $<$<CONFIG:Release>:NDEBUG>
    WIN32_LEAN_AND_MEAN
    NOMINMAX
)

target_link_libraries(PWEXT PRIVATE
    winmm
    ws2_32
)

target_compile_options(PWEXT PRIVATE
    /MP
    /EHsc
    
    /O2
    # O2 included
    /Ob2
    /Oi
    /Ot
    /GF
    /Gy

    /GL
    /Gw
    /GR-
    /GS-
    
    /Qpar

    /std:c++20
    /Zc:inline

    $<$<CONFIG:Debug>:/MTd>
    $<$<CONFIG:Release>:/MT>
)

target_link_options(PWEXT PRIVATE
    /LTCG
    /OPT:REF
    /OPT:ICF
    /DEBUG:NONE
    /INCREMENTAL:NO
    /CGTHREADS:8
)