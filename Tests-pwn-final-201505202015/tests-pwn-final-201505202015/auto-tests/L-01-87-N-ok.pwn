local #f(#i) {
  if (i == 0) f = 0; else { f = f(i-1) + i; return }
  f = 9;
}
#pwn() = 0 { f(3)! }

