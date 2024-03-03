
#include "s21_queue_test.cc"
#include "s21_array_test.cc"
#include "s21_stack_test.cc"
#include "s21_vector_test.cc"

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
