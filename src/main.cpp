#include <opencv2/opencv.hpp>

#include <iostream>
#include <string_view>

constexpr std::string_view sample1_path{ R"(C:\Users\Dawid Wdowiak\Desktop\Development\MoviesColorVisualization\build\test_samples\sample1.jpg)" };

int main()
{
	const auto sample1_image = cv::imread(sample1_path.data());

	std::cout << sample1_image;
}
