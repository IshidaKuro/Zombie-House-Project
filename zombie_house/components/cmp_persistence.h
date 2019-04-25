#pragma once
#include <ecm.h>

class LoadFileComponent : public Component {
protected:

public:
	LoadFileComponent() = delete;
	void update(double dt) override;
	void render() override {}
	
	std::string LoadFile(std::string fileToRead);
	explicit LoadFileComponent(Entity* p);
};

class SaveFileComponent : public Component {
protected:
	std::string level;
	std::weak_ptr<Entity> _player;
public:
	void update(double dt) override;
	void render() override {}
	SaveFileComponent() = delete;
	void SaveFile(std::string in);
	explicit SaveFileComponent(Entity* p);
};