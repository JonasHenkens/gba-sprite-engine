project(zombieshooter)

add_executable(${PROJECT_NAME}.elf
        src/main.cpp
        src/pats.h
        src/GameScreen.cpp src/GameScreen.h src/DeathScreen.cpp src/DeathScreen.h
        src/spritedata.h src/dead.h src/StartScreen.cpp src/StartScreen.h src/splashimage.h
        src/DeathScreenImage.h
        src/startscreenimage.h
        src/Bullet.h
        src/Weapon.cpp src/Weapon.h
        src/Person.cpp src/Person.h src/Pistol.h
        src/Zombie.cpp src/Zombie.h)

target_link_libraries(${PROJECT_NAME}.elf gba-sprite-engine)

add_custom_command(TARGET ${PROJECT_NAME}.elf POST_BUILD
        COMMAND ${CMAKE_OBJCOPY} -v -O binary ${PROJECT_NAME}.elf ${PROJECT_NAME}.gba
        )
