#pwn() = 0 {
  #x;
  #y;
  repeat (y = 1; y <= 3; y = y + 1)
    repeat (x = 1; x <= 6; x = x + 1)
      if (y % 2 == 1) next; else x!
}

