#pragma once
//#include "atlcomtime.h"

#include "resource.h"
//#include "afxcmn.h"

#include "Utilidades.h"
#include "BD.h"
#include "afxwin.h"
//#include "afxwin.h"
//#include "atltime.h"
//#include "afxdtctl.h"

#define TITULO_GESTION     "Gestión de compras"
#define TITULO_ALBARANES   "Gestión de albaranes"

#define GESTCOMPRAS    1
#define GESTALBARAN   2

// Cuadro de diálogo de CComprasDlg

class CComprasDlg : public CDialog
{
	DECLARE_DYNAMIC(CComprasDlg)

public:
	CComprasDlg(CWnd* pParent = NULL);   // Constructor estándar
	virtual ~CComprasDlg();
	
	virtual BOOL OnInitDialog();
	void SetConexion(CDatabase *db);
	void SetTipo(int iTipo);
	//void RellenaProveedor();
	void LimpiaCampos();
	BOOL BuscaProveedor();
	BOOL BuscaCentro();
	BOOL BuscaAlmacen();
	BOOL BuscaAlbaranes(CStringList *strAlbaranes);
	BOOL BuscaCompra(CString);
	void BuscaDatosPersonales(CString);
	void LimpiaVentana();
	void GuardaCompra();
	void GuardaAlbaran();
	void RellenaCompra();
	void RellenaAlbaran();
	void SoloLectura();
	void Buscar();
	BOOL BuscaCobro(CString cadena);
	HRESULT EliminaAlbaranes(CStringList *lNumAlbaran, CString strAlmacen);
	/*********FUNCIONES DEL GRID**************/
	void InsertaRegistroVacio();
	BOOL PreTranslateMessage(MSG* pMsg);
	void BuscaArticulosPedido(CString strNumPedido);
	void BuscaArticulo(CString strCodArti);
	LRESULT OnEnKillfocusEditlabel(WPARAM, LPARAM lParam);
	afx_msg void OnNMClickListArticulos(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMSetfocusListArticulos(NMHDR *pNMHDR, LRESULT *pResult);
	void CambiaCantidad();
	void CambiaDescuento();
	void CambiaTarifa();
	void CompruebaIva();
	BOOL CompruebaNumero(CString);
	void BuscarArtiAlb();
// Datos del cuadro de diálogo
	enum { IDD = IDD_COMPRAS_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // Compatibilidad con DDX o DDV

	DECLARE_MESSAGE_MAP()
public:
	double dDtoGeneral;
	BOOL m_bTipo;
	BOOL bAlbaranesBorrados;
	CString m_strProveedor;
	CString m_strDesProveedor;
	CString m_strDireccion;
	CString m_strNumero;
	CString m_strCP;
	CString m_strPoblacion;
	CString m_strObservaciones;
	CString m_strTelefono;
	CString m_strFax;
	CString m_strAlmacen;
	CString m_strDesAlmacen;
	CString m_strCentro;
	CString m_strDesCentro;
	CString m_strFPagCob;
	CString m_strDesFPagCob;
	CString m_strObsped;
	CString m_strReferencia;
	double m_dNPagos;
	double m_dPago;
	double m_dDiaPago1;
	double m_dDiaPago2;
	double m_dDiaPago3;
	CString m_strPP;
	double m_dDiasDescuento;
	//double m_strDescuento1;
	double m_dDescuento2;
	double m_dDescuento3;
	
	CTime m_timeFech;

	CDatabase *m_db;
	CAlbCompra m_rsAlbaranC;
	CCompras m_rsCompras;

	int m_iTipo;
	CString m_strTitulo;
	////////////////////////////////////////////
	CDialogBusqueda m_dlgBusquedaProveedor;
	CDialogBusqueda m_dlgBusquedaAlmacen;
	CDialogBusqueda m_dlgBusquedaCentros;
	CDialogBusqueda m_dlgBusquedaArticulos;
	CDialogBusqueda m_dlgBusquedaFpagcob;
	////////////////////////////////////////////
	afx_msg void OnEnKillfocusAlmacen();
	afx_msg void OnEnKillfocusProveedor();
	afx_msg void OnEnKillfocusCentro();
	afx_msg void OnNMSetfocusFecha(NMHDR *pNMHDR, LRESULT *pResult);
	////////////////////////////////////////////
	afx_msg void OnBnClickedBtnAlmacen();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedModificar();
	afx_msg void OnBnClickedNuevo();
	afx_msg void OnBnClickedEmitir();
	afx_msg void OnBnClickedBtnCuenta();
	afx_msg void OnBnClickedBtnCentro();
	afx_msg void OnBnClickedRecibir();
	afx_msg void OnBnClickedConformar();
	//////////////////////////////////////////
	int m_iNumArti;
	BOOL m_bReadOnly;
	BOOL m_bFocusListCtrl;
	BOOL m_bFecha;
	BOOL m_bTabFecha;
	BOOL m_bNuevo;
	CString m_strTarifa;
	//CList <int, int> m_lIniCantidad;
	CStringList m_lArtiEliminados;
	CList <int, int> m_lOldCantidad;
	CList <double, double> m_lOldTarifa;
	CList <double, double> m_lOldDto;
	///////////////////////////
	BOOL m_bEmitir1;
	BOOL m_bEmitir2;
	BOOL m_bEmitir3;
	//////////////////////////
	CStringList m_lArtiNoDisponible;
	CStringList m_lCodArtiNoDisponible;
	CReportCtrl m_lstArticulos;
	
	CString m_strPedido;
		
	afx_msg void OnBnClickedBuscar();
	afx_msg void OnBnClickedEliminar();
	double m_dTotalBruto;
	CString m_strTotalBruto;
	CEdit m_ctrlProveedor;
	CEdit m_ctrlAlmacen;
	CEdit m_ctrlCentro;
	CEdit m_ctrlObsPed;
	CButton m_ctrlBuscar;
	CEdit m_ctrlReferencia;
	CEdit m_ctrlFPagCob;
	CString m_strDtoGeneral;
	//afx_msg void OnEnKillfocusDtogeneral();
	afx_msg void OnEnKillfocusDescuento1();
	afx_msg void OnBnClickedBtnFpagcob();
	afx_msg void OnEnKillfocusFpagcob();
	CEdit m_ctrlNPagos;
	CEdit m_ctrlPago;
	CEdit m_ctrlDiasDes;
	CEdit m_ctrlDiaPago1;
	CEdit m_ctrlDiaPago3;
	CEdit m_ctrlDiaPago2;
	CEdit m_ctrlDescuento;
	CEdit m_ctrlPP;
	afx_msg void OnEnKillfocusPp();
};
