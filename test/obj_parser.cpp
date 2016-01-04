
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

struct OBJ_t {
    size_t num_vertices;
    float  *vertices;
    size_t num_indices;
    int    *indices;
};

void obj_parse(std::ifstream *obj_file, struct OBJ_t *obj);

int main(int argc, char *argv[])
{
    std::ifstream file;
    struct OBJ_t cube;

    file.open(argv[1]);
    obj_parse(&file, &cube);

    for (int i = 0; i < cube.num_vertices; i++) {
        std::cout << cube.vertices[i] << std::endl;
    }

    for (int i = 0; i < cube.num_indices; i++) {
        std::cout << cube.indices[i] << std::endl;
    }

    file.close();
    return 0;
}

void obj_parse(std::ifstream *obj_file, struct OBJ_t *obj)
{
    std::vector<float> temp_vertices;
    std::vector<int>   temp_indices;
    std::string line;
    std::string name;

    while (std::getline(*obj_file, line)) {
        if (line == "" || line[0] == '#') { // Skip everything and continue with the next line.
            continue;
        }

        std::istringstream line_stream(line);
        line_stream >> name;

        if (name == "v") { // Vertex.
            float vertex[3];
            sscanf(line.c_str(), "%*s %f %f %f", &vertex[0], &vertex[1], &vertex[2]);
            temp_vertices.push_back(vertex[0]);
            temp_vertices.push_back(vertex[1]);
            temp_vertices.push_back(vertex[2]);
        } else if (name == "f") { // Face.
            int face[3];
            sscanf(line.c_str(), "%*s %u %u %u", &face[0], &face[1], &face[2]);
            temp_indices.push_back(face[0]);
            temp_indices.push_back(face[1]);
            temp_indices.push_back(face[2]);
        }
    };

    obj->num_vertices = temp_vertices.size();
    obj->vertices = (float *)malloc(obj->num_vertices * sizeof(float));
    std::copy(temp_vertices.begin(), temp_vertices.end(), obj->vertices);

    obj->num_indices = temp_vertices.size();
    obj->indices = (int *)malloc(obj->num_indices * sizeof(int));
    std::copy(temp_indices.begin(), temp_indices.end(), obj->indices);
}
