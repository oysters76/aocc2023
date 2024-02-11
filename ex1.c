#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>

#define ASCII_MIN 48
#define ASCII_MAX 57
#define DO_ASSERT 0 // disable/enable function testing 

int is_number(char c){
  return c >= ASCII_MIN && c <= ASCII_MAX; 
}

int char_to_number(char c){
  int ind = c - ASCII_MIN;
  return ind; 
}

int parse(char * line){
  int n = strlen(line); 
  int result[] = {-1, -1};
  int p = 0; 
  for (int i = 0; i < n; i++){
    char c = line[i]; 
    if (is_number(c) == 0) continue;
    if (p >= 2) p = 1; 
    result[p++] = char_to_number(c); 
  }
  if (result[1] == -1) result[1] = result[0]; 
  return (result[0]*10 + result[1]); 
}

void test_is_number(void){
  assert(is_number('a') == 0);
  assert(is_number('b') == 0);
  assert(is_number('9') == 1); 
}

void test_char_to_number(void){
  assert(char_to_number('3') == 3);
  assert(char_to_number('5') == 5);
  assert(char_to_number('4') == 4); 
}

void test_parse(void){
  assert(parse("1abc2") == 12);
  assert(parse("pqr3stu8vwx") == 38);
  assert(parse("a1b2c3d4e5f") == 15);
  assert(parse("treb7uchet") == 77); 
}

int solve(char * fname){
  int total = 0; 
  FILE * fptr; 
  char * line;
  size_t len = 0;
  ssize_t read;

  fptr = fopen(fname, "r");
  while ((read = getline(&line, &len, fptr)) != -1){
    total += parse(line); 
  }
  fclose(fptr);
  return total; 
}

int main(void){
  if (DO_ASSERT){
    test_is_number();
    test_char_to_number();
    test_parse();
  }
  printf("problem solved: %d\n", solve("ex1.txt"));
  return 0; 
}
