#include "cmp_hurt_player.h"
#include <engine.h>
#include <SFML/Audio/Sound.hpp>
#include <SFML/Audio/SoundBuffer.hpp>

using namespace std;
using namespace sf;

sf::SoundBuffer buffer4;
sf::Sound sound4;

void HurtComponent::update(double dt) {
  if (auto pl = _player.lock()) {
    if (length(pl->getPosition() - _parent->getPosition()) < 25.0) {
		if (!buffer4.loadFromFile("res/sounds/player_die.wav"))
		{
			cout << "Error loading zombie sound";
		}
		else
		{
			cout << "Play sound";

			sound4.setBuffer(buffer4);
			sound4.play();
		}

		pl->setForDelete();
		_parent->setForDelete();
    }
  }
}

HurtComponent::HurtComponent(Entity* p)
    : Component(p), _player(_parent->scene->ents.find("player")[0]) {}
