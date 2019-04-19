#include <opencv2/opencv.hpp>

#include <iostream>
#include <string_view>

constexpr std::string_view sample1_input{ R"(C:\Users\Dawid Wdowiak\Desktop\Development\MoviesColorVisualization\build\test_samples\sample1.jpg)" };
constexpr std::string_view sample_input_video{ R"(C:\Users\Dawid Wdowiak\Desktop\Development\MoviesColorVisualization\build\test_samples\sample.mkv)" };

constexpr std::string_view sample_output{ R"(C:\Users\Dawid Wdowiak\Desktop\Development\MoviesColorVisualization\build\test_samples\output.jpg)" };

enum class e_frame_to_average_color_error
{
	ok,
	video_capture_is_not_opened,
	video_capture_has_no_frames
};

// todo, todo, return pair? <frames + error(result)>
std::vector<cv::Scalar> get_frames_average_color(cv::VideoCapture& video_capture, e_frame_to_average_color_error& error)
{
	if(!video_capture.isOpened())
	{
		error = e_frame_to_average_color_error::video_capture_is_not_opened;
		return {};
	}

	const auto frame_count = static_cast<size_t>(video_capture.get(cv::CAP_PROP_FRAME_COUNT));
	if(frame_count == 0)
	{
		error = e_frame_to_average_color_error::video_capture_has_no_frames;
		return {};
	}

	const auto video_capture_previous_position = video_capture.get(cv::CAP_PROP_POS_FRAMES);
	video_capture.set(cv::CAP_PROP_POS_FRAMES, 0);

	std::vector<cv::Scalar> frames_average_color;
	frames_average_color.reserve(frame_count);

	cv::Mat frame{};
	while(video_capture.read(frame))
	{
		frames_average_color.push_back(mean(frame));
	}

	video_capture.set(cv::CAP_PROP_POS_FRAMES, video_capture_previous_position);
	
	error = e_frame_to_average_color_error::ok;
	return frames_average_color;
}

cv::Mat create_image_from_scalars(const std::vector<cv::Scalar> &scalars, const int height)
{
	if(height <= 0)
	{
		// could have used unsigned as parameter type, but unfortunately cv::Mat takes a plain int anyway...
		// so then we could get into another problem - parameter value > int::max
		throw std::invalid_argument{"Height cannot be 0 or less"};
	}

	cv::Mat result_image(height, static_cast<int>(scalars.size()), CV_8UC3);

	uchar* data = result_image.data;
	for (int i = 0; i < height; ++i)
	{
		for (const auto& scalar : scalars)
		{
			for (int k = 0; k < result_image.channels(); ++k)
			{
				*data++ = static_cast<uchar>(scalar[k]);
			}
		}
	}

	return result_image;
}

int main()
{
	cv::VideoCapture video_capture(sample_input_video.data());
	if (!video_capture.isOpened())
	{
		std::cout << "Cannot open the video, either file is corrupted or you are missing some codecs\n";
		std::cin.get();
		return -1;
	}

	e_frame_to_average_color_error get_frames_average_color_result{ e_frame_to_average_color_error::ok };
	const auto frames_average_color = get_frames_average_color(video_capture, get_frames_average_color_result);

	video_capture.release();

	if(get_frames_average_color_result == e_frame_to_average_color_error::ok)
	{
		const auto image = create_image_from_scalars(frames_average_color, 5000);
		imwrite(sample_output.data(), image);
	}
}
