//-------------------------------------------------------------------
// 
//
//
//-------------------------------------------------------------------

#include "stdafx.h"
#include "../include/IAudioEngine.h"
#include <boost/bind.hpp>

namespace Ogre
{
	namespace FKAudio
	{
		//-------------------------------------------------------------------
		IAudioEngine::IAudioEngine()
			: m_fSoundVolume(1)
			, m_fMusicVolume(1)
		{
		
		}
		//-------------------------------------------------------------------
		IAudioEngine::~IAudioEngine()
		{
		
		}
		//-------------------------------------------------------------------
		// ��ȡ��Ƶ�����е���Ƶ�������ĸ���
		size_t IAudioEngine::GetBuffersNum() const
		{
			return m_AudioBuffers.size();
		}
		//-------------------------------------------------------------------
		// ��ȡָ����ŵ���Ƶ������
		SP_AUDIOBUFFERS IAudioEngine::GetBuffer(size_t uId) 
		{
			AUDIO_BUFFERS_MAP_ITE ite(m_AudioBuffers.find(uId));
			if (ite != m_AudioBuffers.end())
			{
				return ite->second;
			}
			return SP_AUDIOBUFFERS();
		}
		//-------------------------------------------------------------------
		// ��ȡ����������С
		float IAudioEngine::GetMusicVolume() const
		{
			return m_fMusicVolume;
		}
		//-------------------------------------------------------------------
		// ��ȡ����������С
		float IAudioEngine::GetSoundVolume() const
		{
			return m_fSoundVolume;
		}
		//-------------------------------------------------------------------
		// ����Ƶ���������ӹ���һ����Ƶ������
		void IAudioEngine::AddBuffer(size_t uId, const SP_AUDIOBUFFERS& pBuffer)
		{
			m_AudioBuffers.insert(std::make_pair(uId, pBuffer));
		}
		//-------------------------------------------------------------------
		// ����ָ����ŵ���Ƶ������
		void IAudioEngine::Play(size_t uId, bool bLoop)
		{
			this->GetBuffer(uId)->Play(bLoop);
		}
		//-------------------------------------------------------------------
		// ָֹͣ����ŵ���Ƶ����
		void IAudioEngine::Stop(size_t uId)
		{
			this->GetBuffer(uId)->Stop();
		}
		//-------------------------------------------------------------------
		// ���Ż�����map���е�������Ƶ
		void IAudioEngine::PlayAll(bool bLoop)
		{
			std::for_each(m_AudioBuffers.begin(), m_AudioBuffers.end(),
				boost::bind(&IAudioBuffer::Play, boost::bind(select2nd<AUDIO_BUFFERS_MAP::value_type>(), _1), bLoop));
		}
		//-------------------------------------------------------------------
		// ֹͣ������map���е�������Ƶ����
		void IAudioEngine::StopAll()
		{
			std::for_each(m_AudioBuffers.begin(), m_AudioBuffers.end(), 
				boost::bind(&IAudioBuffer::Stop, boost::bind(select2nd<AUDIO_BUFFERS_MAP::value_type>(), _1)));
		}
		//-------------------------------------------------------------------
		// ��������������С
		void IAudioEngine::SetMusicVolume(float fVol)
		{
			FK_ASSERT((fVol >= 0.0f) && (fVol <= 1.0f));
			m_fMusicVolume = fVol;

			for (AUDIO_BUFFERS_MAP_ITE ite = m_AudioBuffers.begin(); ite != m_AudioBuffers.end(); ++ite )
			{
				if (!(ite->second->IsSound()))
				{
					ite->second->SetVolume(fVol);
				}
			}			
		}
		//-------------------------------------------------------------------
		// ��������������С
		void IAudioEngine::SetSoundVolume(float fVol)
		{
			FK_ASSERT((fVol >= 0.0f) && (fVol <= 1.0f));
			m_fSoundVolume = fVol;

			for (AUDIO_BUFFERS_MAP_ITE ite = m_AudioBuffers.begin(); ite != m_AudioBuffers.end(); ++ite )
			{
				if (ite->second->IsSound())
				{
					ite->second->SetVolume(fVol);
				}
			}
		}
		//-------------------------------------------------------------------
	}
}