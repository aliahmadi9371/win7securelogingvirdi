// ---------------------------------------------------------------------------
#include <vcl.h>

#include "mainForm.h"
// ---------------------------------------------------------------------------
#pragma hdrstop
#pragma package(smart_init)
#pragma link "ipwwebsocket"
#pragma resource "*.dfm"

TMForm *MForm;
static int iAppState = -1;

// ---------------------------------------------------------------------------
__fastcall TMForm::TMForm(TComponent* Owner) : TForm(Owner)
{
//	Memo->Lines->Add("TMForm");

	startApp = false;

	TRect rect = Screen->PrimaryMonitor->BoundsRect;
	MForm->SetBounds(0, 0, rect.Width(), rect.Height());
	MForm->Left = 0;
	MForm->Top = 0;
	MForm->Width = rect.Width();
	MForm->Height = rect.Height();
}
// ---------------------------------------------------------------------------

void __fastcall TMForm::FormShow(TObject *Sender)
{

	Memo->Lines->Add("FormShow");
	if (!startApp) {
		startApp = true;

		CreateObjects();

		StartTimer->Interval = 100;
		StartTimer->Enabled = true;
	}
}
// ---------------------------------------------------------------------------

void __fastcall TMForm::StartTimerTimer(TObject *Sender)
{
	Memo->Lines->Add("StartTimerTimer");
	StartTimer->Enabled = false;

	Image1->Picture->LoadFromFile("bk.jpg");
	Image1->Stretch = true;
	Image2->Picture->LoadFromFile("box.png");
	Image2->Stretch = true;

	InitValues();
	ConfigApplication();
	PrepairScreen();
	RunTimer->Enabled = true;
}
// ---------------------------------------------------------------------------

void TMForm::InitValues()
{
	Memo->Lines->Add("InitValues");
	socket_connection = false;
//	switchuser = false;
	SwitchUser = true;
}
// ---------------------------------------------------------------------------

void TMForm::CreateObjects()
{
	Memo->Lines->Add("CreateObjects");
	StartTimer = new TTimer(NULL);
	StartTimer->Enabled = false;
	StartTimer->OnTimer = StartTimerTimer;
	StartTimer->Interval = 100;

	DualLcdTimer = new TTimer(NULL);
	DualLcdTimer->Enabled = false;
	DualLcdTimer->OnTimer = DualLcdTimerTimer;
	DualLcdTimer->Interval = 20;

	CheckTimer = new TTimer(NULL);
	CheckTimer->Enabled = false;
	CheckTimer->OnTimer = CheckTimerTimer;
	CheckTimer->Interval = 1000;

	RunTimer = new TTimer(NULL);
	RunTimer->Enabled = false;
	RunTimer->OnTimer = RunTimerTimer;
	RunTimer->Interval = 100;

	OutTimer = new TTimer(NULL);
	OutTimer->Enabled = false;
	OutTimer->OnTimer = OutTimerTimer;
	OutTimer->Interval = 30000;

	EnrolTimer = new TTimer(NULL);
	EnrolTimer->Enabled = false;
	EnrolTimer->OnTimer = EnrolTimerTimer;
	EnrolTimer->Interval = 2000;

	ipwWebSocket1 = new TipwWebSocket(NULL);
	ipwWebSocket1->OnConnected = ipwWebSocket1Connected;
	ipwWebSocket1->OnDisconnected = ipwWebSocket1Disconnected;
	ipwWebSocket1->OnError = ipwWebSocket1Error;
	ipwWebSocket1->OnSSLServerAuthentication =
		ipwWebSocket1SSLServerAuthentication;
	ipwWebSocket1->OnDataIn = ipwWebSocket1DataIn;
}
// ---------------------------------------------------------------------------

void TMForm::ConfigApplication()
{
	Memo->Lines->Add("ConfigApplication");
	Auth = false;
	socket_connection = false;
	sdk_init = false;
	finger_enrolling = false;
	try_count = 0;
	memo = false;
	first_appstate = 0;
	closing = false;

	TIniFile *ini;
	ini = new TIniFile(ChangeFileExt(Application->ExeName, ".INI"));
	iSocketPort = ini->ReadInteger("socket", "port", 80);
	sServerUrl = ini->ReadString("socket", "server_url", "");
	sUsername = ini->ReadString("socket", "username", "");
	sPassword = ini->ReadString("socket", "password", "");
	iSocketCheck = ini->ReadInteger("socket", "check_timeout", 1);
	iSocketTimeout = ini->ReadInteger("socket", "connection_timeout", 0);
	bLoged = ini->ReadBool("main", "log", false);
	sSocketOrigin = sUsername + ":" + sPassword;
	sFullServerUrl = sServerUrl + ":" + iSocketPort;

	sKeyStart = ini->ReadString("socket", "key_start", "CMD");
	sKeyEnd = ini->ReadString("socket", "key_end", "END");
	sKeyMid = ini->ReadString("socket", "key_mid", ":");
	iStatationIdLength = ini->ReadInteger("socket", "station_id_length", 3);
	iTextFirLength = ini->ReadInteger("socket", "text_fir_length", 8);
	iTryCountLength = ini->ReadInteger("socket", "try_count_length", 3);
	iStatusLength = ini->ReadInteger("socket", "status_length", 1);
	iErrorLength = ini->ReadInteger("socket", "error_length", 1);
	iResultLength = ini->ReadInteger("socket", "result_length", 1);
	iUserNameLength = ini->ReadInteger("socket", "username_length", 8);

	iStationId = ini->ReadInteger("main", "station_id", 0);
	memo = ini->ReadBool("main", "memo", false);
	first_appstate = ini->ReadInteger("main", "first_state", 0);

	sStationId = Format("%.*d", ARRAYOFCONST((iStatationIdLength, iStationId)));

	bSocketConnected = false;
	bSdkInit = UCBioAPIERROR_UNKNOWN;

	Label1->Caption = "";

	delete ini;

	char username[100];
	DWORD username_len = 100;
	GetUserNameA(username, &username_len);
	sCurrentUsername = username;

	if (!memo) {
		Memo->Visible = false;
	}
	else {
		Memo->Visible = true;
	}

	iAppState = first_appstate;
}
// ---------------------------------------------------------------------------

void TMForm::PrepairScreen()
{
	Memo->Lines->Add("PrepairScreen");
	ShowFullScreen(true);

	Label3->Caption = sCurrentUsername;
	Panel2->Left = (this->Width) / 2 - (Panel2->Width) / 2;
	Panel2->Top = (this->Height) / 2 - (Panel2->Height) / 2 +
		(this->Height) / 4;
	Label3->Left = (Label3->Parent->Width) / 2 - (Label3->Width) / 2;
	Label3->Top = (Label3->Parent->Height) / 2 - (Label3->Height) / 2;

	Label1->Caption = L"ارتباط با سرور برقرار نمی‌باشد";
	Label1->Left = (this->Width) / 2 - (Label1->Width) / 2;
	Label1->Top = (this->Height) - (Label1->Height) - 50;
}
// ---------------------------------------------------------------------------

void __fastcall TMForm::RunTimerTimer(TObject *Sender)
{
	Memo->Lines->Add("RunTimerTimer");
	RunTimer->Enabled = false;
	OpenBioSdk();
	WWindowState(iAppState);
	FHandle = AllocateHWnd(WndProc);
	WTSRegisterSessionNotification(FHandle, NOTIFY_FOR_THIS_SESSION);
	ShowWindow(Application->Handle, SW_HIDE);
	if (!socket_connection && (iAppState != 0)) {
		OutTimer->Interval = 30000;
		OutTimer->Enabled = true;
		OpenSocket();
	}
}
// ---------------------------------------------------------------------------

void TMForm::OpenBioSdk()
{
	Memo->Lines->Add("OpenBioSdk");
	bSdkInit = BioInit();
	if (bSdkInit != UCBioAPIERROR_NONE) {
		ShowMessage("Finger Print SDK Failure!!!!!");
	}
	else {
		sdk_init = true;
		CloseFohDevice();
	}

}
// ---------------------------------------------------------------------------

UCBioAPI_RETURN TMForm::BioInit()
{
	Memo->Lines->Add("BioInit");
	UCBioAPI_RETURN ret = UCBioAPI_Init(&hUCBioAPI);
	return ret;
}
// ---------------------------------------------------------------------------

UCBioAPI_RETURN TMForm::BioTerminate()
{
	Memo->Lines->Add("BioTerminate");
	UCBioAPI_RETURN ret = UCBioAPI_Terminate(hUCBioAPI);
	return ret;
}
// ---------------------------------------------------------------------------

void TMForm::OpenSocket()
{
	Memo->Lines->Add("OpenSocket");
	if (iAppState == -1)
		return;
	ipwWebSocket1->FSetOrigin(sSocketOrigin);
	ipwWebSocket1->Timeout = 0;
	Label1->Caption = L"تلاش برای ارتباط با سرور ...";

	Label1->Left = (this->Width) / 2 - (Label1->Width) / 2;
	Label1->Top = (this->Height) - (Label1->Height) - 50;
	Memo->Lines->Add(sFullServerUrl);
	if ((!socket_connection) && (iAppState != 0) && (!closing)) {
		try {
			Memo->Lines->Add("socket connection ... ");
			ipwWebSocket1->Connect(sFullServerUrl);

		}
		catch (Exception &Err) {
			Memo->Lines->Add("Error try catch connection --> " +
				Err.ToString());
		}
		OpenSocket();
	}
}
// ---------------------------------------------------------------------------

void __fastcall TMForm::CheckTimerTimer(TObject *Sender)
{
	Memo->Lines->Add("CheckTimerTimer");
	if (socket_connection)
		Label1->Caption = L"ارتباط با سرور برقرار است";
	else
		Label1->Caption = L"ارتباط با سرور برقرار نیست";

//	Memo->Lines->Add("App State == " + IntToStr(iAppState));
	if ((!socket_connection) && (iAppState != 0) && (!closing)) {
		Memo->Lines->Add("check connection");
		if (CheckTimer->Enabled)
			CheckTimer->Enabled = false; // open socket
		OutTimer->Interval = 30000;
		OutTimer->Enabled = true;
		OpenSocket();
	}
}
// ---------------------------------------------------------------------------

void __fastcall TMForm::ipwWebSocket1Error(TObject *Sender,TipwWebSocketErrorEventParams *e)
{
	Memo->Lines->Add("ipwWebSocket1Error");
	Memo->Lines->Add("Error callback --> socket error " + e->Description);
}
// ---------------------------------------------------------------------------

void __fastcall TMForm::ipwWebSocket1SSLServerAuthentication(TObject *Sender,TipwWebSocketSSLServerAuthenticationEventParams *e)
{
	Memo->Lines->Add("ipwWebSocket1SSLServerAuthentication");
	Memo->Lines->Add("ssl auth callback --> SSL Authentication " + e->Status);
	e->Accept = true;
}
// ---------------------------------------------------------------------------

void __fastcall TMForm::ipwWebSocket1Connected(TObject *Sender,TipwWebSocketConnectedEventParams *e){
	Memo->Lines->Add("ipwWebSocket1Connected");
	if (e->StatusCode == 0) {
		Memo->Lines->Add("Connected callback --> socket connection " +
			e->Description + " : " + IntToStr(e->StatusCode));
		Label1->Caption = "";
		Label1->Caption = L"ارتباط با سرور برقرار است";
		Memo->Lines->Add("socket connection sucsess");

		Label1->Left = (this->Width) / 2 - (Label1->Width) / 2;
		Label1->Top = (this->Height) - (Label1->Height) - 50;
		socket_connection = true;
		OutTimer->Enabled = false;

		if (!CheckTimer->Enabled)
			CheckTimer->Enabled = true; // check socket
	}
}
// ---------------------------------------------------------------------------

void __fastcall TMForm::ipwWebSocket1Disconnected(TObject *Sender,TipwWebSocketDisconnectedEventParams *e)
{
	Memo->Lines->Add("ipwWebSocket1Disconnected");
	Memo->Lines->Add("Disconnected callback --> socket disconnection " +
		e->Description + " : " + IntToStr(e->StatusCode));
	Label1->Caption = L"ارتباط با سرور قطع شد!!!";
	Memo->Lines->Add("ghat");
	Label1->Left = (this->Width) / 2 - (Label1->Width) / 2;
	Label1->Top = (this->Height) - (Label1->Height) - 50;
	socket_connection = false;
}
// ---------------------------------------------------------------------------

void TMForm::WWindowState(int State)
{
	Memo->Lines->Add("WWindowState");
	Memo->Lines->Add("AppState = " + IntToStr(iAppState));
	if (State == 0) {
		mymode = false;
		if (!(DualLcdTimer->Enabled))
			DualLcdTimer->Enabled = true;
		if (EnrolTimer->Enabled)
			EnrolTimer->Enabled = false;
		Memo->Lines->Add("WWindowState == 0");
	}
	else {
		mymode = true;
		if (!(DualLcdTimer->Enabled))
			DualLcdTimer->Enabled = true;
		if (!(EnrolTimer->Enabled))
			EnrolTimer->Enabled = true;
		Memo->Lines->Add("WWindowState == 1");
	}
}
// ---------------------------------------------------------------------------

void TMForm::ShowFullScreen(bool show)
{
	Memo->Lines->Add("ShowFullScreen");
	if (show) {
		if (memo) {
			MForm->Memo->Visible = true;
			MForm->BorderStyle = bsDialog;
		}
		else {
			MForm->Memo->Visible = false;
			MForm->BorderStyle = bsNone;
		}

		MForm->Visible = true;
		MForm->Show();

		Application->ShowMainForm = false;
		MForm->WindowState = wsMaximized;
	}
	else {
		MForm->Visible = false;
		MForm->Hide();
		Application->ShowMainForm = false;
		MForm->WindowState = wsMinimized;
	}
}
// ---------------------------------------------------------------------------

void __fastcall TMForm::DualLcdTimerTimer(TObject *Sender)
{
	Memo->Lines->Add("DualLcdTimerTimer");
	if (DualLcdTimer->Enabled)
		DualLcdTimer->Enabled = false;
	AppMode(mymode);
}
// ---------------------------------------------------------------------------

void TMForm::AppMode(bool mode)
{
	Memo->Lines->Add("AppMode");
	if (mode) {
		// HideTaskBar(true);
		ShowFullScreen(true);
		g_hKeyboardHook = SetWindowsHookEx(WH_KEYBOARD_LL,
			LowLevelKeyboardProc, 0, 0);
		if (GetSystemMetrics(SM_CMONITORS) > 1)
			system("disable.bat");
	}
	else {
		// HideTaskBar(false);
		ShowFullScreen(false);
		UnhookWindowsHookEx(g_hKeyboardHook);
		if (GetSystemMetrics(SM_CMONITORS) > 1)
			system("enable.bat");
	}
}
// ---------------------------------------------------------------------------

void __fastcall TMForm::EnrolTimerTimer(TObject *Sender)
{
	Memo->Lines->Add("EnrolTimerTimer");
	if (iAppState != 0) {
		if ((socket_connection) && (sdk_init) && (!finger_enrolling)) {

			finger_enrolling = true;
			Label2->Caption = L"لطفا اثر انگشت خود را وارد کنید";
			Label2->Left = (this->Width) / 2 - (Label2->Width) / 2;
			Label2->Top = 20;

			Memo->Lines->Add("enrolling finger print");
			if (!GetFringerPrint()) {
				finger_enrolling = false;
				Label2->Caption = L"خطا در وارد کردن اثر انگشت!!!";
			}
		}
	}
}
// ---------------------------------------------------------------------------

bool TMForm::GetFringerPrint()
{
	Memo->Lines->Add("GetFringerPrint");
	bool ret = false;
	if (!EnrollFP())
		return ret;
	if (GetTextFIRFromHandle() != UCBioAPIERROR_NONE)
		return ret;
	char* TextFirData = inputFIR.InputFIR.TextFIR->TextFIR;
	AnsiString TEXT;
	TEXT = "";
	// int i = 0;
	while (*TextFirData != NULL) {
		TEXT += (*TextFirData);
		TextFirData++;
		// i++;
	}
	SendSocketMessage(TEXT);
	UCBioAPI_FreeFIRHandle(hEnrolledFIR);
	UCBioAPI_FreeTextFIR(&TextFir);

	ret = true;
	return ret;
}
// ---------------------------------------------------------------------------

bool TMForm::EnrollFP()
{
	Memo->Lines->Add("EnrollFP");
	bool ret = false;
	if (OpenFohDevice() != UCBioAPIERROR_NONE) {
		ShowMessage(
			"Fingerprint Device is not connected to computer or driver error!!! Please connect Virdi fingerprint device to computer or report problem to administrator ... ");
		return ret;
	}
	UCBioAPI_RETURN err = UCBioAPI_Capture(hUCBioAPI,
		UCBioAPI_FIR_PURPOSE_VERIFY, &hEnrolledFIR, 10000, NULL, NULL);
	CloseFohDevice();
	if (err == UCBioAPIERROR_NONE)
		ret = true;
	return ret;
}
// ---------------------------------------------------------------------------

UCBioAPI_RETURN TMForm::OpenFohDevice()
{
	Memo->Lines->Add("OpenFohDevice");
	UCBioAPI_RETURN ret = UCBioAPI_OpenDevice(hUCBioAPI,
		UCBioAPI_DEVICE_ID_AUTO);
	return ret;
}
// ---------------------------------------------------------------------------

UCBioAPI_RETURN TMForm::CloseFohDevice()
{
	Memo->Lines->Add("CloseFohDevice");
	UCBioAPI_RETURN ret = UCBioAPI_CloseDevice(hUCBioAPI,
		UCBioAPI_DEVICE_ID_AUTO);
	return ret;
}
// ---------------------------------------------------------------------------

UCBioAPI_RETURN TMForm::GetTextFIRFromHandle()
{
   Memo->Lines->Add("GetTextFIRFromHandle");
	UCBioAPI_RETURN ret = UCBioAPI_GetTextFIRFromHandle(hEnrolledFIR, &TextFir,
		UCBioAPI_FALSE);
	if (ret == UCBioAPIERROR_NONE) {
		inputFIR.Form = UCBioAPI_FIR_FORM_TEXTENCODE;
		inputFIR.InputFIR.TextFIR = &TextFir;
	}
	return ret;
}
// ---------------------------------------------------------------------------

void TMForm::SendSocketMessage(AnsiString messageFir)
{
	Memo->Lines->Add("SendSocketMessage");
	try_count++;
	Memo->Lines->Add("app state = " + IntToStr(iAppState) + " , try count = " +
		IntToStr(try_count));
	AnsiString message = "";
	sTryCount = Format("%.*d", ARRAYOFCONST((iTryCountLength, try_count)));
	int tmp = sCurrentUsername.Length();
	sCurrentUsernameLength =
		Format("%.*d", ARRAYOFCONST((iUserNameLength, tmp)));
	tmp = messageFir.Length();
	sFirLength = Format("%.*d", ARRAYOFCONST((iTextFirLength, tmp)));
	message = sKeyStart + sKeyMid + sStationId + sKeyMid + IntToStr(iAppState) +
		sKeyMid + sTryCount + sKeyMid + sCurrentUsernameLength + sKeyMid +
		sFirLength + sKeyMid + sCurrentUsername + sKeyMid + messageFir +
		sKeyMid + sKeyEnd;
	if (socket_connection)
		try {
		ipwWebSocket1->SendText(message);
		}
	catch (Exception &Err) {
		ShowMessage(message);
		ShowMessage(Err.ToString());
	}
}
// ---------------------------------------------------------------------------

void __fastcall TMForm::ipwWebSocket1DataIn(TObject *Sender,TipwWebSocketDataInEventParams *e)
{
	Memo->Lines->Add("ipwWebSocket1DataIn");
	Memo->Lines->Add("socket data in");
	socket_connection = false;
	if (e->Text.Length() == sKeyStart.Length() + sKeyMid.Length() * 6 +
		sKeyEnd.Length() + iStatationIdLength + iStatusLength +
		iTryCountLength + iErrorLength + iResultLength) {
		if (finger_enrolling) {
			if (e->Text.SubString((e->Text.Length() - sKeyEnd.Length() -
				sKeyMid.Length()), 1) == "1") {

				finger_enrolling = false;
				Label2->Caption = L"احراز هویت با موفقیت انجام شد";
				Panel2->Left = (this->Width) / 2 - (Panel2->Width) / 2;
				Panel2->Top = (this->Height) / 2 - (Panel2->Height) / 2 +
					(this->Height) / 4;

				Memo->Lines->Add("ok");
				try_count = 0;
				iAppState = 0;
				WWindowState(iAppState);
				return;
			}
			else {
				if (try_count > 2 && iAppState == 1) {
					Memo->Lines->Add
						("log off system successfully without autentication");
					MySystemSignout();
				}
				else {
					Label2->Caption =
						L"شما دارای مجوز دسترسی به این رایانه نمی‌باشید!!!";
					Panel2->Left = (this->Width) / 2 - (Panel2->Width) / 2;
					Panel2->Top = (this->Height) / 2 - (Panel2->Height) / 2 +
						(this->Height) / 4;
					finger_enrolling = false;
				}
			}
		}
		else {
			Memo->Lines->Add("received data when not authentication");
		}
	}
	else {
		Memo->Lines->Add("invalid data in");
	}

}
// ---------------------------------------------------------------------------

void __fastcall TMForm::FormCloseQuery(TObject *Sender, bool &CanClose)
{
	Memo->Lines->Add("FormCloseQuery");
	if (!memo)
		CanClose = false;
	else {
		CanClose = true;
		closing = true;
		CloseFohDevice();
		Application->Terminate();
		exit(EXIT_FAILURE);
	}
}
// ---------------------------------------------------------------------------

void __fastcall TMForm::WndProc(TMessage& Msg)
{
//	Memo->Lines->Add("WndProc");
	if (Msg.Msg == WM_WTSSESSION_CHANGE) {
		Memo->Lines->Add("Message = WM_WTSSESSION_CHANGE");

//		switch (Msg.WParam) {
//		case WTS_CONSOLE_CONNECT:
//			Memo->Lines->Add("WTS_CONSOLE_CONNECT");
//			break;
//		case WTS_CONSOLE_DISCONNECT:
//			Memo->Lines->Add("WTS_CONSOLE_DISCONNECT");
//			break;
//		case WTS_REMOTE_CONNECT:
//			Memo->Lines->Add("WTS_REMOTE_CONNECT");
//			break;
//		case WTS_REMOTE_DISCONNECT:
//			Memo->Lines->Add("WTS_REMOTE_DISCONNECT");
//			break;
//		case WTS_SESSION_LOGON:
//			Memo->Lines->Add("WTS_SESSION_LOGON");
//			break;
//		case WTS_SESSION_LOGOFF:
//			Memo->Lines->Add("WTS_SESSION_LOGOFF");
//			break;
//		case WTS_SESSION_LOCK:
//			Memo->Lines->Add("WTS_SESSION_LOCK");
//			break;
//		case WTS_SESSION_UNLOCK:
//			Memo->Lines->Add("WTS_CONSOLE_CONNECT");
//			break;
//		case WTS_SESSION_REMOTE_CONTROL:
//			Memo->Lines->Add("WTS_CONSOLE_CONNECT");
//			break;
//		case WTS_SESSION_CREATE:
//			Memo->Lines->Add("WTS_SESSION_CREATE");
//			break;
//		case WTS_SESSION_TERMINATE:
//			Memo->Lines->Add("WTS_SESSION_TERMINATE");
//			break;
//		}
		 if(Msg.WParam == WTS_SESSION_LOCK){
			Memo->Lines->Add("WTS_SESSION_LOCK");

			TIniFile *ini;
			ini = new TIniFile(ChangeFileExt(Application->ExeName, ".INI"));
			int state = ini->ReadInteger("last","state",0);
			ini->WriteInteger("last","state",1);
			delete ini;
			if(state == 2){
				Memo->Lines->Add("Not Real Lock");
				Msg.Result = FALSE;
			}
			else{
                Memo->Lines->Add("Real Lock");
				Application->Terminate();
			}
		 }
		 else if (Msg.WParam == WTS_CONSOLE_DISCONNECT){
			Memo->Lines->Add("WTS_CONSOLE_DISCONNECT");
			Memo->Lines->Add("Switch User");

			TIniFile *ini;
			ini = new TIniFile(ChangeFileExt(Application->ExeName, ".INI"));
			ini->WriteInteger("last","state",2); //switch
			delete ini;

			Application->Terminate();
		 }
		 else{
			Msg.Result = TRUE;
			TForm::WndProc(Msg);
		 }
	}
	else {
		Msg.Result = TRUE;
		TForm::WndProc(Msg);
	}
}
// ---------------------------------------------------------------------------

void TMForm::MySystemShutdown()
{
	Memo->Lines->Add("MySystemShutdown");
	CheckTimer->Enabled = false;
	EnrolTimer->Enabled = false;
	HANDLE hToken;
	TOKEN_PRIVILEGES tkp;

	// Get a token for this process.

	OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY,
		&hToken);

	// Get the LUID for the shutdown privilege.

	LookupPrivilegeValue(NULL, SE_SHUTDOWN_NAME, &tkp.Privileges[0].Luid);

	tkp.PrivilegeCount = 1; // one privilege to set
	tkp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;

	// Get the shutdown privilege for this process.

	AdjustTokenPrivileges(hToken, FALSE, &tkp, 0, (PTOKEN_PRIVILEGES)NULL, 0);

	if (GetLastError() != ERROR_SUCCESS)
		return;

	// Shut down the system and force all applications to close.

	CloseFohDevice();
	system("enable.bat");
	ExitWindowsEx(EWX_SHUTDOWN | EWX_FORCE,
		SHTDN_REASON_MAJOR_OPERATINGSYSTEM | SHTDN_REASON_MINOR_UPGRADE |
		SHTDN_REASON_FLAG_PLANNED);
	Application->Terminate();
}
// ---------------------------------------------------------------------------

void TMForm::MySystemSignout()
{
	Memo->Lines->Add("MySystemSignout");
	CheckTimer->Enabled = false;
	EnrolTimer->Enabled = false;
	CloseFohDevice();
	system("enable.bat");
	ExitWindowsEx(EWX_LOGOFF | EWX_FORCE, 0);
	Application->Terminate();
}
// ---------------------------------------------------------------------------

void __fastcall TMForm::OutTimerTimer(TObject *Sender)
{
	Memo->Lines->Add("OutTimerTimer");
	if (iAppState == 1) {
		// HideTaskBar(false);
		Memo->Lines->Add("log off system successfully without autentication");
		MySystemSignout();
	}
	else if (iAppState == 2) {
		// HideTaskBar(false);
		Memo->Lines->Add("turn off system successfully without autentication");
		MySystemShutdown();
	}
}
// ---------------------------------------------------------------------------

LRESULT CALLBACK TMForm::LowLevelKeyboardProc(int nCode, WPARAM wParam,LPARAM lParam)
{
//	MForm->Memo->Lines->Add("LowLevelKeyboardProc");
	if (iAppState != 0) {
		if (nCode < 0 || nCode != HC_ACTION) // do not process message
				return CallNextHookEx(NULL, nCode, wParam, lParam);
		tagKBDLLHOOKSTRUCT *str = (tagKBDLLHOOKSTRUCT*)lParam;
		switch (str->flags) {
		case (LLKHF_ALTDOWN):
			return 1;
		}
		if ((wParam == WM_KEYDOWN) || (wParam = WM_SYSKEYDOWN) || (wParam =
			WM_KEYUP) || (wParam = WM_SYSKEYUP) || (nCode == HC_ACTION)) {
			switch (str->vkCode) {
			case VK_RWIN:
			case VK_LWIN:
			case VK_CONTROL:
			case VK_LCONTROL:
			case VK_RCONTROL:
			case VK_APPS:
			case VK_SLEEP:
			case VK_MENU:
			case VK_LMENU:
			case VK_RMENU:
			case VK_DELETE: ;
				return 1;
			}
		}
		return CallNextHookEx(NULL, nCode, wParam, lParam);
	}
	else {
		return CallNextHookEx(NULL, nCode, wParam, lParam);
	}

}
// ---------------------------------------------------------------------------

void TMForm::HideTaskBar(bool hide)
{
	Memo->Lines->Add("HideTaskBar");
	UnicodeString tmp = "Shell_traywnd";
	HWND hwnd = FindWindow(tmp.c_str(), NULL);

	if (!hide) { // show taskbar
		if (!IsWindowVisible(hwnd)) {
			Memo->Lines->Add("show taskbar");
			SetWindowPos(hwnd, 0, 0, 0, 0, 0, SWP_SHOWWINDOW);
		}
	}
	else { // hide taskbar
		if (IsWindowVisible(hwnd)) {
			Memo->Lines->Add("hide taskbar");
			SetWindowPos(hwnd, 0, 0, 0, 0, 0, SWP_HIDEWINDOW);
		}
	}
}
// ---------------------------------------------------------------------------
