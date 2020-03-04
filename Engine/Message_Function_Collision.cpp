#include "Message_Function_Collision.h"
#include "Component_Item.h"
#include "Component_Player.h"
#include "Engine.hpp"
#include <iostream>
#include "Component_Sprite.h"
#include "Object.h"
#include "Player_Ui.h"
#include "Component_Hpbar.h"
#include "Component_Text.h"
#include "Message.h"
#include "Physics.h"

std::pair<float, float> Damaege_Calculation(Object target, Object from);

void Msg_Func_Collision::Init()
{

	
}

std::pair<float, float> Damaege_Calculation(Object target, Object from)
{
	Physics* target_physics = target.GetComponentByTemplate<Physics>();
	Physics* from_physics = from.GetComponentByTemplate<Physics>();

	if (target_physics != nullptr && from_physics != nullptr)
	{
		float target_scale = 1.f;
		target_scale += target.Get_Plus_Dmg();
		float from_scale = 1.f;
		from_scale += from.Get_Plus_Dmg();

		vector2 target_pos = target.GetTransform().GetTranslation();
		vector2 from_pos = from.GetTransform().GetTranslation();

		bool same_direction_x = false;
		bool same_direction_y = false;

		same_direction_x = (target_physics->GetAcceleration().x < 0 && from_physics->GetAcceleration().x < 0);
		same_direction_x |= (target_physics->GetAcceleration().x > 0 && from_physics->GetAcceleration().x > 0);
		same_direction_y = (target_physics->GetAcceleration().y < 0 && from_physics->GetAcceleration().y < 0);
		same_direction_y |= (target_physics->GetAcceleration().y > 0 && from_physics->GetAcceleration().y > 0);


		//both directions are same.
		if (same_direction_x && same_direction_y)
		{
			//if the positive.
			if (target_physics->GetAcceleration().x > 0)
			{
				if (target_pos.x > from_pos.x&& target_pos.y > from_pos.y)
				{
					std::pair<float, float> dmg;
					dmg.first = (sqrt((from_physics->Get_Save_Acceleration_Reference().x * from_physics->Get_Save_Acceleration_Reference().x) +
						(from_physics->Get_Save_Acceleration_Reference().y * from_physics->Get_Save_Acceleration_Reference().y))) * from_scale;
					dmg.first -= target_scale;
					dmg.second = 2;
					dmg.second -= from_scale;
					return dmg;
				}
				if (from_pos.x > target_pos.x&& from_pos.y > target_pos.y)
				{
					std::pair<float, float> dmg;
					dmg.second = (sqrt((target_physics->Get_Save_Acceleration_Reference().x * target_physics->Get_Save_Acceleration_Reference().x) +
						(target_physics->Get_Save_Acceleration_Reference().y * target_physics->Get_Save_Acceleration_Reference().y))) * target_scale;
					dmg.second -= from_scale;
					dmg.first = 2;
					dmg.first -= target_scale;
					return dmg;
				}

				float target_dmg = (sqrt((from_physics->Get_Save_Acceleration_Reference().x * from_physics->Get_Save_Acceleration_Reference().x) +
					(from_physics->Get_Save_Acceleration_Reference().y * from_physics->Get_Save_Acceleration_Reference().y))) * from_scale;
				target_dmg -= target_scale;
				float from_dmg = (sqrt((target_physics->Get_Save_Acceleration_Reference().x * target_physics->Get_Save_Acceleration_Reference().x) +
					(target_physics->Get_Save_Acceleration_Reference().y * target_physics->Get_Save_Acceleration_Reference().y))) * target_scale;
				from_dmg -= from_scale;
				return std::pair<float, float> {target_dmg, from_dmg};
			}
			if (target_physics->GetAcceleration().x < 0)
			{
				if (target_pos.x < from_pos.x && target_pos.y < from_pos.y)
				{
					std::pair<float, float> dmg;
					dmg.first = (sqrt((from_physics->Get_Save_Acceleration_Reference().x * from_physics->Get_Save_Acceleration_Reference().x) +
						(from_physics->Get_Save_Acceleration_Reference().y * from_physics->Get_Save_Acceleration_Reference().y))) * from_scale;
					dmg.first -= target_scale;
					dmg.second = 2;
					dmg.second -= from_scale;
					return dmg;
				}
				if (from_pos.x < target_pos.x && from_pos.y < target_pos.y)
				{
					std::pair<float, float> dmg;
					dmg.second = (sqrt((target_physics->Get_Save_Acceleration_Reference().x * target_physics->Get_Save_Acceleration_Reference().x) +
						(target_physics->Get_Save_Acceleration_Reference().y * target_physics->Get_Save_Acceleration_Reference().y))) * target_scale;
					dmg.first = 2;
					dmg.second -= from_scale;
					dmg.first -= target_scale;
					return dmg;
				}

				float target_dmg = (sqrt((from_physics->Get_Save_Acceleration_Reference().x * from_physics->Get_Save_Acceleration_Reference().x) +
					(from_physics->Get_Save_Acceleration_Reference().y * from_physics->Get_Save_Acceleration_Reference().y))) * from_scale;
				target_dmg -= target_scale;
				float from_dmg = (sqrt((target_physics->Get_Save_Acceleration_Reference().x * target_physics->Get_Save_Acceleration_Reference().x) +
					(target_physics->Get_Save_Acceleration_Reference().y * target_physics->Get_Save_Acceleration_Reference().y))) * target_scale;
				from_dmg -= from_scale;

				return std::pair<float, float> {target_dmg, from_dmg};
			}
		}
		else if (same_direction_x)
		{
			if (target_physics->GetAcceleration().x > 0)
			{
				if (target_pos.x > from_pos.x)
				{
					std::pair<float, float> dmg;
					dmg.first = (sqrt((from_physics->Get_Save_Acceleration_Reference().x * from_physics->Get_Save_Acceleration_Reference().x) +
						(from_physics->Get_Save_Acceleration_Reference().y * from_physics->Get_Save_Acceleration_Reference().y))) * from_scale;
					dmg.first -= target_scale;
					dmg.second = 2;
					dmg.second -= from_scale;
					return dmg;
				}
				if (from_pos.x > target_pos.x)
				{
					std::pair<float, float> dmg;
					dmg.second = (sqrt((target_physics->Get_Save_Acceleration_Reference().x * target_physics->Get_Save_Acceleration_Reference().x) +
						(target_physics->Get_Save_Acceleration_Reference().y * target_physics->Get_Save_Acceleration_Reference().y))) * target_scale;

					dmg.first = 2;
					dmg.first -= target_scale;
					dmg.second -= from_scale;
					return dmg;
				}
			}
			if (target_physics->GetAcceleration().x < 0)
			{
				if (target_pos.x < from_pos.x)
				{
					std::pair<float, float> dmg;
					dmg.first = (sqrt((from_physics->Get_Save_Acceleration_Reference().x * from_physics->Get_Save_Acceleration_Reference().x) +
						(from_physics->Get_Save_Acceleration_Reference().y * from_physics->Get_Save_Acceleration_Reference().y))) * from_scale;
					dmg.second = 2;
					dmg.first -= target_scale;
					dmg.second -= from_scale;

					return dmg;
				}
				if (from_pos.x < target_pos.x)
				{
					std::pair<float, float> dmg;
					dmg.second = (sqrt((target_physics->Get_Save_Acceleration_Reference().x * target_physics->Get_Save_Acceleration_Reference().x) +
						(target_physics->Get_Save_Acceleration_Reference().y * target_physics->Get_Save_Acceleration_Reference().y))) * target_scale;
					dmg.first = 2;
					dmg.first -= target_scale;
					dmg.second -= from_scale;

					return dmg;
				}
			}
			float target_dmg = (sqrt((from_physics->Get_Save_Acceleration_Reference().x * from_physics->Get_Save_Acceleration_Reference().x) +
				(from_physics->Get_Save_Acceleration_Reference().y * from_physics->Get_Save_Acceleration_Reference().y))) * from_scale;
			target_dmg -= target_scale;
			float from_dmg = (sqrt((target_physics->Get_Save_Acceleration_Reference().x * target_physics->Get_Save_Acceleration_Reference().x) +
				(target_physics->Get_Save_Acceleration_Reference().y * target_physics->Get_Save_Acceleration_Reference().y))) * target_scale;
			from_dmg -= from_scale;
			return std::pair<float, float> {target_dmg, from_dmg};
		}
		else if (same_direction_y)
		{
			if (target_physics->GetAcceleration().y > 0)
			{
				if (target_pos.y > from_pos.y)
				{
					std::pair<float, float> dmg;
					dmg.first = (sqrt((from_physics->Get_Save_Acceleration_Reference().x * from_physics->Get_Save_Acceleration_Reference().x) +
						(from_physics->Get_Save_Acceleration_Reference().y * from_physics->Get_Save_Acceleration_Reference().y))) * from_scale;
					dmg.second = 2;
					dmg.first -= target_scale;
					dmg.second -= from_scale;

					return dmg;
				}
				if (from_pos.y > target_pos.y)
				{
					std::pair<float, float> dmg;
					dmg.second = (sqrt((target_physics->Get_Save_Acceleration_Reference().x * target_physics->Get_Save_Acceleration_Reference().x) +
						(target_physics->Get_Save_Acceleration_Reference().y * target_physics->Get_Save_Acceleration_Reference().y))) * target_scale;
					dmg.first = 2;
					dmg.first -= target_scale;
					dmg.second -= from_scale;

					return dmg;
				}
			}
			if (target_physics->GetAcceleration().y < 0)
			{
				if (target_pos.y < from_pos.y)
				{
					std::pair<float, float> dmg;
					dmg.first = (sqrt((from_physics->Get_Save_Acceleration_Reference().x * from_physics->Get_Save_Acceleration_Reference().x) +
						(from_physics->Get_Save_Acceleration_Reference().y * from_physics->Get_Save_Acceleration_Reference().y))) * from_scale;
					dmg.second = 2;
					dmg.first -= target_scale;
					dmg.second -= from_scale;

					return dmg;
				}
				if (from_pos.y < target_pos.y)
				{
					std::pair<float, float> dmg;
					dmg.second = (sqrt((target_physics->Get_Save_Acceleration_Reference().x * target_physics->Get_Save_Acceleration_Reference().x) +
						(target_physics->Get_Save_Acceleration_Reference().y * target_physics->Get_Save_Acceleration_Reference().y))) * target_scale;
					dmg.first = 2;
					dmg.first -= target_scale;
					dmg.second -= from_scale;

					return dmg;
				}
			}
			float target_dmg = (sqrt((from_physics->Get_Save_Acceleration_Reference().x * from_physics->Get_Save_Acceleration_Reference().x) +
				(from_physics->Get_Save_Acceleration_Reference().y * from_physics->Get_Save_Acceleration_Reference().y))) * from_scale;
			target_dmg -= target_scale;
			float from_dmg = (sqrt((target_physics->Get_Save_Acceleration_Reference().x * target_physics->Get_Save_Acceleration_Reference().x) +
				(target_physics->Get_Save_Acceleration_Reference().y * target_physics->Get_Save_Acceleration_Reference().y))) * target_scale;
			from_dmg -= from_scale;
			return std::pair<float, float> {target_dmg, from_dmg};
		}
		else
		{
			float target_dmg = (sqrt((from_physics->Get_Save_Acceleration_Reference().x * from_physics->Get_Save_Acceleration_Reference().x) +
				(from_physics->Get_Save_Acceleration_Reference().y * from_physics->Get_Save_Acceleration_Reference().y))) * from_scale;
			float from_dmg = (sqrt((target_physics->Get_Save_Acceleration_Reference().x * target_physics->Get_Save_Acceleration_Reference().x) +
				(target_physics->Get_Save_Acceleration_Reference().y * target_physics->Get_Save_Acceleration_Reference().y))) * target_scale;
			target_dmg -= target_scale;
			from_dmg -= from_scale;
			return std::pair<float, float> {target_dmg, from_dmg};
		}

	}

}

void Msg_Func_Collision::Update(float dt)
{
	if (m_target->Get_Tag() == "item" && m_from->Get_Tag() == "player")
	{
		sound.Play(SOUND::Item);
		std::cout << "item" << std::endl;
		if (m_target->GetComponentByTemplate<Item>()->Get_Kind() == Item::Item_Kind::Dash)
		{
			m_target->SetDeadCondition(true);
			if (m_from->GetComponentByTemplate<Player>() != nullptr)
			{
				m_from->GetComponentByTemplate<Player>()->Set_Item_State(Item::Item_Kind::Dash);

				if (m_from->GetComponentByTemplate<Player>()->Get_Ui()->Get_Item_Info()->GetComponentByTemplate<Sprite>() == nullptr)
				{
					m_from->GetComponentByTemplate<Player>()->Get_Ui()->Get_Item_Info()->AddComponent(new Sprite(
						m_from->GetComponentByTemplate<Player>()->Get_Ui()->Get_Item_Info(), "../sprite/dash.png",
						m_from->GetComponentByTemplate<Player>()->Get_Ui()->Get_Item_Info()->GetTransform().GetTranslation()
						, false));

					m_from->GetComponentByTemplate<Player>()->Get_Ui()->Get_Item_Info()->GetMesh().Get_Is_Moved() = true;
				}
			}
		}
		if (m_target->GetComponentByTemplate<Item>()->Get_Kind() == Item::Item_Kind::HP)
		{
			m_target->SetDeadCondition(true);
			if (m_from->GetComponentByTemplate<Player>() != nullptr)
			{
				m_from->GetComponentByTemplate<Player>()->Set_Item_State(Item::Item_Kind::HP);

				if (m_from->GetComponentByTemplate<Player>()->Get_Ui()->Get_Item_Info()->GetComponentByTemplate<Sprite>() == nullptr)
				{
					m_from->GetComponentByTemplate<Player>()->Get_Ui()->Get_Item_Info()->AddComponent(new Sprite(
						m_from->GetComponentByTemplate<Player>()->Get_Ui()->Get_Item_Info(), "../sprite/heal.png",
						m_from->GetComponentByTemplate<Player>()->Get_Ui()->Get_Item_Info()->GetTransform().GetTranslation(), false));


					m_from->GetComponentByTemplate<Player>()->Get_Ui()->Get_Item_Info()->GetMesh().Get_Is_Moved() = true;
				}
			}
		}
		if (m_target->GetComponentByTemplate<Item>()->Get_Kind() == Item::Item_Kind::Bulkup)
		{
			m_target->SetDeadCondition(true);
			if (m_from->GetComponentByTemplate<Player>() != nullptr)
			{
				m_from->GetComponentByTemplate<Player>()->Set_Item_State(Item::Item_Kind::Bulkup);

				if (m_from->GetComponentByTemplate<Player>()->Get_Ui()->Get_Item_Info()->GetComponentByTemplate<Sprite>() == nullptr)
				{
					m_from->GetComponentByTemplate<Player>()->Get_Ui()->Get_Item_Info()->AddComponent(new Sprite(
						m_from->GetComponentByTemplate<Player>()->Get_Ui()->Get_Item_Info(), "../sprite/bulkup.png",
						m_from->GetComponentByTemplate<Player>()->Get_Ui()->Get_Item_Info()->GetTransform().GetTranslation(), false));


					m_from->GetComponentByTemplate<Player>()->Get_Ui()->Get_Item_Info()->GetMesh().Get_Is_Moved() = true;
				}
			}
		}
		if (m_target->GetComponentByTemplate<Item>()->Get_Kind() == Item::Item_Kind::Throwing)
		{
			m_target->SetDeadCondition(true);
			if (m_from->GetComponentByTemplate<Player>() != nullptr)
			{
				m_from->GetComponentByTemplate<Player>()->Set_Item_State(Item::Item_Kind::Throwing);

				if (m_from->GetComponentByTemplate<Player>()->Get_Ui()->Get_Item_Info()->GetComponentByTemplate<Sprite>() == nullptr)
				{
					m_from->GetComponentByTemplate<Player>()->Get_Ui()->Get_Item_Info()->AddComponent(new Sprite(
						m_from->GetComponentByTemplate<Player>()->Get_Ui()->Get_Item_Info(), "../sprite/Master.png",
						m_from->GetComponentByTemplate<Player>()->Get_Ui()->Get_Item_Info()->GetTransform().GetTranslation(), false));


					m_from->GetComponentByTemplate<Player>()->Get_Ui()->Get_Item_Info()->GetMesh().Get_Is_Moved() = true;
				}
			}
		}
	}
	else if (m_from->Get_Tag() == "item" && m_target->Get_Tag() == "player")
	{
		if (m_from->GetComponentByTemplate<Item>()->Get_Kind() == Item::Item_Kind::Dash)
		{
			m_from->SetDeadCondition(true);
			if (m_target->GetComponentByTemplate<Player>() != nullptr)
			{
				m_target->GetComponentByTemplate<Player>()->Set_Item_State(Item::Item_Kind::Dash);

				if (m_target->GetComponentByTemplate<Player>()->Get_Ui()->Get_Item_Info()->GetComponentByTemplate<Sprite>() == nullptr)
				{
					m_target->GetComponentByTemplate<Player>()->Get_Ui()->Get_Item_Info()->AddComponent(new Sprite(
						m_target->GetComponentByTemplate<Player>()->Get_Ui()->Get_Item_Info(), "../sprite/dash.png",
						m_target->GetComponentByTemplate<Player>()->Get_Ui()->Get_Item_Info()->GetTransform().GetTranslation(), false));
					m_target->GetComponentByTemplate<Player>()->Get_Ui()->Get_Item_Info()->GetMesh().Get_Is_Moved() = true;
				}
			}
		}
		if (m_from->GetComponentByTemplate<Item>()->Get_Kind() == Item::Item_Kind::HP)
		{
			m_from->SetDeadCondition(true);
			if (m_target->GetComponentByTemplate<Player>() != nullptr)
			{
				m_target->GetComponentByTemplate<Player>()->Set_Item_State(Item::Item_Kind::HP);

				if (m_target->GetComponentByTemplate<Player>()->Get_Ui()->Get_Item_Info()->GetComponentByTemplate<Sprite>() == nullptr)
				{
					m_target->GetComponentByTemplate<Player>()->Get_Ui()->Get_Item_Info()->AddComponent(new Sprite(
						m_target->GetComponentByTemplate<Player>()->Get_Ui()->Get_Item_Info(), "../sprite/heal.png",
						m_target->GetComponentByTemplate<Player>()->Get_Ui()->Get_Item_Info()->GetTransform().GetTranslation(), false));

					m_target->GetComponentByTemplate<Player>()->Get_Ui()->Get_Item_Info()->GetMesh().Get_Is_Moved() = true;
				}
			}
		}
		if (m_from->GetComponentByTemplate<Item>()->Get_Kind() == Item::Item_Kind::Bulkup)
		{
			m_from->SetDeadCondition(true);
			if (m_target->GetComponentByTemplate<Player>() != nullptr)
			{
				m_target->GetComponentByTemplate<Player>()->Set_Item_State(Item::Item_Kind::Bulkup);

				if (m_target->GetComponentByTemplate<Player>()->Get_Ui()->Get_Item_Info()->GetComponentByTemplate<Sprite>() == nullptr)
				{
					m_target->GetComponentByTemplate<Player>()->Get_Ui()->Get_Item_Info()->AddComponent(new Sprite(
						m_target->GetComponentByTemplate<Player>()->Get_Ui()->Get_Item_Info(), "../sprite/bulkup.png",
						m_target->GetComponentByTemplate<Player>()->Get_Ui()->Get_Item_Info()->GetTransform().GetTranslation(), false));

					m_target->GetComponentByTemplate<Player>()->Get_Ui()->Get_Item_Info()->GetMesh().Get_Is_Moved() = true;
				}
			}
		}
		if (m_from->GetComponentByTemplate<Item>()->Get_Kind() == Item::Item_Kind::Throwing)
		{
			m_from->SetDeadCondition(true);
			if (m_target->GetComponentByTemplate<Player>() != nullptr)
			{
				m_target->GetComponentByTemplate<Player>()->Set_Item_State(Item::Item_Kind::Throwing);

				if (m_target->GetComponentByTemplate<Player>()->Get_Ui()->Get_Item_Info()->GetComponentByTemplate<Sprite>() == nullptr)
				{
					m_target->GetComponentByTemplate<Player>()->Get_Ui()->Get_Item_Info()->AddComponent(new Sprite(
						m_target->GetComponentByTemplate<Player>()->Get_Ui()->Get_Item_Info(), "../sprite/Master.png",
						m_target->GetComponentByTemplate<Player>()->Get_Ui()->Get_Item_Info()->GetTransform().GetTranslation(), false));

					m_target->GetComponentByTemplate<Player>()->Get_Ui()->Get_Item_Info()->GetMesh().Get_Is_Moved() = true;
				}
			}
		}
	}
	else
	{
		std::pair<float, float> dmg_set = Damaege_Calculation(*m_target, *m_from);

		m_target->GetComponentByTemplate<Player>()->Get_Regeneration_Timer() = 0.f;
		m_from->GetComponentByTemplate<Player>()->Get_Regeneration_Timer() = 0.f;

		m_target->Get_Dmg_Text()->GetComponentByTemplate<TextComp>()->GetText().SetString(L"-" + std::to_wstring(static_cast<int>(dmg_set.first)));
		m_target->Get_Dmg_Text()->GetComponentByTemplate<TextComp>()->Get_Timer() = 1.f;
		m_from->Get_Dmg_Text()->GetComponentByTemplate<TextComp>()->GetText().SetString(L"-" + std::to_wstring(static_cast<int>(dmg_set.second)));
		m_from->Get_Dmg_Text()->GetComponentByTemplate<TextComp>()->Get_Timer() = 1.f;

		m_target->Get_Dmg_Text()->GetTransform().GetTranslation_Reference().x = m_target->GetTransform().GetTranslation().x;
		m_target->Get_Dmg_Text()->GetTransform().GetTranslation_Reference().y = m_target->GetTransform().GetTranslation().y;

		m_from->Get_Dmg_Text()->GetTransform().GetTranslation_Reference().x = m_from->GetTransform().GetTranslation().x;
		m_from->Get_Dmg_Text()->GetTransform().GetTranslation_Reference().y = m_from->GetTransform().GetTranslation().y;

		if (m_from->GetComponentByTemplate<Player>() != nullptr)
		{
			m_target->Set_Hitted_By(m_from);
		}

		if (m_target->GetComponentByTemplate<Player>() != nullptr)
		{
			m_from->Set_Hitted_By(m_target);
		}
		Object* target_hp_bar = m_target->Get_Belong_Object_By_Tag("hp_bar");
		Object* from_hp_bar = m_from->Get_Belong_Object_By_Tag("hp_bar");

		if (target_hp_bar != nullptr || from_hp_bar != nullptr)
		{
			target_hp_bar->GetComponentByTemplate<Hp_Bar>()->Decrease(dmg_set.first / 50);
			from_hp_bar->GetComponentByTemplate<Hp_Bar>()->Decrease(dmg_set.second / 50);
		}
	}

	msg->Set_Should_Delete(true);
	
}
