// #include "materialTRough.h"
// #include <cassert>
// #include <microfacetTransmissionBxdf.h>

// MaterialTRough::MaterialTRough()
// {
// }

// std::unique_ptr<Bsdf> MaterialTRough::createBsdf(const Interaction &interaction)
// {
//     std::unique_ptr<Bsdf> bsdf = std::make_unique<Bsdf>(interaction.normal_shading);

//     bsdf->addBxdf(std::make_shared<MicrofacetTransmissionBxdf>(0.01f));

//     return bsdf;
// };