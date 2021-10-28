#ifndef _VECTOR_H_
#define _VECTOR_H_

#include <iostream>
#include <string>


namespace Prog3 {
	class Vector {
	private:
		static const int QUOTA = 1;
		int SZ;
		int top;
		char* c;
	public:
		//Constructors

		Vector() :SZ(0), top(0), c(new char[0]) {}; // Default constructor
		Vector(int x); // Constructor by number of 'X'
		Vector(std::string str); // Constructor by string input
		Vector(const Vector&); // Copy constructor
		Vector(Vector&&); // Move constructor

		//Destructor
		~Vector() { delete[] c; };

		//Setters
		void set_C(char c); // Symbol input

		//Getters
		const char* get_c(){ return c; }
		int get_SZ() const { return SZ; } // Max size
		int get_size() const { return top; } // Vector max size

		//Other methods and operators
		Vector& operator=(const Vector&); // Overloaded assignment operator
		Vector& operator=(Vector&&); // Move assignment operator
		Vector operator+(const Vector&); // Logical summation (OR)
		Vector operator*(const Vector&); // Logical addition (AND)
		bool operator==(const Vector&); // Comparison
		friend std::ostream& operator <<(std::ostream&, const Vector&); // Output operator

        friend std::istream &operator>>(std::istream &is, Vector &num); // Сам написал!!!!!!!

		Vector operator!(); // Inversion opearator
		bool Certainity(); // Analysis of certainity


	};
}

#endif