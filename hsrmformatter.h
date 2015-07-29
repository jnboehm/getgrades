
typedef struct mo {
  char course_number[16];
  char course_desc[255];
  char sem[32];
  char termin[32];
  char grade[32];
  char status[32];
  char credit_points[32];
  struct mo *next;
//  char vermerk[32];
//  char versuch[32];
} module;

typedef struct {
  int length;
  module *modulepointer;
} modarray;

char *delete_whitespace(char *text);
char *delete_whitespace(char *text);
char *find_end_of_module(char *text);
module *create_module(char **table_string);
modarray sort_data(char *table_string);
void print_module(module m, module *old);
