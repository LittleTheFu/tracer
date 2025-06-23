#include "gtest/gtest.h"     // Google Test framework
#include "ImageTexture.h"    // Your ImageTexture class (which includes PerlinNoise.h)
#include "vector.h"         // Your Vector3 class
#include "MathUtility.h"     // Your MathUtility class

#include <string>
#include <iostream>
#include <filesystem>        // For checking file existence (C++17+)

// Define image dimensions for the test
const unsigned int TEST_IMAGE_WIDTH = 256;
const unsigned int TEST_IMAGE_HEIGHT = 256;
const float TEST_NOISE_SCALE = 4.0f; // Adjust this to change noise frequency/zoom
const float TEST_Z_SLICE = 0.5f;     // Fixed Z-slice for 2D visualization

// You might want to define the output directory for test images
const std::string TEST_OUTPUT_DIR = "test_output/"; 

// Test Fixture for Perlin Noise Image generation
// This allows for common setup/teardown if needed, though simple for this test.
class PerlinNoiseImageTest : public ::testing::Test {
protected:
    // Setup method run before each test in this fixture
    void SetUp() override {
        // Ensure the output directory exists
        if (!std::filesystem::exists(TEST_OUTPUT_DIR)) {
            std::filesystem::create_directories(TEST_OUTPUT_DIR);
            std::cout << "Created test output directory: " << TEST_OUTPUT_DIR << std::endl;
        }
    }
};

// --- Test Case: Generate and Save Perlin Noise Image ---
TEST_F(PerlinNoiseImageTest, GenerateAndSaveBasicPerlinNoiseImage) {
    // 1. Generate the Perlin Noise ImageTexture
    std::cout << "Generating Perlin Noise texture for GTest..." << std::endl;
    ImageTexture perlinTexture = ImageTexture::createPerlinNoiseTexture(
        TEST_IMAGE_WIDTH, 
        TEST_IMAGE_HEIGHT, 
        TEST_NOISE_SCALE, 
        TEST_Z_SLICE
    );

    // Define the output filename within the test output directory
    const std::string outputFilename = TEST_OUTPUT_DIR + "gtest_perlin_output.png";

    // 2. Save the generated ImageTexture to a file
    std::cout << "Attempting to save test image to: " << outputFilename << std::endl;
    bool saveSuccess = perlinTexture.writeToFile(outputFilename);

    // 3. Assert that the save operation was successful
    ASSERT_TRUE(saveSuccess) << "Failed to save Perlin Noise image to " << outputFilename 
                             << ". Check console for LodePNG errors.";

    // 4. (Optional) Assert that the file actually exists on disk
    ASSERT_TRUE(std::filesystem::exists(outputFilename)) 
        << "Output file was not found on disk: " << outputFilename;

    std::cout << "Successfully generated and saved Perlin Noise image for test." << std::endl;

    // You could add more sophisticated checks here, like:
    // - Loading the image back and checking a few pixel values (requires fixed PerlinNoise seed)
    // - Comparing with a "golden" reference image (more complex, requires an image comparison lib)
}

// --- Main function to run all tests ---
int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}