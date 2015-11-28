//-------------------------------------------------------------------
// 
//
//
//-------------------------------------------------------------------

#include "stdafx.h"
#include "../include/WaveAudioData.h"

namespace Ogre
{
	namespace FKAudio
	{
		//-------------------------------------------------------------------
		// WavChunk��־��ʽ
		enum eWaveFileStyle
		{
			EWFS_RIFF = MakeFourCC<'R', 'I', 'F', 'F'>::value,	
			EWFS_WAVE = MakeFourCC<'W', 'A', 'V', 'E'>::value,
			EWFS_FMT  = MakeFourCC<'f', 'm', 't', ' '>::value,
			EWFS_DATA = MakeFourCC<'d', 'a', 't', 'a'>::value,
		};

		// �������ֽڶ���
		#pragma pack(push, 1)
		// Chunk�����п�ͨ�õ�ͷ��Ϣ
		struct WAVEChunkHdr
		{
			eWaveFileStyle		uId;			// ���е�ͷ���ͱ�־ 
			uint32				uSize;			// ����Ĵ�С
		};

		// WaveChunk�����ݽṹ
		struct WAVEFileHdr
		{
			eWaveFileStyle		uId;			// ���е�ͷ���ͱ�־ 
			uint32				uSize;			// ����Ĵ�С
			eWaveFileStyle		eType;			// Tape�ֶ�
		};

		// FormatChunk����Ҫ���ݽṹ
		struct WaveFmt
		{
			unsigned short		formatTag;		// ���뷽ʽ
			unsigned short		channels;		// ��/˫ �������ж���
			uint32				samplesPerSec;	// ����Ƶ��
			uint32				avgBytesPerSec;	// ��Ƶ���ݴ�������
			unsigned short		blockAlign;		// ÿ�������Ķ�����
		};

		// FormatChunk��16�ֽڴ�С�汾�����ݽṹ
		struct PCMWaveFmt
		{
			WaveFmt				wf;
			unsigned short		bitsPerSample;	// ÿ��������Ҫ��Bit��
		};

		// FormatChunk��18�ֽڴ�С�汾�����ݽṹ
		struct WaveFmtEx
		{
			WaveFmt				wf;	
			unsigned short		bitsPerSample;	// ÿ��������Ҫ��Bit��
			unsigned short		extraSize;		// ���ⲹ������ֽ�
		};
		// �رյ��ֽڶ���
		#pragma pack(pop)
		//-------------------------------------------------------------------
		// ���캯��
		WaveAudioData::WaveAudioData(const SP_ISTREAM& file)
			: m_pWavFile(file)
			, m_cDataOffset(0)
			, m_uSize(0)
		{
			this->LoadFileHdr();
			this->Reset();
		}
		//-------------------------------------------------------------------
		// ��������
		WaveAudioData::~WaveAudioData()
		{
			m_pWavFile->clear();
		}
		//-------------------------------------------------------------------
		// ��ȡ��ǰ�ļ���С
		uint32 WaveAudioData::GetSize()
		{
			return m_uSize;
		}
		//-------------------------------------------------------------------
		// ��ȡָ����Ƶ�ļ�
		uint32 WaveAudioData::Read(void* pAudioData, uint32 uSize)
		{
			FK_ASSERT(NULL != pAudioData);
			m_pWavFile->read(static_cast<char*>(pAudioData), static_cast<std::streamsize>(uSize));
			return m_pWavFile->gcount();
		}
		//-------------------------------------------------------------------
		// ��λ��Ƶ����
		void WaveAudioData::Reset()
		{
			m_pWavFile->clear();
			m_pWavFile->seekg(m_cDataOffset);	
		}
		//-------------------------------------------------------------------
		// ��ȡWAVE�ļ�ͷ
		void WaveAudioData::LoadFileHdr()
		{
			m_pWavFile->seekg(0);

			WAVEFileHdr tagFileHdr;
			m_pWavFile->read(reinterpret_cast<char*>(&tagFileHdr), sizeof(tagFileHdr));

			// ����Ƿ���һ����Ч�� Wave �ļ�
			FK_ASSERT(EWFS_RIFF == tagFileHdr.uId); 
			FK_ASSERT(EWFS_WAVE == tagFileHdr.eType);

			PCMWaveFmt tagPcmWaveFmt;
			WAVEChunkHdr tagChunkHdr;

			for ( ; ; )
			{
				// ��ȡChunkͷ,��ʧ��������
				m_pWavFile->read(reinterpret_cast<char*>(&tagChunkHdr), sizeof(tagChunkHdr));
				if (m_pWavFile->fail())
				{
					m_pWavFile->clear();
					break;
				}

				// ѭ����ȡWAVE��ÿ��Chunk��
				switch(tagChunkHdr.uId)
				{
				case EWFS_FMT:
					// ��ȡWave��������ʽ��Ϣ
					m_pWavFile->read(reinterpret_cast<char*>(&tagPcmWaveFmt), sizeof(tagPcmWaveFmt));
					FK_ASSERT(0x0001 == tagPcmWaveFmt.wf.formatTag);
					m_pWavFile->seekg(tagChunkHdr.uSize - sizeof(tagPcmWaveFmt), std::ios_base::cur);
					m_nFrequency = tagPcmWaveFmt.wf.samplesPerSec;
					if (1 == tagPcmWaveFmt.wf.channels)	
					{
						if (8 == tagPcmWaveFmt.bitsPerSample)
						{
							m_nDataFormat = EADF_Mono_8;
						}
						else
						{
							m_nDataFormat = EADF_Mono_16;
						}
					}
					else
					{
						if (8 == tagPcmWaveFmt.bitsPerSample)
						{
							m_nDataFormat = EADF_Stereo_8;
						}
						else
						{
							m_nDataFormat = EADF_Stereo_16;
						}
					}
					break;
				case EWFS_DATA:
					m_cDataOffset = m_pWavFile->tellg();
					m_uSize = tagChunkHdr.uSize;
					m_pWavFile->seekg(tagChunkHdr.uSize, std::ios_base::cur);
					break;
				default:
					m_pWavFile->seekg(tagChunkHdr.uSize, std::ios_base::cur);
					break;					
				}
			}
			m_pWavFile->seekg(tagChunkHdr.uSize, std::ios_base::cur);
		}
		//-------------------------------------------------------------------
	}
}