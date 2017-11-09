#include "pch.h"
#include "AudioRender.h"

using namespace Windows::Media::Devices;
using namespace sample_uwp_cpp;
extern void set_audio_client(IAudioClient* audio_client);

AudioRender::AudioRender() : m_AudioClient(nullptr)
{
	IActivateAudioInterfaceAsyncOperation *asyncOp;
	HRESULT hr = S_OK;

	// Get a string representing the Default Audio Device Renderer
	Platform::String^ DeviceIdString = MediaDevice::GetDefaultAudioRenderId(Windows::Media::Devices::AudioDeviceRole::Default);

	// This call must be made on the main UI thread.  Async operation will call back to 
	// IActivateAudioInterfaceCompletionHandler::ActivateCompleted, which must be an agile interface implementation
	hr = ActivateAudioInterfaceAsync(DeviceIdString->Data(), __uuidof(IAudioClient), nullptr, this, &asyncOp);
	if (FAILED(hr))
	{
		throw ref new Platform::Exception(-1, "ActivateAudioInterfaceAsync failed!");
	}
}

HRESULT AudioRender::ActivateCompleted(IActivateAudioInterfaceAsyncOperation *operation)
{
	HRESULT hr = S_OK;
	HRESULT hrActivateResult = S_OK;
	IUnknown *punkAudioInterface = nullptr;

	hr = operation->GetActivateResult(&hrActivateResult, &punkAudioInterface);
	if (SUCCEEDED(hr) && SUCCEEDED(hrActivateResult))
	{
		// Get the pointer for the Audio Client
		punkAudioInterface->QueryInterface(IID_PPV_ARGS(&m_AudioClient));
		if (nullptr == m_AudioClient)
		{
			throw ref new Platform::Exception(-1, "Get AudioClient failed!");
		}
		set_audio_client(m_AudioClient);
	}
	return hr;
}