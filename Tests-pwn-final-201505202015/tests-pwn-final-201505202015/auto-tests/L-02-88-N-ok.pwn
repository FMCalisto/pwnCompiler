#g(#i)
#f(#i) = 9 { if (i == 0) f = 0; else f = g(i-1) + i; }
#g(#i) = 9 { if (i == 0) g = 0; else g = f(i-1) + i; }
#pwn() = 0 { f(3)! }

