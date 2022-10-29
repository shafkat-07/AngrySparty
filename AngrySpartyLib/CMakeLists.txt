project(AngrySpartyLib)

set(SOURCE_FILES Consts.h ids.h pch.h
        MainFrame.cpp MainFrame.h
        GameView.cpp GameView.h
        Game.cpp Game.h
        LevelManager.cpp LevelManager.h
        Level.cpp Level.h
        Item.cpp Item.h
        World.cpp World.h
        Scoreboard.cpp Scoreboard.h
        Background.cpp Background.h
        PhysicalObject.cpp PhysicalObject.h
        Block.cpp Block.h
        DebugDraw.cpp DebugDraw.h
        Foe.cpp Foe.h
        Shooter.cpp Shooter.h
        Slingshot.cpp Slingshot.h
        Goalpost.cpp Goalpost.h
        Poly.cpp Poly.h
        PolygonBody.cpp PolygonBody.h
        CircleBody.cpp CircleBody.h
        Sparty.cpp Sparty.h
        ItemVisitor.cpp ItemVisitor.h
        FoeVisitor.h
        Ring.cpp Ring.h KillFoeVisitor.cpp KillFoeVisitor.h)

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
