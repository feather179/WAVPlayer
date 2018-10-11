#if _MSC_VER > 1000
#pragma once
#endif //_MSC_VER > 1000

#include <afxwin.h>
#include <mmsystem.h>
#include <mciavi.h>
#include <digitalv.h>


//处理波形类
class CWaveAudio
{
public:
	CWaveAudio();			//构造函数
	virtual~CWaveAudio();	//析构函数

	int GetDevices(void);	//得到播放设备
	BOOL Load(CString);		//载入文件
	void Close(void);		//关闭文件
	BOOL Play(void);		//播放
	void Stop(void);		//停止播放
	BOOL Record(void);		//录制
	BOOL Save(CString);		//保存
	WORD GetResolution(void);	//得到位长
	DWORD GetSampleRate(void);	//得到采样率
	WORD GetChannel(void);		//得到声道
	DWORD GetWaveLength(void);	//得到音频长度



private:
	BOOL m_bRecording;		//是否在录音
	BOOL m_bOpened;			//是否打开文件
	WORD m_wDeviceID;		//播放设备ID
};
