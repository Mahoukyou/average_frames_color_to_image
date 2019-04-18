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

	std::vector<Scalar> frames_average_color;
	frames_average_color.reserve(video_capture.get(CAP_PROP_FRAME_COUNT));

	Mat frame{};
	
	int counter = 0;
	for (;;)
	{
		if (!video_capture.read(frame))
		{
			break;
		}

		frames_average_color.push_back(mean(frame));
	}

	video_capture.release();

	constexpr int height{ 720 };
	Mat result_image(height, static_cast<int>(frames_average_color.size()), CV_8UC3 );
	uchar* data = result_image.data;
	for (int j = 0; j < height; ++j)
	{

		for (size_t i = 0; i < frames_average_color.size(); ++i)
		{
			for (int k = 0; k < 3; ++k)
			{
				*data++ = frames_average_color[i][k];
			}
		}
	}

	imwrite(sample_output.data(), result_image);
}
