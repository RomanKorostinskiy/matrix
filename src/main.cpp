#include "main.hpp"

int main() {
  int N;
  std::cin >> N;
  std::vector<int> seq(N * N);
  for (int i = 0; i < N * N; i++)
    std::cin >> seq[i];

  Matrix<int> m{N, N, seq.begin(), seq.end()};
  m.Dump();

  return 0;
}