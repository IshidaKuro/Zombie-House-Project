#include "cmp_hp.h"
using namespace std;
using namespace sf;

void HPComponent::update(double dt) {

}

int HPComponent::getHP()
{
	return hp;
}

HPComponent::HPComponent(Entity* p, int hp)
    : Component(p), hp(hp) {}
