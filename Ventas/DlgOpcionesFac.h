#pragma once

#include "resource.h"
#include "atltime.h"
#include "afxwin.h"
#include "BD.h"

// Cuadro de diálogo de CDlgOpcionesFac

class CDlgOpcionesFac : public CDialog
{
	DECLARE_DYNAMIC(CDlgOpcionesFac)

public:
	CDlgOpcionesFac(CWnd* pParent = NULL);   // Constructor estándar
	virtual ~CDlgOpcionesFac();
	virtual BOOL OnInitDialog();
	void SetConexion(CDatabase *db);
	void SetPedidos(CList <CPedidos, CPedidos&> *lPedidos);
	void SetFacturacion(BOOL bFacturacion);
	CTime GetFechaFinAlq();
	int GetContador();

// Datos del cuadro de diálogo
	enum { IDD = IDD_DLG_OPCIONES_FACTURACION };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // Compatibilidad con DDX o DDV

	DECLARE_MESSAGE_MAP()
public:
	CTime m_fechaAsiento;
	CTime m_fechaFinAlq;
	int m_iTipoFac;
	afx_msg void OnBnClickedRbtnContrato();
	afx_msg void OnBnClickedRbtnObra();
	CComboBox m_cmbContadores;

private:
	CDatabase *m_db;
	CList <CPedidos, CPedidos&> *m_lPedidos;
	int m_iContador;
	BOOL m_bFacturacion;

public:
	afx_msg void OnBnClickedOk();
};
