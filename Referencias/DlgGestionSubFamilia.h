#pragma once

#include "Resource.h"
#include "BD.h"
#include "utilidades.h"
#include "afxwin.h"

// Cuadro de diálogo de CDlgGestionFamilias

class CDlgGestionSubFamilia : public CDialog
{
	DECLARE_DYNAMIC(CDlgGestionSubFamilia)

public:
	CDlgGestionSubFamilia(CWnd* pParent = NULL);   // Constructor estándar
	virtual ~CDlgGestionSubFamilia();
	void SetConexion(CDatabase *db);

	BOOL BuscaRegistro();
	void LimpiarCampos();
	void ChequeaPosicion();
	BOOL ChequeaNumeros(CString );
	void RellenaCampos();
// Datos del cuadro de diálogo
	enum { IDD = IDD_GESTION_SUBFAMILIAS };

private:
	void NuevaFamilia();//para cada vez que se cambie la familia que cargue las subfamilias oportunas

protected:
	BOOL PreTranslateMessage(MSG* pMsg); 
	virtual void DoDataExchange(CDataExchange* pDX);    // Compatibilidad con DDX o DDV


	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()

/**************************************************************************************************************/

public:
	CDatabase *m_db;
	CSubfami m_rsSubFamilia;
	CFamilias m_rsFamilia;
	
	CDialogBusqueda m_dlgBusquedaSubFamilia;	
	CDialogBusqueda m_dlgBusquedaFamilia;

	BOOL bInicial;
	BOOL bUpdate;

	afx_msg void OnBnClickedIni();
	afx_msg void OnBnClickedAnt();
	afx_msg void OnBnClickedSig();
	afx_msg void OnBnClickedFin();
	afx_msg void OnBnClickedNuevo();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedBuscarSubFamilia();
	/* Variables de editbox */
	CString m_strCodSFamilia;
	CString m_strDesSFamilia;
	CString m_strComercial;
	CString m_strCompra;
	/* Variables de control
	CEdit m_ctrlCodSFamilia;
	CBitmapButton m_botonFin;
	CBitmapButton m_botonSig;
	CBitmapButton m_botonAnt;
	CBitmapButton m_botonIni;
	/* para guardar el primer 
	y ultimo registro*/
	CString strPrimero;
	CString strUltimo;

	afx_msg void OnEnKillfocusSFamilia();
	afx_msg void OnBnClickedCancel();

	afx_msg void OnEnKillfocusDescomercial();
	afx_msg void OnEnKillfocusDescompra();
	afx_msg void OnBnClickedBuscarFamilia();
	CString m_strCFamilia;
	CString m_strDFamilia;
	afx_msg void OnEnKillfocusCfamilia();
};