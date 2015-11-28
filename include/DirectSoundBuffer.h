//-------------------------------------------------------------------
// 
//
// Comment: �ص㴦���������Ƶ����
//-------------------------------------------------------------------

#pragma once


#include "Unorderly.h"
#include "IAudioBuffer.h"

namespace Ogre
{
	namespace FKAudio
	{
		class DirectSoundBuffer : public MusicAudioBuffer
		{
		public:
			DirectSoundBuffer(const SP_AUDIOBUFFERS& pSourceData, uint32 uBufferSeconds, float fVolume);
			~DirectSoundBuffer();

			// ״̬��ȡ�������Ƿ��ڲ���
			bool IsPlaying() const;
			// ״̬��ȡ��������ȡ����λ��
			Vector3f GetPlayerPos() const;
			// ״̬��ȡ��������ȡ�����ٶ�
			Vector3f GetVelocity() const;
			// ״̬��ȡ��������ȡ��������
			Vector3f GetDirection() const;

			// �������ú�������������( 0.0f - 1.0f )
			void SetVolume(float fVolume);
			// �������ú��������ò���λ��
			void SetPlayerPos(const Vector3f& Pos);
			// �������ú��������������ٶ�
			void SetVelocity(const Vector3f& Pos);
			// �������ú�����������������
			void SetDirection(const Vector3f& Pos);
			// ���ſ��ƺ��������ű���Ƶ����������Ϣ
			void Play(bool bLoop = false);
			// ���ſ��ƺ�������λ����Ƶ����������Ϣ
			void Reset();
			// ���ſ��ƺ�����ֹͣ���ű���Ƶ����������Ϣ
			void Stop();
		private:
			
		};
	}
}
