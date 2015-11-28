//-------------------------------------------------------------------
// 
//
//
//-------------------------------------------------------------------

#include "stdafx.h"
#include "../include/SoundAudioBuffer.h"

namespace Ogre
{
	namespace FKAudio
	{
		//-------------------------------------------------------------------
		SoundAudioBuffer::SoundAudioBuffer(const SP_AUDIODATA& AudioData)
			: IAudioBuffer(AudioData)
		{
		
		}
		//-------------------------------------------------------------------
		SoundAudioBuffer::~SoundAudioBuffer()
		{
		
		}
		//-------------------------------------------------------------------
		bool SoundAudioBuffer::IsSound() const
		{
			return true;
		}
		//-------------------------------------------------------------------
		void SoundAudioBuffer::Reset()
		{
			// ���ȸ�λ�����������ݶ���������λ
			this->Stop();
			m_AudioData->Reset();
			this->ResetBuffer();
		}
		//-------------------------------------------------------------------
	}
}