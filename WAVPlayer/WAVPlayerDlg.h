
// WAVPlayerDlg.h: 头文件
//
#include "Media.h"

#pragma once


// CWAVPlayerDlg 对话框
class CWAVPlayerDlg : public CDialogEx
{
// 构造
public:
	CWAVPlayerDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_WAVPLAYER_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	//绘制波形函数
	void DrawWave(HDC hdc, unsigned int x, unsigned int y, char* path);

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();

	afx_msg void OnOpen();
	afx_msg void OnPlay();
	afx_msg void OnRecord();
	afx_msg void OnSave();
	afx_msg void OnStop();

private:
	CString path;			//文件路径
	CWaveAudio m_Wave;		//可重用类的对象
	unsigned int INFO_WAVEWIDE;		//绘画框的宽度
	unsigned int INFO_WAVEDEEP;		//绘画框的高度
	bool m_bOpen;			//判断是否有波形音频文件打开
};
