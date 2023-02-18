#include "../viewer.h"
#include <check.h>

int is_obj_eq(data_t o1, data_t o2) {
  int res = 0;
  res += o1.countVertexes != o2.countVertexes;
  res += o1.countFacets != o2.countFacets;
  if (!res) {
    for (int i = 0; i < o1.countVertexes * 3; i++) {
      if (fabs(o1.vertexArray[i] - o2.vertexArray[i]) > 1e06) {
        res++;
        break;
      }
    }
    for (int i = 0; i < o1.countFacets * 3; i++) {
      if (abs(o1.facetsArray[i] - o2.facetsArray[i]) > 0) {
        res++;
        break;
      }
    }
  }
  return res == 0;
}

/* функция для отладки
void print_obj(data_t o1) {
  printf("vertexes %d\n", o1.countVertexes);
  printf("facets %d\n", o1.countFacets);
  for (int i = 0; i < o1.countVertexes * 3; i += 3) {
    printf("%f %f %f", o1.vertexArray[i], o1.vertexArray[i + 1],
           o1.vertexArray[i + 2]);
    printf("\n");
  }

  for (int i = 0; i < o1.countFacets * 3; i += 3) {
    printf("%d %d %d", o1.facetsArray[i], o1.facetsArray[i + 1],
           o1.facetsArray[i + 2]);
    printf("\n");
  }
  printf("\n");
}
*/

START_TEST(move_1) {
  double vertexArray[24] = {1.0, 1.0, 1.0, 0.5, 0.5, 2.0, 0.0, 2.0,
                            0.0, 0.5, 2.5, 2.0, 2.0, 0.0, 0.0, 2.5,
                            0.5, 2.0, 2.0, 2.0, 0.0, 2.5, 2.5, 2.0};

  double vertexArray2[24] = {3.0, 1.0, 1.0, 2.5, 0.5, 2.0, 2.0, 2.0,
                             0.0, 2.5, 2.5, 2.0, 4.0, 0.0, 0.0, 4.5,
                             0.5, 2.0, 4.0, 2.0, 0.0, 4.5, 2.5, 2.0};
  data_t object;
  object.countVertexes = 8;
  object.countFacets = 0;
  object.vertexArray = vertexArray;
  data_t object2;
  object2.countVertexes = 8;
  object2.countFacets = 0;
  object2.vertexArray = vertexArray2;
  set_move(&object, 2, 0, 0);
  ck_assert_int_eq(is_obj_eq(object, object2), 1);
}
END_TEST

START_TEST(move_2) {
  double vertexArray[24] = {1.0, 1.0, 1.0, 0.5, 0.5, 2.0, 0.0, 2.0,
                            0.0, 0.5, 2.5, 2.0, 2.0, 0.0, 0.0, 2.5,
                            0.5, 2.0, 2.0, 2.0, 0.0, 2.5, 2.5, 2.0};

  double vertexArray2[24] = {3.0, 3.0, 3.0, 2.5, 2.5, 4.0, 2.0, 4.0,
                             2.0, 2.5, 4.5, 4.0, 4.0, 2.0, 2.0, 4.5,
                             2.5, 4.0, 4.0, 4.0, 2.0, 4.5, 4.5, 4.0};
  data_t object;
  object.countVertexes = 8;
  object.countFacets = 0;
  object.vertexArray = vertexArray;
  data_t object2;
  object2.countVertexes = 8;
  object2.countFacets = 0;
  object2.vertexArray = vertexArray2;
  set_move(&object, 2, 2, 2);
  ck_assert_int_eq(is_obj_eq(object, object2), 1);
}
END_TEST

START_TEST(scale) {
  double vertexArray[24] = {1.0, 1.0, 1.0, 0.5, 0.5, 2.0, 0.0, 2.0,
                            0.0, 0.5, 2.5, 2.0, 2.0, 0.0, 0.0, 2.5,
                            0.5, 2.0, 2.0, 2.0, 0.0, 2.5, 2.5, 2.0};

  double vertexArray2[24] = {2.0, 2.0, 2.0, 1.0, 1.0, 4.0, 0.0, 4.0,
                             0.0, 1.0, 5.0, 4.0, 4.0, 0.0, 0.0, 5.0,
                             1.0, 4.0, 4.0, 4.0, 0.0, 5.0, 5.0, 4.0};
  data_t object;
  object.countVertexes = 8;
  object.countFacets = 0;
  object.vertexArray = vertexArray;
  data_t object2;
  object2.countVertexes = 8;
  object2.countFacets = 0;
  object2.vertexArray = vertexArray2;
  set_scale(&object, 2);
  ck_assert_int_eq(is_obj_eq(object, object2), 1);
}
END_TEST

START_TEST(rotate) {
  double vertexArray[24] = {1.0, 1.0, 1.0, 0.5, 0.5, 2.0, 0.0, 2.0,
                            0.0, 0.5, 2.5, 2.0, 2.0, 0.0, 0.0, 2.5,
                            0.5, 2.0, 2.0, 2.0, 0.0, 2.5, 2.5, 2.0};

  double vertexArray2[24] = {
      1.207107,  1.207107, 0.292893,  1.883883, 0.383883, 0.896447,
      -0.292893, 1.707107, 1.000000,  1.590990, 2.090990, 1.896447,
      1.000000,  1.000000, -1.414214, 2.883883, 1.383883, -0.517767,
      0.707107,  2.707107, -0.414214, 2.590990, 3.090990, 0.482233};
  data_t object;
  object.countVertexes = 8;
  object.countFacets = 0;
  object.vertexArray = vertexArray;
  data_t object2;
  object2.countVertexes = 8;
  object2.countFacets = 0;
  object2.vertexArray = vertexArray2;
  set_rotate(&object, 45, 45, 45);
  ck_assert_int_eq(is_obj_eq(object, object2), 1);
}
END_TEST

START_TEST(parse_1) {
  data_t fileData;
  const char *filename = "objFiles/cube.obj";
  parseObj(filename, &fileData);
  ck_assert_int_eq(fileData.countVertexes, 8);
  ck_assert_int_eq(fileData.countFacets, 36);
  removeData(&fileData);
}
END_TEST

START_TEST(parse_2) {
  data_t fileData;
  const char *filename = "objFiles/Deer.obj";
  parseObj(filename, &fileData);
  ck_assert_int_eq(fileData.countVertexes, 772);
  ck_assert_int_eq(fileData.countFacets, 4524);
  removeData(&fileData);
}
END_TEST

int main(void) {
  Suite *s1 = suite_create("Core");
  TCase *tc = tcase_create("Core");
  SRunner *sr = srunner_create(s1);
  int nf;
  suite_add_tcase(s1, tc);

  tcase_add_test(tc, move_1);
  tcase_add_test(tc, move_2);
  tcase_add_test(tc, scale);
  tcase_add_test(tc, rotate);
  tcase_add_test(tc, parse_1);
  tcase_add_test(tc, parse_2);

  // srunner_set_fork_status(sr, CK_NOFORK);
  srunner_run_all(sr, CK_ENV);
  nf = srunner_ntests_failed(sr);
  srunner_free(sr);

  return nf == 0 ? 0 : 1;
}
