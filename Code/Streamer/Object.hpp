#pragma once

#ifndef STREAMER_OBJECT_DD
#define STREAMER_OBJECT_DD 0.0f
#endif

#ifndef STREAMER_OBJECT_SD
#define STREAMER_OBJECT_SD 300.0f
#endif


enum class ObjectEditionResponse : uint8_t
{
	kCancel = 0, // EDIT_RESPONSE_CANCEL - Player cancelled (ESC). 
	kFinal, // EDIT_RESPONSE_FINAL - Player clicked on save.
	kUpdate // EDIT_RESPONSE_UPDATE - Player moved the object (edition did not stop at all).
};

namespace Object
{
	const bool AttachToObject(uint32_t ID, uint32_t AttachToID, float X, float Y, float Z, float RotationX, float RotationY, float RotationZ, bool SyncRotation = true);

	const bool AttachToVehicle(uint32_t ID, uint32_t VehicleID, float X, float Y, float Z, float RotationX, float RotationY, float RotationZ);

	const uint32_t Create(uint32_t ModelID, const Point3D<float>& Position, const Point3D<float>& Rotation, int32_t VirtualWorld = -1, int32_t Interior = -1, int32_t PlayerID = -1, float StreamDistance = STREAMER_OBJECT_SD, float DrawDistance = STREAMER_OBJECT_DD);

	const bool Destroy(uint32_t ID);

	const bool GetNoCameraCol(uint32_t ID);

	const Point3D<float> GetPosition(uint32_t ID);

	const Point3D<float> GetRotation(uint32_t ID);

	const bool IsValid(uint32_t ID);

	const bool IsMaterialUsed(uint32_t ID, uint32_t MaterialIndex);

	const bool IsMoving(uint32_t ID);

	void Move(uint32_t ID, const Point3D<float>& Position, float Speed, const Point3D<float>& Rotation = { -1000.0, -1000.0, -1000.0 });

	void Move(uint32_t ID, float X, float Y, float Z, float Speed, float RotationX = -1000.0, float RotationY = -1000.0, float RotationZ = -1000.0);

	bool SetNoCameraCol(uint32_t ID);

	void SetPosition(uint32_t ID, const Point3D<float>& Position);

	void SetPosition(uint32_t ID, float X, float Y, float Z);

	void SetRotation(uint32_t ID, const Point3D<float>& Position);

	void SetRotation(uint32_t ID, float X, float Y, float Z);

	void StopMove(uint32_t ID);

	/* Unimplemented:
		* native STREAMER_TAG_OBJECT CreateDynamicObjectEx(modelid, Float:x, Float:y, Float:z, Float:rx, Float:ry, Float:rz, Float:streamdistance = STREAMER_OBJECT_SD, Float:drawdistance = STREAMER_OBJECT_DD, worlds[] = { -1 }, interiors[] = { -1 }, players[] = { -1 }, maxworlds = sizeof worlds, maxinteriors = sizeof interiors, maxplayers = sizeof players);
		* native IsDynamicObjectMaterialUsed(STREAMER_TAG_OBJECT objectid, materialindex);
		* native GetDynamicObjectMaterial(STREAMER_TAG_OBJECT objectid, materialindex, &modelid, txdname[], texturename[], &materialcolor, maxtxdname = sizeof txdname, maxtexturename = sizeof texturename);
		* native SetDynamicObjectMaterial(STREAMER_TAG_OBJECT objectid, materialindex, modelid, const txdname[], const texturename[], materialcolor = 0);
		* native IsDynamicObjectMaterialTextUsed(STREAMER_TAG_OBJECT objectid, materialindex);
		* native GetDynamicObjectMaterialText(STREAMER_TAG_OBJECT objectid, materialindex, text[], &materialsize, fontface[], &fontsize, &bold, &fontcolor, &backcolor, &textalignment, maxtext = sizeof text, maxfontface = sizeof fontface);
		* native SetDynamicObjectMaterialText(STREAMER_TAG_OBJECT objectid, materialindex, const text[], materialsize = OBJECT_MATERIAL_SIZE_256x128, const fontface[] = "Arial", fontsize = 24, bold = 1, fontcolor = 0xFFFFFFFF, backcolor = 0, textalignment = 0);
	*/
}