
#ifndef DF_UNIT
#define DF_UNIT

extern int errors;
extern int asserts;

void assert(int condition, const char *message, ...);
int report(const char *name);

#endif // DF_UNIT
