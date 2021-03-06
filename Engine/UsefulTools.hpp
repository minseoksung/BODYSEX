#pragma once
#include "vector2.hpp"

class Object;
bool MouseCollision(vector2 object_pos_max, vector2 object_pos_min, vector2 mouse_pos);
void ObjectHover(Object* current_obj, Object* next_obj);
std::wstring StringToWstring(std::string str);