#pragma once

#include "resource.h"
#include "afxwin.h"

// Cuadro de diálogo de CDlgGestionUsuarios

class CDlgGestionUsuarios : public CDialog
{
	DECLARE_DYNAMIC(CDlgGestionUsuarios)

public:
	CDlgGestionUsuarios(CWnd* pParent = NULL);   // Constructor estándar
	virtual ~CDlgGestionUsuarios();
	virtual BOOL OnInitDialog();
	void SetConexion(CDatabase *db);

// Datos del cuadro de diálogo
	enum { IDD = IDD_DLG_GESTION_USUARIOS };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // Compatibilidad con DDX o DDV

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedAgregar();
	afx_msg void OnBnClickedEliminar();
	afx_msg void OnBnClickedPassword();
	afx_msg void OnBnClickedCancel();
private:
	CDatabase *m_db;
	CString m_strUsuario;
	int m_iIndex;
	void CargarListaUsuarios();

public:
	CListBox m_lstUsuarios;
	afx_msg void OnLbnSelchangeListUsuarios();
};
