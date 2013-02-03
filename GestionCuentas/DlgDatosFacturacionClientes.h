#pragma once

#include "afxwin.h"
#include "Resource.h"
#include "BD.h"
#include "utilidades.h"

// Cuadro de diálogo de CDlgDatosFacturacionClientes

class CDlgDatosFacturacionClientes : public CDialog
{
	DECLARE_DYNAMIC(CDlgDatosFacturacionClientes)

public:
	CDlgDatosFacturacionClientes(CWnd* pParent = NULL);   // Constructor estándar
	virtual ~CDlgDatosFacturacionClientes();
	virtual BOOL OnInitDialog();

	CString EncuentraCuenta(CString);
	CString EncuentraPais(CString);
	
	BOOL ChequeaNumeros(CString);
	void SetCliente(CClientes*);
	void SetUpdate(BOOL);
	void SetConexion(CDatabase*);

// Datos del cuadro de diálogo
	enum { IDD = IDD_DATOS_FACTURACION_CLIENTES };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // Compatibilidad con DDX o DDV

	DECLARE_MESSAGE_MAP()
public:
	BOOL m_bUpdate;

	CClientes *m_rsCliente;
	CDatabase *m_db;

	CDialogBusqueda m_dlgBusquedaCuenta;
	CDialogBusqueda m_dlgBusquedaPais;

	CComboBox m_comboTarifa;
	CString m_strComercial1;
	CString m_strComercial2;
	CString m_strComercial3;
	CString m_strPronto;
	BOOL m_bFiscal;
	//CString m_strCuentaComercial;
	CString m_strCuentaFiscal;
	CString m_strDesCuentaFiscal;
	//CString m_strDesCuentaComercial;
	CString m_strGrupoFacturacion;
	CString m_strCopias;
	CString m_strAbonar;
	CString m_strNombre;
	CString m_strDireccion;
	CString m_strSG;
	CString m_strNumero;
	CString m_strCP;
	CString m_strPoblacion;
	CString m_strProvincia;
	CString m_strPais;
	CString m_strDesPais;
	CString m_strTarifa;
	BOOL m_bAbonoProx;
	//BOOL m_bComercial;
	CString m_strPorrete;

	afx_msg void OnEnKillfocusCuentaFiscal();
	//afx_msg void OnEnKillfocusCuentaComercial();
	afx_msg void OnEnKillfocusPais();
	afx_msg void OnBnClickedProximaFactura();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedBotonFiscal();
	//afx_msg void OnBnClickedBotonComercial();
	afx_msg void OnBnClickedBotonPais();
	
	CEdit m_ctrlCuentaFiscal;
	CEdit m_ctrlCuentaComercial;
	
	afx_msg void OnEnKillfocusComercial1();
	afx_msg void OnEnKillfocusComercial2();
	afx_msg void OnEnKillfocusComercial3();
	afx_msg void OnEnKillfocusProntopago();
	afx_msg void OnEnKillfocusPorcentajeFiscal();
	afx_msg void OnEnKillfocusAbonar();
	
	CEdit m_ctrlComercial1;
	CEdit m_ctrlComercial2;
	CEdit m_ctrlComercial3;
	CEdit m_ctrlPorrete;
	CEdit m_ctrlPronto;
	CEdit m_ctrlCopias;
	CEdit m_ctrlAbonar;
	CEdit m_ctrlNumero;
	CEdit m_ctrlPais;
	afx_msg void OnBnClickedRfiscal2();
	afx_msg void OnBnClickedRfiscal1();
	afx_msg void OnBnClickedRcomercial1();
	afx_msg void OnBnClickedRcomercial2();
};
