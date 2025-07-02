#include <strix/strix.h>
#include <strix/module.h>
#include <iostream>

#include <strix/strix_gl.h>

void onStart(){
    glClearColor(0.0f, 0.0f, 0.4f, 1.0f);
    // Initialize game resources
    std::cout << "Game started!" << std::endl;
}

void onUpdate(float delta){
    // Update game state
    std::cout << "Game updated!" << std::endl;
}

void onRender(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // Render game graphics
    std::cout << "Game rendered!" << std::endl;
}

void onStop(){
    // Clean up game resources
    std::cout << "Game ended!" << std::endl;
}