#pragma once

#include "Component.h"

class ObjObject : public Component {
public:
	void onStart() override;
	void onRender() override;
	void onUpdate() override;

	static ObjObject * create(std::string const & val);
};