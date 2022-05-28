#include "pch.h"
#include "MaterialLambertian.h"

MaterialLambertian::MaterialLambertian(Texture* albedo)
    : _albedo(albedo->shared_from_this())
{}

bool MaterialLambertian::scatter(const Ray& ray,
                                 const Intersection& hit,
                                 ScatteredResult* result)
{
    vec3 scattered = hit.normal + random_on_unit_sphere();
    if (is_near_zero(scattered))
        scattered = hit.normal;

    result->radiance = _albedo->sample(hit.uv, hit.position);
    result->scattered_rays.push_back(Ray(hit.position, scattered, ray.time));

    return glm::dot(result->scattered_rays[0].direction, hit.normal) > 0;
}

std::shared_ptr<Material> make_lambertian(Texture* albedo)
{
    return std::make_shared<MaterialLambertian>(albedo);
}