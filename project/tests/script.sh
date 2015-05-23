for f in *.pwn; do ./${f%.pwn} > ${f%.pwn}.out; echo Testing $f; diff --ignore-all-space ${f%.pwn}.out expected/${f%.pwn}.out; done
