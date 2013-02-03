#pragma once

#include "resource.h"
#include "atltime.h"
#include "BD.h"
#include "Utilidades.h"
#include "afxwin.h"

// Cuadro de diálogo de CDlgAceptaOferta

class CDlgAceptaOferta : public CDialog
{
	DECLARE_DYNAMIC(CDlgAceptaOferta)

public:
	CDlgAceptaOferta(CWnd* pParent = NULL);   // Constructor estándar
	virtual ~CDlgAceptaOferta();
	virtual BOOL OnInitDialog();
	void SetConexion(CDatabase *db);

// Datos del cuadro de diálogo
	enum { IDD = IDD_DLG_ACEPTA_OFERTA };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // Compatibilidad con DDX o DDV

	DECLARE_MESSAGE_MAP()

private: 
	CDatabase *m_db;
	CProforma m_rsProforma;
	CStringList m_lArtiNoDisponible;
	CStringList m_strTiposEstado;
	CDialogBusqueda m_dlgBusquedaOfertas;
	CDialogBusqueda m_dlgBusquedaAlmacen;

	BOOL BuscaNumOferta();
	void RellenaPedido(CPedidos *rsPedidos);
	HRESULT ObtenerArticulos(CArtiProforma *rsArtiProforma);
	void CompruebaArtiDisponible(CArtiProforma *rsArtiProforma);
	void RellenaArtiVenta(CArtiProforma *rsArtiProforma, CArtiVenta *rsArtiVenta);
	void LimpiaVentana();
	BOOL BuscaAlmacen();
	void MuestraAviso();

public:
	CString m_strNumOferta;
	CString m_strEstado;
	CTime m_fechaPedido;
	CString m_strMotivo;
	afx_msg void OnBnClickedBtnOferta();
	int m_iAccion;
	afx_msg void OnBnClickedAceptar();
	afx_msg void OnBnClickedDenegar();
	afx_msg void OnEnKillfocusNumoferta();
	afx_msg void OnBnClickedOk();
	CString m_strAlmacen;
	CString m_strDesAlmacen;
	afx_msg void OnEnKillfocusEditAlmacen();
	afx_msg void OnBnClickedBtnAlmacen();
//	afx_msg void OnNMKillfocusFechaPedido(NMHDR *pNMHDR, LRESULT *pResult);
};
