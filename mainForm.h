//---------------------------------------------------------------------------
#ifndef mainFormH
#define mainFormH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <IniFiles.hpp>
#include "UCBioAPI.h"
#include "UCBioAPI_Basic.h"
#include "UCBioAPI_Error.h"
#include "UCBioAPI_Export.h"
#include "UCBioAPI_ExportType.h"
#include "ipwwebsocket.h"
#include <Vcl.ExtCtrls.hpp>
#include <Winapi.Messages.hpp>
#include <Vcl.Graphics.hpp>
#include <Lmcons.h>
#include <winuser.h>
#include <Windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <Vcl.Imaging.jpeg.hpp>
#include <Vcl.Imaging.pngimage.hpp>
#include <fstream>

#define UCBioAPIERROR_UNKNOWN 100

//---------------------------------------------------------------------------
class TMForm : public TForm
{
__published:	// IDE-managed Components
	TPanel *Panel1;
	TImage *Image1;
	TLabel *Label1;
	TLabel *Label2;
	TLabel *Label3;
	TPanel *Panel2;
	TImage *Image2;
	TMemo *Memo;

	void __fastcall FormCloseQuery(TObject *Sender, bool &CanClose);
	void __fastcall FormShow(TObject *Sender);

private:	// User declarations
	TTimer* StartTimer;
	void __fastcall StartTimerTimer(TObject *Sender);

	TTimer* DualLcdTimer;
	void __fastcall DualLcdTimerTimer(TObject *Sender);

	TTimer* CheckTimer;
	void __fastcall CheckTimerTimer(TObject *Sender);

	TTimer* RunTimer;
	void __fastcall RunTimerTimer(TObject *Sender);

	TTimer* OutTimer;
	void __fastcall OutTimerTimer(TObject *Sender);

	TTimer* EnrolTimer;
	void __fastcall EnrolTimerTimer(TObject *Sender);


	TipwWebSocket* ipwWebSocket1;
	void __fastcall ipwWebSocket1Disconnected(TObject *Sender, TipwWebSocketDisconnectedEventParams *e);
	void __fastcall ipwWebSocket1Error(TObject *Sender, TipwWebSocketErrorEventParams *e);
	void __fastcall ipwWebSocket1Connected(TObject *Sender, TipwWebSocketConnectedEventParams *e);
	void __fastcall ipwWebSocket1SSLServerAuthentication(TObject *Sender, TipwWebSocketSSLServerAuthenticationEventParams *e);
	void __fastcall ipwWebSocket1DataIn(TObject *Sender, TipwWebSocketDataInEventParams *e);



	void InitValues();
	void CreateObjects();
	void ConfigApplication();
	void OpenSocket();
	void OpenBioSdk();
	UCBioAPI_RETURN BioInit();
	UCBioAPI_RETURN BioTerminate();
	UCBioAPI_RETURN OpenFohDevice();
	UCBioAPI_RETURN CloseFohDevice();
	bool EnrollFP();
	bool GetFringerPrint();
	UCBioAPI_RETURN GetTextFIRFromHandle();

	void SendSocketMessage(AnsiString messageFir);

	UCBioAPI_HANDLE hUCBioAPI;
	UCBioAPI_FIR_HANDLE hEnrolledFIR;
    UCBioAPI_INPUT_FIR inputFIR;
	UCBioAPI_EXPORT_DATA ExData;
	UCBioAPI_FINGER_BLOCK_PTR blockptr;
	UCBioAPI_FIR_TEXTENCODE TextFir;
	UCBioAPI_RETURN bSdkInit;

	void WWindowState(int State);
	void AppMode(bool mode);
	void ShowFullScreen(bool show);
	void PrepairScreen();

	void HideTaskBar(bool visible);

	HWND FHandle;
	void __fastcall WndProc(TMessage& Msg);

	static LRESULT CALLBACK LowLevelKeyboardProc(int nCode, WPARAM wParam, LPARAM lParam);
	HHOOK g_hKeyboardHook;

	bool mymode;
	bool SwitchUser;


public:		// User declarations
	__fastcall TMForm(TComponent* Owner);

//	void LogDataOneLine(AnsiString str);
//	ofstream *file;

	int iSocketPort;
	AnsiString sServerUrl;
	AnsiString sFullServerUrl;
	AnsiString sUsername;
	AnsiString sPassword;
	AnsiString sSocketOrigin;
	bool bSocketConnected;
	int iSocketCheck;
	bool bLoged;
	int iSocketTimeout;

	AnsiString sKeyStart;
	AnsiString sKeyEnd;
	AnsiString sKeyMid;
	int iStatationIdLength;
	AnsiString sStationId;
	int iTextFirLength;
	int iTryCountLength;
    int iStatusLength;
    int iErrorLength;
	int iResultLength;
	int iUserNameLength;
	//int iUserNameCount;
	AnsiString sCurrentUsername;
	int iStationId;
    int first_appstate;

	bool memo;
	AnsiString sCurrentUsernameLength;
	AnsiString sFirLength;

	AnsiString sTryCount;

	bool Auth;

	bool socket_connection;
	bool sdk_init;
	bool finger_enrolling;
	int try_count;
	bool current_auth;
	bool turnoff;
	bool end;
	bool end_query;
	int ws;

	void MySystemShutdown();
	void MySystemSignout();

	bool startApp;
	int monitorCount;
	bool first;
	bool closing;

};
//---------------------------------------------------------------------------
extern PACKAGE TMForm *MForm;
//---------------------------------------------------------------------------
#endif
