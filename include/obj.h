
#pragma once

#include <cstdlib>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

#include "obj_type.h"

void obj_parse(std::ifstream *obj_file, struct OBJ_t *obj);

void obj_write_header(std::ofstream *header_file, struct OBJ_t *obj);

#endif /* _OBJ_H_ */
