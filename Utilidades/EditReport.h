#pragma once

// CEditReport

class CEditReport : public CEdit
{
	DECLARE_DYNAMIC(CEditReport)

public:
	CEditReport();
	virtual ~CEditReport();

protected:

	//{{AFX_MSG(CReportCtrl)
	afx_msg void OnEnKillfocus();
	afx_msg void OnEnSetfocus();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};


