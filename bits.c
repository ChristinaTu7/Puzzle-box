/* 
 * WARNING: Do not include the <stdio.h> header; it confuses the dlc
 * compiler. You can still use printf for debugging without including
 * <stdio.h>, although you might get a compiler warning. In general,
 * it's not good practice to ignore compiler warnings, but in this
 * case it's OK.  
 */

#if 0
/*
 * Instructions to Students:
 *
 * STEP 1: Read the following instructions carefully.
 */

You will provide your solution to the Data Lab by
editing the collection of functions in this source file.

INTEGER CODING RULES:
 
  Replace the "return" statement in each function with one
  or more lines of C code that implements the function. Your code 
  must conform to the following style:
 
  int Funct(arg1, arg2, ...) {
      /* brief description of how your implementation works */
      int var1 = Expr1;
      ...
      int varM = ExprM;

      varJ = ExprJ;
      ...
      varN = ExprN;
      return ExprR;
  }

  Each "Expr" is an expression using ONLY the following:
  1. Integer constants 0 through 255 (0xFF), inclusive. You are
      not allowed to use big constants such as 0xffffffff.
  2. Function arguments and local variables (no global variables).
  3. Unary integer operations ! ~
  4. Binary integer operations & ^ | + << >>
    
  Some of the problems restrict the set of allowed operators even further.
  Each "Expr" may consist of multiple operators. You are not restricted to
  one operator per line.

  You are expressly forbidden to:
  1. Use any control constructs such as if, do, while, for, switch, etc.
  2. Define or use any macros.
  3. Define any additional functions in this file.
  4. Call any functions.
  5. Use any other operations, such as &&, ||, -, or ?:
  6. Use any form of casting.
  7. Use any data type other than int.  This implies that you
     cannot use arrays, structs, or unions.

 
  You may assume that your machine:
  1. Uses 2s complement, 32-bit representations of integers.
  2. Performs right shifts arithmetically.
  3. Has unpredictable behavior when shifting if the shift amount
     is less than 0 or greater than 31.


EXAMPLES OF ACCEPTABLE CODING STYLE:
  /*
   * pow2plus1 - returns 2^x + 1, where 0 <= x <= 31
   */
  int pow2plus1(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     return (1 << x) + 1;
  }

  /*
   * pow2plus4 - returns 2^x + 4, where 0 <= x <= 31
   */
  int pow2plus4(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     int result = (1 << x);
     result += 4;
     return result;
  }

FLOATING POINT CODING RULES

For the problems that require you to implement floating-point operations,
the coding rules are less strict.  You are allowed to use looping and
conditional control.  You are allowed to use both ints and unsigneds.
You can use arbitrary integer and unsigned constants. You can use any arithmetic,
logical, or comparison operations on int or unsigned data.

You are expressly forbidden to:
  1. Define or use any macros.
  2. Define any additional functions in this file.
  3. Call any functions.
  4. Use any form of casting.
  5. Use any data type other than int or unsigned.  This means that you
     cannot use arrays, structs, or unions.
  6. Use any floating point data types, operations, or constants.


NOTES:
  1. Use the dlc program (described in the writeup) to 
     check the legality of your solutions.
  2. Each function has a maximum number of operations (integer, logical,
     or comparison) that you are allowed to use for your implementation
     of the function.  The max operator count is checked by dlc.
     Note that assignment ('=') is not counted; you may use as many of
     these as you want without penalty.
  3. Use the btest test harness to check your functions for correctness.
  4. The maximum number of ops for each function is given in the
     header comment for each function. If there are any inconsistencies 
     between the maximum ops in the writeup and in this file, consider
     this file the authoritative source.

/*
 * STEP 2: Modify the following functions according the coding rules.
 * 
 *   IMPORTANT. TO AVOID GRADING SURPRISES:
 *   1. Use the dlc compiler to check that your solutions conform
 *      to the coding rules.
 *
 *       YOU WILL RECEIVE NO CREDIT IF YOUR CODE DOES NOT PASS THIS CHECK.
 *
 *   2. Use the btest checker to verify that your solutions produce 
 *      the correct answers.
 */


#endif

/* 
 * bitOr - x|y using only ~ and & 
 *   Example: bitOr(6, 5) = 7
 *   Legal ops: ~ &
 *   Max ops: 8
 *   Rating: 1
 */
int bitOr(int x, int y) {
  return ~(~x & ~y);
}


/* 
 * TMax - return maximum two's complement integer 
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 4
 *   Rating: 1
 */
int tmax(void) {
  return ~(1 << 31);
}


/* 
 * sign - return 1 if positive, 0 if zero, and -1 if negative
 *  Examples: sign(130) = 1
 *            sign(-23) = -1
 *  Legal ops: ! ~ & ^ | + << >>
 *  Max ops: 10
 *  Rating: 2
 */
int sign(int x) {
  int signBit = x >> 31;                         //shift sign bit to rightmost position
  int nonZero = !!x;                             //check if x is non-zero
    return signBit | nonZero ;  
}


/* 
 * copyLSB - set all bits of result to least significant bit of x
 *   Example: copyLSB(5) = 0xFFFFFFFF, copyLSB(6) = 0x00000000
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 5
 *   Rating: 2
 */
int copyLSB(int x) {
  int least_sign_bit = x & 1;                    //get least significant bit
  int result = (least_sign_bit << 31) >> 31;     //set bits of result to least significant bit
  return result;
}


/* 
 * replaceByte(x,n,c) - Replace byte n in x with c
 *   Bytes numbered from 0 (LSB) to 3 (MSB)
 *   Examples: replaceByte(0x12345678,1,0xab) = 0x1234ab78
 *   You can assume 0 <= n <= 3 and 0 <= c <= 255
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 10
 *   Rating: 3
 */
int replaceByte(int x, int n, int c) {
  int shiftAmount = n << 3;                    //convert byte to bit shift amount
  int mask = ~(0xFF << shiftAmount);           //clear byte at position n
  int replace = c << shiftAmount;              //shift replace byte to correct position
  return  (x & mask) | replace;                //clear byte at position n and insert replace byte
}


/* 
 * rotateLeft - Rotate x to the left by n
 *   Can assume that 0 <= n <= 31
 *   Examples: rotateLeft(0x87654321,4) = 0x76543218
 *   Legal ops: ~ & ^ | + << >> !
 *   Max ops: 25
 *   Rating: 3 
 */
int rotateLeft(int x, int n) { 
  int bits = 32;
  int inverse = ~n + 1;
  int leftShift = x << n;
  int shiftRightAmount = bits + inverse;
  int rightShift = (x >> shiftRightAmount) & ((1 << n) + ~ 0);        //right shifts logically by 32 - n bits
  return leftShift | rightShift;           
}


/* 
 * bang - Compute !x without using !
 *   Examples: bang(3) = 0, bang(0) = 1
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 4 
 */
int bang(int x) {
  return ((x >> 31) | ((~x + 1) >> 31)) + 1;              //if x nonzero, sign bit of x is 1, else 0
}                                                         //OR can determine if x is zero or not


/*
 * bitParity - returns 1 if x contains an odd number of 0's
 *   Examples: bitParity(5) = 0, bitParity(7) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 4
 */
int bitParity(int x) {
  x = x ^ (x >> 16);
  x = x ^ (x >> 8);
  x = x ^ (x >> 4);
  x = x ^ (x >> 2);
  x = x ^ (x >> 1);
  return x & 1;
}

/* 
 * floatScale4 - Return bit-level equivalent of expression 4*f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   When argument is NaN, return argument
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
unsigned floatScale4(unsigned uf) {
  int sign = uf >> 31;                           //masking the sign
  int exp = ((uf >> 23) & 0xFF);                 //mask off the exponent

  int mask = (0xFF << 15) | (0x7F << 8) | 0xFF;  //fraction mask

  int frac = (uf & mask);                        //applying mask

  if ( (exp == 0xFF) && (frac == 0) ) {          //checks for infinity
      return uf;
  }
  if ( (exp == 0xFF) && (frac != 0 )) {          //checks for NaN
      return uf;
  } 
  else if (exp == 0) {                           //only fraction has value, denormalized
      frac = frac << 2;                          //multiply by 4
      if (frac > mask) {                         //frac is bigger than mask
        frac = frac >> 1;                        //normalize fraction
        frac = frac & mask;                      //make sure frac is 23 bits
        exp =+ 2;                                //normalize exponent
      }
  } else {
      exp += 2;
      if( (exp >= 0xFF)){                        //overflow of exp, turn into special value infinity
        exp = 0xFF;
        frac = 0;
      }
  }
  return (sign << 31) | (exp << 23) | frac;      //reassembled float
}




/* 
 * floatFloat2Int - Return bit-level equivalent of expression (int) f
 *   for floating point argument f.
 *   Argument is passed as unsigned int, but
 *   it is to be interpreted as the bit-level representation of a
 *   single-precision floating point value.
 *   Anything out of range (including NaN and infinity) should return
 *   0x80000000u.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
int floatFloat2Int(unsigned uf) {
  int sign = uf >> 31;
  int exp = ((uf >> 23) & 0xFF) - 127;            //adjust for bias

  int mask = (0xFF << 15) | (0x7F << 8) | 0xFF;   //construct fraction and implicit leading 1
  int leadingOne = 1 << 23;

  int frac = (uf & mask) | leadingOne;            //apply constructed values

  if (exp >= 31) {                                //checks for overflow
    return 0x80000000u;

  } else if (exp < 0) {                           
    return 0;

  } else {                                        
    int result;
    if (exp > 23) {                               //adjusts fraction to get int value
      result = frac << (exp - 23);

    } else {
      result = frac >> (23 - exp);
    }

    if (sign) {                                   //applies sign to result
      result = -result;                           //if floating point num is negative, negates result
    }

    return result;
  }
}
