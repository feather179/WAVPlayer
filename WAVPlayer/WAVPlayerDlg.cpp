
// WAVPlayerDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "WAVPlayer.h"
#include "WAVPlayerDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

	// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CWAVPlayerDlg 对话框



CWAVPlayerDlg::CWAVPlayerDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_WAVPLAYER_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CWAVPlayerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CWAVPlayerDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CWAVPlayerDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CWAVPlayerDlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_OPEN, &CWAVPlayerDlg::OnOpen)
	ON_BN_CLICKED(IDC_PLAY, &CWAVPlayerDlg::OnPlay)
	ON_BN_CLICKED(IDC_RECORD, &CWAVPlayerDlg::OnRecord)
	ON_BN_CLICKED(IDC_SAVE, &CWAVPlayerDlg::OnSave)
	ON_BN_CLICKED(IDC_STOP, &CWAVPlayerDlg::OnStop)
END_MESSAGE_MAP()


// CWAVPlayerDlg 消息处理程序

BOOL CWAVPlayerDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	CWnd* m_pWnd;
	m_pWnd = GetDlgItem(IDC_PLAY);
	m_pWnd->EnableWindow(false);
	m_pWnd = GetDlgItem(IDC_SAVE);
	m_pWnd->EnableWindow(false);



	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CWAVPlayerDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CWAVPlayerDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);

		
	}
	else
	{
		CDialogEx::OnPaint();


	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CWAVPlayerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CWAVPlayerDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnOK();
}


void CWAVPlayerDlg::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnCancel();
}






void CWAVPlayerDlg::OnOpen()
{
	// TODO: 在此添加控件通知处理程序代码
	CString Filter, str;
	Filter = "波形音频文件(*.WAV)|*.WAV||";

	CFileDialog FileDlg(true, NULL, NULL, OFN_HIDEREADONLY, Filter);
	if (FileDlg.DoModal() == IDOK)
	{
		if (!m_Wave.Load(FileDlg.GetPathName()))
		{
			MessageBox("不能打开文件!", "错误", MB_OK | MB_ICONSTOP);
			m_bOpen = false;
		}
		else
		{
			m_bOpen = true;
		}

	}

	if (m_bOpen)
	{
		CWnd* m_pWnd;
		m_pWnd = GetDlgItem(IDC_PLAY);
		m_pWnd->EnableWindow(true);


		path = FileDlg.GetPathName();
		SetDlgItemText(IDC_WAVE_NAME, FileDlg.GetFileName());
		str.Format("%5.3f", m_Wave.GetSampleRate() / 1000.);
		str += _T("kHZ");
		SetDlgItemText(IDC_SAMPLE_RATE, str);
		str.Empty();
		switch (m_Wave.GetChannel())
		{
		case 1:
			str = "单声道";
			break;
		case 2:
			str = "立体声";
			break;
		default:
			str = "未知";
			break;
		}
		SetDlgItemText(IDC_CHANNEL, str);
		str.Empty();
		str.Format("%d", m_Wave.GetResolution());
		str += "位";
		SetDlgItemText(IDC_RESOLUTION, str);
		str.Empty();
		str.Format("%2.2u:%02.2f:%02.2u", m_Wave.GetWaveLength() / 1000 / 60,
			m_Wave.GetWaveLength() / 1000., m_Wave.GetWaveLength() / 1000 / 3600);
		SetDlgItemText(IDC_WAVE_LENGTH, str);

		//m_bOpen = true;
		if (m_bOpen)
		{
			CWnd* m_pWnd;
			CRect rect;
			m_pWnd = GetDlgItem(IDC_WAVE_GRAPH);
			m_pWnd->GetClientRect(rect);
			INFO_WAVEWIDE = rect.Width();
			INFO_WAVEDEEP = rect.Height();
			CClientDC dc(m_pWnd);
			DrawWave(dc.m_hDC, rect.left, rect.top, (char*)path.operator LPCTSTR());
		}
	
	}

}


void CWAVPlayerDlg::OnPlay()
{
	// TODO: 在此添加控件通知处理程序代码
	//if (m_bOpen)
	//{
	//	CWnd* m_pWnd;
	//	CRect rect;
	//	m_pWnd = GetDlgItem(IDC_WAVE_GRAPH);
	//	m_pWnd->GetClientRect(rect);
	//	INFO_WAVEWIDE = rect.Width();
	//	INFO_WAVEDEEP = rect.Height();
	//	CClientDC dc(m_pWnd);
	//	DrawWave(dc.m_hDC, rect.left, rect.top, (char*)path.operator LPCTSTR());
	//}
	m_Wave.Play();

}


void CWAVPlayerDlg::OnRecord()
{
	// TODO: 在此添加控件通知处理程序代码
	CWnd* m_pWnd;
	m_pWnd = GetDlgItem(IDC_PLAY);
	m_pWnd->EnableWindow(false);
	m_pWnd = GetDlgItem(IDC_OPEN);
	m_pWnd->EnableWindow(false);
	m_pWnd = GetDlgItem(IDC_SAVE);
	m_pWnd->EnableWindow(false);

	m_Wave.Record();

}


void CWAVPlayerDlg::OnSave()
{
	// TODO: 在此添加控件通知处理程序代码
	CString Filter;
	Filter = "Wave File(*.WAV)|*.WAV||";
	CFileDialog FileDlg(false, NULL, NULL, OFN_OVERWRITEPROMPT, Filter);
	FileDlg.m_ofn.lpstrDefExt = "wav";
	if (FileDlg.DoModal() == IDOK)
		m_Wave.Save(FileDlg.GetPathName());

}


void CWAVPlayerDlg::OnStop()
{
	// TODO: 在此添加控件通知处理程序代码
	CWnd* m_pWnd;
	m_pWnd = GetDlgItem(IDC_PLAY);
	m_pWnd->EnableWindow(true);
	m_pWnd = GetDlgItem(IDC_OPEN);
	m_pWnd->EnableWindow(true);
	m_pWnd = GetDlgItem(IDC_SAVE);
	m_pWnd->EnableWindow(true);

	m_Wave.Stop();

}


void CWAVPlayerDlg::DrawWave(HDC hdc, unsigned int x, unsigned int y, char*path)
{
	HMMIO h;
	MMCKINFO mmParent, mmSub;//MMCKINFO结构中包含了有关部分的信息
	GLOBALHANDLE gh;
	PCMWAVEFORMAT waveformat;//fmt部分结构
	char *p;
	unsigned long nextsample;
	long afactor;
	unsigned int i, n, amp;
	int *ip;

	HPEN OldPen = (HPEN)SelectObject(hdc, GetStockObject(BLACK_PEN));
	HBRUSH OldBrush = (HBRUSH)SelectObject(hdc, GetStockObject(WHITE_BRUSH));
	Rectangle(hdc, x, y, x + INFO_WAVEWIDE, y + INFO_WAVEDEEP);
	if ((h = mmioOpen(path, NULL, MMIO_READ)) == NULL)
		return;

	mmParent.fccType = mmioFOURCC('W', 'A', 'V', 'E');
	if (mmioDescend(h, (LPMMCKINFO)&mmParent, NULL, MMIO_FINDRIFF))
	{
		mmioClose(h, 0);
		return;
	}

	mmSub.ckid = mmioFOURCC('f', 'm', 't', ' ');
	if (mmioDescend(h, (LPMMCKINFO)&mmSub, (LPMMCKINFO)&mmParent, MMIO_FINDCHUNK))
	{
		mmioClose(h, 0);
		return;
	}

	n = min((unsigned int)mmSub.cksize, sizeof(PCMWAVEFORMAT));
	if (mmioRead(h, (LPSTR)&waveformat, n) != (int)n)
	{
		mmioClose(h, 0);
		return;
	}

	if (waveformat.wf.wFormatTag != WAVE_FORMAT_PCM)
	{
		mmioClose(h, 0);
		return;
	}

	mmioAscend(h, &mmSub, 0);//当读出一个部分的数据后，退出该部分

	mmSub.ckid = mmioFOURCC('d', 'a', 't', 'a');
	if (mmioDescend(h, (LPMMCKINFO)&mmSub, (LPMMCKINFO)&mmParent, MMIO_FINDCHUNK))
	{
		mmioClose(h, 0);
		return;
	}

	if (waveformat.wBitsPerSample == 8 && waveformat.wf.nChannels == 1)
	{
		nextsample = mmSub.cksize / (long)INFO_WAVEWIDE;
		afactor = 2L * (255L / (long)INFO_WAVEDEEP);
	}
	else if (waveformat.wBitsPerSample == 8 && waveformat.wf.nChannels == 1)
	{
		nextsample = 2L * ((mmSub.cksize / 2L) / (long)INFO_WAVEWIDE);
		afactor = 2L * (255L / (long)INFO_WAVEDEEP);
	}
	else if (waveformat.wBitsPerSample > 8 && waveformat.wf.nChannels == 1)
	{
		nextsample = 2L * ((mmSub.cksize / (long)INFO_WAVEWIDE)) & 0xfffffffeL;
		afactor = 2L * (65535L / (long)INFO_WAVEDEEP);
	}
	else
	{
		nextsample = 4L * ((mmSub.cksize / 4L) / (long)INFO_WAVEWIDE) & 0xfffffffeL;
		afactor = 2L * (65535L / (long)INFO_WAVEDEEP);
	}

	MoveToEx(hdc, x, y + INFO_WAVEDEEP / 2, NULL);
	LineTo(hdc, x + INFO_WAVEWIDE, y + INFO_WAVEDEEP / 2);
	if ((gh = GlobalAlloc(GMEM_MOVEABLE, mmSub.cksize)) != NULL)
	{
		if ((p = (char*)GlobalLock(gh)) != NULL)
		{
			if (mmioRead(h, p, mmSub.cksize) == mmSub.cksize)
			{
				for (i = 0; i < INFO_WAVEWIDE;)
				{
					ip = (int *)p;
					if (waveformat.wBitsPerSample == 8 && waveformat.wf.nChannels == 1)
						amp = (unsigned int)max(labs(((long)p[0] - 128L) / afactor), 1L);
					else if (waveformat.wBitsPerSample == 8 && waveformat.wf.nChannels == 2)
						amp = (unsigned int)max(labs(((long)p[0] - 128L + (long)p[1] - 128L) / 2) / afactor, 1L);
					else if (waveformat.wBitsPerSample > 8 && waveformat.wf.nChannels == 1)
						amp = (unsigned int)max(labs((long)ip[0] / afactor), 1L);
					else
						amp = (unsigned int)max(labs((((long)ip[0] + (long)ip[1]) / 2) / afactor), 1L);

					if (amp > (unsigned int)INFO_WAVEDEEP / 2)
						amp = INFO_WAVEDEEP / 2 - 3;

					MoveToEx(hdc, x + i, y + (INFO_WAVEDEEP / 2) - amp, NULL);
					LineTo(hdc, x + i, y + (INFO_WAVEDEEP / 2) + amp);
					i += 2;
					p += nextsample;
				}
			}
			GlobalUnlock(gh);
		}
		GlobalFree(gh);
	}

	SelectObject(hdc, OldPen);
	(HBRUSH)SelectObject(hdc, OldBrush);

	mmioClose(h, 0);
	return;
}

