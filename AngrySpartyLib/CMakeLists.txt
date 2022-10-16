project(AngrySpartyLib)

set(SOURCE_FILES MainFrame.cpp MainFrame.h
        GameView.cpp GameView.h
        Game.cpp Game.h
        LevelManager.cpp LevelManager.h
        Level.cpp Level.h
        Item.cpp Item.h
        Physics.cpp Physics.h
        pch.h
        Score.cpp Score.h
        Scoreboard.cpp Scoreboard.h
        Consts.h Obstacle.cpp Obstacle.h Obstacle.cpp Obstacle.h)

set(wxBUILD_PRECOMP OFF)
find_package(wxWidgets COMPONENTS core base xrc html xml REQUIRED)

include(FetchContent)
FetchContent_Declare(
        box2d
        GIT_REPOSITORY https://github.com/erincatto/box2d.git
        GIT_TAG v2.4.1
)

FetchContent_MakeAvailable(box2d)
include_directories(${box2d_SOURCE_DIR}/include/box2d)

include(${wxWidgets_USE_FILE})

add_library(${PROJECT_NAME} STATIC ${SOURCE_FILES})

target_link_libraries(${PROJECT_NAME} ${wxWidgets_LIBRARIES} box2d)

target_precompile_headers(${PROJECT_NAME} PRIVATE pch.h)
