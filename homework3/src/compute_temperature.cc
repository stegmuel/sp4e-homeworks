#include "compute_temperature.hh"
#include "fft.hh"
#include "material_point.hh"
#include "matrix.hh"
#include <cmath>

/* -------------------------------------------------------------------------- */

void ComputeTemperature::compute(System& system) {
    // We assume particles are aranged in a N*N grid with N>=2
    UInt size = sqrt(system.getNbParticles());
    // double delta = size*(system.getParticle(1).getPosition()[0] - system.getParticle(0).getPosition()[0]);
    double delta = size;
    Matrix<complex> theta_grid(size);
    Matrix<complex> hv_grid(size);

    // Fill temperature and volumetric heat source grid
    int idx = 0;
    for (auto& part : system){
        int i = idx % size;
        int j = idx / size;
        MaterialPoint& mp = dynamic_cast<MaterialPoint&>(part);
        theta_grid(i,j) = mp.getTemperature();
        // theta_grid(i,j).real(mp.getTemperature());
        // theta_grid(i,j).imag(0.);
        hv_grid(i,j) = mp.getHeatRate();
        // hv_grid(i,j).real(mp.getHeatRate());
        // hv_grid(i,j).imag(0.);
        idx += 1;
    }

    // Compute fourier transforms of temperature and volumetric heat source grids
    Matrix<complex> fft_theta_grid = FFT::transform(theta_grid);
    Matrix<complex> fft_hv_grid = FFT::transform(hv_grid);
    Matrix<std::complex<int>> fft_freqs = FFT::computeFrequencies(size);

    // Compute derivative of fourier theta grid
    Matrix<complex> der_fft_theta_grid(size);

    for (auto  [i, j, value]: index(der_fft_theta_grid)){
        // int i = std::get<0>(entry);
        // int j = std::get<1>(entry);
        // auto& val = std::get<2>(entry);

        if (i != 0 and j != 0){
            value = (1./(rho * capacity)) * (fft_hv_grid(i,j) - kappa * fft_theta_grid(i,j) * (pow(fft_freqs(i,j).real() / delta, 2) + pow(fft_freqs(i,j).imag() / delta, 2)));
        }
        else{
            value = 0.0;
        }
    }

    // We update temperature of the system. We assume delta T is 1.
    Matrix<complex> der_theta_grid = FFT::itransform(der_fft_theta_grid);
    idx = 0.;

    for (auto& part : system){
        int i = idx % size;
        int j = idx / size;
        MaterialPoint& mp = dynamic_cast<MaterialPoint&>(part);
        if (i != 0 and j != 0){
            mp.getTemperature() += delta_t * std::real(der_theta_grid(i,j));
        }
        // mp.getTemperature() += delta_t * std::real(der_theta_grid(i,j));
        idx+=1;
    }
}

/* -------------------------------------------------------------------------- */
