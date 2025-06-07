// SPDX-FileCopyrightText: 2023 Erin Catto
// SPDX-License-Identifier: MIT

#pragma once

#include "box2d/base.h"

#define B2_NULL_INDEX ( -1 )

#ifdef NDEBUG
	#define B2_DEBUG 0
#else
	#define B2_DEBUG 1
#endif

#if defined( BOX2D_VALIDATE ) && !defined( NDEBUG )
	#define B2_VALIDATE 1
#else
	#define B2_VALIDATE 0
#endif

// Define platform
#if defined( _WIN64 )
	#define B2_PLATFORM_WINDOWS
#elif defined( __ANDROID__ )
	#define B2_PLATFORM_ANDROID
#elif defined( __linux__ )
	#define B2_PLATFORM_LINUX
#elif defined( __APPLE__ )
	#include <TargetConditionals.h>
	#if defined( TARGET_OS_IPHONE ) && !TARGET_OS_IPHONE
		#define B2_PLATFORM_MACOS
	#else
		#define B2_PLATFORM_IOS
	#endif
#elif defined( __EMSCRIPTEN__ )
	#define B2_PLATFORM_WASM
#elif defined(ESP32)
	#define B2_PLATFORM_WASM
#else
	#error Unsupported platform
#endif

// Define CPU
#if defined( __x86_64__ ) || defined( _M_X64 )
	#define B2_CPU_X64
#elif defined( __aarch64__ ) || defined( _M_ARM64 )
	#define B2_CPU_ARM
#elif defined( __EMSCRIPTEN__ )
	#define B2_CPU_WASM
#elif defined(ESP32)
	#define B2_CPU_WASM
#else
	#error Unsupported CPU
#endif

// Define compiler
#if defined( __clang__ )
	#define B2_COMPILER_CLANG
#elif defined( __GNUC__ )
	#define B2_COMPILER_GCC
#elif defined( _MSC_VER )
	#define B2_COMPILER_MSVC
#endif

#if defined( B2_COMPILER_MSVC )
	#define B2_BREAKPOINT __debugbreak()
#elif defined( B2_PLATFORM_WASM )
	#define B2_BREAKPOINT                                                                                                        \
		do                                                                                                                       \
		{                                                                                                                        \
		}                                                                                                                        \
		while ( 0 )
#elif defined( B2_COMPILER_GCC ) || defined( B2_COMPILER_CLANG )
	#if defined( B2_CPU_X64 )
		#define B2_BREAKPOINT __asm volatile( "int $0x3" )
	#elif defined( B2_CPU_ARM )
		#define B2_BREAKPOINT __builtin_trap()
	#endif
#else
	#error Unknown platform
#endif

#if !defined( NDEBUG ) || defined( B2_ENABLE_ASSERT )
extern b2AssertFcn* b2AssertHandler;
	#define B2_ASSERT( condition )                                                                                               \
		do                                                                                                                       \
		{                                                                                                                        \
			if ( !( condition ) && b2AssertHandler( #condition, __FILE__, (int)__LINE__ ) )                                      \
				B2_BREAKPOINT;                                                                                                   \
		}                                                                                                                        \
		while ( 0 )
#else
	#define B2_ASSERT( ... ) ( (void)0 )
#endif

/// Tracy profiler instrumentation
///	https://github.com/wolfpld/tracy
#ifdef BOX2D_PROFILE

	#include <tracy/TracyC.h>
	#define b2TracyCZoneC( ctx, color, active ) TracyCZoneC( ctx, color, active )
	#define b2TracyCZoneNC( ctx, name, color, active ) TracyCZoneNC( ctx, name, color, active )
	#define b2TracyCZoneEnd( ctx ) TracyCZoneEnd( ctx )

#else

	#define b2TracyCZoneC( ctx, color, active )
	#define b2TracyCZoneNC( ctx, name, color, active )
	#define b2TracyCZoneEnd( ctx )

#endif

extern float b2_lengthUnitsPerMeter;

//用于检测错误值。大于约16公里的位置将存在精度问题，因此在所有情况下，100公里的限制应该是可以的。
#define b2_huge ( 100000.0f * b2_lengthUnitsPerMeter )

// 最大并行工人数。用于调整某些静态数组的大小。
#define b2_maxWorkers 32

//约束图中的最大颜色数。找不到颜色的约束被添加到溢出集中，这些约束是单线程解决的。
#define b2_graphColorCount 12

// 用作碰撞和约束公差的小长度。通常，它被选择为具有数字意义，但在视觉上无关紧要。以米为单位。
// @warning 修改此设置可能会对稳定性产生重大影响
#define b2_linearSlop ( 0.005f * b2_lengthUnitsPerMeter )

// 可分配的最大并发世界数
#define b2_maxWorlds 128

// The maximum rotation of a body per time step. This limit is very large and is used
// to prevent numerical problems. You shouldn't need to adjust this.
// @warning increasing this to 0.5f * b2_pi or greater will break continuous collision.
#define b2_maxRotation ( 0.25f * b2_pi )

// @warning modifying this can have a significant impact on performance and stability
#define b2_speculativeDistance ( 4.0f * b2_linearSlop )

// This is used to fatten AABBs in the dynamic tree. This allows proxies
// to move by a small amount without triggering a tree adjustment.
// This is in meters.
// @warning modifying this can have a significant impact on performance
#define b2_aabbMargin ( 0.1f * b2_lengthUnitsPerMeter )

// 身体必须静止才能入睡的时间。几秒钟内。
#define b2_timeToSleep 0.5f

// 返回数组的元素数
#define B2_ARRAY_COUNT( A ) (int)( sizeof( A ) / sizeof( A[0] ) )

// 用于防止编译器对未使用的变量发出警告
#define B2_MAYBE_UNUSED( x ) ( (void)( x ) )

// 用于验证定义。不要拿走我的饼干。
#define B2_SECRET_COOKIE 1152023

#define b2CheckDef( DEF ) B2_ASSERT( DEF->internalValue == B2_SECRET_COOKIE )
