/**
 * Test file for encode and decode functions
 * @author: ElinorB
 */
#include "cipher.h"
#include <string.h>


int test_encode_1();
int test_encode_2();
int test_encode_3();
int test_encode_4();

int test_decode_1();
int test_decode_2();
int test_decode_3();
int test_decode_4();

/**
 * Tests encode with lower case letters without cyclic operation
 * @return 0 if test passed 1 otherwise
 */


int test_encode_1(){
  const int shift_num = 2;
  char a[] = "aaa";
  encode (a, shift_num);
  if(strcmp(a,"ccc")==0){
    printf("test 1 encode worked\n");
    return EXIT_SUCCESS;
  }
  printf("test 1 encode didn't work\n");
  return EXIT_FAILURE;
}

/**
 * Tests encode with lower and upper case letters with cyclic operation
 * @return 0 if test passed 1 otherwise
 */
int test_encode_2(){
  const int shift_num = 2;
  char a[] = "AYz";
  encode (a, shift_num);
  if(strcmp(a,"CAb")==0){
      printf("test 2 encode worked\n");
      return EXIT_SUCCESS;
  }
  printf("test 2 encode didn't work\n");
  return EXIT_FAILURE;
}

/**
 * Tests encode with lower and upper case letters with cyclic operation
 * and non alphabetical characters, with a negative shift value
 * @return 0 if test passed 1 otherwise
 */
int test_encode_3(){
  const int shift_num = -5;
  char a[] = "AYz! L";
  encode (a, shift_num);
  if(strcmp(a,"VTu! G")==0){
      printf("test 3 encode worked\n");
      return EXIT_SUCCESS;
  }
  printf("test 3 encode didn't work\n");
  return EXIT_FAILURE;
}

/**
 * Tests encode with lower and upper case letters with cyclic operation
 * and non alphabetical characters, with shift value larger than 26
 * @return 0 if test passed 1 otherwise
 */
int test_encode_4(){
  const int shift_num = 28;
  char a[] = "AYz! L";
  encode (a, shift_num);
  if(strcmp(a,"CAb! N")==0){
      printf("test 4 encode worked\n");
      return EXIT_SUCCESS;
    }
  printf("test 4 encode didn't work\n");
  return EXIT_FAILURE;
}

/**
 * Tests decode with lower case letters without cyclic operation
 * @return 0 if test passed 1 otherwise
 */
int test_decode_1(){
  const int shift_num = 2;
  char a[] = "glf";
  decode (a, shift_num);
  if(strcmp(a,"ejd")==0){
      printf("test 1 decode worked\n");
      return EXIT_SUCCESS;
    }
  printf("test 1 decode didn't work\n");
  return EXIT_FAILURE;
}

/**
 * Tests decode with lower and upper case letters with cyclic operation
 * @return 0 if test passed 1 otherwise
 */
int test_decode_2(){
  const int shift_num = 3;
  char a[] = "CAb";
  decode (a, shift_num);
  if(strcmp(a,"ZXy")==0){
      printf("test 2 decode worked\n");
      return EXIT_SUCCESS;
    }
  printf("test 2 decode didn't work\n");
  return EXIT_FAILURE;
}

/**
 * Tests decode with lower and upper case letters and non alphabet characters
 * with cyclic operation,
 * when shift value is negative
 * @return 0 if test passed 1 otherwise
 */
int test_decode_3(){
  const int shift_num = -5;
  char a[] = "VTu! G";
  decode (a, shift_num);
  if(strcmp(a,"AYz! L")==0){
      printf("test 3 decode worked\n");
      return EXIT_SUCCESS;
    }
  printf("test 3 decode didn't work\n");
  return EXIT_FAILURE;
}

/**
 * Tests decode with lower and upper case letters and non alphabet characters
 * with cyclic operation,
 * when shift value is larger than 26
 * @return 0 if test passed 1 otherwise
 */
int test_decode_4(){
  const int shift_num = 28;
  char a[]= "abAB !2A";
  decode (a, shift_num);
  if(strcmp(a,"yzYZ !2Y")==0){
      printf("test 4 decode worked\n");
      return EXIT_SUCCESS;
    }
  printf("test 4 decode didn't work\n");
  return EXIT_FAILURE;


}
