#pragma once
#include "afxwin.h"


// Cuadro de diálogo de CDlgEjercicio

class CDlgEjercicio : public CDialog
{
	DECLARE_DYNAMIC(CDlgEjercicio)

public:
	CDlgEjercicio(CWnd* pParent = NULL);   // Constructor estándar
	virtual ~CDlgEjercicio();
	void SetPrimeraVez(BOOL bFlag);

// Datos del cuadro de diálogo
	enum { IDD = IDD_EJERCICIOS_DIALOG};

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // Compatibilidad con DDX o DDV
	virtual BOOL OnInitDialog();
	
	DECLARE_MESSAGE_MAP()

public:
	CListBox m_lstEjercicios;

private:
	CString m_strIdEmpresa;
	CString m_strEjercicio;
	BOOL m_bPrimeraVez;

public:
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedOk();
	void SetEmpresa(CString strIdEmpresa);
	afx_msg void OnLbnDblclkEjerciciosLista();
	afx_msg void OnLbnSelchangeEjerciciosLista();
};
