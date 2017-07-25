/*
* Copyright (C) 2008-2016 TrinityCore <http://www.trinitycore.org/>
*
* This program is free software; you can redistribute it and/or modify it
* under the terms of the GNU General Public License as published by the
* Free Software Foundation; either version 3 of the License, or (at your
* option) any later version.
*
* This program is distributed in the hope that it will be useful, but WITHOUT
* ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
* FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
* more details.
*
* You should have received a copy of the GNU General Public License along
* with this program. If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef TRINITY_POINTMOVEMENTGENERATOR_H
#define TRINITY_POINTMOVEMENTGENERATOR_H

#include "MovementGenerator.h"
#include "FollowerReference.h"

template<class T>
class PointMovementGenerator : public MovementGeneratorMedium< T, PointMovementGenerator<T> >
{
public:
	PointMovementGenerator(uint32 _id, float _x, float _y, float _z, bool _generatePath, float _speed = 0.0f) : id(_id), i_x(_x), i_y(_y), i_z(_z), speed(_speed), m_generatePath(_generatePath), i_recalculateSpeed(false) { }

	void DoInitialize(T* owner);
	void DoFinalize(T* owner);
	void DoReset(T* owner);
	bool DoUpdate(T* owner, uint32 diff);

	void MovementInform(T* owner);
	void unitSpeedChanged() { i_recalculateSpeed = true; }

	MovementGeneratorType GetMovementGeneratorType() { return POINT_MOTION_TYPE; }

	bool GetDestination(float& x, float& y, float& z) const { x = i_x; y = i_y; z = i_z; return true; }

private:
	uint32 id;
	float i_x, i_y, i_z;
	float speed;
	bool m_generatePath;
	bool i_recalculateSpeed;
};

class AssistanceMovementGenerator : public PointMovementGenerator<Creature>
{
public:
	AssistanceMovementGenerator(float _x, float _y, float _z) : PointMovementGenerator<Creature>(0, _x, _y, _z, true) { }

	void DoInitialize(Unit* owner) { }
	void DoFinalize(Unit* owner);
	void DoReset(Unit* owner) { }
	bool DoUpdate(Unit* owner, uint32 diff) { return true; }

	MovementGeneratorType GetMovementGeneratorType() { return ASSISTANCE_MOTION_TYPE; }
};

// Does almost nothing - just doesn't allow previous movegen interrupt current effect.
class EffectMovementGenerator : public MovementGenerator
{
public:
	explicit EffectMovementGenerator(uint32 Id) : m_Id(Id) { }

	void Initialize(Unit* owner) { }
	void Finalize(Unit* owner);
	void Reset(Unit* owner) { }
	bool Update(Unit* owner, uint32 diff);

	void MovementInform(Unit* owner);

	MovementGeneratorType GetMovementGeneratorType() { return EFFECT_MOTION_TYPE; }

private:
	uint32 m_Id;
};

#endif
