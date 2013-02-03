#pragma once

#include "resource.h"
#include "atltime.h"
#include "afxwin.h"
#include "BD.h"
#include "Utilidades.h"

class __declspec(dllexport) CDlgDireccionEnvio : public CDialog
{
	DECLARE_DYNAMIC(CDlgDireccionEnvio)

public:
	CDlgDireccionEnvio(CWnd* pParent = NULL);   // Constructor estándar
	virtual ~CDlgDireccionEnvio();
	
	virtual BOOL OnInitDialog();

	void BuscarDirEnv();
	BOOL RellenaCampos();
	BOOL ChequeaNumeros(CString);
	void ChequeaPosicion();
	void SetCliente(CString, CString);
	void SetTipo(BOOL);
	void SetObra(CString);
	void SetConexion(CDatabase*);
	void SetCreado(BOOL);
	BOOL GetCreado();
	void Limpia();
	void BuscarUltimoDirEnv();
// Datos del cuadro de diálogo
	enum { IDD = IDD_DLG_DIRECCION_ENVIO };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // Compatibilidad con DDX o DDV

	DECLARE_MESSAGE_MAP()
public:
	CString m_strObra;
	CString m_strNombre;
	CString m_strDireccion;
	CString m_strCP;
	CString m_strPoblacion;
	CString m_strProvincia;
	CString m_strDistancia;
	CString m_strContacto;
	CString m_strTelefono;
	CTime m_FechAlta;
	CTime m_FechBaja;
	CString m_strCliente;
	CString m_strDesCliente;
	BOOL m_bCerrada;
	
	CEdit m_ctrlObra;
	CEdit m_ctrlDistancia;

	CDialogBusqueda m_dlgBusquedaDirEnv;

	BOOL bUpdate;
	BOOL bNuevo;
	BOOL bCreado;

	int iEstado;

	BOOL bBuscado;
	CString strPrimero;
	CString strUltimo;

	CDirEnv m_rsDirEnv;
	CDatabase* m_db;
	
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedLimpiar();
	afx_msg void OnBnClickedBuscar();
	afx_msg void OnEnKillfocusDistancia();
	afx_msg void OnEnKillfocusObra();
	CEdit m_ctrlNombre;
	afx_msg void OnBnClickedIni();
	afx_msg void OnBnClickedAnt();
	afx_msg void OnBnClickedSig();
	afx_msg void OnBnClickedFin();
};
