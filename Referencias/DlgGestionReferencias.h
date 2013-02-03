#pragma once

#include "Resource.h"
#include "atltime.h"
#include "afxwin.h"

#include "BD.h"
#include "Utilidades.h"


// Cuadro de diálogo de CDlgGestionReferencias

class CDlgGestionReferencias : public CDialog
{
	DECLARE_DYNAMIC(CDlgGestionReferencias)

public:
	CDlgGestionReferencias(CWnd* pParent = NULL);   // Constructor estándar
	virtual ~CDlgGestionReferencias();
	void SetConexion(CDatabase *db);

// Datos del cuadro de diálogo
	enum { IDD = IDD_DLG_GESTION_REFERENCIAS };

private:
	BOOL PreTranslateMessage(MSG* pMsg); 
	BOOL BuscaArticulo();
	BOOL BuscaRegistro();	//Busca los registros en ARTICULO
	BOOL BuscaFamilia();	//Busca los registros en FAMILIAS
	BOOL BuscaSubFamilia();	//Busca los registros en SUBFAMI
	bool BuscaCuenta(CString,BOOL);	//Busca los registros en CUENTA
	
	void RellenaCampos(CArticulo*);
	void LimpiarArticulo();

	void BuscarArticuloenLista();
	BOOL ChequeaNumeros(CString cadena);


protected:
	HICON m_hIcon;

	virtual void DoDataExchange(CDataExchange* pDX);    // Compatibilidad con DDX o DDV
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	DECLARE_MESSAGE_MAP()

public:
	CString m_strCodReferencia;
	afx_msg void OnBnClickedBusquedaReferencia();
	void LimpiarCampos();
	void ChequeaPosicion();

/***************************** VARIABLES ************************************/
private:
	CDatabase *m_db;
	CArticulo m_rsArticulo;
	CBitmapButton m_botonFin;
	CBitmapButton m_botonSig;
	CBitmapButton m_botonAnt;
	CBitmapButton m_botonIni;
	
	CList <CProveArti, CProveArti&> m_pProve;

public:
	
	CString m_strNombre;
	CString m_strNombreLargo;
	CString m_strDescripcion;
	CString m_strFamilia;
	CString m_strDesFamilia;
	CString m_strSubfami;
	CString m_strDesSubfami;
	CString m_strCuentasventa;
	CString m_strCuentascompra;
	
	CString m_strPuntoVerde;
	CString m_strIVA;
	CString m_strRecargo;
	CString m_strPeso;
	CString m_strMinimo;
	
	CTime m_timeAlta;
	CTime m_timeBaja;
	CString m_chMovAlmacen;
	CString m_chAlquilado;
	CString m_strDesCompras;
	CString m_strDesVentas;

	CComboBox m_ctrlMovAlmacen;
	CComboBox m_ctrlAlquilado;

	CEdit m_ctrlCodReferencia;
	CEdit m_ctrlFam;
	CEdit m_ctrlSubFam;
	CEdit m_ctrlVentas;
	CEdit m_ctrlCompras;

	afx_msg void OnBnClickedBusquedaFamilias();
	afx_msg void OnBnClickedBusquedaSubfamilias();
	afx_msg void OnBnClickedBusquedaCuentasVentas();
	afx_msg void OnBnClickedBusquedaCuentasCompras();
	afx_msg void OnBnClickedTarifasCompras();
	afx_msg void OnBnClickedTarifasVentas();
	afx_msg void OnBnClickedAceptar();
	afx_msg void OnBnClickedNuevo();
	afx_msg void OnBnClickedCancelar();
		
	afx_msg void OnEnKillfocusFamilia();
	afx_msg void OnEnKillfocusSubfamilia();
	afx_msg void OnEnKillfocusCuentasVentas();
	afx_msg void OnEnKillfocusCuentasCompras();
	afx_msg void OnEnKillfocusCodReferencia();
	afx_msg void OnBnClickedProveedores();

	afx_msg void OnBnClickedIni();
	afx_msg void OnBnClickedFin();
	afx_msg void OnBnClickedAnt();
	afx_msg void OnBnClickedSig();

	BOOL bInicial;
	BOOL bUpdate;
	//CArticulo m_TotalArticulos;

	CDialogBusqueda m_dlgBusquedaCuentas;	
	CDialogBusqueda m_dlgBusquedaFamilia;	
	CDialogBusqueda m_dlgBusquedaSubFami;	
	CDialogBusqueda m_dlgBusquedaRef;	

	CString strPrimero;
	CString strUltimo;

	CEdit m_ctrlNombre;
	CEdit m_ctrlNombreLargo;
	CEdit m_ctrlDescripcion;

	//afx_msg void OnEnKillfocusNombre();
	afx_msg void OnEnKillfocusNombreLargo();
	afx_msg void OnEnKillfocusDescripcion();
	afx_msg void OnEnKillfocusPuntoverde();
	afx_msg void OnEnKillfocusIva();
	afx_msg void OnEnKillfocusRecargo();
	afx_msg void OnEnKillfocusPeso();

	CEdit m_ctrlPuntoVerde;
	CEdit m_ctrlIVA;
	CEdit m_ctrlRecargo;
	CEdit m_ctrlPeso;
	afx_msg void OnEnKillfocusNombre();
};

