///////////////////////////////////////////////////////////////////////////////
// ReportCtrlEx2.cpp
//
// CReportCtrlEx2, a CReportCtrl derived class that use a edit combo
//
///////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ReportCtrlEx2.h"
#include <afxtempl.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CReportCtrlEx2 Implementation
/////////////////////////////////////////////////////////////////////////////
CReportCtrlEx2::CReportCtrlEx2(): m_pDateTimeCtrlReport(NULL)
{
	m_pDateTimeCtrlReport = new CDateTimeCtrlReport;
	VERIFY(m_pDateTimeCtrlReport != NULL);

	m_bEdit = TRUE;
}

CReportCtrlEx2::~CReportCtrlEx2()
{	
	if (m_pDateTimeCtrlReport != NULL)
		delete m_pDateTimeCtrlReport;

}

BEGIN_MESSAGE_MAP(CReportCtrlEx2, CListCtrl)
	//{{AFX_MSG_MAP(CReportCtrlEx)
	ON_WM_VSCROLL()
	ON_WM_HSCROLL()
	ON_NOTIFY_REFLECT(LVN_COLUMNCLICK, OnColumnclick)
	ON_WM_LBUTTONDOWN()
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_MBUTTONDOWN()
	ON_WM_MBUTTONDBLCLK()
	ON_WM_RBUTTONDOWN()
	ON_WM_RBUTTONDBLCLK()
	ON_NOTIFY_REFLECT(NM_CUSTOMDRAW, OnCustomDraw)
	//}}AFX_MSG_MAP
	ON_MESSAGE(WM_KILLFOCUS, OnEnKillfocus)
	//ON_MESSAGE(WM_SETFOCUS, OnEnSetfocus)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CReportCtrlEx message handlers

LRESULT CReportCtrlEx2::OnEnKillfocus( WPARAM wParam, LPARAM lParam )
{
	// Recoge el mensaje de KillFocus del CEditReport
	GetParent()->SendMessage (WM_KILLFOCUS);
	return 0;
}

LRESULT CReportCtrlEx2::OnEnSetfocus( WPARAM wParam, LPARAM lParam )
{
	// Recoge el mensaje de KillFocus del CEditReport
	GetParent()->SendMessage (WM_SETFOCUS);
	return 0;
}

BOOL CReportCtrlEx2::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class
	if (pMsg->message == WM_KEYDOWN)
	{	if (!_IsEditVisible())
		{
			// disable user from check/uncheck the checkboxes using space key
			// things get nasty if the user is HOLDING the space bar down
			if (pMsg->wParam == VK_SPACE)
				return TRUE;
		}
		else
		{
			POINT pt = m_ptEditting;
			switch (pMsg->wParam)
			{
			case VK_ESCAPE: // Cancel edit
				EndItem(FALSE);
				return TRUE;

			case VK_RETURN: // Commit edit
				EndItem(TRUE);
				return TRUE;

			case VK_TAB: // switch edit sub items

					if (pt.y == GetColumnCount() - 1)
					{
						pt.y = 0;
						if (pt.x < CListCtrl::GetItemCount() - 1)
							pt.x++;
						else
							pt.x = 0;						
					}
					else
						pt.y++;

					EndItem(TRUE);

					// Si es el primer elemento hacemos el scroll hacia la izquierda
					if (pt.y == 0)
						SendMessage( WM_HSCROLL, SB_LEFT, 0 );
					// Si llegamos al elemento no visible se hace scroll a la derecha
					if (pt.y == 8)
						SendMessage( WM_HSCROLL, SB_RIGHT, 0 );	

					EnsureVisible(pt.x, FALSE);

					if (pt.y == 4 || pt.y == 5)
					{
						m_bEdit = FALSE;
						StartDateTimeCtrl(pt.x, pt.y);
					}
					else
					{
						m_bEdit = TRUE;
						StartEdit(pt.x, pt.y);
					}

					//if (m_bEdit && !m_pWndEdit->IsWindowVisible())
					//	SendMessage( WM_HSCROLL, /*SB_LINERIGHT*/SB_RIGHT, 0 );
					return TRUE;

			case VK_UP: // edit upper item
				if (pt.x > 0)
				{
					pt.x--;

					EndItem(TRUE);
				
					EnsureVisible(pt.x, FALSE);

					if (pt.y == 4 || pt.y == 5)
					{
						m_bEdit = FALSE;
						StartDateTimeCtrl(pt.x, pt.y);
					}
					else
					{
						m_bEdit = TRUE;
						StartEdit(pt.x, pt.y);
					}

					//EnsureVisible(pt.x, FALSE);

					return TRUE;
				}
				break;
				
			case VK_DOWN: // edit lower item
				if (pt.x < CListCtrl::GetItemCount() - 1)
				{
					pt.x++;

					EndItem(TRUE);

					EnsureVisible(pt.x, FALSE);

					if (pt.y == 4 || pt.y == 5)
					{
						m_bEdit = FALSE;
						StartDateTimeCtrl(pt.x, pt.y);
					}
					else
					{
						m_bEdit = TRUE;
						StartEdit(pt.x, pt.y);
					}
					
					//EnsureVisible(pt.x, FALSE);

					return TRUE;
				}
				break;			

			case VK_RIGHT: // edit lower item

				// Si estamos en la columna de la descripcion no se puede navegar por el
				// liscontrol a la derecha puesto que nos movemos dentro del texto
				if (pt.y != 11)
				{
					if (pt.y < GetColumnCount() - 1)
					{
						pt.y++;
					}
					else
					{
						pt.y = 0;
						if (pt.x < CListCtrl::GetItemCount() - 1)
							pt.x++;
						else
							pt.x = 0;
					}

					EndItem(TRUE);

					// Si es el primer elemento hacemos el scroll hacia la izquierda
					if (pt.y == 0)
						SendMessage( WM_HSCROLL, SB_LEFT, 0);
					// Si llegamos al elemento no visible se hace scroll a la derecha
					if (pt.y == 8)
						SendMessage( WM_HSCROLL, SB_RIGHT, 0 );

					EnsureVisible(pt.x, FALSE);

					if (pt.y == 4 || pt.y == 5)
					{
						m_bEdit = FALSE;
						StartDateTimeCtrl(pt.x, pt.y);
					}
					else
					{
						m_bEdit = TRUE;
						StartEdit(pt.x, pt.y);
					}
					
					return TRUE;
				}

				break;			

			case VK_LEFT: // edit lower item

				// Si estamos en la columna de la descripcion no se puede navegar por el
				// liscontrol a la izquierda puesto que nos movemos dentro del texto
				if (pt.y != 11)
				{
					if (pt.y > 0)
					{
						pt.y--;
					}
					else
					{
						pt.y = GetColumnCount()-1;
						if (pt.x == 0)
						{
							pt.y = 0;
							pt.x = CListCtrl::GetItemCount()-1;						
						}
						else
							pt.x--;
					}					

					EndItem(TRUE);

					// Si estamos en el 3 elemento del CListCtrl se hace scroll a la izquierda
					// porque es el primero que deja de ser visible
					if (pt.y == 3)
						SendMessage( WM_HSCROLL, SB_LEFT, 0 );
					// Si es el último elemento hacemos el scroll hacia la derecha
					if (pt.y == GetColumnCount()-1)
						SendMessage( WM_HSCROLL, SB_RIGHT, 0);					

					EnsureVisible(pt.x, FALSE);

					if (pt.y == 4 || pt.y == 5)
					{
						m_bEdit = FALSE;
						StartDateTimeCtrl(pt.x, pt.y);
					}
					else
					{
						m_bEdit = TRUE;
						StartEdit(pt.x, pt.y);
					}

					return TRUE;
				}

				break;

			default:
				break;				
			}
		}
	}

	return CListCtrl::PreTranslateMessage(pMsg);
}

void CReportCtrlEx2::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	_MouseClkMonitor(WM_LBUTTONDOWN, nFlags, point, TRUE);
}

void CReportCtrlEx2::OnLButtonDblClk(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	_MouseClkMonitor(WM_LBUTTONDBLCLK, nFlags, point, TRUE);
}

void CReportCtrlEx2::OnMButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	_MouseClkMonitor(WM_MBUTTONDOWN, nFlags, point, FALSE);
}

void CReportCtrlEx2::OnMButtonDblClk(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	_MouseClkMonitor(WM_MBUTTONDBLCLK, nFlags, point, FALSE);
}

void CReportCtrlEx2::OnRButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	_MouseClkMonitor(WM_RBUTTONDOWN, nFlags, point, FALSE);
}

void CReportCtrlEx2::OnRButtonDblClk(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	_MouseClkMonitor(WM_RBUTTONDBLCLK, nFlags, point, FALSE);
}

void CReportCtrlEx2::_MouseClkMonitor(UINT nMsg, UINT nFlags, CPoint point, BOOL bTriggerEdit)
{
	LVHITTESTINFO hti;
	hti.pt = point;
	const int IDX = SubItemHitTest(&hti);
	const BOOL BEFORE = CListCtrl::GetCheck(IDX) > 0;
	const BOOL WAS_EDIT = _IsEditVisible();
	EndItem(TRUE);
	const BOOL WASACTIVE = bTriggerEdit ? ExamItemStates(IDX, RC_ITEM_FOCUSED | RC_ITEM_SELECTED) : FALSE;

	switch (nMsg)
	{
	case WM_LBUTTONDOWN:
		CListCtrl::OnLButtonDown(nFlags, point);
		break;

	case WM_LBUTTONDBLCLK:
		CListCtrl::OnLButtonDblClk(nFlags, point);
		break;

	case WM_MBUTTONDOWN:
		CListCtrl::OnMButtonDown(nFlags, point);
		break;

	case WM_MBUTTONDBLCLK:
		CListCtrl::OnMButtonDblClk(nFlags, point);
		break;

	case WM_RBUTTONDOWN:
		CListCtrl::OnRButtonDown(nFlags, point);
		break;

	case WM_RBUTTONDBLCLK:
		CListCtrl::OnRButtonDblClk(nFlags, point);
		break;

	default:
		break;		
	}
	
	const BOOL STATSCHANGED = _ItemCheckMonitor(IDX, BEFORE, CListCtrl::GetCheck(IDX) > 0, nMsg);

	if (bTriggerEdit && m_bAllowEdit && !STATSCHANGED && !WAS_EDIT && WASACTIVE)
	{
		if (hti.iSubItem == 4 || hti.iSubItem == 5)
		{
			m_bEdit = FALSE;
			StartDateTimeCtrl(IDX, hti.iSubItem);
		}
		else
		{
			m_bEdit = TRUE;
			StartEdit(IDX, hti.iSubItem);
		}
	}
}

BOOL CReportCtrlEx2::StartEdit(int nItem, int nSubItem)
{
	// Get the grid width and height
	if (!m_bAllowEdit || /*!_IsValidIndex(nItem) ||*/ nSubItem < 0 || nSubItem >= GetColumnCount())
		return FALSE;

	if (m_ptEditting.x == nItem && m_ptEditting.y == nSubItem)
		return TRUE;

	EndItem(TRUE);
		
	m_ptEditting.x = nItem;
	m_ptEditting.y = nSubItem;
	SetAllItemStates(RC_ITEM_SELECTED, RC_ITEM_UNSELECTED); // unselect all
	//SetItemStates(m_ptEditting.x, RC_ITEM_SELECTED | RC_ITEM_FOCUSED);

	// determine editbox font and alignment
	const DWORD FMT = _GetHeaderTextFormat(nSubItem);
	if (FMT != m_dwPrevEditFmt)
	{
		m_dwPrevEditFmt = FMT;

		// Funny thing:
		// Changing CEdit style among ES_LEFT, ES_CENTER, ES_RIGHT at runtime works
		// sometimes and fails other times. It just cannot guarantee to be succeed.
		// So I decided to destroy and recreate the CEdit every time when the text
		// format changes.
		if (m_pWndEdit->GetSafeHwnd() != NULL)
			m_pWndEdit->DestroyWindow();

		if (!m_pWndEdit->Create(ES_AUTOHSCROLL | ES_NOHIDESEL | WS_CHILD | WS_BORDER | FMT, CRect(0, 0, 1, 1), this, 0))
			return FALSE;
	}
	else
	{
		if (m_pWndEdit->GetSafeHwnd() == NULL
			&& !m_pWndEdit->Create(ES_AUTOHSCROLL | ES_NOHIDESEL | WS_CHILD | WS_BORDER | FMT, CRect(0, 0, 1, 1), this, 0))
		{
			return FALSE;
		}
	}

	m_pWndEdit->SetFont(GetFont());

	CRect rcEdit;
	ListView_GetSubItemRect(GetSafeHwnd(), m_ptEditting.x, m_ptEditting.y, LVIR_LABEL, &rcEdit);
	if (m_ptEditting.y > 0 && GetImageList() != NULL && GetItemImage(m_ptEditting.x, m_ptEditting.y) >= 0)
		rcEdit.DeflateRect(16, 0, 0, 0);

	// Move the editbox to that grid, obtain text from the grid, display the
	// editbox, and, finally, highlights all text in the editbox and set the
	// windows focus to the editbox.
	m_pWndEdit->MoveWindow(&rcEdit);
	m_pWndEdit->SetWindowText(GetItemText(m_ptEditting.x, m_ptEditting.y));
	m_pWndEdit->ShowWindow(SW_SHOW);
	m_pWndEdit->SetSel(0, -1);
	m_pWndEdit->SetFocus();

	return TRUE;
}

BOOL CReportCtrlEx2::EndEdit(BOOL bCommit)
{
	if (!_IsEditVisible())
		return FALSE;

	CString str;
	m_pWndEdit->GetWindowText(str);
	BOOL bChanged = bCommit && str.Compare(GetItemText(m_ptEditting.x, m_ptEditting.y)) != 0;
	if (bChanged)
	{
		// update the list item
		CListCtrl::SetItemText(m_ptEditting.x, m_ptEditting.y, str);
		_UnsetSortedColumn();
		GetParent()->SendMessage(WM_EDIT_COMMITTED, (WPARAM)m_ptEditting.x, (LPARAM)m_ptEditting.y);
	}
	m_pWndEdit->ShowWindow(SW_HIDE);
	m_ptEditting.x = -1;
	m_ptEditting.y = -1;
	return bChanged;
}

CDateTimeCtrlReport* CReportCtrlEx2::GetDateTimeControl()
{
	return m_pDateTimeCtrlReport;
}

BOOL CReportCtrlEx2::StartDateTimeCtrl(int nItem, int nSubItem)
{
	// Get the grid width and height
	if (!m_bAllowEdit || /*!_IsValidIndex(nItem) ||*/ nSubItem < 0 || nSubItem >= GetColumnCount())
		return FALSE;

	if (m_ptEditting.x == nItem && m_ptEditting.y == nSubItem)
		return TRUE;

	EndItem(TRUE);

	m_ptEditting.x = nItem;
	m_ptEditting.y = nSubItem;
	SetAllItemStates(RC_ITEM_SELECTED, RC_ITEM_UNSELECTED); // unselect all
	//SetItemStates(m_ptEditting.x, RC_ITEM_SELECTED | RC_ITEM_FOCUSED);

	if (m_pDateTimeCtrlReport->GetSafeHwnd() != NULL)
		m_pDateTimeCtrlReport->DestroyWindow();

	CRect rcDateTimeCtrl;
	ListView_GetSubItemRect(GetSafeHwnd(), m_ptEditting.x, m_ptEditting.y, LVIR_BOUNDS, &rcDateTimeCtrl);

	m_pDateTimeCtrlReport->Create(WS_VISIBLE | WS_CHILD | WS_TABSTOP | /*DTS_SHOWNONE |*/ DTS_SHORTDATEFORMAT,
      rcDateTimeCtrl, this, 1006);

	CString strDate = CListCtrl::GetItemText(nItem, nSubItem);
	if (!strDate.IsEmpty())
	{
		int iDay = atoi(strDate.Left(2));
		int iMes = atoi(strDate.Mid(3, 2));
		int iAgno = atoi(strDate.Right(4));
		CTime date(iAgno, iMes, iDay, 0, 0, 0);
		m_pDateTimeCtrlReport->SetTime(&date);
	}
	
	m_pDateTimeCtrlReport->MoveWindow(&rcDateTimeCtrl);
	m_pDateTimeCtrlReport->ShowWindow(SW_SHOW);
	m_pDateTimeCtrlReport->SetFocus();

	return TRUE;
}

BOOL CReportCtrlEx2::EndDateTimeCtrl (BOOL bCommit)
{
	if (!_IsEditVisible())
		return FALSE;

	CString str;
	m_pDateTimeCtrlReport->GetWindowText(str);
	BOOL bChanged = bCommit && str.Compare(GetItemText(m_ptEditting.x, m_ptEditting.y)) != 0;
	if (bChanged)
	{
		// update the list item
		CListCtrl::SetItemText(m_ptEditting.x, m_ptEditting.y, str);
		_UnsetSortedColumn();
		GetParent()->SendMessage(WM_EDIT_COMMITTED, (WPARAM)m_ptEditting.x, (LPARAM)m_ptEditting.y);
	}

	m_pDateTimeCtrlReport->ShowWindow(SW_HIDE);
	m_ptEditting.x = -1;
	m_ptEditting.y = -1;
	return bChanged;
}

BOOL CReportCtrlEx2::EndItem(BOOL bCommit)
{
	BOOL bRes;

	if (m_bEdit)
		bRes = EndEdit(bCommit);
	else
		bRes = EndDateTimeCtrl(bCommit);

	return bRes;
}

void CReportCtrlEx2::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	EndItem(TRUE);

	CWnd::OnHScroll(nSBCode, nPos, pScrollBar);
}


