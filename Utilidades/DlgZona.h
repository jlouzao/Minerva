#pragma once
#include "afxwin.h"
#include "BD.h"
#include "resource.h"
#include "Utilidades.h"

// Cuadro de diálogo de CDlgZona

class  __declspec(dllexport)CDlgZona : public CDialog
{
	DECLARE_DYNAMIC(CDlgZona)

public:
	CDlgZona(CWnd* pParent = NULL);   // Constructor estándar
	virtual ~CDlgZona();

	virtual BOOL OnInitDialog();
	void SetConexion(CDatabase *db);
	void SetZona(CString,CString);
	void SetUpdate(BOOL);
	BOOL BuscarZonas();
	BOOL BuscarCuenta();
	void ChequeaPosicion();
	void RellenaCampos();
	void Limpiar();

	afx_msg void OnBnClickedBuscar();
	afx_msg void OnEnKillfocusCuenta();
	afx_msg void OnBnClickedLimpiar();
	afx_msg void OnEnKillfocusCodigo();
	afx_msg void OnBnClickedBuscarcuenta();
// Datos del cuadro de diálogo
	enum { IDD = IDD_DLG_ZONA };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // Compatibilidad con DDX o DDV

	DECLARE_MESSAGE_MAP()

public:
	CString m_strCodigo;
	CString m_strDescripcion;
	CString m_strCuenta;
	CString m_strDesCuenta;

	CString strPrimero;
	CString strUltimo;
	
	int iEstado;
	BOOL bNuevaBusqueda;

	BOOL bUpdate;
	CZona m_rsZona;
	CDialogBusqueda m_dlgBusquedaZona;
	CDialogBusqueda m_dlgBusquedaCuenta;
	CDatabase* m_db;

	/************ Botones de navegación ********/
	CBitmapButton m_botonFin;
	CBitmapButton m_botonSig;
	CBitmapButton m_botonAnt;
	CBitmapButton m_botonIni;

	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedIni();
	afx_msg void OnBnClickedAnt();
	afx_msg void OnBnClickedSig();
	afx_msg void OnBnClickedFin();
};