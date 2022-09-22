#pragma once

#include <godot_cpp/classes/resource.hpp>
#include <godot_cpp/variant/vector2i.hpp>
#include <godot_cpp/variant/vector2.hpp>
#include <godot_cpp/variant/rid.hpp>
#include <godot_cpp/classes/material.hpp>
#include <godot_cpp/classes/mesh.hpp>
#include <godot_cpp/variant/aabb.hpp>
#include <godot_cpp/core/math.hpp>
#include <godot_cpp/variant/plane.hpp>
#include <godot_cpp/classes/object.hpp>
#include <godot_cpp/classes/rendering_server.hpp>
#include <godot_cpp/variant/transform3d.hpp>
#include <godot_cpp/variant/basis.hpp>
#include <godot_cpp/variant/color.hpp>
#include <godot_cpp/variant/quaternion.hpp>
#include <godot_Cpp/classes/texture2d.hpp>

#include <memory.hpp>

#include "terrain_patch_info.hpp"
#include "terrain_patch.hpp"
#include "terrain3d.hpp"


using namespace godot;

class TerrainChunk : Resource
{
public:
    Vector2i position = Vector2i();

    Vector2 offsetUv = Vector2();

    float TerrainChunkSizeLOD0 = 0.0;

    float offset = 0;

    float height = 1;

protected:

    RID instanceRid;

    RID materialId;

    // Material *materialInUse;
    std::unique_ptr<Material> materialInUse;

    RID meshId;

    // Mesh *mesh;
    std::unique_ptr<Mesh> mesh;

    Array _neighbours = {}; //Array<TerrainChunks>

public:
    int _cachedDrawLOD;

    AABB getBounds(TerrainPatchInfo info, Vector3 patchOffset);

protected:
    Plane getNeightbours();

public:
    void clearDraw();

    Transform3D updatePosition(TerrainPatchInfo info, Transform3D terrainTransform, Vector3 patchOffset);

    Plane getUVScale();

    void updateInpectorMaterial(Color color, Plane brushData0, Plane brushData1);

    void setDefaultMaterial(Texture2D image);

    void cacheNeighbours(Terrain3D terrainNode, TerrainPatch currentPatch);
};