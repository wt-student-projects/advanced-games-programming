/**
*
* Copyright (c) 2014 : William Taylor : wi11berto@yahoo.co.uk
*
* This software is provided 'as-is', without any
* express or implied warranty. In no event will
* the authors be held liable for any damages
* arising from the use of this software.
*
* Permission is granted to anyone to use this software for any purpose,
* including commercial applications, and to alter it and redistribute
* it freely, subject to the following restrictions:
*
* 1. The origin of this software must not be misrepresented;
*    you must not claim that you wrote the original software.
*    If you use this software in a product, an acknowledgment
*    in the product documentation would be appreciated but
*    is not required.
*
* 2. Altered source versions must be plainly marked as such,
*    and must not be misrepresented as being the original software.
*
* 3. This notice may not be removed or altered from any source distribution.
*/

#include "Multiplayer.h"
#include "Networking.h"
#include "Scenes.h"

Multiplayer::Multiplayer(Bank * bank)
{
	this->bank = bank;
}

Multiplayer::~Multiplayer()
{
}

void Multiplayer::onRender(Renderer& renderer)
{
	renderer.renderTexture(&background);
	renderer.renderLabel(&servername);
	renderer.renderLabel(&hostname);
	renderer.renderLabel(&title);

	renderer.renderButton(&player1);
	renderer.renderButton(&player2);
}

void Multiplayer::onLoad(SceneManager&, Renderer& renderer)
{
	background.create(&renderer, "data/background.png");
	background.setPosition(0, 0, 1920, 1080);
	title.create(font, "Multiplayer", 300);
	title.setPosition(1920 / 2, 200, CENTER);

	this->click = bank->pop_item<Music>("mouse_click_music");

	player1.createL(font, "Player 1", 100);
	player1.setPosition(660, 600, 200, 200);
	player1.onClick(this);

	hostname.create(font, std::string("Your Hostname : ").append(getHostname()), 60);
	hostname.setPosition(10, 1000, RIGHT);

	player2.createL(font, "Player 2", 100);
	player2.setPosition(1060, 600, 200, 200);
	player2.onClick(this);
}

void Multiplayer::onActivated(void * data)
{
	Button * clickedButton = static_cast<Button *>(data);

	click->play(0);

	if (&player1 == clickedButton) {
		OnlinePlayerMap * scene = (OnlinePlayerMap*)sceneManager->getScene(ONLINE_PLAYER_MAP);
		scene->giveDetails("PLAYER1", name.substr(1));
		sceneManager->setScene(ONLINE_PLAYER_MAP);
	}

	if (&player2 == clickedButton) {
		OnlinePlayerMap * scene = (OnlinePlayerMap*)sceneManager->getScene(ONLINE_PLAYER_MAP);
		scene->giveDetails("PLAYER2", name.substr(1));
		sceneManager->setScene(ONLINE_PLAYER_MAP);
	}
}

void Multiplayer::onUpdate(SceneManager& scenes, Renderer&)
{
	sceneManager = &scenes;
}

void Multiplayer::onEvent(SceneManager& scenes, SDL_Event * e)
{
	if (e->key.type == SDL_KEYDOWN && e->key.keysym.sym == SDLK_ESCAPE) {
		scenes.setScene(MENU);
		click->play(0);
	}
	
	if (e->key.type == SDL_KEYDOWN && e->key.keysym.sym == SDLK_BACKSPACE) {
		name.pop_back();
		if (name.empty() || name == "Type Opponents Hostname ..") {
			name = " ";
		}

		servername.create(font, name, 100);
		servername.setPosition(1920 / 2, 500, CENTER);
	}

	if (e->type == SDL_TEXTINPUT) {
		if (name == "Enter opponents hostname ...") {
			name.clear();
		}

		name += e->text.text;

		servername.create(font, name, 100);
		servername.setPosition(1920 / 2, 500, CENTER);
	}

	player1.onEvent(e);
	player2.onEvent(e);
}

void Multiplayer::onEnter()
{
	SDL_StartTextInput();
	
	name = "Type Opponents Hostname ...";

	servername.create(font, name, 100);
	servername.setPosition(1920 / 2, 500, CENTER);
}

void Multiplayer::onExit()
{
	SDL_StopTextInput();
}
