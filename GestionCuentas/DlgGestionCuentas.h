#pragma once

#include "Resource.h"
#include "BD.h"
#include "utilidades.h"
#include "afxwin.h"
#include "DlgProveedores.h"
#include "DlgCliente.h"

// Cuadro de diálogo de CDlgGestionCuentas

class CDlgGestionCuentas : public CDialog
{
	DECLARE_DYNAMIC(CDlgGestionCuentas)

public:
	CDlgGestionCuentas(CWnd* pParent = NULL);   // Constructor estándar
	virtual ~CDlgGestionCuentas();
	void SetConexion(CDatabase *db);

	BOOL BuscaRegistro();
	void LimpiarRegistro();
	void ChequeaPosicion();
// Datos del cuadro de diálogo
	enum { IDD = IDD_GESTION_CUENTAS };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // Compatibilidad con DDX o DDV
	virtual BOOL OnInitDialog();
	void RellenaCampos(CCuentas* rsAux);

	DECLARE_MESSAGE_MAP()
/***************************************************************************************************************/
public:
	BOOL bOp;
	CDatabase *m_db;
	CCuentas m_rsCuentas;
	BOOL bTotalBuscado;//si está buscado en m_TotalFamilia
	BOOL brsBuscado;//si está buscado en m_rsFamilia

	BOOL bUpdate;
	BOOL bInicial;
	CDialogBusqueda m_dlgBusquedaCuenta;	

	afx_msg void OnBnClickedIni();
	afx_msg void OnBnClickedAnt();
	afx_msg void OnBnClickedSig();
	afx_msg void OnBnClickedFin();
	afx_msg void OnBnClickedNuevo();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedBuscarCuentas();
	afx_msg void OnEnKillfocusCuenta();
	/*******************************************/
	CEdit m_ctrlCuenta;
	CString m_strCuenta;
	CString m_strDescripcion;
	/************ Botones de navegación ********/
	CBitmapButton m_botonFin;
	CBitmapButton m_botonSig;
	CBitmapButton m_botonAnt;
	CBitmapButton m_botonIni;
	/* para guardar el primer y ultimo registro*/
	CString strPrimero;
	CString strUltimo;
	/******************************************/

};
