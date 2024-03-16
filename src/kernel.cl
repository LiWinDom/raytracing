__kernel void test(__global int* result) {
  int ix = get_global_id(0);
  int iy = get_global_id(1);

  result = 12;
}
