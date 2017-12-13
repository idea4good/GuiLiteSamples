//
// MainPage.xaml.h
// Declaration of the MainPage class.
//

#pragma once
using namespace Windows::Storage::Streams;
using namespace Windows::UI::Xaml;

#include "MainPage.g.h"
#include "AudioRender.h"

namespace sample_uwp_cpp
{
	/// <summary>
	/// An empty page that can be used on its own or navigated to within a Frame.
	/// </summary>
	public ref class MainPage sealed
	{
	public:
		MainPage();
	protected:
		void bDoubleTapped_DoubleTapped(Object^ sender, Windows::UI::Xaml::Input::DoubleTappedRoutedEventArgs^ e);
	private:
		void init();
		void update_screen(Platform::Object^ sender, Platform::Object^ e);
	private:
		int					m_color_bytes;
		DispatcherTimer		m_timer;
		ComPtr<AudioRender>	m_audio_render;
	};
}
