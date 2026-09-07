#ifndef PRINTER_H
#define PRINTER_H

#include <string>
#include "../include/kmeans.h"
#include "../include/fastmap.h"

using namespace std;

void print_kmeans(const KMeansResult& result,const KMeansInput& input,double execution_time,const string& output_file);
void print_fastmap(const FastMapResult& result,const FastMapInput& input,double execution_time,const string& output_file);

#endif
