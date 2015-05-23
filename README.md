# pwn Language Compiler

The pwn language is an imperative language and is presented intuitively on the source code.

## Examples

The examples are not exhaustive and do not illustrate all aspects of language.

Others can be obtained in the course of the page.

### Program with several modules

Definition of the factorial function in a file (```factorial.pwn``` file):

```
#factorial(#n) = 1 {
  if (n > 1) factorial = n * factorial(n-1); else factorial = 1;
}
```

Example of the factorial function use in another file (```main.pwn``` file):

```
// external builtin functions
import #argc()
import $argv(#n)
import #atoi($s)

// external user functions
import #factorial(#n)

// the main function
#pwn() {
  #f = 1;
  "Teste para a função factorial"!!
  if (argc() == 2) f = atoi(argv(1));
  f! "! = "! factorial(f)!!
}
```

### Using xml2dot to draw ASTs

The xml2dot JAR can be Googled and used as shown below:

```
pwn myprog.cpt -target xml
java -cp xml2dot.jar xml2dot.xml2dot myprog.xml
```

Note that pwn is assumed to be available in the PATH. Otherwise, the explicit path must be provided, e.g., ./pwn or other specification.
