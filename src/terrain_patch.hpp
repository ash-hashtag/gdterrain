
#include <godot_cpp/classes/resource.hpp>
#include <godot_cpp/variant/vector2i.hpp>
#include <godot_cpp/variant/vector3.hpp>
#include <godot_cpp/variant/array.hpp>

using namespace godot;

class TerrainPatch : Resource {
public:
    Vector2i patch_coord = Vector2i();

    Vector3 offset = Vector3();

    Array chunks = {}; // Array<TerrainChunk>

};