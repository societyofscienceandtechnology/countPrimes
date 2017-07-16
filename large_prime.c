/* Finds a somewhat large prime using the Sieve of sieve of Eratosthenes. 
     c source file
     by Hannah Leitheiser
     compile command: gcc large_prime.c */

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

int main() {
   
   printf( "This program finds a large prime by sieving through a block of memory.\n" );
   printf( "The process may take several minutes...\n\n" );
   
   /* Bits in the memory block will represent odd numbers.
      memoryBlock[0] - bit 00 - represents 1
                       bit 01 - represents 3
                       bit 02 - represents 5
                       ...
                       bit 63 - represents 127
      memoryBlock[1] - bit 00 - represents 129

      and so on... 
      
      A low (0) bit will represent possible prime,
      a set bit (1) will represent known composite.
      */

   unsigned int memorySize = -1; /* trick to get it to a large value. */
   uint64_t *memoryBlock;

   /* Give me a gob of memory. */

   while ( !(memoryBlock = calloc(memorySize, sizeof(uint64_t)))) {
      /* if the operating system won't grant, ask for half as much
         the next time */
      memorySize /= 2;
      }
      
   /* These refer to the sieve base.  To prevent having to do modulus division,
      we will work with the memoryBlock array position and the bit index
      inside that position. */

   unsigned int arrayPosition = 0;
   int bitIndex = 1;

   /* we only need to use sieve bases smaller than the square root of the largest number */
   while ( arrayPosition * arrayPosition <= memorySize ) {

      /* These represent the position for bit-setting to 1 for known composites. */
      unsigned int sievePosition = arrayPosition * 3, 
          sieveBitIndex = bitIndex * 3 +  1;

         /* Don't let the bit index go out of bounds. */
         while ( sieveBitIndex >= 64) {
            sievePosition++;
            sieveBitIndex -= 64;
            }

      while ( sievePosition < memorySize ) {
         /* Turn on the bit for the multiple. */
         memoryBlock[sievePosition] = memoryBlock[sievePosition] | ((uint64_t)1 << sieveBitIndex);       

         /* Note, because we are working in odd-number-space, we can add the sieve base twice.
            The sieve base will be odd, and adding once will give us an even, which we don't need. */
         sievePosition += arrayPosition*2;
         sieveBitIndex += bitIndex*2 + 1;
         while ( sieveBitIndex >= 64) {
            sievePosition++;
            sieveBitIndex -= 64;
            }

         }

      /* Find the next prime to use as a sieve base. */
      
      do { 
         bitIndex++;
         if ( bitIndex >= 64) {
            arrayPosition++;
            bitIndex -= 64;
            }
         } while ( memoryBlock[arrayPosition] & ((uint64_t)1 << bitIndex) );
      
      }


   /* Sieve complete: now lets work backward to find the biggest prime in the memory block. */
   
   arrayPosition = memorySize-1;
   bitIndex = 63;
   while ( memoryBlock[arrayPosition] & ((uint64_t)1 << bitIndex) ) {
      bitIndex--;
      if ( bitIndex < 0) {
            arrayPosition--;
            bitIndex = 63;
            }
      }

   
   /* And print the result.  
      Hopefully there's not enough memory to exceed unsigned long long type (we're probably safe). */


   printf("Fairly Big Prime: %llu\n\n", (unsigned long long) arrayPosition * 128 + (bitIndex * 2 + 1) );

   free( memoryBlock );

   return 0;
   }
