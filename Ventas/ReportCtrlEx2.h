///////////////////////////////////////////////////////////////////////////////
// ReportCtrlEx2.h
//
// CReportCtrlEx2, a CListCtrl derived class that is specialized on "Report View"
// style. 
//
// Features:
//
// 1, Item sorting by clicking on column header.
// 2, Sub-item text edit.
// 3, Item repositioning.
// 4, Customizing checkbox styles, including "single" and "disabled".
// 5, Sending a message to parent window when user clicks on a checkbox.
// 6, Convenient item insertion, deletion, moving, and sub-item text changing.
// 7, Sub-item images and color
// 8, And much more... 
//
// This code may be used in compiled form in any way you desire. This file may be
// redistributed unmodified by any means PROVIDING it is not sold for profit without
// the authors written consent, and providing that this notice and the authors name 
// is included. If the source code in  this file is used in any commercial application 
// then acknowledgement must be made to the author of this file .
//
// This file is provided "as is" with no expressed or implied warranty.
//
// Written by Bin Liu (abinn32@yahoo.com)
//
// History
//
// Nov. 26, 2003 - Initial release.
// Dec. 03, 2003 - Fixed a bug in "EndEdit" where item text were not preperly committed.
//                 Completed the implementation of the "Sort-Separator" feature.
// Jan. 01, 2004 - Fixed a bug in "SetItemData".
//               - Added message "WM_EDIT_COMMITTED" which is sent to the parent window
//                 when an item text editing is committed.
//               - Fixed a bug in "SetItemText"(double type).
//               - Fixed a bug where item sorting does not work properly when there
//                 are multiple CReportCtrlEx objects on same window.
//
///////////////////////////////////////////////////////////////////////////////

#include "DateTimeCtrlReport.h"
#include "Utilidades.h"

#ifndef __REPORTCTRLEX2_H__
#define __REPORTCTRLEX2_H__

#define	ALQUILER        "Alquiler"
#define	VENTA           "Venta"
#define	OTROS           "Otros"
#define	ENTREGA         "Entrega"
#define	RECOGIDA        "Recogida"

#define	MENSUAL         "Mensual"
#define	DIA_LABORABLE   "Dia laborable"
#define	DIA_NATURAL     "Dia natural"

//////////////////////////////////////////////////////////////////////////
// The CReportCtrlEx2 Class Definition
//////////////////////////////////////////////////////////////////////////

class __declspec(dllexport) CReportCtrlEx2 : public CReportCtrl
{
public:		
		
	//////////////////////////////////////////////////////////////////////
	//		Constructor & Destructor
	//////////////////////////////////////////////////////////////////////
	CReportCtrlEx2();
	virtual ~CReportCtrlEx2();
	//void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);

	// Item text edit	
	BOOL StartEdit(int nItem, int nSubItem); // Display the editbox, previous edit are committed
	BOOL EndEdit(BOOL bCommit = TRUE); // Commit/cancel text edit, hide the editbox

	// Item combo edit	
	//CComboBox* GetComboControl();
	//BOOL StartCombo(int nItem, int nSubItem);
	//BOOL EndCombo(BOOL bCommit = TRUE);
	CDateTimeCtrlReport* GetDateTimeControl();
	BOOL StartDateTimeCtrl(int nItem, int nSubItem);
	BOOL EndDateTimeCtrl(BOOL bCommit = TRUE);
	BOOL EndItem(BOOL bCommit = TRUE);
	
protected:	
	
	void _MouseClkMonitor(UINT nMsg, UINT nFlags, CPoint point, BOOL bTriggerEdit);

	// Member data	
	BOOL m_bEdit;
	CDateTimeCtrlReport *m_pDateTimeCtrlReport;
	//CComboBox* m_pWndCombo;

	//////////////////////////////////////////////////////////////////////
	// Wizard Generated Stuff
	//////////////////////////////////////////////////////////////////////

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CReportCtrlEx2)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	//}}AFX_VIRTUAL

	// Generated message map functions

protected:	

	//{{AFX_MSG(CReportCtrlEx2)
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg LRESULT OnEnKillfocus( WPARAM wParam, LPARAM lParam );
	afx_msg LRESULT OnEnSetfocus( WPARAM wParam, LPARAM lParam );
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnMButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDblClk(UINT nFlags, CPoint point);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

//////////////////////////////////////////////////////////////////////////
// End of CReportCtrlEx2 Class Definition
//////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // __REPORTCTRLEX2_H__
