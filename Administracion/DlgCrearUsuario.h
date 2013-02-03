#pragma once

#include "resource.h"
#include "afxwin.h"


// Cuadro de diálogo de CDlgCrearUsuario

class CDlgCrearUsuario : public CDialog
{
	DECLARE_DYNAMIC(CDlgCrearUsuario)

public:
	CDlgCrearUsuario(CWnd* pParent = NULL);   // Constructor estándar
	virtual ~CDlgCrearUsuario();
	virtual BOOL OnInitDialog();
	void SetConexion(CDatabase *db);

// Datos del cuadro de diálogo
	enum { IDD = IDD_DLG_CREAR_USUARIO };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // Compatibilidad con DDX o DDV

	DECLARE_MESSAGE_MAP()

public:
	CString m_strUsuario;
	CString m_strPassword;
	CString m_strPassword2;
	CComboBox m_cmbPerfiles;

private:
	CString m_strPerfil;
	CDatabase *m_db;

private:
	void Encriptar(CString &strPassw);

public:
	afx_msg void OnCbnSelchangeComboPerfil();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedOk();
};
