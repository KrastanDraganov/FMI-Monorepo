#pragma once

#include <iostream>
#include <cstring>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>

namespace Object3dConstants
{
    const std::string END_HEADER_KEYWORD = "end_header";
    const std::string COMMENT_KEYWORD = "comment";
    const std::string ELEMENT_KEYWORD = "element";
    const std::string VERTEX_KEYWORD = "vertex";
    const std::string FACE_KEYWORD = "face";
}

class Object3d
{
public:
    Object3d() = default;
    Object3d(const std::string &filename);
    Object3d(std::istream &in);

    int getVertexCount() const;
    int getFaceCount() const;

    void save(const std::string &filename) const;
    void print(std::ostream &out) const;

    Object3d &cut(std::function<bool(float, float, float)> f) const;
    void flip();

    static Object3d &cube(float edgeLength);
    static Object3d &sphere(float radius);

private:
    struct Vertex
    {
        float x, y, z;
    };

    using Polygon = std::vector<int>;

    std::vector<Vertex> vertices;
    std::vector<Polygon> polygons;

    void loadContent(std::istream &in);

    Polygon &loadPolygon(std::istream &in, int verticesCount);

    bool checkIsValidPolygonAfterReorder(const Polygon &polygon, const std::vector<int> &oldToNewIndexMap) const;
    Polygon &createNewPolygonAfterReorder(const std::vector<int> &oldToNewIndexMap) const;
};