#include <opencv2/opencv.hpp>

#include <iostream>
#include <string_view>

constexpr std::string_view sample1_input{ R"(C:\Users\Dawid Wdowiak\Desktop\Development\MoviesColorVisualization\build\test_samples\sample1.jpg)" };
constexpr std::string_view sample_input_video{ R"(C:\Users\Dawid Wdowiak\Desktop\Development\MoviesColorVisualization\build\test_samples\sample.mkv)" };

constexpr std::string_view sample_output{ R"(C:\Users\Dawid Wdowiak\Desktop\Development\MoviesColorVisualization\build\test_samples\output.jpg)" };

int main()
{
	using namespace cv;

	VideoCapture video_capture(sample_input_video.data());
	if (!video_capture.isOpened())
	{
		std::cout << "Cannot open the video, either file is corrupted or you are missing some codecs\n";
		std::cin.get();
		return -1;
	}

	for (;;)
	{
		Mat frame{};
		if (!video_capture.read(frame))
		{
			break;
		}

		imwrite(sample_output.data(), frame);

		// tmp
		break;
	}
}
