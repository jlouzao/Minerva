#pragma once

#include "BD.h"
#include "afxwin.h"

// Cuadro de di�logo de CDlgObservaciones

class CDlgObservaciones : public CDialog
{
	DECLARE_DYNAMIC(CDlgObservaciones)

public:
	CDlgObservaciones(CWnd* pParent = NULL);   // Constructor est�ndar
	virtual ~CDlgObservaciones();
	virtual BOOL OnInitDialog();

	void SetConexion(CDatabase *db);
	void SetObservaciones(CString strObs);
	CString GetObservaciones();
	void SetObsCliente(CString strObsCliente);
	void SetTitulo(CString strTitulo);
	void SetReadOnly();

// Datos del cuadro de di�logo
	enum { IDD = IDD_DLG_OBSERVACIONES };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // Compatibilidad con DDX o DDV

	DECLARE_MESSAGE_MAP()
public:
	CString m_strObs;
	CString m_strObsCliente;
	CString m_strTitulo;

private: 
	CDatabase *m_db;
	BOOL m_bReadOnly;

public:
	afx_msg void OnBnClickedOk();
	CEdit m_cObservaciones;
};
