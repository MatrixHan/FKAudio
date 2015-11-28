//-------------------------------------------------------------------
// 
//
//
//-------------------------------------------------------------------

#pragma once


#include "Unorderly.h"
#include "IAudioData.h"
#include "Vector3.h"
#include  <algorithm>

namespace Ogre
{
	namespace FKAudio
	{
		class IAudioBuffer
		{
		public:
			IAudioBuffer( const SP_AUDIODATA& AudioData ) 
				: m_AudioData(AudioData)
				, m_nFrequency(AudioData->GetFrequency())
				, m_nDataFormat(AudioData->GetFormat()) 
			{};
			  virtual ~IAudioBuffer(){};

		public:
			// ���ſ��ƺ��������ű���Ƶ����������Ϣ
			virtual void Play(bool bLoop = false) = 0;
			// ���ſ��ƺ�������λ����Ƶ����������Ϣ
			virtual void Reset() = 0;
			// ���ſ��ƺ�����ֹͣ���ű���Ƶ����������Ϣ
			virtual void Stop() = 0;

			// ״̬��ȡ�������Ƿ��ڲ���
			virtual bool IsPlaying() const = 0;
			// ״̬��ȡ�������Ƿ��������ļ�
			virtual bool IsSound() const = 0;
			// ״̬��ȡ��������ȡ����λ��
			virtual Vector3f GetPlayerPos() const = 0;
			// ״̬��ȡ��������ȡ�����ٶ�
			virtual Vector3f GetVelocity() const = 0;
			// ״̬��ȡ��������ȡ��������
			virtual Vector3f GetDirection() const = 0;

			// �������ú�������������(0.0f - 1.0f)
			virtual void SetVolume(float fVolume) = 0;
			// �������ú��������ò���λ��
			virtual void SetPlayerPos(const Vector3f& Pos) = 0;
			// �������ú��������������ٶ�
			virtual void SetVelocity(const Vector3f& Pos) = 0;
			// �������ú�����������������
			virtual void SetDirection(const Vector3f& Pos) = 0;
		protected:
			SP_AUDIODATA			m_AudioData;	// ��Ƶ�����ļ�ָ��
			eAudioDataFormat		m_nDataFormat;	// ��Ƶ�����ļ�����	
			uint32					m_nFrequency;	// ��Ƶ����Ƶ��
		};
		// ��Ч���ݻ�����������ָ��
		typedef boost::shared_ptr<IAudioBuffer> SP_AUDIOBUFFERS;
	}
}


