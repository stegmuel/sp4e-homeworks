#include "compute_temperature.hh"
#include "fft.hh"
#include "material_point.hh"
#include "matrix.hh"
#include <cmath>

/* -------------------------------------------------------------------------- */

void ComputeTemperature::compute(System& system) {
    // We assume particles are aranged in a N*N grid with N>=2
    UInt grid_size = sqrt(system.getNbParticles());
    Real delta = grid_size*(system.getParticle(1).getPosition()[0] - system.getParticle(0).getPosition()[0]);
    Matrix<complex> theta_grid(grid_size);
    Matrix<complex> hv_grid(grid_size);

    // Fill temperature and volumetric heat source grid
    for (UInt j=0; j < grid_size; ++j){
        for (UInt i=0; i < grid_size; ++i){
            MaterialPoint& mp = dynamic_cast<MaterialPoint&>(system.getParticle(j*grid_size+i));
            theta_grid(i,j) = mp.getTemperature();
            hv_grid(i,j) = mp.getHeatRate();
        }
    }

    // Compute fourier transforms of temperature and volumetric heat source grids
    Matrix<complex> fft_theta_grid = FFT::transform(theta_grid);
    Matrix<complex> fft_hv_grid = FFT::transform(hv_grid);
    Matrix<std::complex<int>> fft_freqs = FFT::computeFrequencies(grid_size);

    // Compute derivative of fourier theta grid
    Real factor = 1.0 / rho / capacity;
    Matrix<complex> der_fft_theta_grid(grid_size);
    for (auto&& entry : index(der_fft_theta_grid)){
        int i = std::get<0>(entry);
        int j = std::get<1>(entry);
        auto& val = std::get<2>(entry);
        Real q2x_q2y = Real(pow(fft_freqs(i,j).real(), 2) + pow(fft_freqs(i,j).imag(), 2));
        val = factor * (fft_hv_grid(i,j) - kappa * fft_theta_grid(i,j) * (q2x_q2y) * pow(2 * M_PI / delta, 2));
    }

    // We update temperature of the system. We assume delta T is 1.
    Matrix<complex> der_theta_grid = FFT::itransform(der_fft_theta_grid);
    for (UInt j=0; j < grid_size; ++j){
        for (UInt i=0; i < grid_size; ++i){
            MaterialPoint& mp = dynamic_cast<MaterialPoint&>(system.getParticle(j*grid_size+i));
            if (!mp.getBoundary()){
                mp.getTemperature() += delta_t * std::real(der_theta_grid(i,j));
            }
        }
    }
}

/* -------------------------------------------------------------------------- */
