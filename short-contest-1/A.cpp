#include <bits/stdc++.h>
typedef long long ll;

int countMatchInRegex(std::string &s, std::string &re) {
    std::regex words_regex(re);
    auto words_begin = std::sregex_iterator(
        s.begin(), s.end(), words_regex);
    auto words_end = std::sregex_iterator();

    return std::distance(words_begin, words_end);
}

int main(){
		std::ios_base::sync_with_stdio(false);
  	std::cin.tie(NULL); std::cout.tie(NULL);

  	int test;
  	std::cin >> test;

  	for (int i = 1; i <= test; i++) {

				std::string db = "";
        std::cout << "Case " << i << ":" << std::endl;

				int N, M;	std::cin >> N >> M;
				std::string temp;
				std::getline(std::cin, temp);
				for (int i = 0; i < N; ++i) {
					std::getline(std::cin, temp);
					//temp.pop_back();
					temp = " " + temp + " ";
					//std::cout << temp << "\n";
					db += "-" + temp;
				}
				for (int j = 0; j < M; ++j) {
					std::getline(std::cin, temp);
					temp = " " + temp + " ";
					//std::cout << temp << "\n";
					int ans = countMatchInRegex(db, temp);
					std::cout << ans << "\n";
				}
  	}

}
