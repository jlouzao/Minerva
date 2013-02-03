#pragma once

// CDateTimeCtrlReport

class CDateTimeCtrlReport : public CDateTimeCtrl
{
	DECLARE_DYNAMIC(CDateTimeCtrlReport)

public:
	CDateTimeCtrlReport();
	virtual ~CDateTimeCtrlReport();

protected:

	//{{AFX_MSG(DateTimeCtrlReport)
	afx_msg void OnNMKillfocus(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMSetfocus(NMHDR *pNMHDR, LRESULT *pResult);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};


