#include "fft.hh"
#include "my_types.hh"
#include <gtest/gtest.h>

/*****************************************************************/
TEST(FFT, transform) {
  UInt N = 512;
  Matrix<complex> m(N);

  Real k = 2 * M_PI / N;
  for (auto&& entry : index(m)) {
    int i = std::get<0>(entry);
    int j = std::get<1>(entry);
    auto& val = std::get<2>(entry);
    val = cos(k * i);
  }

  Matrix<complex> res = FFT::transform(m);

  for (auto&& entry : index(res)) {
    int i = std::get<0>(entry);
    int j = std::get<1>(entry);
    auto& val = std::get<2>(entry);
    if (std::abs(val) > 1e-10)
      std::cout << i << "," << j << " = " << val << std::endl;

    if (i == 1 && j == 0)
      ASSERT_NEAR(std::abs(val), N * N / 2, 1e-10);
    else if (i == N - 1 && j == 0)
      ASSERT_NEAR(std::abs(val), N * N / 2, 1e-10);
    else
      ASSERT_NEAR(std::abs(val), 0, 1e-10);
  }
}
/*****************************************************************/

TEST(FFT, inverse_transform) {
  UInt N = 512;
  Matrix<complex> m(N);

  Real k = 2 * M_PI / N;
  for (auto&& entry : index(m)) {
    int i = std::get<0>(entry);
    int j = std::get<1>(entry);
    auto& val = std::get<2>(entry);
    val = cos(k * i);
  }

  Matrix<complex> res = FFT::transform(m);
  Matrix<complex> res_inv = FFT::itransform(res);

  for (auto&& entry : index(res_inv)){
    int i = std::get<0>(entry);
    int j = std::get<1>(entry);
    auto& val = std::get<2>(entry);
    ASSERT_NEAR(val.real(), cos(k*i), 1e-10);
    ASSERT_NEAR(val.imag(), 0, 1e-10);
  }
}
/*****************************************************************/

TEST(FFT, computeFrequencies) {
  // Test even case
  UInt N_even = 8;
  Matrix<std::complex<int>> freqs_even = FFT::computeFrequencies(N_even);
  std::vector<int> ref_even = {0, 1, 2, 3, -4, -3, -2, -1}; 

  for (auto&& entry: index(freqs_even)){
    int i = std::get<0>(entry);
    int j = std::get<1>(entry);
    auto& val = std::get<2>(entry);
    ASSERT_EQ(val.real(), ref_even[i]);
    ASSERT_EQ(val.imag(), ref_even[j]);
  }

  // Test odd case
  UInt N_odd = 9;
  Matrix<std::complex<int>> freqs_odd = FFT::computeFrequencies(N_odd);
  std::vector<int> ref_odd = {0, 1, 2, 3, 4, -4, -3, -2, -1}; 

  for (auto&& entry: index(freqs_odd)){
    int i = std::get<0>(entry);
    int j = std::get<1>(entry);
    auto& val = std::get<2>(entry);
    ASSERT_EQ(val.real(), ref_odd[i]);
    ASSERT_EQ(val.imag(), ref_odd[j]);
  }
}

/*****************************************************************/
