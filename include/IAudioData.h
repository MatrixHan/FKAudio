//-------------------------------------------------------------------
// 
//
//
//-------------------------------------------------------------------

#pragma once


#include "Unorderly.h"

namespace Ogre
{
	namespace FKAudio
	{
		// ö��pcm��Ƶ���ݴ�Ÿ�ʽ
		enum eAudioDataFormat
		{
			EADF_Mono_8 = 0x84,		// 8λ������  ������
			EADF_Mono_16,			// 16λ������ ������
			EADF_Stereo_8,			// 8λ������  ������	
			EADF_Stereo_16,			// 16λ������ ������
			EADF_Unknown			// δ֪����
		};

		// ��Ƶ������ӿ�
		class IAudioData
		{
		protected:
			eAudioDataFormat		m_nDataFormat;	// ��Ƶ�ļ����ݸ�ʽ
			uint32					m_nFrequency;	// ��ƵƵ��
			const char*				m_szFilename;	// ��Ƶ�ļ�����
		public:
			IAudioData()
				: m_szFilename(NULL)
				, m_nDataFormat(EADF_Unknown)
				, m_nFrequency(0)
			{}
			IAudioData(const char* szFilename)
				: m_szFilename(szFilename)
				, m_nDataFormat(EADF_Unknown)
				, m_nFrequency(0)
			{}
			virtual ~IAudioData(){}

			// ��ȡ��ǰ�ļ���ʽ
			eAudioDataFormat		GetFormat() const	{return this->m_nDataFormat;}
			// ��ȡ��ǰ�ļ�Ƶ��
			uint32					GetFrequency() const{return this->m_nFrequency;}
			// ��ȡ��ǰ�ļ�����
			const char*				GetFilename() const {return this->m_szFilename;}

			// ��ȡ��ǰ�ļ���С
			virtual uint32		GetSize() const = 0;
			// ��ȡָ����Ƶ�ļ�
			virtual uint32		Read(void* pAudioData, uint32 uSize) = 0;
			// ����������Ƶ����
			virtual void		Reset() = 0;
		};

		// ��Ч���ݵ�Ԫ������ָ��
		typedef boost::shared_ptr<IAudioData> SP_AUDIODATA;
	}
}
