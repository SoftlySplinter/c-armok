#include <stdio.h>
#include <stdlib.h>

#include "unit.h"
#include "syntax.h"
#include "parse.h"
#include "run.h"

int main(int argc, char **argv) {
  return syntax_tests() &  parse_tests() & run_tests();
}
