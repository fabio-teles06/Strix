#ifndef STRIX_RENDERER_H
#define STRIX_RENDERER_H

#include <strix/strix.h>
#include <strix/strix_stream_buffer.h>

namespace strix
{
    class STRIX_API Renderer
    {
    public:
        static void initialize();
        void terminate();

        //
        // Shader resources
        //

        static bool createShaderProgram(ShaderProgram *outShader, const char *vertexShader, const char *fragmentShader, const char *geometryShader = nullptr);
        static void destroyShaderProgram(ShaderProgram *program);
        static ShaderProgram getDefaultShaderProgram();

        //
        // Mesh resources
        //
        // static bool createMesh(Mesh *outMesh,
        //                        bool dynamic, Primitive primitive,
        //                        const Vector3 *vertices, int numVertices,
        //                        const unsigned int *indices, int numIndices,
        //                        const Color *color,
        //                        const Vector2 *uv0,
        //                        const Vector2 *uv1,
        //                        const Vector3 *normals);

        // static void updateMesh(Mesh *mesh, MeshData *meshData);
        // static void destroyMesh(Mesh *mesh);

        //
        // StreamBuffers
        //

        static bool createStreamBuffer(StreamBuffer *out, uint32 capacity = 8, StreamBuffer::Format format = StreamBuffer::POS_COLOR_UV, uint32 indicesPerElement = 6);
        static bool resizeStreamBuffer(StreamBuffer &streamBuffer, uint32 capacity);
        static void bindStreamBuffer(StreamBuffer &streamBuffer);
        static void unbindStreamBuffer(StreamBuffer &streamBuffer);
        static bool destroyStreamBuffer(StreamBuffer &streamBuffer);

        static void begin(StreamBuffer &streamBuffer);
        static void pushSprite(StreamBuffer &streamBuffer, const Vector3 &position, const Vector2 &size, const Rectf &uv, const Color &color);
        static void pushSprite(StreamBuffer &streamBuffer, const Vector3 &position, const Vector2 &size, const Rectf &uv, const Color &tlColor, const Color &trColor, const Color &blColor, const Color &brColor);
        static void pushLines(StreamBuffer &streamBuffer, const Vector2 *points, int numPoints, const Color &color, float thickness);
        static void end(StreamBuffer &streamBuffer);
        static void flush(StreamBuffer &streamBuffer);
    }
}