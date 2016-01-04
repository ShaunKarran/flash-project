
#ifndef _OBJ_TYPE_H_
#define _OBJ_TYPE_H_

// struct OBJ_t {
//     size_t num_vertices;
//     float  *vertices;
//     size_t num_vertex_indices;
//     int    *vertex_indices;
//     size_t num_normals;
//     float  *normals;
//     size_t num_normal_indices;
//     int    *normal_indices;
// };

struct OBJ_t {
    size_t num_vertices;
    float  vertices[24];
    size_t num_vertex_indices;
    int    vertex_indices[36];
    size_t num_normals;
    float  normals[18];
    size_t num_normal_indices;
    int    normal_indices[36];
};

#endif /* _OBJ_TYPE_H_ */
