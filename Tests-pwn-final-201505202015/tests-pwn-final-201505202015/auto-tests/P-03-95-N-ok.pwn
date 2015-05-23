local *f;
#pwn() = 0 {
  #n = 4;
  #i;
  #j;
  #k;
  #l;
  *f = 0;
  f = [n];
  repeat (i = 0; i <= n-1; i = i + 1) f[i] = 2;
  repeat (j = 0; j <= n-1; j = j + 1) f[j]!
  "\n"!
  repeat (k = 0; k <= n-1; k = k + 1) f[k] = 6/f[k];
  repeat (l = 0; l <= n-1; l = l + 1) f[l]!
}

