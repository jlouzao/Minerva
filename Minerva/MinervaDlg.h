// MinervaDlg.h: archivo de encabezado
//

#pragma once

#include "Admin.h"
#include "Referencias.h"
#include "Almacen.h"
#include "GestionCuentas.h"
#include "Ventas.h"
#include "Compras.h"
#include "Cobros.h"

// Cuadro de diálogo de CMinervaDlg
class CMinervaDlg : public CDialog
{
// Construcción
public:
	CMinervaDlg(CWnd* pParent = NULL);	// Constructor estándar
	virtual ~CMinervaDlg();

// Datos del cuadro de diálogo
	enum { IDD = IDD_MINERVA_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// Compatibilidad con DDX/DDV


// Implementación
protected:
	HICON m_hIcon;

	// Funciones de asignación de mensajes generadas
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

// Variables
private:

	CAdministracion m_administracion;
	CReferenciasMngr m_referencias;
	CAlmacenMngr m_almacen;
	CGestionCuentasMng m_gestionCuentas;
	CVentasMngr m_ventas;
	CComprasMngr m_compras;
	CCobrosMngr m_cobros;

	CDatabase m_db;
	CString m_strIdEmpresa;
	CString m_strNombreEmpresa;
	CString m_strUsuario;
	int m_iPerfil;

	void IniciarEmpresa();
	void InicializaConexiones();

public:
	afx_msg void OnAdmCrearusuario();
	afx_msg void OnUtilCambiarempresa();
	afx_msg void OnGestiGesti();
	afx_msg void OnAlmacenRegularizaciones();
	afx_msg void OnGestiGestiFamilia();
	afx_msg void OnGestiGestiSubFamilia();
	afx_msg void OnAlmacenTransferencias();
	afx_msg void OnGestionCuentas();
	afx_msg void OnAlmacenExistenciasPorArticulo();
	afx_msg void OnVentasGestionOfertas();
	afx_msg void OnVentasGestionPedidos();
	afx_msg void OnVentasAceptaOferta();
	afx_msg void OnGestionIdiomas();
	afx_msg void OnGestionPaises();
	afx_msg void OnGestionDivisas();
	afx_msg void OnGestionZonas();
	afx_msg void OnGestionSeguros();
	afx_msg void OnGestionConceptos();
	afx_msg void OnGestionRutrans();
	afx_msg void OnGestionGestiondeformasdepago();
	afx_msg void OnGestionCentros();
	afx_msg void OnVentasGestionAlbaranes();
	//afx_msg void OnComprasGestion();
	//afx_msg void OnComprasAlbaranes();
	afx_msg void OnVentasPrealbaranes();
	afx_msg void OnGestionalbaranesRecepci();
	afx_msg void OnGestiGestioncompra();
	afx_msg void OnGestionalbaranesGestionalbaranes();
	afx_msg void OnVentasAltaObras();
	afx_msg void OnVentasCierreObras();
	afx_msg void OnVentasConsultaObra();
	afx_msg void OnVentasFacturacion();
	afx_msg void OnVentasModificafacturas();
	afx_msg void OnVentasCalendariolaboral();
	afx_msg void OnVentasEmitirOfertas();
	afx_msg void OnVentasEmitirPedidos();
	afx_msg void OnVentasEmitirAlbaranes();
	afx_msg void OnVentasEmitirFacturas();
	afx_msg void OnVentasEmitirFacturasOrigen();
	afx_msg void OnGestionModificacionCobro();
	afx_msg void OnGestionNuevocobro();
	afx_msg void OnCobrosIntroCobros();
	afx_msg void OnRecepciondefacturas();
	afx_msg void OnCobrosRecepAceptos();
	afx_msg void OnCobrosInformes();
};
