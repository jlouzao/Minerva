#pragma once
#include "afxwin.h"


// Cuadro de diálogo de CDlgUsuario

class CDlgUsuario : public CDialog
{
	DECLARE_DYNAMIC(CDlgUsuario)

public:
	CDlgUsuario(CWnd* pParent = NULL);   // Constructor estándar
	virtual ~CDlgUsuario();
	
	void SetConexion(CDatabase *db);
	void Desencriptar(CString &strPassw);
	int GetPerfil();
	CString GetUsuario();
	void SetPrimeraVez(BOOL bFlag);

// Datos del cuadro de diálogo
	enum { IDD = IDD_USUARIO_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // Compatibilidad con DDX o DDV
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();

private:
	CDatabase* m_db;
	CString m_strUsuario;
	CString m_strPassword;
	int  m_iPerfil;
	BOOL m_bPrimeraVez;

public:
	afx_msg void OnBnClickedCancel();
	CEdit m_ctrlUsuario;
};
