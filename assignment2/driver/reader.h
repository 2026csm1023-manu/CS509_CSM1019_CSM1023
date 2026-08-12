#ifndef READER_H
#define READER_H

#include <fstream>
#include "../include/graph.h"

bool read_buddy_graph(std::ifstream& file, GraphInput& input);

#endif