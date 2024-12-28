#include "camera.h"
#include <lodepng/lodepng.h>
#include "common.h"
#include "simpleTracer.h"
#include "randomTracer.h"
#include <iomanip>
#include "timeRecorder.h"
#include "config.h"
#include "mathConstantDef.h"

const int Camera::default_screen_width = 256;
const int Camera::default_screen_height = 256;

Camera::Camera(std::shared_ptr<Tracer> tracer)
{
    m_factor = configCameraFactor;

    m_Width = default_screen_width * m_factor;
    m_Height = default_screen_height * m_factor;

    m_pTracer = tracer;
}

void Camera::setPool(std::shared_ptr<const ObjectPool> pool)
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

// #include <thread>
// #include <vector>

// void Camera::render()
// {
//     m_Image.resize(m_Width * m_Height * 4);

//     // 创建一个线程池，线程数量可以根据硬件核心数调整
//     unsigned numThreads = std::thread::hardware_concurrency();
//     std::vector<std::thread> threads(numThreads);

//     // 每个线程处理一部分行
//     unsigned rowsPerThread = m_Height / numThreads;
//     unsigned remainingRows = m_Height % numThreads;

//     for (unsigned i = 0; i < numThreads; ++i)
//     {
//         unsigned startRow = i * rowsPerThread;
//         unsigned endRow = startRow + rowsPerThread;

//         // 最后一个线程处理剩余的行
//         if (i == numThreads - 1)
//         {
//             endRow += remainingRows;
//         }

//         threads[i] = std::thread([this, startRow, endRow]() {
//             for (unsigned y = startRow; y < endRow; y++)
//             {


//                 for (unsigned x = 0; x < m_Width; x++)
//                 {
//                     if (configLogProgress)
//                         logProgress(x,y);

//                     HitRecord record = InitHitRecord();
//                     Ray ray = generateRay(static_cast<float>(x), static_cast<float>(y));

//                     Color color = Color::COLOR_BLACK;
//                     for (int time = 0; time < configSamplersPerPixel; time++)
//                     {
//                         color += m_pTracer->trace(m_pObjectPool, ray);
//                     }
//                     color /= static_cast<float>(configSamplersPerPixel);

//                     setImage(x, y, color);
//                 }
//             }
//         });
//     }

//     // 等待所有线程完成
//     for (auto& thread : threads)
//     {
//         thread.join();
//     }
// }

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

            // Color color = m_pTracer->traceFirstBounce(m_pObjectPool, ray);
            Color color = Color::COLOR_BLACK;
            for (int time = 0; time < configSamplersPerPixel; time++)
            {
                color += m_pTracer->trace(m_pObjectPool, ray);
            }
            color /= static_cast<float>(configSamplersPerPixel);
            
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
