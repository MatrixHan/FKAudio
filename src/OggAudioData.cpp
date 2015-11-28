//-------------------------------------------------------------------
// 
//
//
//-------------------------------------------------------------------

#include "stdafx.h"
#include "../include/OggAudioData.h"
#include <vector>

#ifdef _DEBUG
#pragma comment(lib, "../external/bin/ogg_static_d.lib")
#pragma comment(lib, "../external/bin/vorbis_static_d.lib")
#else
#pragma comment(lib, "../external/bin/ogg_static.lib")
#pragma comment(lib, "../external/bin/vorbis_static.lib")
#endif

namespace Ogre
{
	namespace FKAudio
	{
		//-------------------------------------------------------------------
		// ����
		OggAudioData::OggAudioData(const SP_ISTREAM& file)
			: m_pOggFile(file)
		{
			Init();
		}
		//-------------------------------------------------------------------
		// ��ʼ��Vorbis
		void OggAudioData::Init()
		{
			// ��ʼ��ͬ��ogg��
			ogg_sync_init(&m_oy);

			// ΪOgg���仺����
			char* buffer(ogg_sync_buffer(&m_oy, OGG_BUFFUR));
			m_pOggFile->read(buffer, OGG_BUFFUR);
			int bytes(static_cast<int>(m_pOggFile->gcount()));
			ogg_sync_wrote(&m_oy, bytes);

			// ��ȡ��һ��Ogg��Ϣҳ,ȷ���ǲ���Vorbis����
			FK_ASSERT(1 == ogg_sync_pageout(&m_oy, &m_og));

			// ��������˳���ŵ�Ogg���������ҽ�������ʹ���Ϊһ�����л�����
			ogg_stream_init(&m_os, ogg_page_serialno(&m_og));

			vorbis_info_init(&m_vi);
			vorbis_comment_init(&m_vc);
			// ȷ�ϰ汾���Ƿ���ȷ
			FK_ASSERT(ogg_stream_pagein(&m_os, &m_og) >= 0);

			// ȷ������ȷ��Vorbis
			FK_ASSERT(1 == ogg_stream_packetout(&m_os ,&m_op));

			// ȷ����Vorbisͷ
			FK_ASSERT(vorbis_synthesis_headerin(&m_vi, &m_vc, &m_op) >= 0);

			// ��ȡ���ͺ�Ƶ��
			m_nDataFormat = (1 == m_vi.channels) ? EADF_Mono_16 : EADF_Stereo_16;
			m_nFrequency = m_vi.rate;

			int i(0);
			while (i < 2)
			{
				while (i < 2)
				{
					int nResult(ogg_sync_pageout(&m_oy, &m_og));

					// �������򷵻أ��ȴ���ø����Ogg���ݰ������������ҳ
					if (0 == nResult)
					{
						break;
					}

					// ���ܻᶪ�������в���ȷ�������Ȼ�ȡ����ŵ�����ҳ�����ٴ���
					if (1 == nResult)
					{
						// ������װҳʱ���ܻ���һЩ���󣬵�������ʱ�����
						ogg_stream_pagein(&m_os, &m_og);
						// ����ҳ���
						while (i < 2)
						{
							nResult = ogg_stream_packetout(&m_os,&m_op);
							if (0 == nResult)
							{
								break;
							}
							vorbis_synthesis_headerin(&m_vi, &m_vc, &m_op);
							++ i;
						}
					}
				}

				// �������Ƕ����������һ�Ρ������ǿա��Ľ�����Ϣ��������ʹ�ǿ���ϢҲû���κλ������������Ӱ�ȫ�����Է�ֹ����
				buffer = ogg_sync_buffer(&m_oy, OGG_BUFFUR);
				m_pOggFile->read(buffer, OGG_BUFFUR);
				bytes = static_cast<int>(m_pOggFile->gcount());
				ogg_sync_wrote(&m_oy, bytes);
			}

			// ���ˣ�����ͷȫ��������ϣ���ʼ��Vorbis��ʼ����
			// ��Ϊ�����������ͬʱ����������������Ҳ���Գ�ʼ������ֲ�������
			vorbis_synthesis_init(&m_vd, &m_vi);	// ��ʼ�����Ľ�����
			vorbis_block_init(&m_vd, &m_vb);		// Ϊ�ֲ���������ʼ���ռ�

			m_cDataOffset = m_pOggFile->tellg();

			this->Reset();	
		}
		//-------------------------------------------------------------------
		// ��������
		OggAudioData::~OggAudioData()
		{
			Destory();
		}
		//-------------------------------------------------------------------
		// �ͷ�Vorbis
		void OggAudioData::Destory()
		{
			ogg_stream_clear(&m_os);
			vorbis_block_clear(&m_vb);
			vorbis_dsp_clear(&m_vd);
			vorbis_comment_clear(&m_vc);
			// ���ſ������vorbis���ýṹ
			vorbis_info_clear(&m_vi); 
			// �ͷ�Oggͬ����
			ogg_sync_clear(&m_oy);
		}
		//-------------------------------------------------------------------
		// ��ȡOgg�ļ���С
		uint32 OggAudioData::GetSize()
		{	
			// ��ʽ�ṹ�����Է���0
			return 0;	
		}
		//-------------------------------------------------------------------
		// ��ȡOgg���ļ�
		uint32 OggAudioData::Read(void* pAudioData, uint32 uSize)
		{
			FK_ASSERT(NULL != pAudioData);

			// ����һ��ָ����С�Ķ����ռ�
			std::vector<ogg_int16_t> vecConvBuffer( uSize / sizeof(ogg_int16_t));
			// ��ʼ��ʣ�ನ������
			int nLeftChannelNums(static_cast<int>(vecConvBuffer.size() / m_vi.channels));
			// ��ʼ����ǰ���ȼ�¼��
			uint32 uCurSize(0);			

			while (nLeftChannelNums > 0)
			{
				while (nLeftChannelNums > 0)
				{
					int nResult(ogg_sync_pageout(&m_oy , &m_og));

					// �޷���ȡOggҳ����Ҫ�������ݰ�
					if (0 == nResult)
					{
						break;
					}

					if (nResult > 0)
					{
						// �˴���Ҫ�Է���ֵ��������ʹ��Щ����Ҳû�й�ϵ���Ȱ�ȫ���ﵽ������ҳҲ�ǿ��Եġ�
						ogg_stream_pagein(&m_os, &m_og); 

						while (nLeftChannelNums > 0)
						{
							nResult = ogg_stream_packetout(&m_os, &m_op);

							// ���ݲ��㣬������ҳʧ�ܣ���Ҫѭ���Ȱ�
							if (0 == nResult)
							{
								break;
							}

							if (nResult > 0)
							{
								// �����һ��������ҳ����ʼ����
								if (0 == vorbis_synthesis(&m_vb, &m_op))
								{
									vorbis_synthesis_blockin(&m_vd, &m_vb);
								}

								// ppPcm��һ���ನ�εĸ����������������������У�pcm[0]����������pcm[1]����������
								// ������Ҫ��ppPcm���[-1, 1]�ĸ�����ת����PCM��ʽ��д����
								// nChannelNum��Pcmÿ�����εĴ�С��
								float** ppPcm;
								int nChannelNums;
								while ((nLeftChannelNums > 0) && ((nChannelNums = vorbis_synthesis_pcmout(&m_vd, &ppPcm)) > 0))
								{
									// ��õ�ǰʣ��δ������Ĳ��θ���
									int nReadyChannelNums = FKMin(nChannelNums, nLeftChannelNums);
									nLeftChannelNums -= nReadyChannelNums;

									// ����������ת��Ϊ16λ�з�������
									for (int i = 0; i < m_vi.channels; ++ i)
									{
										ogg_int16_t* ptr(&vecConvBuffer[i]);
										float const * mono(ppPcm[i]);

										for (int j = 0; j < nReadyChannelNums; ++ j)
										{
											*ptr = FKClamp< ogg_int16_t >(static_cast<ogg_int16_t>(mono[j] * 32767.0f), -32768, 32767);
											ptr += m_vi.channels;
										}
									}

									// ���Ѿ�������Ĳ��ν���Vorbis���봦��
									vorbis_synthesis_read(&m_vd, nReadyChannelNums);

									// ��ǰ�Ѿ���������ݿռ��С
									uint32 const uReadyBufZize = nReadyChannelNums * m_vi.channels;
									// �ѽ��������ݷ��뻺����
									std::copy(vecConvBuffer.begin(), vecConvBuffer.begin() + uReadyBufZize,
										static_cast<ogg_int16_t*>(pAudioData) + uCurSize);

									// ���ĵ�ǰλ�ü�¼��
									uCurSize += uReadyBufZize;
								}
							}
						}
					}
				}

				if (nLeftChannelNums > 0)
				{
					char* buffer(ogg_sync_buffer(&m_oy, OGG_BUFFUR));
					m_pOggFile->read(buffer, OGG_BUFFUR);
					int bytes(static_cast<int>(m_pOggFile->gcount()));

					if (m_pOggFile->fail())
					{
						m_pOggFile->clear();
						nLeftChannelNums = 0;
					}

					ogg_sync_wrote(&m_oy, bytes);
				}
			}

			return uCurSize * sizeof(ogg_int16_t);
		}
		//-------------------------------------------------------------------
		// ��λOgg�ļ�
		void OggAudioData::Reset()
		{
			FK_ASSERT(NULL != m_pOggFile);

			m_pOggFile->clear();
			m_pOggFile->seekg(m_cDataOffset);
		}
		//-------------------------------------------------------------------
	}
}