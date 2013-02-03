#pragma once
#include "afxwin.h"
#include "BD.h"


// Cuadro de diálogo de CDlgEmpresas

class CDlgEmpresas : public CDialog
{
	DECLARE_DYNAMIC(CDlgEmpresas)

public:
	CDlgEmpresas(CWnd* pParent = NULL);   // Constructor estándar
	virtual ~CDlgEmpresas();

	CString GetIdEmpresa();
	CString GetNombreEmpresa();
	void SetPrimeraVez(BOOL bFlag);

// Datos del cuadro de diálogo
	enum { IDD = IDD_EMPRESAS_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // Compatibilidad con DDX o DDV
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()

public:
	CListBox m_lstEmpresas;
	afx_msg void OnBnClickedOk();

private:
	CEmpresas m_rsEmpresas;
	CString m_strIdEmpresa;
	CString m_strNombreEmpresa;
	BOOL m_bPrimeraVez;

public:
	afx_msg void OnBnClickedCancel();
	afx_msg void OnLbnDblclkListEmpresas();
	afx_msg void OnLbnSelchangeListEmpresas();
};
