#pragma once

#include "afxwin.h"
#include "Resource.h"
#include "BD.h"
#include "utilidades.h"

// Cuadro de diálogo de CDlgDatosCobro

class CDlgDatosCobro : public CDialog
{
	DECLARE_DYNAMIC(CDlgDatosCobro)

public:
	CDlgDatosCobro(CWnd* pParent = NULL);   // Constructor estándar
	virtual ~CDlgDatosCobro();
	virtual BOOL OnInitDialog();

	void SetCliente(CClientes*);
	void SetUpdate(BOOL);
	void SetConexion(CDatabase*);

	BOOL EncuentraDivisa(CString);
	BOOL EncuentraSeguro(CString);
	BOOL EncuentraCobro(CString);
	BOOL ChequeaNumeros(CString);
// Datos del cuadro de diálogo
	enum { IDD = IDD_DLG_DATOS_COBRO };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // Compatibilidad con DDX o DDV

	DECLARE_MESSAGE_MAP()
public:
	BOOL m_bUpdate;
	CEdit m_ctrlDivisa;
	CString m_strDivisa;
	CEdit m_ctrlCobro;
	CString m_strCobro;
	CString m_strDesDivisa;
	CString m_strDesCobro;
	CString m_strVencimientos;
	CString m_strPrimer;
	CString m_strDiasEntre;
	CString m_strPago1;
	CString m_strPago2;
	CString m_strPago3;
	CString m_strIniDia;
	CString m_strIniMes;
	CString m_strFinDia;
	CString m_strFinMes;
	CString m_strNSeguro;
	CEdit m_ctrlSeguro;
	CString m_strSeguro;
	CString m_strDesSeguro;
	CString m_strRiesgo;
	CString m_strRiesgoAct;
	CString m_strCuenta1;
	CString m_strCuenta2;
	CString m_strCuenta3;
	CString m_strCuenta4;
	CString m_strEntidad;
	CString m_strIBAN;

	afx_msg void OnBnClickedBotonDivisa();
	afx_msg void OnBnClickedBotonFormaCobro();
	afx_msg void OnBnClickedBotonSeguros();
	afx_msg void OnBnClickedOk();
	
	afx_msg void OnEnKillfocusDivisa();
	afx_msg void OnEnKillfocusCobro();
	afx_msg void OnEnKillfocusSeguro();

	CClientes *m_rsCliente;
	CDatabase *m_db;

	CDialogBusqueda m_dlgBusquedaCobro;
	CDialogBusqueda m_dlgBusquedaSeguro;
	CDialogBusqueda m_dlgBusquedaDivisa;
	afx_msg void OnEnKillfocusIniDia();
	CEdit m_ctrlIniDia;
	CEdit m_ctrlIniMes;
	afx_msg void OnEnKillfocusIniMes();
	afx_msg void OnEnKillfocusFinDia();
	CEdit m_ctrlFinDia;
	CEdit m_ctrlFinMes;
	afx_msg void OnEnKillfocusFinMes();
	afx_msg void OnEnKillfocusRiesgo();
	afx_msg void OnEnKillfocusRiesgoAct();
	CEdit m_ctrlRiesgo;
	CEdit m_ctrlRiesgoAct;
};
