//
// SubScreen.xaml.h
// Declaration of the SubScreen class
//

#pragma once
using namespace Windows::Storage::Streams;
using namespace Windows::UI::Xaml;
#include "SubScreen.g.h"

namespace sample_uwp_cpp
{
	[Windows::Foundation::Metadata::WebHostHidden]
	public ref class SubScreen sealed
	{
	public:
		SubScreen();
		void update_screen();
		void set_attr(int index, int color_bytes);
	protected:
		void OnPointerPressed(Platform::Object^ sender, Windows::UI::Xaml::Input::PointerRoutedEventArgs^ e);
		void OnPointerRelease(Platform::Object^ sender, Windows::UI::Xaml::Input::PointerRoutedEventArgs^ e);
		void OnPointerMoved(Platform::Object^ sender, Windows::UI::Xaml::Input::PointerRoutedEventArgs^ e);
	private:
		int m_index;
		int m_color_bytes;
		void initScreen();
		byte* get_pixel_data(IBuffer^ pixelBuffer, unsigned int *length);
		Windows::UI::Xaml::Media::Imaging::WriteableBitmap^ m_fb_bitmap = nullptr;
		int m_fb_width;
		int m_fb_height;
		bool m_is_dragging;
	};
}
