#include <game/Precompiled.h>
#include <game/Game.h>
#include <game/Input.h>
#include <game/Text.h>
#include <iostream>

Game::Game()
{
}

void Game::Init() noexcept
{
	std::cout << "Initialize game..\n";
	
	glViewport(0, 0, (float)SCREEN_WIDTH, (float)SCREEN_HEIGHT);

	Text &rText = Text::Instance();
	rText.Create((float) SCREEN_WIDTH,(float) SCREEN_HEIGHT);
	rText.SetFace("../assets/fonts/RobotoMono-Regular.ttf");
	float scale[2] = {
		1.f,
		1.f
	};
	rText.SetScale(scale);
	rText.SetFontSize(24);
	rText.SetColor(1.0f, 1.0f, 1.0f, 1.f);
}

void Game::Update(float deltaTime) noexcept
{
	if (Input::Instance().GetKeyState(SDLK_ESCAPE) == 1)
	{
		Stop();

		return;
	}

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.6f, 0.9f, 1.f, 1.f);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();

	glm::mat4 m1 = glm::ortho(0.f, (float)SCREEN_WIDTH, 0.f, (float)SCREEN_HEIGHT, 0.f, 100.f); // near must be equal to zero
	glLoadMatrixf(glm::value_ptr(m1));

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();


	Text &rText = Text::Instance();
	float pos[2] = {
		SCREEN_WIDTH/2,
		SCREEN_HEIGHT/2
	};
	rText.SetPosition(pos);
	rText.SetAlign(Text::ALIGN_CENTER);
	rText.SetText("Hello");

	rText.Render();

	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	
	glDisable(GL_BLEND);

	glFlush();
}
