#include <Streamer/Object.hpp>

const bool Object::AttachToObject(uint32_t ID, uint32_t AttachToID, float X, float Y, float Z, float RotationX, float RotationY, float RotationZ, bool SyncRotation)
{
	static AMX_NATIVE Native = sampgdk::FindNative("AttachDynamicObjectToObject");
	return !!sampgdk::InvokeNative(Native, "iiffffffb", ID, AttachToID, X, Y, Z, RotationX, RotationY, RotationZ, SyncRotation);
}

const bool Object::AttachToVehicle(uint32_t ID, uint32_t VehicleID, float X, float Y, float Z, float RotationX, float RotationY, float RotationZ)
{
	static AMX_NATIVE Native = sampgdk::FindNative("AttachDynamicObjectToVehicle");
	return !!sampgdk::InvokeNative(Native, "iiffffff", ID, VehicleID, X, Y, Z, RotationX, RotationY, RotationZ);
}

const uint32_t Object::Create(uint32_t ModelID, const Point3D<float>& Position, const Point3D<float>& Rotation, int VirtualWorld, int Interior, int PlayerID, float StreamDistance, float DrawDistance)
{
	static AMX_NATIVE Native = sampgdk::FindNative("CreateDynamicObject");
	return static_cast<uint32_t>(sampgdk::InvokeNative(Native, "iffffffiiiff", ModelID, Position.X, Position.Y, Position.Z, Rotation.X, Rotation.Y, Rotation.Z, VirtualWorld, Interior, PlayerID, StreamDistance, DrawDistance));
}

const bool Object::Destroy(uint32_t ID)
{
	static AMX_NATIVE Native = sampgdk::FindNative("DestroyDynamicObject");
	return !!sampgdk::InvokeNative(Native, "i", ID);
}

const bool Object::GetNoCameraCol(uint32_t ID)
{
	static AMX_NATIVE Native = sampgdk::FindNative("GetDynamicObjectNoCameraCol");
	return !!sampgdk::InvokeNative(Native, "i", ID);
}

const Point3D<float> Object::GetPosition(uint32_t ID)
{
	Point3D<float> Restult;

	static AMX_NATIVE Native = sampgdk::FindNative("GetDynamicObjectPos");
	sampgdk::InvokeNative(Native, "iRRR", ID, &Restult.X, &Restult.Y, &Restult.Z);

	return Restult;
}

const Point3D<float> Object::GetRotation(uint32_t ID)
{
	Point3D<float> Restult;

	static AMX_NATIVE Native = sampgdk::FindNative("GetDynamicObjectRot");
	sampgdk::InvokeNative(Native, "iRRR", ID, &Restult.X, &Restult.Y, &Restult.Z);

	return Restult;
}

const bool Object::IsValid(uint32_t ID)
{
	static AMX_NATIVE Native = sampgdk::FindNative("IsValidDynamicObject");
	return !!sampgdk::InvokeNative(Native, "i", ID);
}

const bool Object::IsMaterialUsed(uint32_t ID, uint32_t MaterialIndex)
{
	static AMX_NATIVE Native = sampgdk::FindNative("IsDynamicObjectMaterialUsed");
	return !!sampgdk::InvokeNative(Native, "ii", ID, MaterialIndex);
}

const bool Object::IsMoving(uint32_t ID)
{
	static AMX_NATIVE Native = sampgdk::FindNative("IsDynamicObjectMoving");
	return !!sampgdk::InvokeNative(Native, "i", ID);
}

void Object::Move(uint32_t ID, const Point3D<float>& Position, float Speed, const Point3D<float>& Rotation)
{
	Move(ID, Position.X, Position.Y, Position.Z, Speed, Rotation.X, Rotation.Y, Rotation.Z);
}

void Object::Move(uint32_t ID, float X, float Y, float Z, float Speed, float RotationX, float RotationY, float RotationZ)
{
	static AMX_NATIVE Native = sampgdk::FindNative("MoveDynamicObject");
	sampgdk::InvokeNative(Native, "ifffffff", ID, X, Y, Z, Speed, RotationX, RotationY, RotationZ);
}

bool Object::SetNoCameraCol(uint32_t ID)
{
	static AMX_NATIVE Native = sampgdk::FindNative("SetDynamicObjectNoCameraCol");
	return !!sampgdk::InvokeNative(Native, "i", ID);
}

void Object::SetPosition(uint32_t ID, const Point3D<float>& Position)
{
	SetPosition(ID, Position.X, Position.Y, Position.Z);
}

void Object::SetPosition(uint32_t ID, float X, float Y, float Z)
{
	static AMX_NATIVE Native = sampgdk::FindNative("SetDynamicObjectPos");
	sampgdk::InvokeNative(Native, "ifff", ID, X, Y, Z);
}

void Object::SetRotation(uint32_t ID, const Point3D<float>& Position)
{
	SetRotation(ID, Position.X, Position.Y, Position.Z);
}

void Object::SetRotation(uint32_t ID, float X, float Y, float Z)
{
	static AMX_NATIVE Native = sampgdk::FindNative("SetDynamicObjectRot");
	sampgdk::InvokeNative(Native, "ifff", ID, X, Y, Z);
}

void Object::StopMove(uint32_t ID)
{
	static AMX_NATIVE Native = sampgdk::FindNative("StopDynamicObject");
	sampgdk::InvokeNative(Native, "i", ID);
}


