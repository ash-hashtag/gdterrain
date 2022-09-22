#include "terrain3d.hpp"

const float Terrain3D::UNITS_PER_VERTEX = 100.0f;

Terrain3D::Terrain3D() {
    set_notify_transform(true);
}

Terrain3D::~Terrain3D() {

}

void Terrain3D::updatePosition() {
    auto size = terrainPatches.size();
    for(int i = 0; i < size; ++i) {
        
    }
}