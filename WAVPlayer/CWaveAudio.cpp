#include "stdafx.h"   
#include "Media.h"   
#include <afxwin.h>   
#include <MMSystem.h>   
#pragma comment(lib, "WINMM.LIB")
   
#ifdef _DEBUG   
#undef THIS_FILE   
static char THIS_FILE[]=__FILE__;   
#define new DEBUG_NEW   
#endif   
   
CWaveAudio::CWaveAudio()   
{   
    m_bRecording = FALSE;   
    m_bOpened = FALSE;   
    m_wDeviceID = 0;   
}   
   
CWaveAudio::~CWaveAudio()   
{   
    Close();   
}   
   
int CWaveAudio::GetDevices (void)   
{   
    return waveOutGetNumDevs ();   
}   
   
BOOL CWaveAudio::Load(CString Filename)   
{   
    Close ();   
	MCIERROR mciError;
    MCI_OPEN_PARMS OpenParms;   
    OpenParms.lpstrDeviceType = "waveaudio";   
    //OpenParms.lpstrElementName = "D:\\WAVPlayer\\中南大学简介.wav";  
	OpenParms.lpstrElementName = Filename;
	
	if (mciError = mciSendCommand(NULL, MCI_OPEN, MCI_OPEN_ELEMENT | MCI_OPEN_TYPE, (DWORD)(LPVOID)&OpenParms))
	{
		//TRACE("错误码：%d\r\n", mciError);
		//TRACE("第一处\r\n");
		return FALSE;
	}

          
    m_wDeviceID = OpenParms.wDeviceID;   
    m_bOpened = TRUE;   
   
    MCI_SET_PARMS SetParms;   
    SetParms.dwTimeFormat=MCI_FORMAT_MILLISECONDS;   
	if (mciSendCommand(m_wDeviceID, MCI_SET, MCI_SET_TIME_FORMAT, (DWORD)(LPVOID)&SetParms))
	{
		//TRACE("第二处\r\/*n");
		return FALSE;
	}
        
   
    return TRUE;   
}   
   
void CWaveAudio::Close (void)   
{   
    m_bRecording = FALSE;   
    m_bOpened = FALSE;   
   
    if (m_wDeviceID){   
        mciSendCommand (m_wDeviceID, MCI_STOP, MCI_WAIT, NULL);   
        mciSendCommand (m_wDeviceID, MCI_CLOSE, NULL, NULL);   
        }   
    m_wDeviceID = 0;   
}   
   
BOOL CWaveAudio::Play ()   
{   
    Stop ();   
    MCI_PLAY_PARMS PlayParms;   
    mciSendCommand (m_wDeviceID, MCI_SEEK, MCI_SEEK_TO_START, NULL);   
    if (mciSendCommand (m_wDeviceID, MCI_PLAY, NULL, (DWORD)(LPVOID) &PlayParms))   
        return FALSE;   
    else   
        return TRUE;   
}   
   
void CWaveAudio::Stop (void)   
{   
    mciSendCommand (m_wDeviceID, MCI_STOP, NULL, NULL);   
}   
   
BOOL CWaveAudio::Record (void)   
{   
    Close ();   
   
    MCI_OPEN_PARMS OpenParms;   
    OpenParms.lpstrDeviceType = "waveaudio";   
    OpenParms.lpstrElementName = "";   
    if (mciSendCommand (NULL, MCI_OPEN, MCI_OPEN_ELEMENT | MCI_OPEN_TYPE | MCI_WAIT, (DWORD)(LPVOID) &OpenParms))   
        return FALSE;   
    m_wDeviceID = OpenParms.wDeviceID;   
   
    MCI_RECORD_PARMS RecordParms;   
    if (mciSendCommand (m_wDeviceID, MCI_RECORD, NULL, (DWORD)(LPVOID) &RecordParms))   
        return FALSE;   
   
    m_bRecording = TRUE;   
    m_bOpened = TRUE;   
    return TRUE;   
}   
   
BOOL CWaveAudio::Save (CString Filename)   
{   
    if (!m_bRecording)   
        return FALSE;   
   
    Stop ();   
   
    MCI_SAVE_PARMS SaveParms;   
    SaveParms.lpfilename = (LPCSTR) Filename;   
    if (mciSendCommand (m_wDeviceID, MCI_SAVE, MCI_SAVE_FILE | MCI_WAIT, (DWORD)(LPVOID) &SaveParms))   
        return FALSE;   
   
    m_bRecording = FALSE;   
   
    Load (Filename);   
   
    return TRUE;   
}   
   
DWORD CWaveAudio::GetSampleRate()   
{   
    MCI_STATUS_PARMS StatusParms;   
    StatusParms.dwItem=MCI_WAVE_STATUS_SAMPLESPERSEC;   
    if(mciSendCommand(m_wDeviceID,MCI_STATUS,MCI_WAIT|MCI_STATUS_ITEM,(DWORD)(LPVOID) &StatusParms))   
        return -1;   
    else return StatusParms.dwReturn;   
}   
   
WORD CWaveAudio::GetChannel()   
{   
    MCI_STATUS_PARMS StatusParms;   
    StatusParms.dwItem=MCI_WAVE_STATUS_CHANNELS;   
    if(mciSendCommand(m_wDeviceID,MCI_STATUS,MCI_WAIT|MCI_STATUS_ITEM,(DWORD)(LPVOID) &StatusParms))   
        return -1;   
    else return StatusParms.dwReturn;   
}   
   
WORD CWaveAudio::GetResolution()   
{   
    MCI_STATUS_PARMS StatusParms;   
    StatusParms.dwItem=MCI_WAVE_STATUS_BITSPERSAMPLE;   
    if(mciSendCommand(m_wDeviceID,MCI_STATUS,MCI_WAIT|MCI_STATUS_ITEM,(DWORD)(LPVOID) &StatusParms))   
        return -1;   
    else return StatusParms.dwReturn;   
}   
   
DWORD CWaveAudio::GetWaveLength()   
{   
    MCI_STATUS_PARMS StatusParms;   
    StatusParms.dwItem=MCI_STATUS_LENGTH;   
    if(mciSendCommand(m_wDeviceID,MCI_STATUS,MCI_WAIT|MCI_STATUS_ITEM,(DWORD)(LPVOID) &StatusParms))   
        return -1;   
    else return StatusParms.dwReturn;   
}   