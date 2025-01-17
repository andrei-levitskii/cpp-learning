#include <array>
#include <iostream>

template<typename T, auto N> void printArray(std::array<T, N> arr)
{
  std::cout << "The array (";
  for (std::size_t i{ 0 }; i < N; ++i) {
    std::cout << arr[i];
    if (!(i == N - 1)) { std::cout << ", "; }
  }
  std::cout << ") has length " << N << '\n';
}

int main()
{
  constexpr std::array arr1{ 1, 4, 9, 16 };
  printArray(arr1);

  constexpr std::array arr2{ 'h', 'e', 'l', 'l', 'o' };
  printArray(arr2);

  return 0;
}