#include "game.h"

#include <iostream>
#include <cassert>
#include <string>
std::string S;
int query_count = 0, limit;
int guess(const std::string &T)
{
	query_count++;
	assert(query_count <= limit);
	assert(T.size() == S.size());
	for (char c : T)
		assert(c == '0' || c == '1');
	int res = 0;
	for (int i = 0; i < S.size(); i++)
		res += S[i] == T[i];
	std::cerr << "Contestant called function guess(" << T << "), and got result: " << res << "." << std::endl;
	return res;
}
int main()
{
	std::cin >> S >> limit;
	for (char c : S)
		assert(c == '0' || c == '1');
	auto ans = game(S.size(), limit);
	std::cerr << "Contestant returned string " << ans << "." << std::endl;
	std::cerr << "Correct answer should be " << S << "." << std::endl;
	assert(ans == S);
	std::cout << "Correct with " << query_count << " queries." << std::endl;
	return 0;
}
