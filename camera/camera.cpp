#include "camera.h"
#include "lodepng.h"
#include "common.h"
#include "simpleTracer.h"
#include "randomTracer.h"
#include <iomanip>
#include "timeRecorder.h"
#include "config.h"

const int Camera::default_screen_width = 256;
const int Camera::default_screen_height = 256;

Camera::Camera(Tracer* tracer)
{
    m_factor = configCameraFactor;

    m_Width = default_screen_width * m_factor;
    m_Height = default_screen_height * m_factor;

    m_BounceTime = configBounceTime;

    m_pTracer = tracer;
}

void Camera::setPool(const ObjectPool *pool)
{
    m_pObjectPool = pool;
}

void Camera::build(const Vector3 &position, const Vector3 &direction, const Vector3 &worldUp)
{
    // todo:
}

void Camera::build(const Vector3 &position, const Vector3 &theta)
{
    m_transform.set(theta, position).scale(-1, -1, 1);
}

Transform Camera::getTransform() const
{
    return m_transform;
}

void Camera::setBounceTime(int bounceTime)
{
    m_BounceTime = bounceTime;
}

void Camera::render()
{
    m_Image.resize(m_Width * m_Height * 4);

    for (unsigned y = 0; y < m_Height; y++)
    {
        // TimeRecorder rec;
        // rec.start();

        for (unsigned x = 0; x < m_Width; x++)
        {
            if (configLogProgress)
                logProgress(x, y);

            HitRecord record = InitHitRecord();
            Ray ray = generateRay(static_cast<float>(x), static_cast<float>(y));

            Color color = Color::COLOR_BLACK;
            for (int i = 2; i < m_BounceTime; i++)
            {
                // if (y==0 && x==21 && i==3)
                color += m_pTracer->trace(m_pObjectPool, ray, i, record);
            }

            setImage(x, y, color);

        }
        // rec.end();
    }
}

bool Camera::saveToImage(const std::string &name) const
{
    unsigned error = lodepng::encode(name + ".png", m_Image, m_Width, m_Height);
    std::cout << "encoder error " << error << ": " << lodepng_error_text(error) << std::endl;

    return error == 0;
}

void Camera::setImage(unsigned int x, unsigned int y, const Color &color)
{
    unsigned char r = 0;
    unsigned char g = 0;
    unsigned char b = 0;

    color.getConvertedValue(r, g, b);

    m_Image[4 * m_Width * y + 4 * x + 0] = r;
    m_Image[4 * m_Width * y + 4 * x + 1] = g;
    m_Image[4 * m_Width * y + 4 * x + 2] = b;
    m_Image[4 * m_Width * y + 4 * x + 3] = 255;
}

HitRecord Camera::InitHitRecord() const
{
    HitRecord record;
    
    record.reflectPdf = 1;
    record.dot = 1;
    record.f = Color::COLOR_WHITE;

    return record;
}

void Camera::logProgress(unsigned int x, unsigned int y) const
{
    unsigned int total = m_Height * m_Width;
    if (x == 0)
    {
        float percent = (float(y * m_Width + x) / total) * 100;
        std::cout << "x:y --- "
                  << "(" << x << "," << y << ")  ~~" 
                  << std::fixed << std::setprecision(10) << percent << "%~~"
                  << std::endl;
    }
}
