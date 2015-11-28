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
		// Wave���ݵ�Ԫ�ṹ
		class WaveAudioData : public IAudioData
		{
		public:
			explicit WaveAudioData(const SP_ISTREAM& file);
			~WaveAudioData();

			// ��ȡ��ǰ�ļ���С
			uint32		GetSize();
			// ��ȡָ����Ƶ�ļ�
			uint32		Read(void* pAudioData, uint32 uSize);
			// ��λ��Ƶ����
			void		Reset();
		private:
			// ��ȡWAVE�ļ�ͷ
			void		LoadFileHdr();
		private:
			SP_ISTREAM				m_pWavFile;		// WAVE�ļ�ָ��
			std::istream::off_type	m_cDataOffset;	// ����ƫ���ֽ���
			uint32					m_uSize;		// WAVE�ļ���С
		};
	}
}