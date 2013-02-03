#pragma once

#include "resource.h"

// Cuadro de diálogo de CDlgCambiarPassw

class CDlgCambiarPassw : public CDialog
{
	DECLARE_DYNAMIC(CDlgCambiarPassw)

public:
	CDlgCambiarPassw(CWnd* pParent = NULL);   // Constructor estándar
	virtual ~CDlgCambiarPassw();
	virtual BOOL OnInitDialog();
	void SetConexion(CDatabase *db);
	void SetUsuario(CString strUsuario);

// Datos del cuadro de diálogo
	enum { IDD = IDD_DLG_CAMBIAR_PASSW };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // Compatibilidad con DDX o DDV

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	CString m_strUsuario;
	CString m_strOldPassw;
	CString m_strNewPassw;
	CString m_strNewPassw2;
	
private:
	CDatabase *m_db;	
};
