#pragma once
#include "afxcmn.h"

#include "resource.h"
#include "Utilidades.h"
#include "BD.h"

// Cuadro de diálogo de CDlgIntroCobros

class CDlgIntroCobros : public CDialog
{
	DECLARE_DYNAMIC(CDlgIntroCobros)

public:
	CDlgIntroCobros(CWnd* pParent = NULL);   // Constructor estándar
	virtual ~CDlgIntroCobros();
	virtual BOOL OnInitDialog();
	void SetConexion(CDatabase *db);

// Datos del cuadro de diálogo
	enum { IDD = IDD_DLG_INTRO_COBRO };

private:
	CDatabase *m_db;
	CCobros m_rsCobros;

	CDialogBusqueda m_dlgBusquedaCuentas;
	CDialogBusqueda m_dlgBusquedaClientes;
	CDialogBusqueda m_dlgBusquedaFCobro;

	BOOL BuscaCuenta();
	BOOL BuscaCliente();
	BOOL BuscaFCobro();
	void LimpiaVentana();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // Compatibilidad con DDX o DDV

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_lstCobros;
	CString m_strCtaTesoreria;
	CString m_strDesCtaTesoreria;
	CString m_strCliente;
	CString m_strDesCliente;
	CString m_strFCobro;
	CString m_strDesFCobro;
	afx_msg void OnEnKillfocusEditCtaTesoreria();
	afx_msg void OnBnClickedBtnCtaTesoreria();
	afx_msg void OnEnKillfocusEditCliente();
	afx_msg void OnBnClickedBtnCliente();
	afx_msg void OnEnKillfocusEditFcobro();
	afx_msg void OnBnClickedBtnFcobro();
	afx_msg void OnBnClickedBuscar();
	afx_msg void OnBnClickedOk();
	double m_dImporte;
	afx_msg void OnNMClickCobros(NMHDR *pNMHDR, LRESULT *pResult);
};
