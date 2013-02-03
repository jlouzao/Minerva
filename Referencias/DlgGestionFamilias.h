#pragma once

#include "Resource.h"
#include "BD.h"
#include "utilidades.h"
#include "afxwin.h"

// Cuadro de diálogo de CDlgGestionFamilias

class CDlgGestionFamilias : public CDialog
{
	DECLARE_DYNAMIC(CDlgGestionFamilias)

public:
	CDlgGestionFamilias(CWnd* pParent = NULL);   // Constructor estándar
	virtual ~CDlgGestionFamilias();
	void SetConexion(CDatabase *db);

	BOOL BuscaRegistro();
	void LimpiarCampos();
	void ChequeaPosicion();
	BOOL ChequeaNumeros(CString);

// Datos del cuadro de diálogo
	enum { IDD = IDD_GESTION_FAMILIAS };

protected:
	BOOL PreTranslateMessage(MSG* pMsg); 
	virtual void DoDataExchange(CDataExchange* pDX);    // Compatibilidad con DDX o DDV

	void RellenaCampos();
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()

/**************************************************************************************************************/

public:
	CDatabase *m_db;
	CFamilias m_rsFamilia;
	
	CDialogBusqueda m_dlgBusquedaFamilia;	
	
	BOOL bInicial;
	BOOL bUpdate;

	afx_msg void OnBnClickedIni();
	afx_msg void OnBnClickedAnt();
	afx_msg void OnBnClickedSig();
	afx_msg void OnBnClickedFin();
	afx_msg void OnBnClickedNuevo();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedBuscarFamilia();
	/* Variables de editbox */
	CString m_strCodFamilia;
	CString m_strDesFamilia;
	CString m_strComercial;
	CString m_strCompra;
	/* Variables de control
	CEdit m_ctrlCodFamilia;
	CBitmapButton m_botonFin;
	CBitmapButton m_botonSig;
	CBitmapButton m_botonAnt;
	CBitmapButton m_botonIni;
	/* para guardar el primer 
	y ultimo registro*/
	CString strPrimero;
	CString strUltimo;
	afx_msg void OnEnKillfocusFamilia();
	afx_msg void OnBnClickedCancel();

	afx_msg void OnEnKillfocusComercial();
	afx_msg void OnEnKillfocusDescompra();

};
