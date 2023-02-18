#ifndef _SRC_VIEWER_H_
#define _SRC_VIEWER_H_

#include <float.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SUCCESS 1
#define FAILURE 0
#define EPS 1e-7

typedef struct data {
  int countVertexes;
  int countFacets;
  double *vertexArray;
  int *facetsArray;
  double maximumVertex;
} data_t;

enum resultCode { OK, ERROR, FILE_NOT_FOUND, MALLOC_ERROR };

#define PI 3.14159265

void set_scale(data_t *obj, double x);
void set_move(data_t *obj, double dx, double dy, double dz);
void set_rotate(data_t *obj, double rotate_x, double rotate_y, double rotate_z);

// return code ( 0 = OK; 1 = ERROR )
int parseObj(const char *fileName, data_t *fileData);
// count vertexes and facets
int countingVertexesAndFacets(FILE *file, data_t *fileData);
// read vertexes and facets
int readingVertexesAndFacets(FILE *file, data_t *fileData);
// parse v string
void parsingVertexes(char *str, data_t *fileData, int countVertex);
// parse f string
int parsingFacets(char *str, data_t *fileData, int *countFacets);
// free memory
void removeData(data_t *fileData);

void centringObject(data_t *fileData);

void changeDotToColumn(char *str);
int isDigit(char ch);

#endif  // _SRC_VIEWER_H_
