//-------------------------------------------------------------------
// 
//
//
//-------------------------------------------------------------------

#pragma once


#include "Unorderly.h"
#include "IAudioBuffer.h"

namespace Ogre
{
	namespace FKAudio
	{
		class NullAudioBuffer : public IAudioBuffer
		{
		public:
			virtual ~NullAudioBuffer();
		public:
			// ���ſ��ƺ��������ű���Ƶ����������Ϣ
			virtual void Play(bool bLoop = false);
			// ���ſ��ƺ�������λ����Ƶ��������Ϣ
			virtual void Reset();
			// ���ſ��ƺ�����ֹͣ���ű���Ƶ����������Ϣ
			virtual void Stop();

			// ״̬��ȡ�������Ƿ��ڲ���
			virtual bool IsPlaying() const;
			// ״̬��ȡ�������Ƿ��������ļ�
			virtual bool IsSound() const;
			// ״̬��ȡ��������ȡ����λ��
			virtual Vector3f GetPlayerPos() const;
			// ״̬��ȡ��������ȡ�����ٶ�
			virtual Vector3f GetVelocity() const = 0;
			// ״̬��ȡ��������ȡ��������
			virtual Vector3f GetDirection() const = 0;

			// �������ú�������������
			virtual void SetVolume(float fVolume);
			// �������ú��������ò���λ��
			virtual void SetPlayerPos(const Vector3f& Pos);
			// �������ú��������������ٶ�
			virtual void SetVelocity(const Vector3f& Pos);
			// �������ú�����������������
			virtual void SetDirection(const Vector3f& Pos);
		};
	}
}