local %f;
#pwn() = 0 {
  *p = 0;
  p = [3];
  p[1] = 6;
  f = p[1];
  f!
}

