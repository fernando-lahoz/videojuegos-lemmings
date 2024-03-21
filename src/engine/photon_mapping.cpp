#include <vector>
#include <random>

#include "geometry/ray.hpp"
#include "geometry/point.hpp"
#include "geometry/vector.hpp"
#include "geometry/transform.hpp"

#include "lib/texture.hpp"



struct Spectrum
{
    public:
    
    Float r, g, b;

    Spectrum operator*(Float f) const
    {
        return Spectrum{r * f, g * f, b * f};
    }
};

class Photon
{
    public:
    Ray ray;
    Spectrum power;


};

class Light_source
{
    public:
    Point2f position;
    Spectrum intensity;


    Spectrum power()
    {
        return intensity * TAU;
    }

};



std::vector<Photon> generate_photons(std::vector<Light_source> lights, int nPhotons)
{
    std::vector<Photon> photons(nPhotons);
    std::vector<int> nPhotonsPerLight(lights.size());
    
    int total_photons = 0;
    Float inv_total_photons = 0;

    // Select the proportion of photons to be emitted by each light source
    for (int i = 0; i < lights.size(); i++) 
    {
        nPhotonsPerLight[i] = rand();
        total_photons += nPhotonsPerLight[i];
    }
    inv_total_photons = 1.0 / total_photons;

    // Normalize the number of photons per light source
    for (int i = 0; i < lights.size(); i++)
    {
        nPhotonsPerLight[i] = nPhotonsPerLight[i] * nPhotons * inv_total_photons;
    }

    // Generate the photons
    for (int i_light = 0, i_photon = 0; i_light < lights.size(); i_light++)
    {
        Float inv_n_light_photons = 1.0 / nPhotonsPerLight[i_light];
        Spectrum light_power = lights[i_light].power();
        Float light_pdf = 1.0 / lights.size(); 

        for (int j = 0; j < nPhotonsPerLight[i_light]; j++)
        {
            photons[i_photon] = Photon();
            photons[i_photon].power.r = light_power.r * inv_n_light_photons;
            photons[i_photon].power.g = light_power.g * inv_n_light_photons;
            photons[i_photon].power.b = light_power.b * inv_n_light_photons;

            // Generate random 2D direction
            Float theta = rand() % TAU;
            Float x = cos(theta);
            Float y = sin(theta);

            photons[i_photon].ray = Ray(lights[i_light].position, Vector2f(x, y));

            i_photon++;
        }
    }

    return photons;
}


std::vector<Photon> propagate_photons(Texture map, std::vector<Light_source> lights)
{
    std::vector<Photon> photons = generate_photons(lights, 1000);
}
