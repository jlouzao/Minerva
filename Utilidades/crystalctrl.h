#if !defined(AFX_CRYSTALCTRL_H__BE29C51F_9FEB_4521_9586_592473625085__INCLUDED_)
#define AFX_CRYSTALCTRL_H__BE29C51F_9FEB_4521_9586_592473625085__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// Machine generated IDispatch wrapper class(es) created by Microsoft Visual C++

// NOTE: Do not modify the contents of this file.  If this class is regenerated by
//  Microsoft Visual C++, your modifications will be overwritten.

// Dispatch interfaces referenced by this interface
class CRowCursor;

/////////////////////////////////////////////////////////////////////////////
// CCrystalCtrl wrapper class

class __declspec(dllexport)CCrystalCtrl : public CWnd
{
protected:
	DECLARE_DYNCREATE(CCrystalCtrl)

	//{{AFX_MSG(CCrystalCtrl)
	//afx_msg void OnClose();
	//}}AFX_MSG
	//DECLARE_MESSAGE_MAP()

public:
	CLSID const& GetClsid()
	{
		static CLSID const clsid
			= { 0x25601, 0x0, 0x0, { 0xc0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x46 } };
		return clsid;
	}
	virtual BOOL Create(LPCTSTR lpszClassName,
		LPCTSTR lpszWindowName, DWORD dwStyle,
		const RECT& rect,
		CWnd* pParentWnd, UINT nID,
		CCreateContext* pContext = NULL)
	{ return CreateControl(GetClsid(), lpszWindowName, dwStyle, rect, pParentWnd, nID); }

    BOOL Create(LPCTSTR lpszWindowName, DWORD dwStyle,
		const RECT& rect, CWnd* pParentWnd, UINT nID,
		CFile* pPersist = NULL, BOOL bStorage = FALSE,
		BSTR bstrLicKey = NULL)
	{ return CreateControl(GetClsid(), lpszWindowName, dwStyle, rect, pParentWnd, nID,
		pPersist, bStorage, bstrLicKey); }

// Attributes
public:

// Operations
public:
	CString GetReportFileName();
	void SetReportFileName(LPCTSTR lpszNewValue);
	short GetWindowLeft();
	void SetWindowLeft(short nNewValue);
	short GetWindowTop();
	void SetWindowTop(short nNewValue);
	short GetWindowWidth();
	void SetWindowWidth(short nNewValue);
	short GetWindowHeight();
	void SetWindowHeight(short nNewValue);
	CString GetWindowTitle();
	void SetWindowTitle(LPCTSTR lpszNewValue);
	BOOL GetWindowControlBox();
	void SetWindowControlBox(BOOL bNewValue);
	BOOL GetWindowMaxButton();
	void SetWindowMaxButton(BOOL bNewValue);
	BOOL GetWindowMinButton();
	void SetWindowMinButton(BOOL bNewValue);
	CString GetPrintFileName();
	void SetPrintFileName(LPCTSTR lpszNewValue);
	CString GetSelectionFormula();
	void SetSelectionFormula(LPCTSTR lpszNewValue);
	CString GetGroupSelectionFormula();
	void SetGroupSelectionFormula(LPCTSTR lpszNewValue);
	long GetWindowParentHandle();
	void SetWindowParentHandle(long nNewValue);
	short GetCopiesToPrinter();
	void SetCopiesToPrinter(short nNewValue);
	short GetAction();
	void SetAction(short nNewValue);
	short GetLastErrorNumber();
	void SetLastErrorNumber(short nNewValue);
	CString GetLastErrorString();
	void SetLastErrorString(LPCTSTR lpszNewValue);
	CString GetConnect();
	void SetConnect(LPCTSTR lpszNewValue);
	long GetSessionHandle();
	void SetSessionHandle(long nNewValue);
	CString GetUserName_();
	void SetUserName(LPCTSTR lpszNewValue);
	CString GetPassword();
	void SetPassword(LPCTSTR lpszNewValue);
	long GetDestination();
	void SetDestination(long nNewValue);
	long GetPrintFileType();
	void SetPrintFileType(long nNewValue);
	long GetWindowBorderStyle();
	void SetWindowBorderStyle(long nNewValue);
	CString GetBoundReportHeading();
	void SetBoundReportHeading(LPCTSTR lpszNewValue);
	BOOL GetBoundReportFooter();
	void SetBoundReportFooter(BOOL bNewValue);
	long GetReportSource();
	void SetReportSource(long nNewValue);
	short GetDetailCopies();
	void SetDetailCopies(short nNewValue);
	BOOL GetDiscardSavedData();
	void SetDiscardSavedData(BOOL bNewValue);
	CString GetEMailCCList();
	void SetEMailCCList(LPCTSTR lpszNewValue);
	CString GetEMailMessage();
	void SetEMailMessage(LPCTSTR lpszNewValue);
	CString GetEMailSubject();
	void SetEMailSubject(LPCTSTR lpszNewValue);
	CString GetEMailToList();
	void SetEMailToList(LPCTSTR lpszNewValue);
	short GetMarginBottom();
	void SetMarginBottom(short nNewValue);
	short GetMarginLeft();
	void SetMarginLeft(short nNewValue);
	short GetMarginRight();
	void SetMarginRight(short nNewValue);
	short GetMarginTop();
	void SetMarginTop(short nNewValue);
	short GetPrintDay();
	void SetPrintDay(short nNewValue);
	long GetPrinterCollation();
	void SetPrinterCollation(long nNewValue);
	short GetPrinterCopies();
	void SetPrinterCopies(short nNewValue);
	CString GetPrinterDriver();
	void SetPrinterDriver(LPCTSTR lpszNewValue);
	CString GetPrinterName();
	void SetPrinterName(LPCTSTR lpszNewValue);
	CString GetPrinterPort();
	void SetPrinterPort(LPCTSTR lpszNewValue);
	short GetPrinterStartPage();
	void SetPrinterStartPage(short nNewValue);
	short GetPrinterStopPage();
	void SetPrinterStopPage(short nNewValue);
	CString GetPrintFileCharSepQuote();
	void SetPrintFileCharSepQuote(LPCTSTR lpszNewValue);
	CString GetPrintFileCharSepSeparator();
	void SetPrintFileCharSepSeparator(LPCTSTR lpszNewValue);
	BOOL GetPrintFileUseRptDateFmt();
	void SetPrintFileUseRptDateFmt(BOOL bNewValue);
	BOOL GetPrintFileUseRptNumberFmt();
	void SetPrintFileUseRptNumberFmt(BOOL bNewValue);
	short GetPrintMonth();
	void SetPrintMonth(short nNewValue);
	short GetPrintYear();
	void SetPrintYear(short nNewValue);
	long GetRecordsPrinted();
	void SetRecordsPrinted(long nNewValue);
	long GetRecordsRead();
	void SetRecordsRead(long nNewValue);
	long GetRecordsSelected();
	void SetRecordsSelected(long nNewValue);
	short GetReportDisplayPage();
	void SetReportDisplayPage(short nNewValue);
	short GetReportLatestPage();
	void SetReportLatestPage(short nNewValue);
	short GetReportStartPage();
	void SetReportStartPage(short nNewValue);
	CString GetSQLQuery();
	void SetSQLQuery(LPCTSTR lpszNewValue);
	short GetStatus();
	void SetStatus(short nNewValue);
	BOOL GetWindowControls();
	void SetWindowControls(BOOL bNewValue);
	long GetWindowState();
	void SetWindowState(long nNewValue);
	long GetDialogParentHandle();
	void SetDialogParentHandle(long nNewValue);
	BOOL GetProgressDialog();
	void SetProgressDialog(BOOL bNewValue);
	CString GetExchangeProfile();
	void SetExchangeProfile(LPCTSTR lpszNewValue);
	CString GetExchangePassword();
	void SetExchangePassword(LPCTSTR lpszNewValue);
	CString GetExchangeFolder();
	void SetExchangeFolder(LPCTSTR lpszNewValue);
	CString GetPrintFileODBCSource();
	void SetPrintFileODBCSource(LPCTSTR lpszNewValue);
	CString GetPrintFileODBCUser();
	void SetPrintFileODBCUser(LPCTSTR lpszNewValue);
	CString GetPrintFileODBCPassword();
	void SetPrintFileODBCPassword(LPCTSTR lpszNewValue);
	CString GetPrintFileODBCTable();
	void SetPrintFileODBCTable(LPCTSTR lpszNewValue);
	short GetPrintFileLinesPerPage();
	void SetPrintFileLinesPerPage(short nNewValue);
	CString GetSubreportToChange();
	void SetSubreportToChange(LPCTSTR lpszNewValue);
	CString GetReportTitle();
	void SetReportTitle(LPCTSTR lpszNewValue);
	CString GetGridSource();
	void SetGridSource(LPCTSTR lpszNewValue);
	BOOL GetWindowShowGroupTree();
	void SetWindowShowGroupTree(BOOL bNewValue);
	BOOL GetWindowAllowDrillDown();
	void SetWindowAllowDrillDown(BOOL bNewValue);
	BOOL GetWindowShowNavigationCtls();
	void SetWindowShowNavigationCtls(BOOL bNewValue);
	BOOL GetWindowShowCancelBtn();
	void SetWindowShowCancelBtn(BOOL bNewValue);
	BOOL GetWindowShowPrintBtn();
	void SetWindowShowPrintBtn(BOOL bNewValue);
	BOOL GetWindowShowExportBtn();
	void SetWindowShowExportBtn(BOOL bNewValue);
	BOOL GetWindowShowZoomCtl();
	void SetWindowShowZoomCtl(BOOL bNewValue);
	BOOL GetWindowShowCloseBtn();
	void SetWindowShowCloseBtn(BOOL bNewValue);
	BOOL GetWindowShowProgressCtls();
	void SetWindowShowProgressCtls(BOOL bNewValue);
	BOOL GetWindowShowSearchBtn();
	void SetWindowShowSearchBtn(BOOL bNewValue);
	BOOL GetWindowShowPrintSetupBtn();
	void SetWindowShowPrintSetupBtn(BOOL bNewValue);
	BOOL GetWindowShowRefreshBtn();
	void SetWindowShowRefreshBtn(BOOL bNewValue);
	CRowCursor GetDataSource();
	void SetDataSource(LPDISPATCH newValue);
	CString GetFormulas(short index);
	void SetFormulas(short index, LPCTSTR lpszNewValue);
	CString GetSortFields(short index);
	void SetSortFields(short index, LPCTSTR lpszNewValue);
	CString GetGroupSortFields(short index);
	void SetGroupSortFields(short index, LPCTSTR lpszNewValue);
	CString GetDataFiles(short index);
	void SetDataFiles(short index, LPCTSTR lpszNewValue);
	CString GetGroupCondition(short index);
	void SetGroupCondition(short index, LPCTSTR lpszNewValue);
	CString GetSectionMinHeight(short index);
	void SetSectionMinHeight(short index, LPCTSTR lpszNewValue);
	CString GetSectionFormat(short index);
	void SetSectionFormat(short index, LPCTSTR lpszNewValue);
	CString GetSectionLineHeight(short index);
	void SetSectionLineHeight(short index, LPCTSTR lpszNewValue);
	CString GetSectionFont(short index);
	void SetSectionFont(short index, LPCTSTR lpszNewValue);
	CString GetStoredProcParam(short index);
	void SetStoredProcParam(short index, LPCTSTR lpszNewValue);
	CString GetGraphType(short index);
	void SetGraphType(short index, LPCTSTR lpszNewValue);
	CString GetGraphData(short index);
	void SetGraphData(short index, LPCTSTR lpszNewValue);
	CString GetGraphText(short index);
	void SetGraphText(short index, LPCTSTR lpszNewValue);
	CString GetGraphOptions(short index);
	void SetGraphOptions(short index, LPCTSTR lpszNewValue);
	CString GetParameterFields(short index);
	void SetParameterFields(short index, LPCTSTR lpszNewValue);
	CString GetLogonInfo(short index);
	void SetLogonInfo(short index, LPCTSTR lpszNewValue);
	void AboutBox();
	short PrintReport();
	void PageFirst();
	void PageNext();
	void PageLast();
	void PagePrevious();
	short PageCount();
	void PageShow(short p);
	void PageZoom(short z);
	void PageZoomNext();
	void PrinterSelect();
	CString FetchSelectionFormula();
	void ReplaceSelectionFormula(LPCTSTR s);
	short RetrieveDataFiles();
	short RetrieveLogonInfo();
	void RetrieveSQLQuery();
	short RetrieveStoredProcParams();
	short LogOnServer(LPCTSTR dll, LPCTSTR server, LPCTSTR database, LPCTSTR userid, LPCTSTR Password);
	void LogOffServer(short id, BOOL all);
	short GetNSubreports();
	CString GetNthSubreportName(short n);
	void Reset();
	void SpecifyDataSourceField(short n, LPCTSTR name, short width);
	void SetTablePrivateData(short TableIndex, long DataTag, const VARIANT& Data);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.
#endif // !defined(AFX_CRYSTALCTRL_H__BE29C51F_9FEB_4521_9586_592473625085__INCLUDED_)