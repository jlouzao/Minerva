#pragma once

#include "resource.h"
#include "ReportCtrlEx2.h"
#include "DlgDatosCobro.h"
#include "afxwin.h"

// Cuadro de diálogo de CDlgFactura

class CDlgFactura : public CDialog
{
	DECLARE_DYNAMIC(CDlgFactura)

public:
	CDlgFactura(CWnd* pParent = NULL);   // Constructor estándar
	virtual ~CDlgFactura();
	virtual BOOL OnInitDialog();
	void SetConexion(CDatabase *db);


// Datos del cuadro de diálogo
	enum { IDD = IDD_DLG_FACTURA };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // Compatibilidad con DDX o DDV

	DECLARE_MESSAGE_MAP()


private:
	CDatabase *m_db;
	double m_dTotalBruto;
	double m_dTotalNeto;
	CStringList m_strTipo;
	CStringList m_strTipoAlquiler;
	CFacturas m_rsFactura;
	CCobros m_rsCobro;
	int m_nCobros;
	CArtiFactura m_rsArtiFactura;

	CList <int, int> m_lOldCantidad;
	CList <double, double> m_lOldTarifa;
	CList <double, double> m_lOldDto;

	CDatosCobro m_datosCobro;

	CDialogBusqueda m_dlgBusquedaFacturas;
	CDialogBusqueda m_dlgBusquedaClientes;
	CDialogBusqueda m_dlgBusquedaObras;
	CDialogBusqueda m_dlgBusquedaCentros;
	CDialogBusqueda m_dlgBusquedaCuentas;

	void SoloLectura(BOOL bReadOnly);
	BOOL BuscaFactura();
	void LimpiaVentana(BOOL bLimpiaNumFac = FALSE);

	BOOL BuscaDatosPersonalesCliente();
	void BuscaDescripcionCuenta();
	void LimpiaCliente();

	BOOL BuscaObra();
	void LimpiaObra();

	BOOL BuscaCentro();
	void LimpiaCentro();

	void BuscaArticulosFactura();
	BOOL BuscaCuenta(CString strCuenta, CString &strNomCuenta);

	void CalculaPrecioNeto();

	void CambiaCantidad();
	void CambiaFecha();
	void CambiaTarifa();
	void CambiaDescuento();
	void CompruebaIva();

	BOOL CompruebaNumero(CString strNumero);
	CTime ObtenerFecha(CString strFecha);

	void GuardaFactura();
	void RellenaFactura();
	HRESULT ModificaCobros();

public:
	CString m_strCuenta;
	CString m_strNombre;
	CString m_strDireccion;
	CString m_strNumero;
	CString m_strCP;
	CString m_strPoblacion;
	CString m_strObservaciones;
	CString m_strTelefono;
	CString m_strFax;
	CString m_strTarifa;
	double  m_dDtos1;
	double  m_dDtos2;
	double  m_dDtos3;
	double  m_dProntoPago;
	CString m_strGFacturacion;
	double  m_dRConcedido;
	double  m_dRActual;
	CString m_strObra;
	CString m_strNomObra;
	CString m_strDireccionObra;
	CString m_strPoblacionObra;
	CString m_strCPObra;
	CString m_strRepre;
	CString m_strSubRepre;
	CString m_strNomRepre;
	CString m_strNomSubRepre;
	double m_dComisionRepre;
	double m_dComisionSubRepre;
	CString m_strCentro;
	CString m_strNomCentro;
	CTime m_timeFecha;
	CString m_strReferencia;
	CReportCtrlEx2 m_lstArticulos;
	CString m_strTotalBruto;
	CString m_strTotalNeto;
	CEdit m_cCuenta;
	CEdit m_cObra;
	CEdit m_cRepre;
	CEdit m_cComisionRepre;
	CEdit m_cSubRepre;
	CEdit m_cComisionSubRepre;
	CDateTimeCtrl m_cFecha;
	CEdit m_cCentro;
	CEdit m_cReferencia;
	CEdit m_cAtn;
	CEdit m_cDtos1;
	CEdit m_cProntoPago;
	double m_dIVA;
	CEdit m_cIVA;
	CComboBox m_cmbPedidos;
	CString m_strTipoFac;
	CString m_strPedido;
	CString m_strNumFac;

	afx_msg void OnBnClickedBuscar();
	afx_msg void OnEnKillfocusEditNumfac();
	afx_msg void OnEnKillfocusEditCuenta();
	afx_msg void OnBnClickedBtnCuenta();
	afx_msg void OnEnKillfocusEditObra();
	afx_msg void OnBnClickedBtnObra();
	afx_msg void OnEnKillfocusEditRepre();
	afx_msg void OnBnClickedBtnCuentarepre();
	afx_msg void OnEnKillfocusEditSubrepre();
	afx_msg void OnBnClickedBtnCuentasubrepre();
	afx_msg void OnEnKillfocusEditCentro();
	afx_msg void OnBnClickedBtnCentro();
	afx_msg void OnEnKillfocusEditDescuento1();
	afx_msg void OnEnKillfocusEditProntopago();
	afx_msg void OnEnKillfocusEditIva();
	afx_msg void OnEnKillfocusEditComisionrepre();
	afx_msg void OnEnKillfocusEditComisionsubrepre();
	afx_msg void OnBnClickedDatosCobro();
	afx_msg void OnBnClickedObservaciones();
	afx_msg void OnNMSetfocusListArticulos(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg LRESULT OnEnKillfocusEditlabel(WPARAM, LPARAM lParam);
	afx_msg void OnCbnSelchangeCmbPedidos();
	afx_msg void OnBnClickedOk();
};
