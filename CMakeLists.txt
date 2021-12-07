project(AI-Takeover-game)
cmake_minimum_required(VERSION 3.16)

add_link_options(-lsfml-graphics -lsfml-window -lsfml-system)

include_directories("include/")
set(SOURCE src/Constants.cpp src/Background.cpp src/ChooseLevelMenuScene.cpp src/Game.cpp src/GameplayScene.cpp src/Level src/Main.cpp src/MainMenuScene.cpp src/PauseScene.cpp src/SceneManager.cpp)

add_executable(main ${SOURCE} ${HEADERS})

target_link_libraries(main sfml-graphics sfml-window sfml-system)