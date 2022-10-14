project(Tests)

set(TEST_FILES gtest_main.cpp TestItem.cpp)

# Get Google Tests
include(FetchContent)
FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG release-1.11.0
)

include(FetchContent)
FetchContent_Declare(
        box2d
        GIT_REPOSITORY https://github.com/erincatto/box2d.git
        GIT_TAG v2.4.1
)

FetchContent_MakeAvailable(box2d)
include_directories(${box2d_SOURCE_DIR}/include/box2d)

# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# Include Google Test directories
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

# adding the Tests_run target
add_executable(Tests_run ${TEST_FILES})

# linking Tests_run with library which will be tested and wxWidgets
target_link_libraries(Tests_run ${APPLICATION_LIBRARY} ${wxWidgets_LIBRARIES} )

# linking Tests_run with the Google Test libraries
target_link_libraries(Tests_run gtest box2d)

# TODO: Uncomment after pch.h file is created.
#target_precompile_headers(Tests_run PRIVATE ../${APPLICATION_LIBRARY}/pch.h)