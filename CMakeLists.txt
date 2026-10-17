cmake_minimum_required(VERSION 4.3)
project(Game)

set(CMAKE_CXX_STANDARD 20)

add_executable(Game
        Game.c
        Files/Ability.c
        Files/Ability.h
        Files/Adventurer.c
        Files/Adventurer.h
        Files/Profession.h
        Files/Enemy.c
        Files/Enemy.h
        Files/Map.c
        Files/Map.h
        Files/Inventory.c
        Files/Inventory.h
        Files/Controllers/MapController.c
        Files/Controllers/MapController.h
        Files/Controllers/Controller.c
        Files/Controllers/Controller.h
)
