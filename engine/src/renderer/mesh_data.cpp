#include <strix/renderer/mesh_data.h>
#include <strix/math/vector2.h>
#include <strix/math/vector3.h>

namespace strix
{
    unsigned int indicesCube[] = {
        0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 0, 18, 1, 3, 19, 4, 6, 20, 7, 9, 21, 10, 12, 22, 13, 15, 23, 16};

    strix::Vector3 positionsCube[] = {
        {-1.0f, 1.0f, -1.0f},
        {1.0f, 1.0f, 1.0f},
        {1.0f, 1.0f, -1.0f},
        {1.0f, 1.0f, 1.0f},
        {-1.0f, -1.0f, 1.0f},
        {1.0f, -1.0f, 1.0f},
        {-1.0f, 1.0f, 1.0f},
        {-1.0f, -1.0f, -1.0f},
        {-1.0f, -1.0f, 1.0f},
        {1.0f, -1.0f, -1.0f},
        {-1.0f, -1.0f, 1.0f},
        {-1.0f, -1.0f, -1.0f},
        {1.0f, 1.0f, -1.0f},
        {1.0f, -1.0f, 1.0f},
        {1.0f, -1.0f, -1.0f},
        {-1.0f, 1.0f, -1.0f},
        {1.0f, -1.0f, -1.0f},
        {-1.0f, -1.0f, -1.0f},
        {-1.0f, 1.0f, 1.0f},
        {-1.0f, 1.0f, 1.0f},
        {-1.0f, 1.0f, -1.0f},
        {1.0f, -1.0f, 1.0f},
        {1.0f, 1.0f, 1.0f},
        {1.0f, 1.0f, -1.0f}};

    MeshData::MeshData() {}

    MeshData::MeshData(Vector3 *positions, int numPositions, unsigned int *indices, int numIndices)
        : positions(positions), indices(indices), numPositions(numPositions), numIndices(numIndices) {}

    MeshData::MeshData(const MeshData &other) : positions(other.positions), indices(other.indices), numPositions(other.numPositions), numIndices(other.numIndices) {}

    MeshData &MeshData::setPosition(Vector3 *positions)
    {
        this->positions = positions;
        return *this;
    }

    MeshData &MeshData::setIndices(unsigned int *indices)
    {
        this->indices = indices;
        return *this;
    }

    const MeshData MeshData::getPrimitiveCube()
    {
        return MeshData(positionsCube, sizeof(positionsCube) / sizeof(Vector3), indicesCube, sizeof(indicesCube) / sizeof(unsigned int));
    }
}
