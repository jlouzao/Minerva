#pragma once

#include "resource.h"
#include "atltime.h"
#include "Utilidades.h"

// Cuadro de diálogo de CDlgInformesCobros

class CDlgInformesCobros : public CDialog
{
	DECLARE_DYNAMIC(CDlgInformesCobros)

public:
	CDlgInformesCobros(CWnd* pParent = NULL);   // Constructor estándar
	virtual ~CDlgInformesCobros();
	virtual BOOL OnInitDialog();
	void SetConexion(CDatabase *db);
	//void SetTipo(int iTipo);

// Datos del cuadro de diálogo
	enum { IDD = IDD_DLG_INFORMES_COBRO };

private:
	CDatabase *m_db;
	int m_iTipo;

	CDialogBusqueda m_dlgBusquedaElementos;
	CDialogBusqueda m_dlgBusquedaClientes;
	CDialogBusqueda m_dlgBusquedaCentros;
	CDialogBusqueda m_dlgBusquedaEstados;

	BOOL BuscaFactura(CString strNumFactura);
	BOOL BuscaCliente(CString strCuenta);
	BOOL BuscaCentro(CString strCentro);
	BOOL BuscaEstado(CString strEstado, CString &strDesEstado);

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // Compatibilidad con DDX o DDV

	DECLARE_MESSAGE_MAP()

public:
	CString m_strElem1;
	CString m_strElem2;
	CString m_strCuenta1;
	CString m_strCuenta2;
	CString m_strCentro1;
	CString m_strCentro2;
	afx_msg void OnBnClickedOk();
	CTime m_fecha1;
	CTime m_fecha2;
	afx_msg void OnEnKillfocusElem1();
	afx_msg void OnBnClickedBtnElem1();
	afx_msg void OnEnKillfocusElem2();
	afx_msg void OnBnClickedBtnElem2();
	afx_msg void OnEnKillfocusCuenta1();
	afx_msg void OnBnClickedBtnCuentas1();
	afx_msg void OnEnKillfocusCuenta2();
	afx_msg void OnBnClickedBtnCuentas2();
	afx_msg void OnEnKillfocusCentro1();
	afx_msg void OnBnClickedBtnCentros1();
	afx_msg void OnEnKillfocusCentro2();
	afx_msg void OnBnClickedBtnCentros2();
	CString m_strEstado1;
	CString m_strEstado2;
	afx_msg void OnEnKillfocusEstado1();
	afx_msg void OnBnClickedBtnCentros3();
	afx_msg void OnEnKillfocusEstado2();
	afx_msg void OnBnClickedBtnCentros4();
	afx_msg void OnBnClickedBtnEstado1();
	afx_msg void OnBnClickedBtnEstado2();
	CString m_strDesEstado1;
	CString m_strDesEstado2;
};
