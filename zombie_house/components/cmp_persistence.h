#pragma once
#include <ecm.h>

class LoadFileComponent : public Component {
protected:

public:
	//LoadFileComponent() = delete;
	void LoadFile();
	explicit LoadFileComponent(Entity* p);
};

class SaveFileComponent : public Component {
protected:
	std::string level;
	std::weak_ptr<Entity> _player;
public:
	void setLevel(std::string in);
	void update(double dt) override;
	void render() override {}
	SaveFileComponent() = delete;
	void SaveFile();
	explicit SaveFileComponent(Entity* p);
};