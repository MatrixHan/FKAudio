//-------------------------------------------------------------------
// 
//
//
//-------------------------------------------------------------------

#pragma once


#include "Unorderly.h"
#include <map>
#include "Vector3.h"
#include "../include/IAudioBuffer.h"

namespace Ogre
{
	namespace FKAudio
	{
		class IAudioEngine
		{
			typedef std::map<size_t, SP_AUDIOBUFFERS>		AUDIO_BUFFERS_MAP;
			typedef AUDIO_BUFFERS_MAP::iterator			AUDIO_BUFFERS_MAP_ITE;
		protected:
			AUDIO_BUFFERS_MAP	m_AudioBuffers;			// �������Ƶ��������
			float				m_fSoundVolume;			// ����������С
			float				m_fMusicVolume;			// ����������С
		public:
			IAudioEngine();
			virtual ~IAudioEngine();

			// ��ȡ��Ƶ��������
			virtual const std::wstring& GetName() const = 0;
			// ��ȡ��Ƶ�����е���Ƶ�������ĸ���
			virtual size_t GetBuffersNum() const;
			// ��ȡָ����ŵ���Ƶ������
			virtual SP_AUDIOBUFFERS GetBuffer(size_t uId);
			// ��ȡ����������С
			virtual float GetMusicVolume() const;
			// ��ȡ����������С
			virtual float GetSoundVolume() const;
			// ��ȡ3D������λ��
			virtual Vector3f GetListenerPos() const = 0;
			// ��ȡ3D�������ٶ�
			virtual Vector3f GetListenerVel() const = 0;
			// ��ȡ3D�����߷���
			virtual void GetListenerOri(Vector3f& Face, Vector3f& Up) const = 0;

			// ����Ƶ���������ӹ���һ����Ƶ������
			virtual void AddBuffer(size_t uId, const SP_AUDIOBUFFERS& pBuffer);
			// ����ָ����ŵ���Ƶ������
			virtual void Play(size_t uId, bool bLoop = false);
			// ָֹͣ����ŵ���Ƶ����
			virtual void Stop(size_t uId);
			// ���Ż�����map���е�������Ƶ
			virtual void PlayAll(bool bLoop = false);
			// ֹͣ������map���е�������Ƶ����
			virtual void StopAll();
			// ��������������С��0.0f-1.0f֮��
			virtual void SetMusicVolume(float fVol);
			// ��������������С��0.0f-1.0f֮��
			virtual void SetSoundVolume(float fVol);
			// ����3D������λ��
			virtual void SetListenerPos(const Vector3f& Pos) = 0;
			// ����3D�������ٶ�
			virtual void SetListenerVel(const Vector3f& Vel) = 0;
			// ����3D�����߷���
			virtual void SetListenerOri(const Vector3f& Face, const Vector3f& Up) = 0;
		};
	}
}