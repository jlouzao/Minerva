#pragma once
#include "afxwin.h"
#include "Resource.h"
#include "BD.h"
#include "utilidades.h"


// Cuadro de diálogo de CDlgDatosFacturacion

class CDlgDatosFacturacion : public CDialog
{
	DECLARE_DYNAMIC(CDlgDatosFacturacion)

public:
	CDlgDatosFacturacion(CWnd* pParent = NULL);   // Constructor estándar
	virtual ~CDlgDatosFacturacion();
	virtual BOOL OnInitDialog();

	void SetProve(CProve*);
	void SetUpdate(BOOL);
	void SetConexion(CDatabase*);

	void Activa();
	void Desactiva();

	CString BuscaCuentas(CString);
	BOOL ChequeaNumeros(CString cadena);
// Datos del cuadro de diálogo
	enum { IDD = IDD_DATOS_FACTURACION };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // Compatibilidad con DDX o DDV

	DECLARE_MESSAGE_MAP()
public:
	CComboBox m_ctrlIRPF;

	BOOL m_bUpdate;
	CProve *m_rsProve;
	CDatabase *m_db;

	afx_msg void OnBnClickedIrpf1();
	afx_msg void OnBnClickedIrpf2();
	
	CString m_strDto1;
	CString m_strDto2;
	CString m_strDto3;
	CString m_strPronto;
	CString m_strPorcentaje;
	CString m_strRetencion;
	CString m_strCompras;

	CDialogBusqueda m_dlgBusquedaCuentas;

	afx_msg void OnBnClickedBotonRetencion();
	afx_msg void OnBnClickedBotonCompra();
	CString m_strComDes;
	afx_msg void OnEnKillfocusPorcentaje();
	afx_msg void OnEnKillfocusCuenta();
	CEdit m_ctrlPorcentaje;
	CEdit m_ctrlRetencion;
	afx_msg void OnEnKillfocusDesCom1();
	afx_msg void OnEnKillfocusDesCom2();
	afx_msg void OnEnKillfocusDesCom3();
	CEdit m_ctrlDto3;
	CEdit m_ctrlDto2;
	CEdit m_ctrlDto1;
	CEdit m_ctrlPronto;
	afx_msg void OnEnKillfocusProntoPago();
	CString m_strDesRetencion;
	char m_cIrpf;
	BOOL m_bIrpf;
	afx_msg void OnBnClickedOk();
	afx_msg void OnEnKillfocusCompras();
	afx_msg void OnBnClickedCancel();
};
