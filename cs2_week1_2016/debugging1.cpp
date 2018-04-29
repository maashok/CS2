/**
 * @file debugging1.cpp
 * @author The CS2 TA Team <cs2tas@caltech.edu>
 * @date 2014-2015
 * @copyright This code is in the public domain.
 *
 * @brief An example of the utility of print statements in debugging.
 */
 
 /**
  * When you increase both the values of a and b, the value of x
  * increases. And when both decrease, the value of x decreases.
  * 
  * This code multiplies the values of a and b together and assigns
  * it to x.
  * It does this by using bitwise operations. In other words, it does 
  * the multiplication in base-2 using these operations. It does this
  * through the steps taken when doing multiplication written out
  * as follows in this example
  *      0111  (7)
  *     x 101  (5) 
  * ------------
  *      0111
  *     00000
  *  + 011100
  * -------------
  *    100011  (35)  
  * The code multiplies the first operand by each of the bits of
  * the second operand separately moving from least to most significant 
  * bit and sums them together. As each bit in b is considered, 
  * a right shift is done to make the next most significant bit the 
  * least signifcant bit. To consider the least significant bit of b, 
  * if it is 1 (the whole number is odd), then you should multiply a by 
  * this bit, and add it to the total. If that bit is 0, then it
  * will not affect the total since it will be like adding zero. After
  * this step, a left shift of a is also done to signify that a more
  * significant bit of b will be considered, so we will multiply
  * the value of a by 2. This is what is done in the above example
  * where successive terms of the sum place zeroes at the end.
  */

#include <iostream>

using namespace std;

/**
 * @brief Does a thing.
 *
 * Does a thing, I dunno, you tell me.
 */
int main(int argc, char ** argv)
{
    // Much of the following is intentionally undocumented.
    // Part of the assignment is to figure out what is going on.
    // You may need to look up some operators!
    unsigned int a = 174, b = 85, x = 0;

    // This construct is known as a 'while loop'.
    // The interior of the loop is run if, and while,
    // the given condition is true.
    // The program proceeds past the loop if, and when,
    // the given condition is found to be false just before any iteration
    // of the interior of the loop.
    while (b != 0)
    {
        // This construct is known as a conditional statement
        // ('if' statement).
        // The interior of the statement is run exactly once in its entirety
        // if the given condition is found to be true.
        // Note that 'true' is defined as nonzero,
        // and 'false' is defined as zero.
        cout << "Checking if the least significant bit is 1" << endl;
        if ((b & 1) != 0)
        {
			cout << "Add the value of a to x and assign it to x" << endl;
            x += a;
        }
        cout << "Left shift a or multiply it by 2" << endl;
        a <<= 1;
        cout << "Right shift b or divide it by 2" << endl;
        b >>= 1;
    }

    // Question for you now: so what is x anyway?
	cout << "The value of x: " << x << endl;
    return 0;
}
