#include "Object3d.h"

Object3d::Object3d(const std::string &filename)
{
    std::ifstream file(filename);

    if (!file)
    {
        throw std::runtime_error("Cannot open file: " + filename);
    }

    loadContent(file);
}

Object3d::Object3d(std::istream &in)
{
    loadContent(in);
}

void Object3d::loadContent(std::istream &in)
{
    std::string line;

    int allVerticesCount = 0, allPolygonsCount = 0;
    bool headerEnded = false;

    while (std::getline(in, line))
    {
        if (line == Object3dConstants::END_HEADER_KEYWORD)
        {
            headerEnded = true;
            break;
        }

        std::istringstream iss(line);

        std::string keyword;
        iss >> keyword;

        if (keyword == Object3dConstants::COMMENT_KEYWORD)
        {
            continue;
        }

        if (keyword == Object3dConstants::ELEMENT_KEYWORD)
        {
            std::string type;
            iss >> type;

            if (type == Object3dConstants::VERTEX_KEYWORD)
            {
                iss >> allVerticesCount;
            }
            else if (type == Object3dConstants::FACE_KEYWORD)
            {
                iss >> allPolygonsCount;
            }
        }
    }

    if (!headerEnded)
    {
        throw std::runtime_error("Invalid PLY header");
    }

    for (int i = 0; i < allVerticesCount; ++i)
    {
        Vertex vertex;

        if (!(in >> vertex.x >> vertex.y >> vertex.z))
        {
            throw std::runtime_error("Invalid vertex");
        }

        vertices.push_back(vertex);
    }

    for (int i = 0; i < allPolygonsCount; ++i)
    {
        int currentVerticesCount;
        in >> currentVerticesCount;

        Polygon currentPolygon(currentVerticesCount);

        for (int j = 0; j < currentVerticesCount; ++j)
        {
            in >> currentPolygon[j];
        }

        polygons.push_back(std::move(currentPolygon));
    }
}

int Object3d::getVertexCount() const
{
    return (int)vertices.size();
}

int Object3d::getFaceCount() const
{
    return (int)polygons.size();
}

void Object3d::save(const std::string &filename) const
{
    std::ofstream out(filename);

    if (!out)
    {
        throw std::runtime_error("Cannot save file: " + filename);
    }

    print(out);

    out.close();
}

void Object3d::print(std::ostream &out) const
{
    out << "ply\n";
    out << "format ascii 1.0\n";
    out << Object3dConstants::ELEMENT_KEYWORD << " " << Object3dConstants::VERTEX_KEYWORD << " " << getVertexCount() << "\n";
    out << "property float x\n";
    out << "property float y\n";
    out << "property float z\n";
    out << Object3dConstants::ELEMENT_KEYWORD << " " << Object3dConstants::FACE_KEYWORD << " " << getFaceCount() << "\n";
    out << "property list uchar int vertex_indices\n";
    out << "end_header\n";

    for (const auto &vertex : vertices)
    {
        out << vertex.x << " " << vertex.y << " " << vertex.z << '\n';
    }

    for (const auto &polygon : polygons)
    {
        out << (int)polygon.size();

        for (int index : polygon)
        {
            out << " " << index;
        }

        out << "\n";
    }
}

bool Object3d::checkIsValidPolygonAfterReorder(const Polygon &polygon, const std::vector<int> &oldToNewIndexMap) const
{
    for (int index : polygon)
    {
        if (oldToNewIndexMap[index] == -1)
        {
            return false;
        }
    }

    return true;
}

Object3d &Object3d::cut(std::function<bool(float, float, float)> f) const
{
    Object3d result;

    std::vector<int> oldVertexIndexToNewVertexIndexMap((int)vertices.size(), -1);

    for (int i = 0; i < (int)vertices.size(); ++i)
    {
        const auto &vertex = vertices[i];

        if (f(vertex.x, vertex.y, vertex.z))
        {
            result.vertices.push_back(vertex);
            oldVertexIndexToNewVertexIndexMap[i] = (int)result.vertices.size() - 1;
        }
    }

    for (const auto &polygon : polygons)
    {
        if (checkIsValidPolygonAfterReorder(polygon, oldVertexIndexToNewVertexIndexMap))
        {
            Polygon newPolygon = createNewPolygonAfterReorder(oldVertexIndexToNewVertexIndexMap);
            result.polygons.push_back(std::move(newPolygon));
        }
    }

    return result;
}

void Object3d::flip()
{
    for (auto &polygon : polygons)
    {
        std::reverse(polygon.begin(), polygon.end());
    }
}

Object3d &Object3d::cube(float edgeLength)
{
    Object3d cube;

    float halfEdgeLength = edgeLength / 2.0;

    cube.vertices = {
        {-halfEdgeLength, -halfEdgeLength, -halfEdgeLength},
        {+halfEdgeLength, -halfEdgeLength, -halfEdgeLength},
        {+halfEdgeLength, -halfEdgeLength, +halfEdgeLength},
        {-halfEdgeLength, -halfEdgeLength, +halfEdgeLength},
        {-halfEdgeLength, +halfEdgeLength, -halfEdgeLength},
        {+halfEdgeLength, +halfEdgeLength, -halfEdgeLength},
        {+halfEdgeLength, +halfEdgeLength, +halfEdgeLength},
        {-halfEdgeLength, +halfEdgeLength, +halfEdgeLength}};

    cube.polygons = {
        {0, 1, 2, 3},
        {7, 6, 5, 4},
        {0, 4, 5, 1},
        {1, 5, 6, 2},
        {2, 6, 7, 3},
        {3, 7, 4, 0}};

    return cube;
}

// Some black magic, found online
Object3d &Object3d::sphere(float radius)
{
    Object3d sphere;

    constexpr int lat = 10, lon = 10;

    for (int i = 0; i <= lat; ++i)
    {
        float theta = i * M_PI / lat;

        for (int j = 0; j <= lon; ++j)
        {
            float phi = j * 2 * M_PI / lon;

            float x = radius * sin(theta) * cos(phi);
            float y = radius * sin(theta) * sin(phi);
            float z = radius * cos(theta);

            sphere.vertices.push_back({x, y, z});
        }
    }

    for (int i = 0; i < lat; ++i)
    {
        for (int j = 0; j < lon; ++j)
        {
            int a = i * (lon + 1) + j;
            int b = a + lon + 1;

            sphere.polygons.push_back({a, a + 1, b + 1, b});
        }
    }

    return sphere;
}
