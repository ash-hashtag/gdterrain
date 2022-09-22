
#include <godot_cpp/classes/resource.hpp>

using namespace godot;

class TerrainPatchInfo: Resource {

public:
    float patchOffset = 0;

    float patchHeight = 0;

    int chunkSize = 0;

    int vertexCountEdge = 0;

    int textureSize = 0;

};