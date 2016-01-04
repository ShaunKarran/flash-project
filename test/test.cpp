
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

#include "obj.h"

int main(int argc, char *argv[])
{
    std::ifstream file;
    struct OBJ_t cube;

    file.open(argv[1]);
    obj_parse(&file, &cube);

    for (int i = 0; i < cube.num_vertices; i++) {
        std::cout << cube.vertices[i] << " ";
        if ((i + 1) % 3 == 0) { std::cout << std::endl; }
    }
    for (int i = 0; i < cube.num_normals; i++) {
        std::cout << cube.normals[i] << " ";
        if ((i + 1) % 3 == 0) { std::cout << std::endl; }
    }
    for (int i = 0; i < cube.num_vertex_indices; i++) {
        std::cout << cube.vertex_indices[i] << "//" << cube.normal_indices[i] << " ";
        if ((i + 1) % 3 == 0) { std::cout << std::endl; }
    }

    file.close();
    return 0;
}
