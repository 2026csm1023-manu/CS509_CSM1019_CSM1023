#ifndef READER_H
#define READER_H

#include <fstream>
#include "../include/kmeans.h"
#include "../include/fastmap.h"

using namespace std;

bool read_kmeans(ifstream& file,KMeansInput& input);
bool read_fastmap(ifstream& file,FastMapInput& input);

#endif
