project(zombieshooter)

add_executable(${PROJECT_NAME}.elf
        src/main.cpp
        src/resources/spritedata.h
        src/Screens/GameScreen.cpp src/Screens/GameScreen.h
        src/Screens/DeathScreen.cpp src/Screens/DeathScreen.h
        src/Screens/StartScreen.cpp src/Screens/StartScreen.h
        src/resources/DeathScreenImage.h
        src/resources/startscreenimage.h
        src/weapons/Weapon.cpp src/weapons/Weapon.h
        src/Person.cpp src/Person.h
        src/weapons/Pistol.cpp src/weapons/Pistol.h
        src/Zombie.cpp src/Zombie.h
        src/Bullet.cpp src/Bullet.h
        src/weapons/Sniper.cpp src/weapons/Sniper.h
        src/weapons/AK47.cpp src/weapons/AK47.h src/resources/gameBackgroundImage.h src/resources/gunshot.h)

target_link_libraries(${PROJECT_NAME}.elf gba-sprite-engine)

add_custom_command(TARGET ${PROJECT_NAME}.elf POST_BUILD
        COMMAND ${CMAKE_OBJCOPY} -v -O binary ${PROJECT_NAME}.elf ${PROJECT_NAME}.gba
        )
