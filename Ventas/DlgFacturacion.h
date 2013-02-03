#pragma once

#include "resource.h"
#include "utilidades.h"
#include "atltime.h"
#include "atlcomtime.h"
#include "BD.h"


// Cuadro de diálogo de CDlgFacturacion

class CDlgFacturacion : public CDialog
{
	DECLARE_DYNAMIC(CDlgFacturacion)

public:
	CDlgFacturacion(CWnd* pParent = NULL);   // Constructor estándar
	virtual ~CDlgFacturacion();
	virtual BOOL OnInitDialog();
	void SetConexion(CDatabase *db);

// Datos del cuadro de diálogo
	enum { IDD = IDD_DLG_FACTURACION };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // Compatibilidad con DDX o DDV

	DECLARE_MESSAGE_MAP()

private:
	CDatabase *m_db;
	CPedidos m_rsPedidos;

	CDialogBusqueda m_dlgBusquedaClientes;
	CDialogBusqueda m_dlgBusquedaObras;
	CDialogBusqueda m_dlgBusquedaObras2;

	BOOL BuscaCliente();
	BOOL BuscaObra(CString strCliente, CString strObra);
	//void LimpiaVentana(BOOL bLimpiaCuenta);
	void LimpiaObra();
	void LimpiaObra2();
	void BuscaPedidos();

public:
	CString m_strCuenta;
	CString m_strCuenta2;
	CString m_strObra;
	CString m_strObra2;
	CTime m_fecha1;
	CTime m_fecha2;
	afx_msg void OnEnKillfocusEditCuenta();
	afx_msg void OnBnClickedBtnCuenta();
	afx_msg void OnEnKillfocusEditCuenta2();
	afx_msg void OnBnClickedBtnCuenta2();
	afx_msg void OnEnKillfocusEditObra();
	afx_msg void OnBnClickedBtnObra();
	afx_msg void OnEnKillfocusEditObra2();
	afx_msg void OnBnClickedBtnObra2();
	afx_msg void OnBnClickedOk();
};
