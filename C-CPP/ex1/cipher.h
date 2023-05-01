/**
 * Header file that contains two functions, encode and decode
 * @author: ElinorB
 */
#ifndef CIPHER
#define CIPHER
#define ALPHABET_NUM 26

#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

void decode(char * p, int k);
/**
 * encode function, receives characters and an
 * integer k which represents the shift value
 * and shifts all the alphabetical characters k
 * times to the right alphabetical character
 * in a cyclic manner.
 * @param p characters to be ciphered
 * @param k shift value
 */
void encode(char * p,int k){
  if (k<0){
      decode (p,-k);
      return;
    }
  if(k > ALPHABET_NUM){ // Makes sure that 0<k<27
    k = k % ALPHABET_NUM;
  }
  int i;
  char curr_char;
  for(i = 0; p[i] != '\0'; ++i){
      curr_char = p[i];
      if((curr_char >= 'a') && (curr_char <= 'z')){
          curr_char = curr_char + k;
          if(curr_char > 'z'){
              curr_char = curr_char - 'z' + 'a' - 1;
          }
          p[i] = curr_char;
      }
      else if(curr_char >= 'A' && curr_char <= 'Z'){
          curr_char = curr_char + k;
          if(curr_char > 'Z'){
              curr_char = curr_char - 'Z' + 'A' - 1;
          }
          p[i] = curr_char;
      }
  }
}

/**
 * decode function, receives characters and an
 * integer k which represents the shift value
 * and shifts all the alphabetical characters k
 * times to the left alphabetical character
 * in a cyclic manner.
 * @param p characters to be ciphered
 * @param k shift value
 */
void decode(char * p,int k){
  if (k < 0){
      encode (p, -k);
      return;
    }
  if(k > ALPHABET_NUM){ // Makes sure that 0<k<27
      k = k % ALPHABET_NUM;
    }
  int i;
  char curr_char;
  for(i = 0; p[i] != '\0'; ++i){
      curr_char = p[i];
      if((curr_char >= 'a') && (curr_char <= 'z')){
          curr_char = curr_char-k;
          if(curr_char < 'a'){
              curr_char = curr_char + 'z' - 'a' + 1;
            }
          p[i] = curr_char;
        }
      else if(curr_char >= 'A' && curr_char <= 'Z'){
          curr_char = curr_char-k;
          if(curr_char < 'A'){
              curr_char = curr_char + 'Z' - 'A' + 1;
            }
          p[i] = curr_char;
        }
    }
}

#endif