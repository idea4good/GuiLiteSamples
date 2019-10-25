//
// SubScreen.xaml.cpp
// Implementation of the SubScreen class
//

#include "pch.h"
#include "SubScreen.xaml.h"
#include <robuffer.h>

using namespace sample_uwp_cpp;

using namespace Platform;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::UI::Xaml::Controls::Primitives;
using namespace Windows::UI::Xaml::Data;
using namespace Windows::UI::Xaml::Input;
using namespace Windows::UI::Xaml::Media;
using namespace Windows::UI::Xaml::Navigation;

using namespace Microsoft::WRL;
using namespace concurrency;
using namespace Windows::UI::ViewManagement;
// The User Control item template is documented at http://go.microsoft.com/fwlink/?LinkId=234236

extern void* getUiOfHostMonitor(int display_id, int* width, int* height, bool force_update);
extern void sendTouch2HostMonitor(int x, int y, bool is_down, int display_id);

SubScreen::SubScreen()
{
	InitializeComponent();
	initScreen();
}

void SubScreen::initScreen()
{
	m_screen_sub->PointerPressed += ref new PointerEventHandler(this, &SubScreen::OnPointerPressed);
	m_screen_sub->PointerReleased += ref new PointerEventHandler(this, &SubScreen::OnPointerRelease);
	m_screen_sub->PointerMoved += ref new PointerEventHandler(this, &SubScreen::OnPointerMoved);
}

void SubScreen::set_attr(int index, int color_bytes)
{
	m_index = index;
	m_color_bytes = color_bytes;
}

byte* SubScreen::get_pixel_data(IBuffer^ pixelBuffer, unsigned int *length)
{
	if (length != nullptr)
	{
		*length = pixelBuffer->Length;
	}
	// Query the IBufferByteAccess interface.
	ComPtr<IBufferByteAccess> bufferByteAccess;
	reinterpret_cast<IInspectable*>(pixelBuffer)->QueryInterface(IID_PPV_ARGS(&bufferByteAccess));

	// Retrieve the buffer data.
	byte* pixels = nullptr;
	bufferByteAccess->Buffer(&pixels);
	return pixels;
}

void SubScreen::update_screen()
{
	if (nullptr == m_fb_bitmap)
	{
		unsigned short* raw_data = (unsigned short*)getUiOfHostMonitor(m_index, &m_fb_width, &m_fb_height, false);
		if (raw_data)
		{
			m_fb_bitmap = ref new Windows::UI::Xaml::Media::Imaging::WriteableBitmap(m_fb_width, m_fb_height);
			m_screen_sub->Source = m_fb_bitmap;
		}
		return;
	}

	unsigned int length;
	byte* sourcePixels = get_pixel_data(m_fb_bitmap->PixelBuffer, &length);

	void* raw_data = getUiOfHostMonitor(m_index, NULL, NULL, false);
	if (!raw_data)
	{
		return;
	}

	if (m_color_bytes == 4)
	{
		unsigned int* p_data = (unsigned int*)raw_data;
		for (int i = 0; i < length; i += 4)
		{
			unsigned int rgb = *p_data++;

			sourcePixels[i + 3] = 0xff;//transport
			sourcePixels[i] = (rgb & 0xFF);
			sourcePixels[i + 1] = ((rgb >> 8) & 0xFF);
			sourcePixels[i + 2] = ((rgb >> 16) & 0xFF);
		}
	}
	else//16 bits
	{
		unsigned short* p_data = (unsigned short*)raw_data;
		for (int i = 0; i < length; i += 4)
		{
			unsigned short rgb = *p_data++;

			sourcePixels[i + 3] = 0xff;//transport
			sourcePixels[i] = ((rgb << 3) & 0xF8);
			sourcePixels[i + 1] = ((rgb >> 3) & 0xFC);
			sourcePixels[i + 2] = ((rgb >> 8) & 0xF8);
		}
	}
	m_fb_bitmap->Invalidate();
}

void SubScreen::OnPointerPressed(Platform::Object^ sender, Windows::UI::Xaml::Input::PointerRoutedEventArgs^ e)
{
	auto pointer = e->GetCurrentPoint(this);
	int native_x = (pointer->Position.X * m_fb_width / ActualWidth);
	int native_y = (pointer->Position.Y * m_fb_height / ActualHeight);

	sendTouch2HostMonitor(native_x, native_y, true, m_index);

	m_is_dragging = true;
}

void SubScreen::OnPointerRelease(Platform::Object^ sender, Windows::UI::Xaml::Input::PointerRoutedEventArgs^ e)
{
	auto pointer = e->GetCurrentPoint(this);
	int native_x = (pointer->Position.X * m_fb_width / ActualWidth);
	int native_y = (pointer->Position.Y * m_fb_height / ActualHeight);

	sendTouch2HostMonitor(native_x, native_y, false, m_index);

	m_is_dragging = false;
}

void SubScreen::OnPointerMoved(Platform::Object^ sender, Windows::UI::Xaml::Input::PointerRoutedEventArgs^ e)
{
	if (m_is_dragging)
	{
		OnPointerPressed(sender, e);
	}
}