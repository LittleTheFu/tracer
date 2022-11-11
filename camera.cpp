#include "camera.h"
#include "lodepng.h"

Camera::Camera(const ObjectPool *pool)
{
    m_pObjectPool = pool;

    m_factor = 1;

    m_Width = 512 * m_factor;
    m_Height = 512 * m_factor;

    m_BounceTime = 10;
}

void Camera::build(const Vector3 &position, const Vector3 &direction, const Vector3 &worldUp)
{

}

void Camera::build(const Vector3 &position, const Vector3 &theta)
{
    m_transform.set(theta, position);
}

Transform Camera::getTransform() const
{
    return m_transform;
}

void Camera::render()
{
    const float half_width = m_Width / 2.0f;
    const float half_height = m_Height / 2.0f;
    m_Image.resize(m_Width * m_Height * 4);

    for (unsigned y = 0; y < m_Height; y++)
        for (unsigned x = 0; x < m_Width; x++)
        {
            if (x == 0)
            {
                std::cout << "x:y --- "
                          << "(" << x << "," << y << ")" << std::endl;
            }
            const Vector3 origin(0, 0, 0);
            const Vector3 dir((x - half_width) / half_width, (y - half_height) / half_height, 2);
            Ray ray(origin, dir);

            HitRecord record;
            // record.reflectPdf = Common::INV_TWO_PI;
            record.reflectPdf = 1;
            record.dot = 1;
            record.f = Color::COLOR_WHITE;

            unsigned char r = 0;
            unsigned char g = 0;
            unsigned char b = 0;

            Color color = Color::COLOR_BLACK;
            for (int i = 2; i < m_BounceTime; i++)
            {
                color += m_pObjectPool->trace(ray, i, record);
            }

            color.getConvertedValue(r, g, b);

            m_Image[4 * m_Width * y + 4 * x + 0] = r;
            m_Image[4 * m_Width * y + 4 * x + 1] = g;
            m_Image[4 * m_Width * y + 4 * x + 2] = b;
            m_Image[4 * m_Width * y + 4 * x + 3] = 255;
        }
}

bool Camera::saveToImage() const
{
    unsigned error = lodepng::encode("img.png", m_Image, m_Width, m_Height);
    std::cout << "encoder error " << error << ": " << lodepng_error_text(error) << std::endl;

    return error == 0;
}