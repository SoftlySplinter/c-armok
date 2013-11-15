#include <wchar.h>

#include "encode.h"

char* encode[256] = {"\0", "☺", "☻"};

char* convert(int character) {
  return encode[character];
}
