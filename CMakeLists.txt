cmake_minimum_required(VERSION 3.26)

if(EXISTS "C:/msys64/ucrt64/bin/gcc.exe")
    set(CMAKE_C_COMPILER "C:/msys64/ucrt64/bin/gcc.exe")
endif()

project(Game C)

set(CMAKE_C_STANDARD 11)

if(EXISTS "C:/msys64/ucrt64/lib/libncursesw.a")
    set(CURSES_INCLUDE_DIR "C:/msys64/ucrt64/include;C:/msys64/ucrt64/include/ncurses")
    set(CURSES_LIBRARIES ncursesw)
    link_directories("C:/msys64/ucrt64/lib")
else()
    find_package(Curses REQUIRED)
endif()

add_executable(Game
        Game.c
        Files/Modules/Profession.h
        Files/Modules/State.h
        Files/Modules/ItemTypes.h
        Files/Modules/Ability.c
        Files/Modules/Ability.h
        Files/Modules/Adventurer.c
        Files/Modules/Adventurer.h
        Files/Modules/EnemyEntity.c
        Files/Modules/EnemyEntity.h
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
        Files/Controllers/ShopController.c
        Files/Controllers/ShopController.h
        Files/Controllers/Controller.c
        Files/Controllers/Controller.h
        Files/Services/Service.c
        Files/Services/Service.h
        Files/Modules/Profession.c
        Files/Modules/ItemGenerator.c
        Files/Modules/ItemGenerator.h
        Files/Modules/State.c
)

target_include_directories(Game PRIVATE ${CURSES_INCLUDE_DIR})
target_link_libraries(Game PRIVATE ${CURSES_LIBRARIES})
