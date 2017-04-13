/*
    Miden Engine, the real one. Built with OpenGL and SDL
    Copyright (C) 2017 Scott Winkelmann <scottlandart@gmail.com>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "libs.h"
#include "engine/display.h"
#include "engine/game.h"
#include "engine/utils/time.h"

class MainComponent
{
private:
    Game* m_game;
    SDL_Event m_e;
    const float m_frameCap = 60.0f;

    void run()
    {
        m_game->initScene();
        m_game->isRunning = true;

        float frameTime = 1.0f/m_frameCap;
        uint frames = 0;
        ulong frameCounter = 0;

        ulong lastTime = Time::getTime();
        ulong startTime = 0;
        ulong passedTime = 0;

        float unprocessedTime = 0;
        bool needToRender = false;


        while(m_game->isRunning)
        {
            needToRender = false;

            //how long the last frame took to render
            startTime = Time::getTime();
            passedTime = startTime - lastTime;
            lastTime = startTime;

            unprocessedTime+=passedTime/(float)Time::second;
            frameCounter+=passedTime;

            while(unprocessedTime > frameTime)
            {
                needToRender = true;
                unprocessedTime-=frameTime;

                m_game->update();

                //FPS counter
                if(frameCounter >= Time::second)
                {
                    m_game->display->setTitle("FPS: "+to_string(frames));
                    frames = 0;
                    frameCounter = 0;
                }
            }
            if(needToRender)
            {
                render();
                frames++;
            }
            else
            {
                Time::sleep(1);
            }
        }

        clean();
    }
    void render()
    {
        m_game->display->clear();

        m_game->render();

        m_game->display->swap();
    }
    void clean()
    {
        m_game->quit();
    }

public:
    MainComponent(Display* display)
    {
        m_game = new Game(display);
    }

    void start()
    {
        if(!m_game->isRunning)
        {
            run();
        }
    }
    void stop()
    {
        if(m_game->isRunning)
        {
            m_game->isRunning = false;
        }
    }
};

int main()
{
    const int width = 1280;
    const int height = 720;
    const string title = "Miden Engine";

    Display d(width,height,title);
    MainComponent game(&d);

    game.start();
}
