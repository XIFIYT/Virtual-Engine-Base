#pragma once

namespace Big
{
	using Void = std::uint32_t;
	using Any = std::uint32_t;
	using Hash = std::uint32_t;
	using Entity = std::int32_t;
	using Player = std::int32_t;
	using FireId = std::int32_t;
	using Ped = Entity;
	using Vehicle = Entity;
	using Cam = std::int32_t;
	using CarGenerator = std::int32_t;
	using Group = std::int32_t;
	using Train = std::int32_t;
	using Object = Entity;
	using Pickup = Object;
	using Weapon = std::int32_t;
	using Interior = std::int32_t;
	using Blip = std::int32_t;
	using Texture = std::int32_t;
	using TextureDict = std::int32_t;
	using CoverPoint = std::int32_t;
	using Camera = std::int32_t;
	using TaskSequence = std::int32_t;
	using ColourIndex = std::int32_t;
	using Sphere = std::int32_t;
	using ScrHandle = std::int32_t;

#define PLAYER_INDEX alignas(8) Player
#define ENTITY_INDEX alignas(8) Entity
#define PED_INDEX alignas(8) Ped
#define VEHICLE_INDEX alignas(8) Vehicle
#define INTERIOR_INDEX alignas(8) Interior
#define NETWORK_INDEX alignas(8) int

#define SCR_HASH alignas(8) Hash
#define SCR_INT alignas(8) int
#define SCR_BOOL alignas(8) BOOL
#define SCR_FLOAT alignas(8) float
#define SCR_VEC3 NativeVector3

#pragma pack(push, 1)
	struct Vector2
	{
		float x{};
		float y{};
	};
#pragma pack(pop)
#pragma pack(push, 1)
	class Vector3 {
	public:
		Vector3() : x(0.f), y(0.f), z(0.f) {}
		Vector3(float x, float y, float z) : x(x), y(y), z(z) {}
		Vector3 operator+(const Vector3& other)
		{
			Vector3 vec;
			vec.x = this->x + other.x;
			vec.y = this->y + other.y;
			vec.z = this->z + other.z;
			return vec;
		}

		Vector3 operator-(const Vector3& other)
		{
			Vector3 vec;
			vec.x = this->x - other.x;
			vec.y = this->y - other.y;
			vec.z = this->z - other.z;
			return vec;
		}

		Vector3 operator*(const Vector3& other)
		{
			Vector3 vec;
			vec.x = this->x * other.x;
			vec.y = this->y * other.y;
			vec.z = this->z * other.z;
			return vec;
		}

		Vector3 operator*(const float& other)
		{
			Vector3 vec;
			vec.x = this->x * other;
			vec.y = this->y * other;
			vec.z = this->z * other;
			return vec;
		}
	public:
		float x;
	private:
		char m_paddingx[0x04];
	public:
		float y;
	private:
		char m_paddingy[0x04];
	public:
		float z;
	private:
		char m_paddingz[0x04];
	};
#pragma pack(pop)
#pragma pack(push, 1)
	struct Color
	{
		std::uint8_t r{ 255 };
		std::uint8_t g{ 255 };
		std::uint8_t b{ 255 };
		std::uint8_t a{ 255 };
	};
#pragma pack(pop)

	template<typename T>
	union vector3
	{
		T data[3];
		struct { T x, y, z; };
	};
	typedef vector3<float> fvector3;
}
