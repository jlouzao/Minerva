#pragma once
#include "afxcmn.h"

#include "resource.h"

// Cuadro de diálogo de CDialogBusqueda

#ifndef __DIALOGBUSQUEDA_H__
#define __DIALOGBUSQUEDA_H__

#define IDD_DLG_BUSQUEDA                50001

class __declspec(dllexport) CDialogBusqueda : public CDialog
{
	DECLARE_DYNAMIC(CDialogBusqueda)

public:

	enum Types
	{
		ARTICULOS =  1,
		FAMILIAS,
		SUBFAMILIAS,
		CUENTAS,
		ALMACEN,
		PROVEEDORES,
		CLIENTES,
		CONCEPTOS,
		IDIOMA, 
		PAIS,
		DIVISAS,
		FPAGCOB,
		DIRENV,
		ZONA,
		RUTRAN,
		SEGURO,
		CENTROS,
		OFERTAS,
		PEDIDOS,
		ALBARANES,
		PEDIDOSCLI,
		COMPRAS,
		ALBCOMPRA,
		PEDIDOSPROVE,
		FACTURAS,
		ALBARANESPEDIDOCLI,
		COBROS,
		ESTADOS,
	};	

	CDialogBusqueda(CWnd* pParent = NULL);   // Constructor estándar
	virtual ~CDialogBusqueda();
	virtual BOOL OnInitDialog();
	void SetConexion(CDatabase *db);
	void SetTipo(int iTipo);
	void SetGestionar(BOOL bGestionar);
	CString GetCodigo();
	CString GetDescripcion();
	void InicializarListas();
	void SetCliente(CString);
	void SetPedido(CString strPedido);
	void SetCodFamilia(CString CodFam);
	void SetFactura(CString strFactura);

	void ReCargaLista();
// Datos del cuadro de diálogo
	enum { IDD = IDD_DLG_BUSQUEDA };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // Compatibilidad con DDX o DDV

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_lstBusqueda;
	
private:
	CDatabase *m_db;
	CStringList m_lstBusquedaPorCod;
	CStringList m_lstBusquedaPorDes;
	CString m_strCodigo;
	CString m_strDescripcion;
	BOOL m_bCodigo;
	int m_iTipo;
	BOOL m_bGestionar;

	CString strCodFamilia;
	CString m_strCliente;
	CString m_strDesCliente;
	CString m_strPedido;
	CString m_strFactura;

	CString strCodigo;

	void CrearListaCodigo();
	void CrearListaDescripcion();

	void CreaListaCodsArticulos();
	void CreaListaDesArticulos();

	void CrearListaCodsFamilias();
	void CrearListaDesFamilias();

	void CrearListaCodsSubFamilias();
	void CrearListaDesSubFamilias();

	void CrearListaCodsCuentas();
	void CrearListaDesCuentas();

	void CrearListaCodsAlmacen();
	void CrearListaDesAlmacen();

	void CrearListaCodsProveedores();
	void CrearListaDesProveedores();

	void CrearListaCodsClientes();
	void CrearListaDesClientes();

	void CrearListaCodsConceptos();
	void CrearListaDesConceptos();

	void CrearListaCodsIdioma();
	void CrearListaDesIdioma();

	void CrearListaCodsPais();
	void CrearListaDesPais();

	void CrearListaCodsDivisas();
	void CrearListaDesDivisas();

	void CrearListaCodsFPagCob();
	void CrearListaDesFPagCob();

	void CrearListaCodsDirEnv();
	void CrearListaDesDirEnv();

	void CrearListaCodsZona();
	void CrearListaDesZona();

	void CrearListaCodsRuTran();
	void CrearListaDesRuTran();

	void CrearListaCodsSeguro();
	void CrearListaDesSeguro();

	void CrearListaCodsCentros();
	void CrearListaDesCentros();

	void CrearListaCodsOfertas();
	void CrearListaDesOfertas();

	void CrearListaCodsPedidos();
	void CrearListaDesPedidos();

	void CrearListaCodsAlbaranes();
	void CrearListaDesAlbaranes();

	void CrearListaCodsPedidosCli();
	void CrearListaDesPedidosCli();

	void CrearListaCodsCompras();
	void CrearListaDesCompras();

	void CrearListaCodsAlbCompra();
	void CrearListaDesAlbCompra();

	void CrearListaCodsPedidosProve();
	void CrearListaDesPedidosProve();

	void CrearListaCodsFacturas();
	void CrearListaDesFacturas();

	void CrearListaCodsAlbaranesPedidoCli();
	void CrearListaDesAlbaranesPedidoCli();

	void CrearListaCodsCobros();
	void CrearListaDesCobros();

	void CrearListaCodsEstados();
	void CrearListaDesEstados();

	void NuevaDirEnv();	void ModificarDirEnv();
	void NuevaIdioma(); void ModificarIdioma();
	void NuevaPais(); void ModificarPais();
	void NuevaFPagCob(); void ModificarFPagCob();
	void NuevaSeguro(); void ModificarSeguro();
	void NuevaCentros(); void ModificarCentros();
	void NuevaConcepto(); void ModificarConcepto();
	void NuevaZona(); void ModificarZona();
	void NuevaRuTran(); void ModificarRuTran();
	void NuevaDivisa(); void ModificarDivisa();

public:
	afx_msg void OnNMDblclkListBusqueda(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedOk();
	afx_msg void OnLvnColumnclickListBusqueda(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedAgregar();
	afx_msg void OnBnClickedModificar();
};

#endif // __DIALOGBUSQUEDA_H__
