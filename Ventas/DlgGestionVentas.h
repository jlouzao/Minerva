#pragma once
//#include "atlcomtime.h"

#include "resource.h"
//#include "afxcmn.h"

#include "ReportCtrlEx.h"
#include "Utilidades.h"
#include "BD.h"
//#include "afxwin.h"
#include "DlgDatosCobro.h"
#include "afxwin.h"
//#include "afxdtctl.h"


// Cuadro de diálogo de CDlgOfertas

class CDlgGestionVentas : public CDialog
{
	DECLARE_DYNAMIC(CDlgGestionVentas)

public:
	CDlgGestionVentas(CWnd* pParent = NULL);   // Constructor estándar
	virtual ~CDlgGestionVentas();
	virtual BOOL OnInitDialog();
	void SetConexion(CDatabase *db);
	void SetTipo(int iTipo);

// Datos del cuadro de diálogo
	enum { IDD = IDD_DLG_VENTAS };

private:
	CDatabase *m_db;
	int m_iTipo;
	int m_iNumArti;
	BOOL m_bReadOnly;
	BOOL m_bFocusListCtrl;
	BOOL m_bAtenCli;
	BOOL m_bTabAtenCli;
	BOOL m_bNuevo;
	BOOL m_bAlbaranPed;
	CList <int, int> m_lIniCantidad;
	CStringList m_lIniTipo;
	CStringList m_lArtiEliminados;
	CList <int, int> m_lOldCantidad;
	CList <double, double> m_lOldTarifa;
	CList <double, double> m_lOldDto;
	double m_dTotalPeso;
	double m_dTotalBruto;
	CString m_strTitulo;
	CStringList m_lArtiNoDisponible;
	CStringList m_lCodArtiNoDisponible;

	CProforma m_rsProforma;
	CPedidos m_rsPedido;
	CAlbaran m_rsAlbaran;
	CDatosCobro m_datosCobro;

	CStringList m_strTipo;
	CStringList m_strTipoAlquiler;
	CStringList m_strTiposEstado;

	CDialogBusqueda m_dlgBusquedaClientes;
	CDialogBusqueda m_dlgBusquedaObras;
	CDialogBusqueda m_dlgBusquedaCentros;
	CDialogBusqueda m_dlgBusquedaArticulos;
	CDialogBusqueda m_dlgBusquedaCuentas;
	CDialogBusqueda m_dlgBusquedaAlmacen;
	CDialogBusqueda m_dlgBusquedaVentas;

	BOOL PreTranslateMessage(MSG* pMsg);

	BOOL BuscaCliente();
	BOOL BuscaDatosPersonalesCliente();
	void BuscaDescripcionCuenta();
	void LimpiaVentana();

	BOOL BuscaObra();
	void LimpiaObra();

	BOOL BuscaCentro();
	void LimpiaCentro();

	BOOL BuscaCuenta(CString strCuenta, CString &strNomCuenta);
	BOOL BuscaAlmacen();

	void InsertaRegistroVacio();

	void BuscaArticulo(CString strCodArti);
	void ObtenerTarifa(CArticulo *rsArticulo, double &dTarifa, double &dDto);

	void CambiaCantidad();
	void CambiaTarifa();
	void CambiaDescuento();

	void CompruebaIva();
	BOOL CompruebaNumero(CString strNumero);
	void CompruebaArtiDisponible(CString strARTI, int iFila, int iCantidad);
	void CompruebaDisponibilidadArticulos();
	void MuestraAviso();
	void RevisaArtiDisponibles();

	BOOL BuscaOferta(CString strNumOferta);
	void BuscaArticulosProfor(CString strNumOferta);
	HRESULT GuardaOferta();
	void RellenaProforma();
	void LimpiaOferta();
	void SoloLectura();

	BOOL BuscaPedido(CString strNumPedido);
	void BuscaArticulosPedido(CString strNumPedido);
	HRESULT GuardaPedido();
	void RellenaPedido();
	void LimpiaPedido();
	BOOL BuscaAlbaranes(CStringList *strAlbaranes);

	BOOL BuscaAlbaran(CString strNumPedido);
	void BuscaArticulosAlbaran(CString strNumAlbaran);
	HRESULT GuardaAlbaran();
	void RellenaAlbaran();
	void RellenaArtiAlbaran(CArtiAlbaran *rsArtiAlbaran, int iFila);
	void RellenaAlmacen(CAlmacen *rsAlmacen, CInventario *rsInventario, CArtiAlbaran *rsArtiAlbaran, int iFila);
	CString GetTipoMov();
	void LimpiaAlbaran();
	HRESULT EliminaAlbaranes(CStringList *llbaran, CString strAlmacen);
	HRESULT CompruebaCambioTipo();
	BOOL ActualizaAlmacen();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // Compatibilidad con DDX o DDV

	DECLARE_MESSAGE_MAP()

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
	CTime m_timeFecha2;
	CString m_strReferencia;
	CString m_strAtencion;
	CReportCtrlEx m_lstArticulos;
	CString m_strTotalBruto;
	CString m_strTotalPeso;
	afx_msg void OnBnClickedBtnCuenta();
	int m_iTipoNacional;
	afx_msg void OnBnClickedRbExportacion();
	afx_msg void OnBnClickedRbNacional();
	afx_msg void OnEnKillfocusEditCuenta();
	afx_msg void OnBnClickedBtnObra();
	afx_msg void OnEnKillfocusEditObra();
	afx_msg void OnBnClickedBtnCentro();
	afx_msg void OnEnKillfocusEditCentro();
	afx_msg LRESULT OnEnKillfocusEditlabel(WPARAM, LPARAM lParam);

	afx_msg void OnBnClickedBuscar();
	afx_msg void OnNMSetfocusListArticulos(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnEnKillfocusEditAtn();
	afx_msg void OnBnClickedNuevo();
	afx_msg void OnNMClickListArticulos(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedEliminar();
	afx_msg void OnBnClickedDatosCobro();
	afx_msg void OnBnClickedObservaciones();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedModificar();
	afx_msg void OnBnClickedBtnCuentarepre();
	afx_msg void OnEnKillfocusEditRepre();
	afx_msg void OnBnClickedBtnCuentasubrepre();
	afx_msg void OnEnKillfocusEditSubrepre();
	afx_msg void OnEnKillfocusEditComisionrepre();
	afx_msg void OnEnKillfocusEditComisionsubrepre();
	afx_msg void OnEnKillfocusEditTelefono();
	afx_msg void OnEnKillfocusEditFax();
	CString m_strEstado;
	CEdit m_cTelefono;
	CEdit m_cFax;
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
	CString m_strAlmacen;
	CString m_strDesAlmacen;
	afx_msg void OnEnKillfocusEditAlmacen();
	afx_msg void OnBnClickedBtnAlmacen();
	afx_msg void OnBnClickedCheckEmitir1();
	afx_msg void OnBnClickedCheckEmitir2();
	BOOL m_bEmitir1;
	BOOL m_bEmitir2;
	CEdit m_cAlmacen;
	afx_msg void OnEnSetfocusEditAtn();
	CEdit m_cDtos1;
	CEdit m_cProntoPago;
	double m_dIVA;
	afx_msg void OnEnKillfocusEditDescuento1();
	afx_msg void OnEnKillfocusEditProntopago();
	afx_msg void OnEnKillfocusEditIva();
	CEdit m_cIVA;
	BOOL m_bEmitir3;
	afx_msg void OnBnClickedCheckEmitir3();
	CButton m_btnEmitir2;
//	CButton m_btnMovAlmacen;
//	BOOL m_bMovAlmacen;
	afx_msg void OnBnClickedCheckMovAlmacen();
	afx_msg void OnBnClickedRbAndamio();
	int m_iTipoPedido;
	afx_msg void OnBnClickedRbMaquinaria();
};
