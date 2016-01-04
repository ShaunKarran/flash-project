//
// #include "obj.h"
//
// void obj_parse(std::ifstream *obj_file, struct OBJ_t *obj)
// {
//     std::vector<float> vertices;
//     std::vector<int>   vertex_indices;
//     std::vector<float> normals;
//     std::vector<int>   normal_indices;
//     std::vector<float> tex_coords;
//     std::vector<int>   tex_coord_indices;
//     std::string line;
//     std::string name;
//     bool has_tex_coords;
//     bool has_normals;
//
//     while (std::getline(*obj_file, line)) {
//         if (line == "" || line[0] == '#') { // Skip everything and continue with the next line.
//             continue;
//         }
//
//         std::istringstream line_stream(line);
//         line_stream >> name;
//
//         if (name == "v") {
//             float vec3[3];
//             sscanf(line.c_str(), "%*s %f %f %f", &vec3[0], &vec3[1], &vec3[2]);
//             vertices.push_back(vec3[0]);
//             vertices.push_back(vec3[1]);
//             vertices.push_back(vec3[2]);
//         } else if (name == "vn") {
//             float vec3[3];
//             has_normals = true;
//             sscanf(line.c_str(), "%*s %f %f %f", &vec3[0], &vec3[1], &vec3[2]);
//             normals.push_back(vec3[0]);
//             normals.push_back(vec3[1]);
//             normals.push_back(vec3[2]);
//         } else if (name == "f") {
//             int vec3_a[3];
//             int vec3_b[3];
//             sscanf(line.c_str(), "%*s %d//%d %d//%d %d//%d",
//                                 &vec3_a[0], &vec3_b[0], &vec3_a[1], &vec3_b[1], &vec3_a[2], &vec3_b[2]);
//             vertex_indices.push_back(vec3_a[0]);
//             vertex_indices.push_back(vec3_a[1]);
//             vertex_indices.push_back(vec3_a[2]);
//             normal_indices.push_back(vec3_b[0]);
//             normal_indices.push_back(vec3_b[1]);
//             normal_indices.push_back(vec3_b[2]);
//         }
//     };
//
//     obj->num_vertices = vertices.size();
//     obj->vertices = (float *)malloc(obj->num_vertices * sizeof(float));
//     std::copy(vertices.begin(), vertices.end(), obj->vertices);
//
//     obj->num_normals = normals.size();
//     obj->normals = (float *)malloc(obj->num_normals * sizeof(float));
//     std::copy(normals.begin(), normals.end(), obj->normals);
//
//     obj->num_vertex_indices = vertex_indices.size();
//     obj->vertex_indices = (int *)malloc(obj->num_vertex_indices * sizeof(int));
//     std::copy(vertex_indices.begin(), vertex_indices.end(), obj->vertex_indices);
//
//     obj->num_normal_indices = normal_indices.size();
//     obj->normal_indices = (int *)malloc(obj->num_normal_indices * sizeof(int));
//     std::copy(normal_indices.begin(), normal_indices.end(), obj->normal_indices);
// }
//
// void obj_write_header(std::ofstream *header_file, struct OBJ_t *obj)
// {
//
// }
