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
	// Create a matrix to store the result
	UInt rows = m_in.rows();
	UInt cols = m_in.cols();
	Matrix<complex> m_out(rows);

	// Create fftw input and output arrays
	fftw_complex *in, *out;

	// Create the fftw plan to infer the best implementation
	fftw_plan p;

	// Allocate the memory for the input and output array
	in = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * rows * cols);
	out = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * rows * cols);

	// Compute the plan before initializing the input
	p = fftw_plan_dft_2d(rows, cols, in, out, FFTW_FORWARD, FFTW_ESTIMATE);

	// Initialize the input
	for (auto [i, j, value] : index(m_in)) {
		in[i * cols + j][0] = std::real(value);
		in[i * cols + j][1] = std::imag(value);
	};

	// Compute the FFT
	fftw_execute(p);

	// Store the result in the output matrix
	for (auto [i, j, value] : index(m_out)) {
    value = std::complex<Real>{out[i * cols + j][0], out[i * cols + j][1]};
	};

	// Destroy the plan
	fftw_destroy_plan(p);

	// De-allocate the memory
	fftw_free(in); fftw_free(out);

	return m_out;
}

/* ------------------------------------------------------ */

inline Matrix<complex> FFT::itransform(Matrix<complex>& m_in) {
	// Create a matrix to store the result
	UInt rows = m_in.rows();
	UInt cols = m_in.cols();
	Matrix<complex> m_out(rows);

	// Create fftw input and output arrays
	fftw_complex *in, *out;

	// Create the fftw plan to infer the best implementation
	fftw_plan p;

	// Allocate the memory for the input and output array
	in = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * rows * cols);
	out = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * rows * cols);

	// Compute the plan before initializing the input
	p = fftw_plan_dft_2d(rows, cols, in, out, FFTW_BACKWARD, FFTW_ESTIMATE);

	// Initialize the input
	for (auto [i, j, value] : index(m_in)) {
		in[i * cols + j][0] = std::real(value);
		in[i * cols + j][1] = std::imag(value);
	};

	// Compute the FFT
	fftw_execute(p);

	// Store the result in the output matrix
	for (auto [i, j, value] : index(m_out)) {
    value = std::complex<Real>{out[i * cols + j][0], out[i * cols + j][1]};
	};

	// Destroy the plan
	fftw_destroy_plan(p);

	// De-allocate the memory
	fftw_free(in); fftw_free(out);

	return m_out;
}

/* ------------------------------------------------------ */

inline Matrix<std::complex<int>> FFT::computeFrequencies(int size) {}

#endif  // FFT_HH
