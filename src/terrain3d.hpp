#pragma once

#include <godot_cpp/classes/node3d.hpp>
#include <godot_cpp/variant/packed_byte_array.hpp>

#include "terrain_patch.hpp"

using namespace godot;

class Terrain3D : Node3D {
public:
    //count of chunks per patch
    static const int PATCH_CHUNKS_AMOUNT = 16;
    //edges per chunk
    static const int PATCH_CHUNK_EDGES = 4;
    //units per vertex (also scale factor)
    static const float UNITS_PER_VERTEX;

    //this missing?
    Array terrainPatches;

    Terrain3D();

    ~Terrain3D();

    void updatePosition();

    void updateSettings();


private:
    void cacheNeighbors();

public:
    int getPatchesCount();

    TerrainPatch getPatch(int x, int y);

    TerrainPatch getPatch(int idx);


    // why is this? $Remember this
    template<typename T>
    T fromByteArray(PackedByteArray source);

    void createPatchGrid(int patchX, int patchY, int chunkSize);

    void createPatch(Vector2i coord, int chunkSize);

    void createPatch(int x, int y, int chunkSize);

};