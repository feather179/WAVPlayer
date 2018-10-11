#if _MSC_VER > 1000
#pragma once
#endif //_MSC_VER > 1000

#include <afxwin.h>
#include <mmsystem.h>
#include <mciavi.h>
#include <digitalv.h>


//��������
class CWaveAudio
{
public:
	CWaveAudio();			//���캯��
	virtual~CWaveAudio();	//��������

	int GetDevices(void);	//�õ������豸
	BOOL Load(CString);		//�����ļ�
	void Close(void);		//�ر��ļ�
	BOOL Play(void);		//����
	void Stop(void);		//ֹͣ����
	BOOL Record(void);		//¼��
	BOOL Save(CString);		//����
	WORD GetResolution(void);	//�õ�λ��
	DWORD GetSampleRate(void);	//�õ�������
	WORD GetChannel(void);		//�õ�����
	DWORD GetWaveLength(void);	//�õ���Ƶ����



private:
	BOOL m_bRecording;		//�Ƿ���¼��
	BOOL m_bOpened;			//�Ƿ���ļ�
	WORD m_wDeviceID;		//�����豸ID
};
