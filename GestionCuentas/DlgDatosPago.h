#pragma once

#include "BD.h"
#include "utilidades.h"
#include "Resource.h"
#include "afxwin.h"
// Cuadro de diálogo de CDlgDatosPago

class CDlgDatosPago : public CDialog
{
	DECLARE_DYNAMIC(CDlgDatosPago)

public:
	CDlgDatosPago(CWnd* pParent = NULL);   // Constructor estándar
	virtual ~CDlgDatosPago();
	virtual BOOL OnInitDialog();
	
	void SetProve(CProve*);
	void SetConexion(CDatabase*);
	BOOL BuscaDivisa(CString);
	BOOL BuscaBanco(CString);
	BOOL BuscaPago(CString);

// Datos del cuadro de diálogo
	enum { IDD = IDD_DATOS_PAGOS };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // Compatibilidad con DDX o DDV

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBotonDivisa();
	afx_msg void OnBnClickedBotonFormapago();
	afx_msg void OnBnClickedBotonBanco();
	afx_msg void OnBnClickedOk();

	CString m_strDivisa;
	CString m_strFormaPago;
	CString m_strVencimientos;
	CString m_strPrimerVen;
	CString m_strEntre;
	CString m_strDias1;
	CString m_strDias2;
	CString m_strDias3;
	CString m_strBanco;
	//CString m_strCuentaBanco;
	CString m_strEntidad;
	CString m_strIban;
	CString m_strCC1;
	CString m_strCC2;
	CString m_strDC;
	CString m_strCC3;
	CString m_strDesFormaPago;
	CString m_strDesDivisa;

	CDialogBusqueda m_dlgBusquedaDivisas;
	CDialogBusqueda m_dlgBusquedaFormaPago;
	CDialogBusqueda m_dlgBusquedaBanco;

	CProve *m_rsProve;
	CDatabase *m_db;
	
	CString m_strDesBanco;
	afx_msg void OnEnKillfocusDivisa();
	afx_msg void OnEnKillfocusFormapago();
	afx_msg void OnEnKillfocusBanco();
	CEdit m_ctrlDivisa;
	CEdit m_ctrlFormaPago;
	CEdit m_ctrlBanco;
	afx_msg void OnEnChangePrimerVen();
};
