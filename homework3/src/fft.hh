#ifndef FFT_HH
#define FFT_HH
/* ------------------------------------------------------ */
#include "matrix.hh"
#include "my_types.hh"
#include <fftw3.h>
/* ------------------------------------------------------ */

struct FFT {

  static Matrix<complex> transform(Matrix<complex>& m);
  static Matrix<complex> itransform(Matrix<complex>& m);

  static Matrix<std::complex<int>> computeFrequencies(int size);
};

/* ------------------------------------------------------ */

inline Matrix<complex> FFT::transform(Matrix<complex>& m_in) {
  // Get Matrix dimension
  UInt n0 = m_in.rows();
  UInt n1 = m_in.cols();

  // convert m_in array to fftw_complex type
  fftw_complex* in = reinterpret_cast<fftw_complex*>(m_in.data());

  // Init m_out
  Matrix<complex> m_out = Matrix<complex>(n0);
  fftw_complex* out = reinterpret_cast<fftw_complex*>(m_out.data());
  
  // Compute plan in forward mode and execute
  fftw_plan p = fftw_plan_dft_2d(n0, n1, in, out, FFTW_FORWARD, FFTW_ESTIMATE);
  fftw_execute(p);
  fftw_destroy_plan(p);
  return m_out;
}

/* ------------------------------------------------------ */

inline Matrix<complex> FFT::itransform(Matrix<complex>& m_in) {
  // Get Matrix dimension
  UInt n0 = m_in.rows();
  UInt n1 = m_in.cols();

  // convert m_in array to fftw_complex type
  fftw_complex* in = reinterpret_cast<fftw_complex*>(m_in.data());

  // Init m_out
  Matrix<complex> m_out = Matrix<complex>(n0);
  fftw_complex* out = reinterpret_cast<fftw_complex*>(m_out.data());
  
  // Compute plan in backward mode and execute
  fftw_plan p = fftw_plan_dft_2d(n0, n1, in, out, FFTW_BACKWARD, FFTW_ESTIMATE);
  fftw_execute(p);
  m_out /= (m_in.rows() * m_in.cols());
  fftw_destroy_plan(p);
  return m_out;
}

/* ------------------------------------------------------ */

inline Matrix<std::complex<int>> FFT::computeFrequencies(int size) {
  Matrix<std::complex<int>> m_out = Matrix<std::complex<int>>(size);
  int N = ((size-1)/2) + 1;

  for (auto&& cell: index(m_out)){
    UInt i = std::get<0>(cell);
    UInt j = std::get<1>(cell);
    std::complex<int>& value = std::get<2>(cell);

    int freq_r = i < N ? i : i - size;
    int freq_i = j < N ? j : j - size;
    value.real(freq_r);
    value.imag(freq_i);
  }
  return m_out;
}

#endif  // FFT_HH
