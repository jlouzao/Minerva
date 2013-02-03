#pragma once

#include "Resource.h"
#include "afxwin.h"
#include "BD.h"
#include "Utilidades.h"
// Cuadro de diálogo de CDlgTarifasVentas

class CDlgTarifasVentas : public CDialog
{
	DECLARE_DYNAMIC(CDlgTarifasVentas)

public:
	CDlgTarifasVentas(CWnd* pParent = NULL);   // Constructor estándar
	virtual ~CDlgTarifasVentas();

	void Seleccionar();
	void Deseleccionar();
	void SetArticulo(CArticulo *articulo);
	void SetConexion(CDatabase *basedatos);
	void RellenaCampos(); //rellena los campos con los datos
	BOOL RellenaDesCuenta();	//busca la descripción de la cuenta de alquiler
	void SetReferencia(CString);	//recoge la referencia para buscar la cuenta
	void TraAlquiler();	//traduce los datos para adaptarlos a los optionbutton 
	char NToLVenta();
	char NToLAlquiler();
	void SetNuevo(BOOL);

	BOOL ChequeaNumeros(CString);
// Datos del cuadro de diálogo
	enum { IDD = IDD_DLG_TARIFAS_VENTAS};

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // Compatibilidad con DDX o DDV
	BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedTipoventa1();
	afx_msg void OnBnClickedTipoventa2();
	afx_msg void OnBnClickedTipoventa3();
	afx_msg void OnBnClickedTipoventa4();
	afx_msg void OnBnClickedTipoventa5();
	int iOpcionVenta;
	afx_msg void OnBnClickedAlquiler1();
	afx_msg void OnBnClickedAlquiler2();
	afx_msg void OnBnClickedAlquiler3();
	

private:
	CArticulo *m_rsArticulo;
	CDatabase *m_db;
	CDialogBusqueda m_dlgBusquedaCuentas;

public:
	BOOL bArtiNuevo;
	CString m_strCodCuenta;
	CString m_strTarifa1;
	CString m_strTarifa2;
	CString m_strTarifa3;
	CString m_strTarifa4;
	CString m_strTarifa5;
	CString m_strTarifa6;
	CString m_strTarifa7;
	CString m_strTarifa8;
	CString m_strTarifa9;
	CString m_strDescuento1;
	CString m_strDescuento2;
	CString m_strDescuento3;
	CString m_strDescuento4;
	CString m_strDescuento5;
	CString m_strDescuento6;
	CString m_strDescuento7;
	CString m_strDescuento8;
	CString m_strDescuento9;
	afx_msg void OnBnClickedCuentaAlquiler();
	CString m_strDesCuenta;
	CString strCodRef;
	int m_iTipoVenta;
	int m_iTipoAlq;
	afx_msg void OnBnClickedOk();
	CEdit m_ctrlCuenta;
	afx_msg void OnEnKillfocusCuenta();
	CEdit m_ctrlTarifa1;
	CEdit m_ctrlTarifa2;
	CEdit m_ctrlTarifa3;
	CEdit m_ctrlTarifa4;
	CEdit m_ctrlTarifa5;
	CEdit m_ctrlTarifa6;
	CEdit m_ctrlTarifa7;
	CEdit m_ctrlTarifa8;
	CEdit m_ctrlTarifa9;
	CEdit m_ctrlDescuento1;
	CEdit m_ctrlDescuento2;
	CEdit m_ctrlDescuento3;
	CEdit m_ctrlDescuento4;
	CEdit m_ctrlDescuento5;
	CEdit m_ctrlDescuento6;
	CEdit m_ctrlDescuento7;
	CEdit m_ctrlDescuento8;
	CEdit m_ctrlDescuento9;
	///////////////////////
	afx_msg void OnEnKillfocusDescuentoa();
	afx_msg void OnEnKillfocusDescuentob();
	afx_msg void OnEnKillfocusDescuentoc();
	afx_msg void OnEnKillfocusDescuentod();
	afx_msg void OnEnKillfocusDescuentoe();
	afx_msg void OnEnKillfocusDescuentof();
	afx_msg void OnEnKillfocusDescuentog();
	afx_msg void OnEnKillfocusDescuentoh();
	afx_msg void OnEnKillfocusDescuentoi();
	///////////////////////////////////////
	afx_msg void OnEnKillfocusTarifaa();
	afx_msg void OnEnKillfocusTarifab();
	afx_msg void OnEnKillfocusTarifac();
	afx_msg void OnEnKillfocusTarifad();
	afx_msg void OnEnKillfocusTarifae();
	afx_msg void OnEnKillfocusTarifaf();
	afx_msg void OnEnKillfocusTarifag();
	afx_msg void OnEnKillfocusTarifah();
	afx_msg void OnEnKillfocusTarifai();
	////////////////////////////////////
	char cTipo;
	char cTipoAlq;
	CString m_strTarVen;
	afx_msg void OnEnKillfocusTarifaVenta();
};