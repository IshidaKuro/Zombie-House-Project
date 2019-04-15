#include "cmp_hp.h"
using namespace std;
using namespace sf;

void HPComponent::update(double dt) {

}

int HPComponent::getHP()
{
	return hp;
}

void HPComponent::setHP(int in)
{
	hp = in;
}

HPComponent::HPComponent(Entity* p, int hp)
    : Component(p), hp(hp) {}
