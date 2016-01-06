#include <Streamer/Object.hpp>

const bool Object::AttachToObject(unsigned int ID, unsigned int AttachToID, float X, float Y, float Z, float RotationX, float RotationY, float RotationZ, bool SyncRotation)
{
	static AMX_NATIVE Native = sampgdk::FindNative("AttachDynamicObjectToObject");
	return !!sampgdk::InvokeNative(Native, "iiffffffb", ID, AttachToID, X, Y, Z, RotationX, RotationY, RotationZ, SyncRotation);
}

const bool Object::AttachToVehicle(unsigned int ID, unsigned int VehicleID, float X, float Y, float Z, float RotationX, float RotationY, float RotationZ)
{
	static AMX_NATIVE Native = sampgdk::FindNative("AttachDynamicObjectToVehicle");
	return !!sampgdk::InvokeNative(Native, "iiffffff", ID, VehicleID, X, Y, Z, RotationX, RotationY, RotationZ);
}

const unsigned int Object::Create(unsigned int ModelID, const Point3D<float>& Position, const Point3D<float>& Rotation, int VirtualWorld, int Interior, int PlayerID, float StreamDistance, float DrawDistance)
{
	static AMX_NATIVE Native = sampgdk::FindNative("CreateDynamicObject");
	return static_cast<unsigned int>(sampgdk::InvokeNative(Native, "iffffffiiiff", ModelID, Position.X, Position.Y, Position.Z, Rotation.X, Rotation.Y, Rotation.Z, VirtualWorld, Interior, PlayerID, StreamDistance, DrawDistance));
}

const bool Object::Destroy(unsigned int ID)
{
	static AMX_NATIVE Native = sampgdk::FindNative("DestroyDynamicObject");
	return !!sampgdk::InvokeNative(Native, "i", ID);
}

const bool Object::GetNoCameraCol(unsigned int ID)
{
	static AMX_NATIVE Native = sampgdk::FindNative("GetDynamicObjectNoCameraCol");
	return !!sampgdk::InvokeNative(Native, "i", ID);
}

const Point3D<float> Object::GetPosition(unsigned int ID)
{
	Point3D<float> Restult;

	static AMX_NATIVE Native = sampgdk::FindNative("GetDynamicObjectPos");
	sampgdk::InvokeNative(Native, "iRRR", ID, &Restult.X, &Restult.Y, &Restult.Z);

	return Restult;
}

const Point3D<float> Object::GetRotation(unsigned int ID)
{
	Point3D<float> Restult;

	static AMX_NATIVE Native = sampgdk::FindNative("GetDynamicObjectRot");
	sampgdk::InvokeNative(Native, "iRRR", ID, &Restult.X, &Restult.Y, &Restult.Z);

	return Restult;
}

const bool Object::IsValid(unsigned int ID)
{
	static AMX_NATIVE Native = sampgdk::FindNative("IsValidDynamicObject");
	return !!sampgdk::InvokeNative(Native, "i", ID);
}

const bool Object::IsMaterialUsed(unsigned int ID, unsigned int MaterialIndex)
{
	static AMX_NATIVE Native = sampgdk::FindNative("IsDynamicObjectMaterialUsed");
	return !!sampgdk::InvokeNative(Native, "ii", ID, MaterialIndex);
}

const bool Object::IsMoving(unsigned int ID)
{
	static AMX_NATIVE Native = sampgdk::FindNative("IsDynamicObjectMoving");
	return !!sampgdk::InvokeNative(Native, "i", ID);
}

void Object::Move(unsigned int ID, const Point3D<float>& Position, float Speed, const Point3D<float>& Rotation)
{
	Move(ID, Position.X, Position.Y, Position.Z, Speed, Rotation.X, Rotation.Y, Rotation.Z);
}

void Object::Move(unsigned int ID, float X, float Y, float Z, float Speed, float RotationX, float RotationY, float RotationZ)
{
	static AMX_NATIVE Native = sampgdk::FindNative("MoveDynamicObject");
	sampgdk::InvokeNative(Native, "ifffffff", ID, X, Y, Z, Speed, RotationX, RotationY, RotationZ);
}

bool Object::SetNoCameraCol(unsigned int ID)
{
	static AMX_NATIVE Native = sampgdk::FindNative("SetDynamicObjectNoCameraCol");
	return !!sampgdk::InvokeNative(Native, "i", ID);
}

void Object::SetPosition(unsigned int ID, const Point3D<float>& Position)
{
	SetPosition(ID, Position.X, Position.Y, Position.Z);
}

void Object::SetPosition(unsigned int ID, float X, float Y, float Z)
{
	static AMX_NATIVE Native = sampgdk::FindNative("SetDynamicObjectPos");
	sampgdk::InvokeNative(Native, "ifff", ID, X, Y, Z);
}

void Object::SetRotation(unsigned int ID, const Point3D<float>& Position)
{
	SetRotation(ID, Position.X, Position.Y, Position.Z);
}

void Object::SetRotation(unsigned int ID, float X, float Y, float Z)
{
	static AMX_NATIVE Native = sampgdk::FindNative("SetDynamicObjectRot");
	sampgdk::InvokeNative(Native, "ifff", ID, X, Y, Z);
}

void Object::StopMove(unsigned int ID)
{
	static AMX_NATIVE Native = sampgdk::FindNative("StopDynamicObject");
	sampgdk::InvokeNative(Native, "i", ID);
}


