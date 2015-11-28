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
		class SoundAudioBuffer : public IAudioBuffer
		{
		public:
			SoundAudioBuffer(const SP_AUDIODATA& AudioData);
			virtual ~SoundAudioBuffer();
			// ��λ�������Լ���������
			virtual void Reset();
			// �ж��Ƿ�����������
			virtual bool IsSound() const;
		protected:
			// ������λ����������,ûд��IAudioBuffer��Ϊ�����ر��ӿ�
			virtual void ResetBuffer() = 0;
		};
	}
}