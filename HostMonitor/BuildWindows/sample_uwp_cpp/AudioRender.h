#pragma once
#include <Windows.h>
#include <wrl\implements.h>
#include <AudioClient.h>
#include <mmdeviceapi.h>

using namespace Microsoft::WRL;

namespace sample_uwp_cpp
{
	class AudioRender :
		public RuntimeClass< RuntimeClassFlags< ClassicCom >, FtmBase, IActivateAudioInterfaceCompletionHandler >
	{
	public:
		AudioRender();
		STDMETHOD(ActivateCompleted)(IActivateAudioInterfaceAsyncOperation *operation);
	private:
		IAudioClient        *m_AudioClient;
	};
}