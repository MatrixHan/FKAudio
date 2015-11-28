//-------------------------------------------------------------------
// 
//
// Comment:	Ogg��һ����Ƶ���ļ���������С�İ�packet���д��䣬֮���Զ�
//			������װΪһ����Oggҳ���ڵ�һ��Oggҳ�б���������������Ϣ��
//			һ��Vorbis���Ľ�����֧�ַֽ�Ϊ����ֲ�������������ͬʱ���롣
//-------------------------------------------------------------------

#pragma once


#include "Unorderly.h"
#include "IAudioData.h"
#include "../external/include/vorbis/codec.h"
#include <iostream>

namespace Ogre
{
	namespace FKAudio
	{
		class OggAudioData : public IAudioData
		{
		public:
			explicit OggAudioData(const SP_ISTREAM& file);
			~OggAudioData();

			// ��ȡOgg�ļ���С
			uint32	GetSize();
			// ��ȡOgg���ļ�
			uint32	Read(void* pAudioData, uint32 uSize);
			// ��λOgg���ļ�
			void	Reset();
		private:
			// ��ʼ��Vorbis
			void Init();
			// �ͷ�Vorbis
			void Destory();
		private:
			SP_ISTREAM				m_pOggFile;		// Ogg�ļ���ָ��
			std::istream::off_type	m_cDataOffset;	// ����ƫ���ֽ���

			ogg_sync_state   m_oy;	// Ogg��Ч��ͬ����״̬		
			ogg_stream_state m_os;	// Ogg��Ч�����ӻ�״̬		
			ogg_page         m_og;	// Oggҳ��Ԫ				
			ogg_packet       m_op;	// Ogg����Ԫ				

			vorbis_info      m_vi;	// vorbis��������Ϣ�ṹ		
			vorbis_comment   m_vc;	// vorbis�û�ע����Ϣ�ṹ	
			vorbis_dsp_state m_vd;	// �������������״̬		
			vorbis_block     m_vb;	// �ֲ������������ռ�		
		};
	}
}