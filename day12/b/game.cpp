#include "game.h"
#include <cstdlib>
#include <string>
std::string game(int n, int k)
{
	// guess for k times
	for (int i = 0; i < k; i++)
	{
		// generate random string T of length n
		std::string T;
		for (int j = 0; j < n; j++)
			T += rand() % 2 + '0';
		// guess the random string T
		int res = guess(T);
		if (res == n)
		{
			// S and T have n positions in common
			// so S should be equal to T!
			return T;
		}
	}
	// return a string with n '0's
	return std::string(n, '0');
}
