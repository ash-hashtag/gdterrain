
#include "terrain_chunk.hpp";
#include "terrain3d.hpp";

AABB TerrainChunk::getBounds(TerrainPatchInfo info, Vector3 patchOffset)
{
    float size = (float)info.chunkSize * Terrain3D::UNITS_PER_VERTEX;
    auto origin = patchOffset + Vector3(position.x * size, offset, position.y * size);
    auto bounds = AABB(origin, Vector3(size, height, size));

    return bounds;
}

Plane TerrainChunk::getNeightbours()
{
    int lod = _cachedDrawLOD;

    int minLod = Math::max(lod + 1, 0);

    auto getNeighbourChunkLOD = [&](size_t index)
    {
        auto terrainChunk = Object::cast_to<TerrainChunk>(_neighbours[index].operator Object *());
        return (float)Math::clamp(terrainChunk->_cachedDrawLOD, lod, minLod);
    };

    auto plane = Plane(
        getNeighbourChunkLOD(0),
        getNeighbourChunkLOD(1),
        getNeighbourChunkLOD(2),
        getNeighbourChunkLOD(3));
    
    return plane;
}

void TerrainChunk::clearDraw() {
    // This might give trouble $Remember this
    auto renderingServer = RenderingServer();
    if (meshId.is_valid()){
        renderingServer.free_rid(meshId);
    }
    if (instanceRid.is_valid()) {
        renderingServer.free_rid(instanceRid);
    }
    if (materialId.is_valid()) {
        renderingServer.free_rid(materialId);
    }

    mesh = nullptr;
    materialInUse = nullptr;
}

Transform3D TerrainChunk::updatePosition(TerrainPatchInfo info, Transform3D terrainTransform, Vector3 patchOffset){
    float size = info.chunkSize * Terrain3D::UNITS_PER_VERTEX;
    auto localPosition = patchOffset + Vector3(position.x * size, info.patchOffset, position.y * size);
    auto localTransform = Transform3D();
    localTransform.origin = localPosition;
    auto quaternion = Quaternion();
    localTransform.basis = Basis(quaternion);

    auto globalTransform = terrainTransform * localTransform;

    if (instanceRid.is_valid()) {
        RenderingServer().instance_set_transform(instanceRid, globalTransform);
    }
    if (materialId.is_valid()) {
        RenderingServer().material_set_param(materialId, "uv_scale", getUVScale());
    }

    return globalTransform;
}

Plane TerrainChunk::getUVScale() {
    auto q = Quaternion(1.0f, 1.0f, position.x, position.y) * (1.0f/ Terrain3D::PATCH_CHUNK_EDGES);
    return Plane(q.x, q.y, q.z, q.w);
}

void TerrainChunk::updateInpectorMaterial(Color color, Plane brushData0, Plane brushData1){
    auto renderingServer = RenderingServer();
    renderingServer.material_set_param(materialId, "Color", color);
    renderingServer.material_set_param(materialId, "BrushData0", brushData0);
    renderingServer.material_set_param(materialId, "BrushData1", brushData1);
}

void TerrainChunk::setDefaultMaterial(Texture2D image) {
    RenderingServer().material_set_param(materialId, "terrainDefaultMaterial", image.get_rid());
}

void TerrainChunk::cacheNeighbours(Terrain3D terrainNode, TerrainPatch currentPatch){
    
    // this might break $Remeber this
    _neighbours.clear();
    _neighbours.append(this);
    _neighbours.append(this);
    _neighbours.append(this);
    _neighbours.append(this);

    if (position.y > 0) {
        auto varChunk = currentPatch.chunks[(Terrain3D::PATCH_CHUNK_EDGES - 1) * Terrain3D::PATCH_CHUNK_EDGES + position.x];

    }
}