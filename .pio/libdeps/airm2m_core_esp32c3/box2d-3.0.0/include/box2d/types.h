// SPDX-FileCopyrightText: 2023 Erin Catto
// SPDX-License-Identifier: MIT

#pragma once

#include "base.h"
#include "collision.h"
#include "id.h"
#include "math_functions.h"

#include <stdbool.h>
#include <stdint.h>

/// 任务界面
/// 这是Box2D任务的原型。您的任务系统应使用这些参数调用Box2D任务。
/// 该任务跨越了以下并行范围：[startIndex，endIndex）
/// worker索引必须正确标识用户线程池中的每个worker，预期在[0，workerCount）中。
/// 一个worker一次只能存在于一个线程上，类似于线程索引。
/// 任务上下文是Box2D在排队时发送的上下文指针。
/// startIndex和endIndex应在[0，itemCount）范围内，其中itemCount是b2EnqueueTaskCallback的参数
/// 在......下面Box2D需要startIndex<endIndex，并将执行如下循环：
///
///	@code{.c}
/// for (int i = startIndex; i < endIndex; ++i)
///	{
///		DoWork();
///	}
///	@endcode
///	@ingroup world
typedef void b2TaskCallback( int32_t startIndex, int32_t endIndex, uint32_t workerIndex, void* taskContext );

///这些函数可以提供给Box2D来调用任务系统。这些设计用于与enkiTS配合使用。
///返回指向用户任务对象的指针。可能为空。nullptr向Box2D指示工作已执行
///在回调中连续执行，无需调用b2FinishTaskCallback。
///itemCount是由用户的任务系统在workers之间划分的Box2D工作项的数量。
///这基本上是一个平行。minRange参数是要分配的最小项目数的建议
///每个工人减少开销。例如，假设任务很小，itemCount为16。minRange为8表示
///即使你有更多可用的工作项，你的任务系统也应该将工作项拆分给两个工人。
///一般来说，发送到b2TaskCallback的范围[startIndex，endIndex）应遵守：
///endIndex-startIndex>=minRange
///当然，itemCount<minRange时除外。
///	@ingroup world
typedef void* b2EnqueueTaskCallback( b2TaskCallback* task, int32_t itemCount, int32_t minRange, void* taskContext,
									 void* userContext );

/// 完成包装Box2D任务的用户任务对象。
///	@ingroup world
typedef void b2FinishTaskCallback( void* userTask, void* userContext );

/// 来自b2World_RayCastClosest的结果
/// @ingroup world
typedef struct b2RayResult
{
	b2ShapeId shapeId;
	b2Vec2 point;
	b2Vec2 normal;
	float fraction;
	bool hit;
} b2RayResult;

///用于创建模拟世界的世界定义。
///必须使用b2DefaultWorldDef（）初始化。
/// @ingroup world
typedef struct b2WorldDef
{
	/// 重力矢量。Box2D没有定义向上矢量。
	b2Vec2 gravity;

	/// 恢复速度阈值，通常以m/s为单位。超过此速度的碰撞将应用恢复（将反弹）。
	float restitutionThreshold;

	/// This parameter controls how fast overlap is resolved and has units of meters per second
	float contactPushoutVelocity;

	/// Threshold velocity for hit events. Usually meters per second.
	float hitEventThreshold;

	/// Contact stiffness. Cycles per second.
	float contactHertz;

	/// Contact bounciness. Non-dimensional.
	float contactDampingRatio;

	/// Joint stiffness. Cycles per second.
	float jointHertz;

	/// Joint bounciness. Non-dimensional.
	float jointDampingRatio;

	/// Maximum linear velocity. Usually meters per second.
	float maximumLinearVelocity;

	/// Can bodies go to sleep to improve performance
	bool enableSleep;

	/// Enable continuous collision
	bool enableContinous;

	/// Number of workers to use with the provided task system. Box2D performs best when using only
	///	performance cores and accessing a single L2 cache. Efficiency cores and hyper-threading provide
	///	little benefit and may even harm performance.
	int32_t workerCount;

	/// Function to spawn tasks
	b2EnqueueTaskCallback* enqueueTask;

	/// Function to finish a task
	b2FinishTaskCallback* finishTask;

	/// User context that is provided to enqueueTask and finishTask
	void* userTaskContext;

	/// Used internally to detect a valid definition. DO NOT SET.
	int32_t internalValue;
} b2WorldDef;

/// Use this to initialize your world definition
/// @ingroup world
B2_API b2WorldDef b2DefaultWorldDef( void );

/// 车身模拟类型。
/// 每个身体都是这三种类型之一。该类型决定了实体在模拟中的行为方式。
/// @ingroup body
typedef enum b2BodyType
{
	/// 零质量、零速度，可以手动移动
	b2_staticBody = 0,

	/// 零质量，速度由用户设置，由求解器移动
	b2_kinematicBody = 1,

	/// 正质量，速度由力决定，由求解器移动
	b2_dynamicBody = 2,

	/// 体型数量
	b2_bodyTypeCount,
} b2BodyType;

/// 实体定义包含构造刚体所需的所有数据。
/// 您可以安全地重复使用身体定义。形状在构造后添加到主体中。
/// 主体定义是用于捆绑创建参数的临时对象。
/// 必须使用b2DefaultBodyDef（）初始化。
/// @ingroup body
typedef struct b2BodyDef
{
	/// 身体类型：静态、运动学或动态。
	b2BodyType type;

	/// 身体的初始世界位置。应按所需位置创建实体。
	///@note 在原点创建实体，然后移动它们，几乎会使实体创建的成本加倍，特别是在添加形状后移动实体的情况下。
	b2Vec2 position;

	/// 身体的初始世界旋转。如果有角度，请使用b2MakeRot（）。
	b2Rot rotation;

	/// 物体原点的初始线速度。通常以米每秒为单位。
	b2Vec2 linearVelocity;

	/// 物体的初始角速度。每秒弧度数。
	float angularVelocity;

	/// 线性阻尼用于降低线速度。阻尼参数可以大于1，但当阻尼参数较大时，阻尼效果对时间步长变得敏感。
	/// 一般来说，线性阻尼是不可取的，因为它会使物体像漂浮一样缓慢移动
	float linearDamping;

	/// 角阻尼用于降低角速度。阻尼参数可以大于1.0f，
	/// 但当阻尼参数较大时，阻尼效果对时间步长变得敏感。角阻尼可以使用减速旋转体。
	float angularDamping;

	/// 缩放施加在该物体上的重力。无量纲。
	float gravityScale;

	/// 缩放施加在该物体上的重力。无量纲
	float sleepThreshold;

	/// 使用此功能存储特定于应用程序的正文数据。
	void* userData;

	/// 如果这个身体永远不会睡着，请将此标志设置为false。
	bool enableSleep;

	/// 这个身体最初是醒着还是睡着了？
	bool isAwake;

	/// 应该阻止这个机构旋转吗？对角色有用。
	bool fixedRotation;

	///将该物体视为高速物体，对动态和运动学物体进行连续碰撞检测，而不是其他弹体。
	///	@warning 子弹应谨慎使用。它们不是一般动态碰撞与动态连续碰撞的解决方案。它们可能会干扰关节约束
	bool isBullet;

	/// 用于禁用身体。残疾的身体不会移动或碰撞。
	bool isEnabled;

	/// 根据形状自动计算此物体的质量和相关属性。
	/// 每当添加/删除/更改形状时触发。默认值为true。
	bool automaticMass;

	/// 这允许该机构绕过转速限制。应仅用于圆形物体，如轮子。
	bool allowFastRotation;

	/// 内部用于检测有效定义。不要设置。
	int32_t internalValue;
} b2BodyDef;

/// 使用此选项初始化您的身体定义
/// @ingroup body
B2_API b2BodyDef b2DefaultBodyDef( void );

/// 这用于过滤形状上的碰撞。它会影响形状与形状碰撞和形状与查询碰撞（如b2World_CastRay）。
/// @ingroup shape
typedef struct b2Filter
{
	/// The collision category bits. Normally you would just set one bit. The category bits should
	///	represent your application object types. For example:
	///	@code{.cpp}
	///	enum MyCategories
	///	{
	///	   Static  = 0x00000001,
	///	   Dynamic = 0x00000002,
	///	   Debris  = 0x00000004,
	///	   Player  = 0x00000008,
	///	   // etc
	/// };
	///	@endcode
	uint32_t categoryBits;

	/// The collision mask bits. This states the categories that this
	/// shape would accept for collision.
	///	For example, you may want your player to only collide with static objects
	///	and other players.
	///	@code{.c}
	///	maskBits = Static | Player;
	///	@endcode
	uint32_t maskBits;

	/// Collision groups allow a certain group of objects to never collide (negative)
	/// or always collide (positive). A group index of zero has no effect. Non-zero group filtering
	/// always wins against the mask bits.
	///	For example, you may want ragdolls to collide with other ragdolls but you don't want
	///	ragdoll self-collision. In this case you would give each ragdoll a unique negative group index
	///	and apply that group index to all shapes on the ragdoll.
	int32_t groupIndex;
} b2Filter;

/// Use this to initialize your filter
/// @ingroup shape
B2_API b2Filter b2DefaultFilter( void );

/// The query filter is used to filter collisions between queries and shapes. For example,
///	you may want a ray-cast representing a projectile to hit players and the static environment
///	but not debris.
/// @ingroup shape
typedef struct b2QueryFilter
{
	/// The collision category bits of this query. Normally you would just set one bit.
	uint32_t categoryBits;

	/// The collision mask bits. This states the shape categories that this
	/// query would accept for collision.
	uint32_t maskBits;
} b2QueryFilter;

/// Use this to initialize your query filter
/// @ingroup shape
B2_API b2QueryFilter b2DefaultQueryFilter( void );

/// Shape type
/// @ingroup shape
typedef enum b2ShapeType
{
	/// A circle with an offset
	b2_circleShape,

	/// A capsule is an extruded circle
	b2_capsuleShape,

	/// A line segment
	b2_segmentShape,

	/// A convex polygon
	b2_polygonShape,

	/// A smooth segment owned by a chain shape
	b2_smoothSegmentShape,

	/// The number of shape types
	b2_shapeTypeCount
} b2ShapeType;

///用于创建形状。
///这是一个用于捆绑形状创建参数的临时对象。您可以使用相同的形状定义来创建多个形状。
///必须使用b2DefaultShapeDef（）初始化。
/// @ingroup shape 形状
typedef struct b2ShapeDef
{
	/// 使用此功能存储特定于应用程序的形状数据。
	void* userData;

	/// 库仑（干）摩擦系数，通常在[0,1]范围内。
	float friction;

	/// 恢复（反弹）通常在[0,1]范围内。
	float restitution;

	/// 密度，通常以kg/m^2为单位。
	float density;

	/// 碰撞过滤数据。
	b2Filter filter;

	/// 自定义调试绘图颜色。
	uint32_t customColor;

	/// 传感器形状会产生重叠事件，但从不产生碰撞响应。
	bool isSensor;

	/// 为此形状启用传感器事件。仅适用于运动学和动力学体。传感器忽略。
	bool enableSensorEvents;

	/// 为此形状启用联系人事件。仅适用于运动学和动力学体。传感器忽略。
	bool enableContactEvents;

	/// 为此形状启用命中事件。仅适用于运动学和动力学体。传感器忽略。
	bool enableHitEvents;

	/// 为此形状启用预解决联系人事件。仅适用于动态物体。
	//// 这些很昂贵，由于螺纹问题必须小心处理。传感器忽略。
	bool enablePreSolveEvents;

	/// 通常，静态体上的形状在添加到世界中时不会调用接触创建。
	/// 这会覆盖该行为并导致联系人创建。
	/// 这大大减缓了静态身体的创建，当有许多静态形状时，这可能很重要。
	bool forceContactCreation;

	/// 内部用于检测有效定义。不要设置。
	int32_t internalValue;
} b2ShapeDef;

/// 使用此选项初始化形状定义
/// @ingroup shape
B2_API b2ShapeDef b2DefaultShapeDef( void );

/// Used to create a chain of edges. This is designed to eliminate ghost collisions with some limitations.
///	- chains are one-sided
///	- chains have no mass and should be used on static bodies
///	- chains have a counter-clockwise winding order
///	- chains are either a loop or open
/// - a chain must have at least 4 points
///	- the distance between any two points must be greater than b2_linearSlop
///	- a chain shape should not self intersect (this is not validated)
///	- an open chain shape has NO COLLISION on the first and final edge
///	- you may overlap two open chains on their first three and/or last three points to get smooth collision
///	- a chain shape creates multiple smooth edges shapes on the body
/// https://en.wikipedia.org/wiki/Polygonal_chain
/// Must be initialized using b2DefaultChainDef().
///	@warning Do not use chain shapes unless you understand the limitations. This is an advanced feature.
/// @ingroup shape
typedef struct b2ChainDef
{
	/// Use this to store application specific shape data.
	void* userData;

	/// An array of at least 4 points. These are cloned and may be temporary.
	const b2Vec2* points;

	/// The point count, must be 4 or more.
	int32_t count;

	/// The friction coefficient, usually in the range [0,1].
	float friction;

	/// The restitution (elasticity) usually in the range [0,1].
	float restitution;

	/// Contact filtering data.
	b2Filter filter;

	/// Indicates a closed chain formed by connecting the first and last points
	bool isLoop;

	/// Used internally to detect a valid definition. DO NOT SET.
	int32_t internalValue;
} b2ChainDef;

/// Use this to initialize your chain definition
/// @ingroup shape
B2_API b2ChainDef b2DefaultChainDef( void );

//! @cond
/// Profiling data. Times are in milliseconds.
typedef struct b2Profile
{
	float step;
	float pairs;
	float collide;
	float solve;
	float buildIslands;
	float solveConstraints;
	float prepareTasks;
	float solverTasks;
	float prepareConstraints;
	float integrateVelocities;
	float warmStart;
	float solveVelocities;
	float integratePositions;
	float relaxVelocities;
	float applyRestitution;
	float storeImpulses;
	float finalizeBodies;
	float splitIslands;
	float sleepIslands;
	float hitEvents;
	float broadphase;
	float continuous;
} b2Profile;

/// Counters that give details of the simulation size.
typedef struct b2Counters
{
	int32_t staticBodyCount;
	int32_t bodyCount;
	int32_t shapeCount;
	int32_t contactCount;
	int32_t jointCount;
	int32_t islandCount;
	int32_t stackUsed;
	int32_t staticTreeHeight;
	int32_t treeHeight;
	int32_t byteCount;
	int32_t taskCount;
	int32_t colorCounts[12];
} b2Counters;
//! @endcond

/// Joint type enumeration
///
/// This is useful because all joint types use b2JointId and sometimes you
/// want to get the type of a joint.
/// @ingroup joint
typedef enum b2JointType
{
	b2_distanceJoint,
	b2_motorJoint,
	b2_mouseJoint,
	b2_prismaticJoint,
	b2_revoluteJoint,
	b2_weldJoint,
	b2_wheelJoint,
} b2JointType;

/// Distance joint definition
///
/// This requires defining an anchor point on both
/// bodies and the non-zero distance of the distance joint. The definition uses
/// local anchor points so that the initial configuration can violate the
/// constraint slightly. This helps when saving and loading a game.
/// @ingroup distance_joint
typedef struct b2DistanceJointDef
{
	/// The first attached body
	b2BodyId bodyIdA;

	/// The second attached body
	b2BodyId bodyIdB;

	/// The local anchor point relative to bodyA's origin
	b2Vec2 localAnchorA;

	/// The local anchor point relative to bodyB's origin
	b2Vec2 localAnchorB;

	/// The rest length of this joint. Clamped to a stable minimum value.
	float length;

	/// Enable the distance constraint to behave like a spring. If false
	///	then the distance joint will be rigid, overriding the limit and motor.
	bool enableSpring;

	/// The spring linear stiffness Hertz, cycles per second
	float hertz;

	/// The spring linear damping ratio, non-dimensional
	float dampingRatio;

	/// Enable/disable the joint limit
	bool enableLimit;

	/// Minimum length. Clamped to a stable minimum value.
	float minLength;

	/// Maximum length. Must be greater than or equal to the minimum length.
	float maxLength;

	/// Enable/disable the joint motor
	bool enableMotor;

	/// The maximum motor force, usually in newtons
	float maxMotorForce;

	/// The desired motor speed, usually in meters per second
	float motorSpeed;

	/// Set this flag to true if the attached bodies should collide
	bool collideConnected;

	/// User data pointer
	void* userData;

	/// Used internally to detect a valid definition. DO NOT SET.
	int32_t internalValue;
} b2DistanceJointDef;

/// Use this to initialize your joint definition
/// @ingroup distance_joint
B2_API b2DistanceJointDef b2DefaultDistanceJointDef( void );

/// A motor joint is used to control the relative motion between two bodies
///
/// A typical usage is to control the movement of a dynamic body with respect to the ground.
/// @ingroup motor_joint
typedef struct b2MotorJointDef
{
	/// The first attached body
	b2BodyId bodyIdA;

	/// The second attached body
	b2BodyId bodyIdB;

	/// Position of bodyB minus the position of bodyA, in bodyA's frame
	b2Vec2 linearOffset;

	/// The bodyB angle minus bodyA angle in radians
	float angularOffset;

	/// The maximum motor force in newtons
	float maxForce;

	/// The maximum motor torque in newton-meters
	float maxTorque;

	/// Position correction factor in the range [0,1]
	float correctionFactor;

	/// Set this flag to true if the attached bodies should collide
	bool collideConnected;

	/// User data pointer
	void* userData;

	/// Used internally to detect a valid definition. DO NOT SET.
	int32_t internalValue;
} b2MotorJointDef;

/// Use this to initialize your joint definition
/// @ingroup motor_joint
B2_API b2MotorJointDef b2DefaultMotorJointDef( void );

/// A mouse joint is used to make a point on a body track a specified world point.
///
/// This a soft constraint and allows the constraint to stretch without
/// applying huge forces. This also applies rotation constraint heuristic to improve control.
/// @ingroup mouse_joint
typedef struct b2MouseJointDef
{
	/// The first attached body.
	b2BodyId bodyIdA;

	/// The second attached body.
	b2BodyId bodyIdB;

	/// The initial target point in world space
	b2Vec2 target;

	/// Stiffness in hertz
	float hertz;

	/// Damping ratio, non-dimensional
	float dampingRatio;

	/// Maximum force, typically in newtons
	float maxForce;

	/// Set this flag to true if the attached bodies should collide.
	bool collideConnected;

	/// User data pointer
	void* userData;

	/// Used internally to detect a valid definition. DO NOT SET.
	int32_t internalValue;
} b2MouseJointDef;

/// Use this to initialize your joint definition
/// @ingroup mouse_joint
B2_API b2MouseJointDef b2DefaultMouseJointDef( void );

/// Prismatic joint definition
///
/// This requires defining a line of motion using an axis and an anchor point.
/// The definition uses local anchor points and a local axis so that the initial
/// configuration can violate the constraint slightly. The joint translation is zero
/// when the local anchor points coincide in world space.
/// @ingroup prismatic_joint
typedef struct b2PrismaticJointDef
{
	/// The first attached body
	b2BodyId bodyIdA;

	/// The second attached body
	b2BodyId bodyIdB;

	/// The local anchor point relative to bodyA's origin
	b2Vec2 localAnchorA;

	/// The local anchor point relative to bodyB's origin
	b2Vec2 localAnchorB;

	/// The local translation unit axis in bodyA
	b2Vec2 localAxisA;

	/// The constrained angle between the bodies: bodyB_angle - bodyA_angle
	float referenceAngle;

	/// Enable a linear spring along the prismatic joint axis
	bool enableSpring;

	/// The spring stiffness Hertz, cycles per second
	float hertz;

	/// The spring damping ratio, non-dimensional
	float dampingRatio;

	/// Enable/disable the joint limit
	bool enableLimit;

	/// The lower translation limit
	float lowerTranslation;

	/// The upper translation limit
	float upperTranslation;

	/// Enable/disable the joint motor
	bool enableMotor;

	/// The maximum motor force, typically in newtons
	float maxMotorForce;

	/// The desired motor speed, typically in meters per second
	float motorSpeed;

	/// Set this flag to true if the attached bodies should collide
	bool collideConnected;

	/// User data pointer
	void* userData;

	/// Used internally to detect a valid definition. DO NOT SET.
	int32_t internalValue;
} b2PrismaticJointDef;

/// Use this to initialize your joint definition
/// @ingroupd prismatic_joint
B2_API b2PrismaticJointDef b2DefaultPrismaticJointDef( void );

/// Revolute joint definition
///
/// This requires defining an anchor point where the bodies are joined.
/// The definition uses local anchor points so that the
/// initial configuration can violate the constraint slightly. You also need to
/// specify the initial relative angle for joint limits. This helps when saving
/// and loading a game.
/// The local anchor points are measured from the body's origin
/// rather than the center of mass because:
/// 1. you might not know where the center of mass will be
/// 2. if you add/remove shapes from a body and recompute the mass, the joints will be broken
/// @ingroup revolute_joint
typedef struct b2RevoluteJointDef
{
	/// The first attached body
	b2BodyId bodyIdA;

	/// The second attached body
	b2BodyId bodyIdB;

	/// The local anchor point relative to bodyA's origin
	b2Vec2 localAnchorA;

	/// The local anchor point relative to bodyB's origin
	b2Vec2 localAnchorB;

	/// The bodyB angle minus bodyA angle in the reference state (radians).
	/// This defines the zero angle for the joint limit.
	float referenceAngle;

	/// Enable a rotational spring on the revolute hinge axis
	bool enableSpring;

	/// The spring stiffness Hertz, cycles per second
	float hertz;

	/// The spring damping ratio, non-dimensional
	float dampingRatio;

	/// A flag to enable joint limits
	bool enableLimit;

	/// The lower angle for the joint limit in radians
	float lowerAngle;

	/// The upper angle for the joint limit in radians
	float upperAngle;

	/// A flag to enable the joint motor
	bool enableMotor;

	/// The maximum motor torque, typically in newton-meters
	float maxMotorTorque;

	/// The desired motor speed in radians per second
	float motorSpeed;

	/// Scale the debug draw
	float drawSize;

	/// Set this flag to true if the attached bodies should collide
	bool collideConnected;

	/// User data pointer
	void* userData;

	/// Used internally to detect a valid definition. DO NOT SET.
	int32_t internalValue;
} b2RevoluteJointDef;

/// Use this to initialize your joint definition.
/// @ingroup revolute_joint
B2_API b2RevoluteJointDef b2DefaultRevoluteJointDef( void );

/// Weld joint definition
///
/// A weld joint connect to bodies together rigidly. This constraint provides springs to mimic
///	soft-body simulation.
/// @note The approximate solver in Box2D cannot hold many bodies together rigidly
/// @ingroup weld_joint
typedef struct b2WeldJointDef
{
	/// The first attached body
	b2BodyId bodyIdA;

	/// The second attached body
	b2BodyId bodyIdB;

	/// The local anchor point relative to bodyA's origin
	b2Vec2 localAnchorA;

	/// The local anchor point relative to bodyB's origin
	b2Vec2 localAnchorB;

	/// The bodyB angle minus bodyA angle in the reference state (radians)
	float referenceAngle;

	/// Linear stiffness expressed as Hertz (cycles per second). Use zero for maximum stiffness.
	float linearHertz;

	/// Angular stiffness as Hertz (cycles per second). Use zero for maximum stiffness.
	float angularHertz;

	/// Linear damping ratio, non-dimensional. Use 1 for critical damping.
	float linearDampingRatio;

	/// Linear damping ratio, non-dimensional. Use 1 for critical damping.
	float angularDampingRatio;

	/// Set this flag to true if the attached bodies should collide
	bool collideConnected;

	/// User data pointer
	void* userData;

	/// Used internally to detect a valid definition. DO NOT SET.
	int32_t internalValue;
} b2WeldJointDef;

/// Use this to initialize your joint definition
/// @ingroup weld_joint
B2_API b2WeldJointDef b2DefaultWeldJointDef( void );

/// Wheel joint definition
///
/// This requires defining a line of motion using an axis and an anchor point.
/// The definition uses local  anchor points and a local axis so that the initial
/// configuration can violate the constraint slightly. The joint translation is zero
/// when the local anchor points coincide in world space.
/// @ingroup wheel_joint
typedef struct b2WheelJointDef
{
	/// The first attached body
	b2BodyId bodyIdA;

	/// The second attached body
	b2BodyId bodyIdB;

	/// The local anchor point relative to bodyA's origin
	b2Vec2 localAnchorA;

	/// The local anchor point relative to bodyB's origin
	b2Vec2 localAnchorB;

	/// The local translation unit axis in bodyA
	b2Vec2 localAxisA;

	/// Enable a linear spring along the local axis
	bool enableSpring;

	/// Spring stiffness in Hertz
	float hertz;

	/// Spring damping ratio, non-dimensional
	float dampingRatio;

	/// Enable/disable the joint linear limit
	bool enableLimit;

	/// The lower translation limit
	float lowerTranslation;

	/// The upper translation limit
	float upperTranslation;

	/// Enable/disable the joint rotational motor
	bool enableMotor;

	/// The maximum motor torque, typically in newton-meters
	float maxMotorTorque;

	/// The desired motor speed in radians per second
	float motorSpeed;

	/// Set this flag to true if the attached bodies should collide
	bool collideConnected;

	/// User data pointer
	void* userData;

	/// Used internally to detect a valid definition. DO NOT SET.
	int32_t internalValue;
} b2WheelJointDef;

/// Use this to initialize your joint definition
/// @ingroup wheel_joint
B2_API b2WheelJointDef b2DefaultWheelJointDef( void );

/**
 * @defgroup events Events
 * World event types.
 *
 * Events are used to collect events that occur during the world time step. These events
 * are then available to query after the time step is complete. This is preferable to callbacks
 * because Box2D uses multithreaded simulation.
 *
 * Also when events occur in the simulation step it may be problematic to modify the world, which is
 * often what applications want to do when events occur.
 *
 * With event arrays, you can scan the events in a loop and modify the world. However, you need to be careful
 * that some event data may become invalid. There are several samples that show how to do this safely.
 *
 * @{
 */

/// A begin touch event is generated when a shape starts to overlap a sensor shape.
typedef struct b2SensorBeginTouchEvent
{
	/// The id of the sensor shape
	b2ShapeId sensorShapeId;

	/// The id of the dynamic shape that began touching the sensor shape
	b2ShapeId visitorShapeId;
} b2SensorBeginTouchEvent;

/// An end touch event is generated when a shape stops overlapping a sensor shape.
typedef struct b2SensorEndTouchEvent
{
	/// The id of the sensor shape
	b2ShapeId sensorShapeId;

	/// The id of the dynamic shape that stopped touching the sensor shape
	b2ShapeId visitorShapeId;
} b2SensorEndTouchEvent;

/// Sensor events are buffered in the Box2D world and are available
///	as begin/end overlap event arrays after the time step is complete.
///	Note: these may become invalid if bodies and/or shapes are destroyed
typedef struct b2SensorEvents
{
	/// Array of sensor begin touch events
	b2SensorBeginTouchEvent* beginEvents;

	/// Array of sensor end touch events
	b2SensorEndTouchEvent* endEvents;

	/// The number of begin touch events
	int32_t beginCount;

	/// The number of end touch events
	int32_t endCount;
} b2SensorEvents;

/// A begin touch event is generated when two shapes begin touching.
typedef struct b2ContactBeginTouchEvent
{
	/// Id of the first shape
	b2ShapeId shapeIdA;

	/// Id of the second shape
	b2ShapeId shapeIdB;
} b2ContactBeginTouchEvent;

/// An end touch event is generated when two shapes stop touching.
typedef struct b2ContactEndTouchEvent
{
	/// Id of the first shape
	b2ShapeId shapeIdA;

	/// Id of the second shape
	b2ShapeId shapeIdB;
} b2ContactEndTouchEvent;

/// A hit touch event is generated when two shapes collide with a speed faster than the hit speed threshold.
typedef struct b2ContactHitEvent
{
	/// Id of the first shape
	b2ShapeId shapeIdA;

	/// Id of the second shape
	b2ShapeId shapeIdB;

	/// Point where the shapes hit
	b2Vec2 point;

	/// Normal vector pointing from shape A to shape B
	b2Vec2 normal;

	/// The speed the shapes are approaching. Always positive. Typically in meters per second.
	float approachSpeed;
} b2ContactHitEvent;

/// Contact events are buffered in the Box2D world and are available
///	as event arrays after the time step is complete.
///	Note: these may become invalid if bodies and/or shapes are destroyed
typedef struct b2ContactEvents
{
	/// Array of begin touch events
	b2ContactBeginTouchEvent* beginEvents;

	/// Array of end touch events
	b2ContactEndTouchEvent* endEvents;

	/// Array of hit events
	b2ContactHitEvent* hitEvents;

	/// Number of begin touch events
	int32_t beginCount;

	/// Number of end touch events
	int32_t endCount;

	/// Number of hit events
	int32_t hitCount;
} b2ContactEvents;

/// Body move events triggered when a body moves.
/// Triggered when a body moves due to simulation. Not reported for bodies moved by the user.
/// This also has a flag to indicate that the body went to sleep so the application can also
/// sleep that actor/entity/object associated with the body.
/// On the other hand if the flag does not indicate the body went to sleep then the application
/// can treat the actor/entity/object associated with the body as awake.
///	This is an efficient way for an application to update game object transforms rather than
///	calling functions such as b2Body_GetTransform() because this data is delivered as a contiguous array
///	and it is only populated with bodies that have moved.
///	@note If sleeping is disabled all dynamic and kinematic bodies will trigger move events.
typedef struct b2BodyMoveEvent
{
	b2Transform transform;
	b2BodyId bodyId;
	void* userData;
	bool fellAsleep;
} b2BodyMoveEvent;

/// Body events are buffered in the Box2D world and are available
///	as event arrays after the time step is complete.
///	Note: this data becomes invalid if bodies are destroyed
typedef struct b2BodyEvents
{
	/// Array of move events
	b2BodyMoveEvent* moveEvents;

	/// Number of move events
	int32_t moveCount;
} b2BodyEvents;

/// The contact data for two shapes. By convention the manifold normal points
///	from shape A to shape B.
///	@see b2Shape_GetContactData() and b2Body_GetContactData()
typedef struct b2ContactData
{
	b2ShapeId shapeIdA;
	b2ShapeId shapeIdB;
	b2Manifold manifold;
} b2ContactData;

/**@}*/

/// Prototype for a contact filter callback.
/// This is called when a contact pair is considered for collision. This allows you to
///	perform custom logic to prevent collision between shapes. This is only called if
///	one of the two shapes has custom filtering enabled. @see b2ShapeDef.
/// Notes:
///	- this function must be thread-safe
///	- this is only called if one of the two shapes has enabled custom filtering
/// - this is called only for awake dynamic bodies
///	Return false if you want to disable the collision
///	@warning Do not attempt to modify the world inside this callback
///	@ingroup world
typedef bool b2CustomFilterFcn( b2ShapeId shapeIdA, b2ShapeId shapeIdB, void* context );

/// Prototype for a pre-solve callback.
/// This is called after a contact is updated. This allows you to inspect a
/// contact before it goes to the solver. If you are careful, you can modify the
/// contact manifold (e.g. modify the normal).
/// Notes:
///	- this function must be thread-safe
///	- this is only called if the shape has enabled pre-solve events
/// - this is called only for awake dynamic bodies
/// - this is not called for sensors
/// - the supplied manifold has impulse values from the previous step
///	Return false if you want to disable the contact this step
///	@warning Do not attempt to modify the world inside this callback
///	@ingroup world
typedef bool b2PreSolveFcn( b2ShapeId shapeIdA, b2ShapeId shapeIdB, b2Manifold* manifold, void* context );

/// Prototype callback for overlap queries.
/// Called for each shape found in the query.
/// @see b2World_QueryAABB
/// @return false to terminate the query.
///	@ingroup world
typedef bool b2OverlapResultFcn( b2ShapeId shapeId, void* context );

/// Prototype callback for ray casts.
/// Called for each shape found in the query. You control how the ray cast
/// proceeds by returning a float:
/// return -1: ignore this shape and continue
/// return 0: terminate the ray cast
/// return fraction: clip the ray to this point
/// return 1: don't clip the ray and continue
/// @param shapeId the shape hit by the ray
/// @param point the point of initial intersection
/// @param normal the normal vector at the point of intersection
/// @param fraction the fraction along the ray at the point of intersection
///	@param context the user context
/// @return -1 to filter, 0 to terminate, fraction to clip the ray for closest hit, 1 to continue
/// @see b2World_CastRay
///	@ingroup world
typedef float b2CastResultFcn( b2ShapeId shapeId, b2Vec2 point, b2Vec2 normal, float fraction, void* context );

/// These colors are used for debug draw.
///	See https://www.rapidtables.com/web/color/index.html
typedef enum b2HexColor
{
	b2_colorAliceBlue = 0xf0f8ff,
	b2_colorAntiqueWhite = 0xfaebd7,
	b2_colorAqua = 0x00ffff,
	b2_colorAquamarine = 0x7fffd4,
	b2_colorAzure = 0xf0ffff,
	b2_colorBeige = 0xf5f5dc,
	b2_colorBisque = 0xffe4c4,
	b2_colorBlack = 0x000000,
	b2_colorBlanchedAlmond = 0xffebcd,
	b2_colorBlue = 0x0000ff,
	b2_colorBlueViolet = 0x8a2be2,
	b2_colorBrown = 0xa52a2a,
	b2_colorBurlywood = 0xdeb887,
	b2_colorCadetBlue = 0x5f9ea0,
	b2_colorChartreuse = 0x7fff00,
	b2_colorChocolate = 0xd2691e,
	b2_colorCoral = 0xff7f50,
	b2_colorCornflowerBlue = 0x6495ed,
	b2_colorCornsilk = 0xfff8dc,
	b2_colorCrimson = 0xdc143c,
	b2_colorCyan = 0x00ffff,
	b2_colorDarkBlue = 0x00008b,
	b2_colorDarkCyan = 0x008b8b,
	b2_colorDarkGoldenrod = 0xb8860b,
	b2_colorDarkGray = 0xa9a9a9,
	b2_colorDarkGreen = 0x006400,
	b2_colorDarkKhaki = 0xbdb76b,
	b2_colorDarkMagenta = 0x8b008b,
	b2_colorDarkOliveGreen = 0x556b2f,
	b2_colorDarkOrange = 0xff8c00,
	b2_colorDarkOrchid = 0x9932cc,
	b2_colorDarkRed = 0x8b0000,
	b2_colorDarkSalmon = 0xe9967a,
	b2_colorDarkSeaGreen = 0x8fbc8f,
	b2_colorDarkSlateBlue = 0x483d8b,
	b2_colorDarkSlateGray = 0x2f4f4f,
	b2_colorDarkTurquoise = 0x00ced1,
	b2_colorDarkViolet = 0x9400d3,
	b2_colorDeepPink = 0xff1493,
	b2_colorDeepSkyBlue = 0x00bfff,
	b2_colorDimGray = 0x696969,
	b2_colorDodgerBlue = 0x1e90ff,
	b2_colorFirebrick = 0xb22222,
	b2_colorFloralWhite = 0xfffaf0,
	b2_colorForestGreen = 0x228b22,
	b2_colorFuchsia = 0xff00ff,
	b2_colorGainsboro = 0xdcdcdc,
	b2_colorGhostWhite = 0xf8f8ff,
	b2_colorGold = 0xffd700,
	b2_colorGoldenrod = 0xdaa520,
	b2_colorGray = 0xbebebe,
	b2_colorGray1 = 0x1a1a1a,
	b2_colorGray2 = 0x333333,
	b2_colorGray3 = 0x4d4d4d,
	b2_colorGray4 = 0x666666,
	b2_colorGray5 = 0x7f7f7f,
	b2_colorGray6 = 0x999999,
	b2_colorGray7 = 0xb3b3b3,
	b2_colorGray8 = 0xcccccc,
	b2_colorGray9 = 0xe5e5e5,
	b2_colorGreen = 0x00ff00,
	b2_colorGreenYellow = 0xadff2f,
	b2_colorHoneydew = 0xf0fff0,
	b2_colorHotPink = 0xff69b4,
	b2_colorIndianRed = 0xcd5c5c,
	b2_colorIndigo = 0x4b0082,
	b2_colorIvory = 0xfffff0,
	b2_colorKhaki = 0xf0e68c,
	b2_colorLavender = 0xe6e6fa,
	b2_colorLavenderBlush = 0xfff0f5,
	b2_colorLawnGreen = 0x7cfc00,
	b2_colorLemonChiffon = 0xfffacd,
	b2_colorLightBlue = 0xadd8e6,
	b2_colorLightCoral = 0xf08080,
	b2_colorLightCyan = 0xe0ffff,
	b2_colorLightGoldenrod = 0xeedd82,
	b2_colorLightGoldenrodYellow = 0xfafad2,
	b2_colorLightGray = 0xd3d3d3,
	b2_colorLightGreen = 0x90ee90,
	b2_colorLightPink = 0xffb6c1,
	b2_colorLightSalmon = 0xffa07a,
	b2_colorLightSeaGreen = 0x20b2aa,
	b2_colorLightSkyBlue = 0x87cefa,
	b2_colorLightSlateBlue = 0x8470ff,
	b2_colorLightSlateGray = 0x778899,
	b2_colorLightSteelBlue = 0xb0c4de,
	b2_colorLightYellow = 0xffffe0,
	b2_colorLime = 0x00ff00,
	b2_colorLimeGreen = 0x32cd32,
	b2_colorLinen = 0xfaf0e6,
	b2_colorMagenta = 0xff00ff,
	b2_colorMaroon = 0xb03060,
	b2_colorMediumAquamarine = 0x66cdaa,
	b2_colorMediumBlue = 0x0000cd,
	b2_colorMediumOrchid = 0xba55d3,
	b2_colorMediumPurple = 0x9370db,
	b2_colorMediumSeaGreen = 0x3cb371,
	b2_colorMediumSlateBlue = 0x7b68ee,
	b2_colorMediumSpringGreen = 0x00fa9a,
	b2_colorMediumTurquoise = 0x48d1cc,
	b2_colorMediumVioletRed = 0xc71585,
	b2_colorMidnightBlue = 0x191970,
	b2_colorMintCream = 0xf5fffa,
	b2_colorMistyRose = 0xffe4e1,
	b2_colorMoccasin = 0xffe4b5,
	b2_colorNavajoWhite = 0xffdead,
	b2_colorNavy = 0x000080,
	b2_colorNavyBlue = 0x000080,
	b2_colorOldLace = 0xfdf5e6,
	b2_colorOlive = 0x808000,
	b2_colorOliveDrab = 0x6b8e23,
	b2_colorOrange = 0xffa500,
	b2_colorOrangeRed = 0xff4500,
	b2_colorOrchid = 0xda70d6,
	b2_colorPaleGoldenrod = 0xeee8aa,
	b2_colorPaleGreen = 0x98fb98,
	b2_colorPaleTurquoise = 0xafeeee,
	b2_colorPaleVioletRed = 0xdb7093,
	b2_colorPapayaWhip = 0xffefd5,
	b2_colorPeachPuff = 0xffdab9,
	b2_colorPeru = 0xcd853f,
	b2_colorPink = 0xffc0cb,
	b2_colorPlum = 0xdda0dd,
	b2_colorPowderBlue = 0xb0e0e6,
	b2_colorPurple = 0xa020f0,
	b2_colorRebeccaPurple = 0x663399,
	b2_colorRed = 0xff0000,
	b2_colorRosyBrown = 0xbc8f8f,
	b2_colorRoyalBlue = 0x4169e1,
	b2_colorSaddleBrown = 0x8b4513,
	b2_colorSalmon = 0xfa8072,
	b2_colorSandyBrown = 0xf4a460,
	b2_colorSeaGreen = 0x2e8b57,
	b2_colorSeashell = 0xfff5ee,
	b2_colorSienna = 0xa0522d,
	b2_colorSilver = 0xc0c0c0,
	b2_colorSkyBlue = 0x87ceeb,
	b2_colorSlateBlue = 0x6a5acd,
	b2_colorSlateGray = 0x708090,
	b2_colorSnow = 0xfffafa,
	b2_colorSpringGreen = 0x00ff7f,
	b2_colorSteelBlue = 0x4682b4,
	b2_colorTan = 0xd2b48c,
	b2_colorTeal = 0x008080,
	b2_colorThistle = 0xd8bfd8,
	b2_colorTomato = 0xff6347,
	b2_colorTurquoise = 0x40e0d0,
	b2_colorViolet = 0xee82ee,
	b2_colorVioletRed = 0xd02090,
	b2_colorWheat = 0xf5deb3,
	b2_colorWhite = 0xffffff,
	b2_colorWhiteSmoke = 0xf5f5f5,
	b2_colorYellow = 0xffff00,
	b2_colorYellowGreen = 0x9acd32,
	b2_colorBox2DRed = 0xdc3132,
	b2_colorBox2DBlue = 0x30aebf,
	b2_colorBox2DGreen = 0x8cc924,
	b2_colorBox2DYellow = 0xffee8c
} b2HexColor;

/// This struct holds callbacks you can implement to draw a Box2D world.
///	@ingroup world
typedef struct b2DebugDraw
{
	/// Draw a closed polygon provided in CCW order.
	void ( *DrawPolygon )( const b2Vec2* vertices, int vertexCount, b2HexColor color, void* context );

	/// Draw a solid closed polygon provided in CCW order.
	void ( *DrawSolidPolygon )( b2Transform transform, const b2Vec2* vertices, int vertexCount, float radius, b2HexColor color,
								void* context );

	/// Draw a circle.
	void ( *DrawCircle )( b2Vec2 center, float radius, b2HexColor color, void* context );

	/// Draw a solid circle.
	void ( *DrawSolidCircle )( b2Transform transform, float radius, b2HexColor color, void* context );

	/// Draw a capsule.
	void ( *DrawCapsule )( b2Vec2 p1, b2Vec2 p2, float radius, b2HexColor color, void* context );

	/// Draw a solid capsule.
	void ( *DrawSolidCapsule )( b2Vec2 p1, b2Vec2 p2, float radius, b2HexColor color, void* context );

	/// Draw a line segment.
	void ( *DrawSegment )( b2Vec2 p1, b2Vec2 p2, b2HexColor color, void* context );

	/// Draw a transform. Choose your own length scale.
	void ( *DrawTransform )( b2Transform transform, void* context );

	/// Draw a point.
	void ( *DrawPoint )( b2Vec2 p, float size, b2HexColor color, void* context );

	/// Draw a string.
	void ( *DrawString )( b2Vec2 p, const char* s, void* context );

	/// Bounds to use if restricting drawing to a rectangular region
	b2AABB drawingBounds;

	/// Option to restrict drawing to a rectangular region. May suffer from unstable depth sorting.
	bool useDrawingBounds;

	/// Option to draw shapes
	bool drawShapes;

	/// Option to draw joints
	bool drawJoints;

	/// Option to draw additional information for joints
	bool drawJointExtras;

	/// Option to draw the bounding boxes for shapes
	bool drawAABBs;

	/// Option to draw the mass and center of mass of dynamic bodies
	bool drawMass;

	/// Option to draw contact points
	bool drawContacts;

	/// Option to visualize the graph coloring used for contacts and joints
	bool drawGraphColors;

	/// Option to draw contact normals
	bool drawContactNormals;

	/// Option to draw contact normal impulses
	bool drawContactImpulses;

	/// Option to draw contact friction impulses
	bool drawFrictionImpulses;

	/// User context that is passed as an argument to drawing callback functions
	void* context;
} b2DebugDraw;
