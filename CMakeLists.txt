cmake_minimum_required(VERSION 4.3)
project(Game)

set(CMAKE_CXX_STANDARD 20)

add_executable(Game
        Game.c
        Files/State.h
        Files/Modules/Ability.c
        Files/Modules/Ability.h
        Files/Modules/Adventurer.c
        Files/Modules/Adventurer.h
        Files/Modules/Profession.h
        Files/Modules/Enemy.c
        Files/Modules/Enemy.h
        Files/Services/MapService.c
        Files/Services/MapService.h
        Files/Services/BattleService.c
        Files/Services/BattleService.h
        Files/Services/DialogService.c
        Files/Services/DialogService.h
        Files/Services/EndService.c
        Files/Services/EndService.h
        Files/Services/InventoryService.c
        Files/Services/InventoryService.h
        Files/Services/SaveLoadService.c
        Files/Services/SaveLoadService.h
        Files/Services/ShopService.c
        Files/Services/ShopService.h
        Files/Controllers/BattleController.c
        Files/Controllers/BattleController.h
        Files/Controllers/DialogController.c
        Files/Controllers/DialogController.h
        Files/Controllers/EndController.c
        Files/Controllers/EndController.h
        Files/Controllers/InventoryController.c
        Files/Controllers/InventoryController.h
        Files/Controllers/MapController.c
        Files/Controllers/MapController.h
        Files/Controllers/SaveLoadController.c
        Files/Controllers/SaveLoadController.h
        Files/Controllers/ShopController.c
        Files/Controllers/ShopController.h
        Files/Controllers/Controller.c
        Files/Controllers/Controller.h
        Files/Modules/Profession.h
)
