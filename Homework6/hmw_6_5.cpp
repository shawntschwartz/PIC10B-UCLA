//
// hmw_6_5.cpp
//
// by Shawn T. Schwartz
// <shawnschwartz@ucla.edu>
// UID: 504570447
//
// PIC10B Winter 2019 - UCLA
//

#include <iostream>
#include <chrono>
#include <set>

/*
* Print a set of integers separated by commas.
* @param in_set set of integers to print that will be the sieved prime numbers
*/
void print_primes(std::set<int> in_set)
{
	auto i = in_set.begin();
	for (i; i != --in_set.end(); i++)
	{
		std::cout << *i << ", ";
	}

	std::cout << *i << std::endl;
}

/*
* Sieve the numbers divisible by an integer m where 1 < m < sqrt(n).
* @param desired get primes numbers not exceeding this value
* @param print indicate whether set of prime numbers should be output to the console
* @return std::chrono::duration<double> elapsed time of prime number computation for measuring complexity
*/
std::chrono::duration<double> primes_sieve(int desired, bool print)
{
	std::set<int> prime_numbers;
	
	for (int i = 1; i <= desired; i++)
	{
		prime_numbers.insert(i);
	}

	auto tic = std::chrono::high_resolution_clock::now(); // begin timer for complexity measurement
	for (int i = 2; i * i <= desired; i++)
	{
		for (int j = 2; i * j <= desired; j++)
		{
			prime_numbers.erase(i * j);
		}

		if (print)
		{
			std::cout << "Removing the elements divisible by " << i << ": " << std::endl;
			print_primes(prime_numbers);
		}
	}

	if (print)
	{
		std::cout << "Prime numbers not exceeding " << desired << ":" << std::endl;
		print_primes(prime_numbers);
	}

	auto toc = std::chrono::high_resolution_clock::now(); // stop timer
	
	std::chrono::duration<double> elapsed_seconds = toc - tic;
	
	return elapsed_seconds;
}

int main()
{
	char cont;

	// Prime Numbers
	// Loop Through Sieve of Erathostens Algorithm
	do
	{
		int numToCheck;
		std::cout << "Enter any positive integer: ";
		std::cin >> numToCheck;
		std::cout << std::endl;
		
		std::chrono::duration<double> secs = primes_sieve(numToCheck, 1);

		std::cout << "\nContinue (y/n)? ";
		std::cin >> cont;
		std::cin.ignore();
		std::cout << std::endl;
	} while (cont == 'y' || cont == 'Y');

	// Complexity Checks
	std::cout << "Complexity check for n = 10^4, 10^5, 10^6:" << std::endl;

	std::cout << std::endl;

	// Store Complexity Times
	std::chrono::duration<double> ten_power_4 = primes_sieve(10000, 0);
	std::cout << "Time (sec) for computing primes not exceeding 10000: " << ten_power_4.count() << std::endl;

	std::chrono::duration<double> ten_power_5 = primes_sieve(100000, 0);
	std::cout << "Time (sec) for computing primes not exceeding 100000: " << ten_power_5.count() << std::endl;

	std::chrono::duration<double> ten_power_6 = primes_sieve(1000000, 0);
	std::cout << "Time (sec) for computing primes not exceeding 1000000: " << ten_power_6.count() << std::endl;

	std::cout << std::endl;

	return 0;
}