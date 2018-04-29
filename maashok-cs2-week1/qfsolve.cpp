#include <cmath>
#include <iostream>
using namespace std;

/**
 * @brief Solves the given quadratic equation.
 *
 * This function, given real coefficients A, B, C to the equation
 * A*x*x + B*x + C = 0, returns the real part of a solution to the
 * equation thus defined. Where two real solutions exist, the one
 * closer to positive infinity is chosen.
 *
 * @param a the quadratic coefficient.
 * @param b the linear coefficient.
 * @param c the constant coefficient.
 *
 * @return the real part of a solution to the defined quadratic equation,
 *         as described.
 */
 
 double qfsolve(double a, double b, double c) {
	 // Quadratic formula: (-b +/- sqrt(b^2 - 4ac)) / (2a)
	 // Determinant is the part inside the square root which determines
	 // how many and what type of roots there will be. Negative
	 // determinant means 2 complex roots (with real parts), zero means
	 // one real root, and positive means two real roots.
	 
	 // If this equation is a linear, not quadratic equation,
	 // the quadratic equation won't work (the 0 in the denominator
	 // for a will return inf). Thus, the formula in this case is
	 // x = -c/b from bx + c = 0
	 if (a == 0) {
		 cout << "This isn't a quadratic equation!" << endl;
		 return (-c/b);
	}
	 	 
	 double determinant = (b*b) - (4*a*c);
	 // If the determinant is zero, then the quadratic equation
	 // only has -b/2a left.
	 // If the determinant is negative, then the real part of the
	 // solution will be -b/2a since sqrt(b^2 - 4ac)/2a will be complex
	 if (determinant <= 0) {
		 double solution = -b / (2*a);
		 return solution;
	}
	 // If the determinant is positive, both solutions must be found
	 // and then compared to see which is closer to positive infinity
	 // The solution is found by simply applying the quadratic formula
	 // and then seeing whether solution1 or solution2 is larger.
	 else {
		 double solution1 = (-b + sqrt(determinant)) / (2*a);
		 double solution2 = (-b - sqrt(determinant)) / (2*a);
		 if (solution1 > solution2) {
			 return solution1;
		}
		 else {
			 return solution2;
		}
	} 
	 
}


int main(int argc, char ** argv) {
	double a = 1;
	double b = 0;
	double c = 5;
	cout << "a: " << a << "   b: " << b << "   c: " << c;
	cout << " Solution: " << qfsolve(a, b, c) << endl;
	
	a = -4;
	b = 2;
	c = 23;
	cout << "a: " << a << "   b: " << b << "   c: " << c;
	cout << " Solution: " << qfsolve(a, b, c) << endl;
	
	a = 0;
	b = 2;
	c = -2;
	cout << "a: " << a << "   b: " << b << "   c: " << c;
	cout << " Solution: " << qfsolve(a, b, c) << endl;
	
	a = 1;
	b = 0;
	c = 5;
	cout << "a: " << a << "   b: " << b << "   c: " << c;
	cout << " Solution: " << qfsolve(a, b, c) << endl;
	
	a = 4.3;
	b = 2.1;
	c = 12.3;
	cout << "a: " << a << "   b: " << b << "   c: " << c;
	cout << " Solution: " << qfsolve(a, b, c) << endl;
	
	a = -2.3;
	b = 32.3;
	c = -1.3;
	cout << "a: " << a << "   b: " << b << "   c: " << c;
	cout << " Solution: " << qfsolve(a, b, c) << endl;
	
	return 0;

}
