#include "viewer.h"

int parseObj(const char *fileName, data_t *fileData) {
  int code = OK;
  FILE *file;
  file = fopen(fileName, "r");
  if (file != NULL) {
    fileData->maximumVertex = 0.0;

    // 1 проход по файлу - считаем кол-во вершин и полигонов
    code = countingVertexesAndFacets(file, fileData);
    fseek(file, 0, SEEK_SET);
    if (!code) {
      if (fileData->countVertexes != 0 && fileData->countFacets != 0) {
        if (!(fileData->vertexArray = (double *)malloc(fileData->countVertexes *
                                                       3 * sizeof(double)))) {
          code = MALLOC_ERROR;
        }
        if (!(fileData->facetsArray =
                  (int *)malloc(fileData->countFacets * 2 * sizeof(int)))) {
          code = MALLOC_ERROR;
        }
        if (!code) {
          // 2 проход по файлу
          code = readingVertexesAndFacets(file, fileData);
          if (code) return code;
        }
      } else {
        code = ERROR;
      }
    }
    fclose(file);
  } else {
    code = FILE_NOT_FOUND;
  }
  return code;
}

int countingVertexesAndFacets(FILE *file, data_t *fileData) {
  int code = OK;
  int countVertexes = 0;
  int countFacets = 0;
  char str[512] = "";
  while (fgets(str, 512, file) != NULL && !code) {
    if (str[0] == 'v' && str[1] == ' ') {
      countVertexes++;
    } else if (str[0] == 'f') {
      for (int i = 1; str[i] != '\n'; i++) {
        if (str[1] == ' ' && str[i] == ' ') {
          countFacets++;
        }
      }
    }
  }
  fileData->countVertexes = countVertexes;
  fileData->countFacets = countFacets;
  return code;
}

int readingVertexesAndFacets(FILE *file, data_t *fileData) {
  int code = OK;
  char str[512] = "";
  int countVertex = 0;
  int countFacets = 0;
  while (fgets(str, 512, file) != NULL) {
    if (str[0] == 'v' && str[1] == ' ') {
      parsingVertexes(str, fileData, countVertex);
      countVertex++;
    } else if (str[0] == 'f' && str[1] == ' ') {
      code = parsingFacets(str, fileData, &countFacets);
      if (code) break;
    }
  }
  centringObject(fileData);
  return code;
}

void parsingVertexes(char *str, data_t *fileData, int countVertex) {
  int counter = 0;
  for (size_t i = 1; i < strlen(str); i++) {
    if (isDigit(str[i]) || str[i] == '-') {
      char temp[512] = "";
      int kolvo = strcspn(str + i, " ");
      strncpy(temp, str + i, kolvo);
      changeDotToColumn(temp);
      double tempNum = atof(temp);
      fileData->vertexArray[countVertex * 3 + counter] = tempNum;
      if (fabs(fileData->vertexArray[countVertex * 3 + counter]) >
          fileData->maximumVertex) {
        fileData->maximumVertex =
            fabs(fileData->vertexArray[countVertex * 3 + counter]);
      }
      counter++;
      i += kolvo - 1;
    }
  }
}

void centringObject(data_t *fileData) {
  double bigV = -100.0;
  double smallV = 100.0;

  if (fileData->maximumVertex > 1.0) {
    for (int i = 0; i < fileData->countVertexes * 3; i++) {
      // приведение всех вершин к диапазону от -1 до 1
      fileData->vertexArray[i] =
          fileData->vertexArray[i] / fileData->maximumVertex;
      if (i % 3 == 0) {
        // самая большая вершина по X
        if (fileData->vertexArray[i] > bigV) {
          bigV = fileData->vertexArray[i];
        }
        // самая маленькая вершина по X
        if (fileData->vertexArray[i] < smallV) {
          smallV = fileData->vertexArray[i];
        }
      }
    }
  }

  double coef = (bigV + smallV) / 2;
  // Центрирование изображения по X
  for (int i = 0; i < fileData->countVertexes * 3; i++) {
    if (i % 3 == 0) {
      fileData->vertexArray[i] -= coef;
    }
  }
}

void changeDotToColumn(char *str) {
  str = str;
  // char *temp;
  // temp = strchr(str, '.');
  // str[temp - str] = ',';
}

int parsingFacets(char *str, data_t *fileData, int *countFacets) {
  int counter = 0;
  int tempFirstValue = 0;
  int code = OK;
  for (size_t i = 1; i < strlen(str) && !code; i++) {
    if (isDigit(str[i])) {
      char temp[512] = "";
      int kolvo = strcspn(str + i, " /");
      strncpy(temp, str + i, kolvo);
      // вычитаем 1 так как в obj файле вершины идут не с 0 а с 1
      int num = atoi(temp) - 1;
      if (counter == 0) {
        tempFirstValue = num;
        fileData->facetsArray[*countFacets + counter] = num;
        counter++;
      } else {
        fileData->facetsArray[*countFacets + counter] = num;
        counter++;
        fileData->facetsArray[*countFacets + counter] = num;
        counter++;
      }
      i += kolvo - 1;
    } else if (str[i] == '/') {
      int kolvo = strcspn(str + i, " ");
      i += kolvo - 1;
    }
  }
  if (!code) {
    fileData->facetsArray[*countFacets + counter] = tempFirstValue;
    counter++;
    (*countFacets) += counter;
  }
  return code;
}

void removeData(data_t *fileData) {
  free(fileData->vertexArray);
  free(fileData->facetsArray);
}

int isDigit(char ch) { return (ch >= '0' && ch <= '9'); }
