//
// MainPage.xaml.cpp
// Implementation of the MainPage class.
//

#include "pch.h"
#include "MainPage.xaml.h"
#include "SubScreen.xaml.h"
#include <assert.h>

using namespace sample_uwp_cpp;

using namespace Platform;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::UI::Xaml::Controls::Primitives;
using namespace Windows::UI::Xaml::Data;
using namespace Windows::UI::Xaml::Input;
using namespace Windows::UI::Xaml::Media;
using namespace Windows::UI::Xaml::Navigation;

using namespace concurrency;
// The Blank Page item template is documented at http://go.microsoft.com/fwlink/?LinkId=402352&clcid=0x409
extern int startHostMonitor(int main_cnt, int main_width, int main_height, int sub_cnt, int sub_width, int sub_height, int color_bytes);

MainPage::MainPage()
{
	m_color_bytes = 2;
	InitializeComponent();
	init();
}

void MainPage::init()
{
	m_audio_render = Make<AudioRender>();

	DoubleTapped += ref new DoubleTappedEventHandler(this, &MainPage::bDoubleTapped_DoubleTapped);
	TimeSpan ts;
	ts.Duration =  30 * 1000 * 10;//30ms
	m_timer.Interval = ts;
	m_timer.Tick += ref new EventHandler<Object^>(this, &MainPage::update_screen);
	m_timer.Start();

	m_screen_main->set_attr(0, m_color_bytes);
	//left
	m_screen_sub_0->set_attr(1, m_color_bytes);
	m_screen_sub_1->set_attr(2, m_color_bytes);
	m_screen_sub_2->set_attr(3, m_color_bytes);
	m_screen_sub_3->set_attr(4, m_color_bytes);
	//right
	m_screen_sub_4->set_attr(5, m_color_bytes);
	m_screen_sub_5->set_attr(6, m_color_bytes);
	m_screen_sub_6->set_attr(7, m_color_bytes);
	m_screen_sub_7->set_attr(8, m_color_bytes);
	create_async([this]() {
		startHostMonitor(1, 1024, 768, 8, 1024, 370, m_color_bytes);
	});
}

void MainPage::update_screen(Platform::Object^ sender, Platform::Object^ e)
{
	if (Windows::UI::Xaml::Visibility::Collapsed == m_screen_main->Visibility)
	{
		//left
		m_screen_sub_0->update_screen();
		m_screen_sub_1->update_screen();
		m_screen_sub_2->update_screen();
		m_screen_sub_3->update_screen();
		//right
		m_screen_sub_4->update_screen();
		m_screen_sub_5->update_screen();
		m_screen_sub_6->update_screen();
		m_screen_sub_7->update_screen();
	}
	else
	{
		m_screen_main->update_screen();
	}
}

void MainPage::bDoubleTapped_DoubleTapped(Object^ sender, DoubleTappedRoutedEventArgs^ e)
{
	if (Windows::UI::Xaml::Visibility::Collapsed == m_screen_main->Visibility)
	{
		m_screen_main->Visibility = Windows::UI::Xaml::Visibility::Visible;
	}
	else
	{
		m_screen_main->Visibility = Windows::UI::Xaml::Visibility::Collapsed;
	}
}
