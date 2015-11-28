//-------------------------------------------------------------------
// 
//
//
//-------------------------------------------------------------------

#pragma once


#include "Unorderly.h"
#include "IAudioData.h"

namespace Ogre
{
	namespace FKAudio
	{
		class IAudioFactory
		{
		public:
			IAudioFactory();
			virtual ~IAudioFactory();

			// ��ȡ��Ƶ��������
			virtual const std::wstring & GetName() const = 0;
			// ��ȡ�����������������ʵ��
			virtual IAudioEngine& GetAudioEngineInstance() = 0;
			// �½�һ������������
			virtual SP_AUDIOBUFFERS MakeSoundBuffer(const SP_AUDIODATA& pSourceData, uint32 uSourceNum = 1) = 0;
			// �½�һ�����ֻ�����
			virtual SP_AUDIOBUFFERS MakeMusicBuffer(const SP_AUDIODATA& pSourceData, uint32 uBufferSeconds = 2) = 0;
		};
	}
}