// ���� ifdef ���Ǵ���ʹ�� DLL �������򵥵�
// ��ı�׼�������� DLL �е������ļ��������������϶���� FKAUDIO_EXPORTS
// ���ű���ġ���ʹ�ô� DLL ��
// �κ�������Ŀ�ϲ�Ӧ����˷��š�������Դ�ļ��а������ļ����κ�������Ŀ���Ὣ
// FKAUDIO_API ������Ϊ�Ǵ� DLL ����ģ����� DLL ���ô˺궨���
// ������Ϊ�Ǳ������ġ�
#ifdef FKAUDIO_EXPORTS
#define FKAUDIO_API __declspec(dllexport)
#else
#define FKAUDIO_API __declspec(dllimport)
#endif

// �����Ǵ� FKAudio.dll ������
class FKAUDIO_API CFKAudio {
public:
	CFKAudio(void);
	// TODO: �ڴ�������ķ�����
};

extern FKAUDIO_API int nFKAudio;

FKAUDIO_API int fnFKAudio(void);
