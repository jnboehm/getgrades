#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "hsrmformatter.h"

char *klausur = " - Klausur";
char *cons = " ";

char *delete_whitespace(char *text)
{
  while(isspace(*text) && *text != '\0')
    text++;
  return text;
}

void write_data(char* into, char** text)
{
  int k=0;
  char *from = *text ;
  while( !(isspace(*(from)) && isspace(*(from+1))) )
    into[k++] = *(from++);
  *text = from;
}

char *find_end_of_module(char *text)
{
  // lolol this is so shitty
  while((*text != 'E' && *(text+1) != 'N' && *(text+2) != 'D' &&
         *(text+3) != 'O' && *(text+4) != 'F') && *text != '\0')
    text++;
  return text+11;
}

module *create_module(char **table_string)
{
  char *text = *table_string;
  module *m = malloc(sizeof(module));
//  printf("Starting to create module.\n");

  text = delete_whitespace(text);
  write_data(m->course_number,&text);
//  printf("Number written. %s\n", m->course_number);

  text = delete_whitespace(text);
  write_data(m->course_desc,&text);
//  printf("Description written.\n");

  text = delete_whitespace(text);
  if(*text == 'W' || *text == 'S')
  {
    write_data(m->sem,&text);
    text = delete_whitespace(text);
//    printf("Semester written.\n");
  }

  if(*text == '0' && isdigit(*(text+1)))
  {
    write_data(m->termin,&text);
    text = delete_whitespace(text);
//    printf("Termin written.\n");
  }

  if(isdigit(*text)  && *text != '0' && !isdigit(*(text+1)))
  {
    write_data(m->grade,&text);
    text = delete_whitespace(text);
//    printf("Grade written. %s\n",m->grade);
  }

  if(!isdigit(*text))
  {
    write_data(m->status,&text);
//  printf("Status written. %s\n",m->status);
  }

  text = delete_whitespace(text);
  write_data(m->credit_points,&text);

  text = find_end_of_module(text);

  *table_string = text;
//  printf("Finishing up, table_string should now be at %c and the address: %x\n", *text, *table_string);
  return m;
}


modarray sort_data(char *table_string)
{
  module *m,*old;
  int j=0,first=1;
  modarray modarr;

  while(*table_string)
  {
    old = m;
    m = create_module(&table_string);
    j++;
    if(first)
    {
      modarr.modulepointer = m;
      first = 0;
      continue;
    }
    old->next = m;
  }
  modarr.length = j;
  return modarr;
}


void print_module(module m, module *prev)
{
  char *str = calloc(255,sizeof(char));
  if(prev != NULL)
  {
    size_t i,len=strlen(prev->course_desc);
    for (i = 0; i < len; i++)
      if(m.course_desc[i] != prev->course_desc[i])
        break;
    if(i == len)
    {
      int k = 1;
      strcat(str, cons);
      while(m.course_desc[i] != '\0')
      {
        str[k] = m.course_desc[i];
        i++;
        k++;
      }
      str[k] = '\0';
      if(k == 1)
        strcat(str, klausur);
    } else {
      strcpy(str, m.course_desc);
      printf("|      |                           |      |          |      |\n");
    }

  } else {
    strcpy(str, m.course_desc);
  }
  printf("| %4s | %-25.25s | %4s | %-8.8s | %4.4s |\n",
         m.course_number, str, m.grade, m.sem,
         m.credit_points);
  free(str);
}

void print_all(module *m)
{
  module *old;
  printf(".------+---------------------------+------+----------+------.\n");
  printf("| Nr   | Modul                     | Note | Semester | CrPt |\n");
  printf("|------+---------------------------+------+----------+------|\n");
  while(m != NULL)
  {
    print_module(*m,old);
    old = m;
    m = m->next;
  }
  printf("`------+---------------------------+------+----------+------´\n");
}


int main(int argc, char** argv)
{
//   FILE *fp = fopen(*argv,"r");


  char *tab_data = *(argv+1);
  //print_tbl_hd();

  modarray ma = sort_data(tab_data);
  print_all(ma.modulepointer);


  return 0;
}
