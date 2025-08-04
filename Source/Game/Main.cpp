#include "Audio/AudioSystem.h"
#include "Core/Random.h"
#include "Core/Time.h"
#include "Core/File.h"
#include "Input/InputSystem.h"
#include "Math/Math.h"
#include "Math/Vector2.h"
#include "Math/Transform.h"
#include "FrameWork/Actor.h"
#include "FrameWork/Scene.h"
#include "Renderer/Renderer.h"
#include "Renderer/Model.h"
#include "Renderer/Font.h"
#include "Renderer/Text.h"
#include "Game/Player.h"
#include "Game/SpaceGame.h"
#include "Engine.h"
#include <fmod.hpp>  
#include <vector>
#include <SDL3/SDL.h>
#include <memory>
#include <filesystem>
#include <iostream>
#include <fstream>
#include <sstream>


using namespace std;
using namespace viper;

//define RENDERER viper::GetEngine().GetRenderer()

int main(int argc, char* argv[]) {

	// SET DIRRECTORY
    viper::file::SetCurrentDirectory("Assets");
    
	// INITIALIZE ENGINE
    GetEngine().Initialize();

    // Initialize Game
    std::unique_ptr<SpaceGame> game = std::make_unique<SpaceGame>();
    game->Initialize();

    //// FONT CREATION
    /*std::shared_ptr<Font> font = std::make_shared <viper::Font>();
    font->Load("ka1.ttf", 20);*/

    //// HELLO WORLD TEXT CREATION
    /*std::shared_ptr<Text> text = std::make_shared<viper::Text>(font);
    text->Create(GetEngine().GetRenderer(), "Hello World", vec3{ 1, 1, 1});*/

    // CREATE MAIN LOOP
    SDL_Event e;
    bool quit = false;

	// INITIALIZE SOUNDS
    GetEngine().GetAudio().AddSound("bass.wav", "bass");
    GetEngine().GetAudio().AddSound("snare.wav", "snare");
    GetEngine().GetAudio().AddSound("open-hat.wav", "openhat");
    GetEngine().GetAudio().AddSound("clap.wav", "clap");
    GetEngine().GetAudio().AddSound("cowbell.wav", "cowbell");
    GetEngine().GetAudio().AddSound("close-hat.wav", "closehat");
    GetEngine().GetAudio().AddSound("arcade-fx-288597.mp3", "death");
    GetEngine().GetAudio().AddSound("Yoshi's Island OST - Athletic.mp3", "1music");
    GetEngine().GetAudio().AddSound("game-music-alien-71795.mp3", "music");


    // CREATE STARS
    vector<vec2> stars;
    for (int i = 0; i < 100; i++) {
        stars.push_back(vec2{ random::getRandomFloat() * GetEngine().GetRenderer().GetWidth(), random::getRandomFloat() * GetEngine().GetRenderer().GetHeight() });
    }
    

    //MAIN LOOP
    while (!quit) {
        //time->Tick();
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_EVENT_QUIT) {
                quit = true;
            }          
        }

        GetEngine().Update();
        game->Update(GetEngine().GetTime().GetDeltaTime());

        if (GetEngine().GetInput().GetKeyPressed(SDL_SCANCODE_ESCAPE)) quit = true;

        //// PLAY SOUND
        /*
        //// update engine systems
        //audio->Update();
        //
        ////audio->update();
        //input->Update();
        //
        if (input.getKeyDown(SDL_SCANCODE_Q) && !input.getPrevKeyDown(SDL_SCANCODE_Q))
        {
            // play bass sound, vector elements can be accessed like an array with [#]
            audio.PlaySound("bass");
        }

        if (input.getKeyDown(SDL_SCANCODE_W) && !input.getPrevKeyDown(SDL_SCANCODE_W))
        {
            // play snare sound, vector elements can be accessed like an array with [#]
            audio.PlaySound("snare");
        }

        if (input.getKeyDown(SDL_SCANCODE_E) && !input.getPrevKeyDown(SDL_SCANCODE_E))
        {
            // play open-hat sound, vector elements can be accessed like an array with [#]
            //audio->playSound(sounds[2], nullptr, false, nullptr);
            audio.PlaySound("openhat");
        }

        if (input.getKeyDown(SDL_SCANCODE_A) && !input.getPrevKeyDown(SDL_SCANCODE_A))
        {
            // play clap sound, vector elements can be accessed like an array with [#]
            //audio->playSound(sounds[3], nullptr, false, nullptr);
            audio.PlaySound("clap");
        }

        if (input.getKeyDown(SDL_SCANCODE_S) && !input.getPrevKeyDown(SDL_SCANCODE_S))
        {
            // play cowbell sound, vector elements can be accessed like an array with [#]
            //audio->playSound(sounds[4], nullptr, false, nullptr);
            audio.PlaySound("cowbell");
        }

        if (input.getKeyDown(SDL_SCANCODE_D) && !input.getPrevKeyDown(SDL_SCANCODE_D))
        {
            // play close-hat sound, vector elements can be accessed like an array with [#]
            //audio->playSound(sounds[5], nullptr, false, nullptr);
            audio.PlaySound("closehat");
        }

        if (input.GetKeyPressed(SDL_SCANCODE_A)) {
            cout << "Pressed \n";
        }

        if (input.GetMouseButtonDown(viper::InputSystem::MouseButton::Left)) {
            cout << "mouse pressed \n";
        }
        */

        viper::GetEngine().GetAudio().PlaySound("music");
        
		// CLEAR RENDERER
        vec3 color{0,0,0};
        GetEngine().GetRenderer().SetColor(color.x, color.y, color.z);
        GetEngine().GetRenderer().Clear();

        //// DRAW TEXT
        /*
        text->Draw(GetEngine().GetRenderer(), 40.0f, 40.0f);
        */

		// DRAW GAME
        game->Draw(GetEngine().GetRenderer());

        //// DRAW RAINBOW LINES     
        /*
        if (GetEngine().GetInput().GetMouseButtonDown(viper::InputSystem::MouseButton::Left)) {
            viper::vec2 position = GetEngine().GetInput().GetMousePosition();
            if (points.empty()) points.push_back(position);
            else if ((position - points.back()).Length() > 10) points.push_back(position);
        }
        
        
        for (int i = 0; i < (int)points.size() - 1; i++) {
            GetEngine().GetRenderer().SetColor(random::getRandomInt(256), random::getRandomInt(256), random::getRandomInt(256));
            GetEngine().GetRenderer().DrawLine(points[i].x, points[i].y, points[i + 1].x, points[i + 1].y);
        }
        */


		// DRAW STARS
        vec2 star_speed{ -140.0f,0.0f };
        float length = star_speed.Length();

        for (auto& star : stars) {
            star += star_speed * GetEngine().GetTime().GetDeltaTime();
            //star = star.Add(speed);

            if (star[0] > GetEngine().GetRenderer().GetWidth()) star[0] = 0;
            if (star[0] < 0) star[0] = GetEngine().GetRenderer().GetWidth();
            GetEngine().GetRenderer().SetColor((uint8_t)(random::getRandomInt(256)), random::getRandomInt(256), random::getRandomInt(256));
            GetEngine().GetRenderer().DrawPoint(star.x, star.y);
        }

		//// DRAW RANDOM LINES AND POINTS
        /*for (int i = 0; i < 100; i++) {
            renderer.SetColor(random::getRandomInt(256), random::getRandomInt(256), random::getRandomInt(256));
            renderer.DrawLine(random::getRandomInt(width), random::getRandomInt(height), random::getRandomInt(width), random::getRandomInt(height));

            renderer.SetColor(random::getRandomInt(256), random::getRandomInt(256), random::getRandomInt(256));
            renderer.DrawPoint(v.x,v.y);
            renderer.DrawPoint(random::getRandomFloat() * width, random::getRandomFloat()* height);
        }*/

        GetEngine().GetRenderer().Present();
    }

    // SHUTDOWN
    game->Shutdown();
    game.release();    
    GetEngine().Shutdown();

    return 0;
}