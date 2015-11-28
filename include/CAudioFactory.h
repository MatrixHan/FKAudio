//-------------------------------------------------------------------
// 
//
//
//-------------------------------------------------------------------

#pragma once


#include "Unorderly.h"
#include "IAudioFactory.h"

namespace Ogre
{
	namespace FKAudio
	{
		template < typename AudioEngineType, typename SoundBufferType, typename MusicBufferType>
		class CAudioFactory : public IAudioFactory
		{
		private:
			const std::wstring m_strName;
		public:
			CAudioFactory(const std::wstring& strName) : m_strName(strName)
			{
			
			}
			//-------------------------------------------------------------------
			~CAudioFactory()
			{
			
			}
			//-------------------------------------------------------------------
			// ��ȡ��Ƶ��������
			const std::wstring GetName() const
			{
				return m_strName;
			}
			//-------------------------------------------------------------------
			// ��ȡ�ù���������ʵ��
			IAudioEngine& GetAudioEngineInstance()
			{
				static AudioEngineType EngineInstance;
				return EngineInstance;
			}
			//-------------------------------------------------------------------
			// �½�һ������������
			SP_AUDIOBUFFERS MakeSoundBuffer(const SP_AUDIODATA& pSourceData, uint32 uSourceNum)
			{
				return SP_AUDIOBUFFERS(new SoundBufferType(pSourceData, uSourceNum, this->GetAudioEngineInstance().GetSoundVolume()));
			}
			//-------------------------------------------------------------------
			// �½�һ�����ֻ�����
			SP_AUDIOBUFFERS MakeMusicBuffer(const SP_AUDIODATA& pSourceData, uint32 uBufferSeconds)
			{
				return SP_AUDIOBUFFERS(new MusicBufferType(pSourceData, uBufferSeconds, this->GetAudioEngineInstance().GetSoundVolume()));
			}
			//-------------------------------------------------------------------
		};
	}
}
	