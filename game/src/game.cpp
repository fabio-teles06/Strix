#include <iostream>

void onStart(){
    // Initialize game resources
    std::cout << "Game started!" << std::endl;
}

void onUpdate(){
    // Update game state
    std::cout << "Game updated!" << std::endl;
}

void onRender(){
    // Render game graphics
    std::cout << "Game rendered!" << std::endl;
}

void onEnd(){
    // Clean up game resources
    std::cout << "Game ended!" << std::endl;
}