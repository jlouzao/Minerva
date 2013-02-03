#include "StdAfx.h"
#include ".\facturapedidos.h"
#include "Etiquetas.h"
#include "Utilidades.h"

#define ALQUILER   "S"
#define VENTA      "V"
#define OTROS      "N"
#define ENTREGA    "E"
#define RECOGIDA   "R"

#define MENSUAL        "M"
#define DIA_LABORABLE  "D"
#define DIA_NATURAL    "N"

/******************************************************************************************/
CFacturaPedidos::CFacturaPedidos(void)
{
	m_bPendientes = FALSE;
	m_dTotalBruto = 0;
	m_OldDirEnv.Empty();
	m_OldCliente.Empty();
	m_strOldNumFactura.Empty();
	m_strFacturaIni.Empty();
	m_strFacturaFin.Empty();
}

/******************************************************************************************/
CFacturaPedidos::~CFacturaPedidos(void)
{
}

/******************************************************************************************/
void CFacturaPedidos::SetConexion(CDatabase *db)
{
	m_db = db;
	m_rsFactura.m_pDatabase = m_db;
}

/******************************************************************************************/
void CFacturaPedidos::SetPedidos(CList <CPedidos, CPedidos&> *lPedidos)
{
	m_lPedidos = lPedidos;
}

/******************************************************************************************/
void CFacturaPedidos::SetFinAlq(CTime fechaFinAlq)
{
	m_fechaFinAlq = fechaFinAlq;
}

/******************************************************************************************/
void CFacturaPedidos::SetTipoFac(int iTipoFac)
{
	m_iTipoFac = iTipoFac;
}

/******************************************************************************************/
void CFacturaPedidos::SetContador(int iContador)
{
	m_iContador = iContador;
}

/******************************************************************************************/
CString CFacturaPedidos::GetFacturaIni()
{
	return m_strFacturaIni.Trim();
}

/******************************************************************************************/
CString CFacturaPedidos::GetFacturaFin()
{
	return m_strFacturaFin;
}

/******************************************************************************************/
/*void CFacturaPedidos::FacturaPedidos()
{
	// Se facturan todos los pedidos seleccionados
	for (int i=0; i<m_lPedidos->GetCount(); i++)
	{
		FacturaPedido(&(m_lPedidos->GetAt(m_lPedidos->FindIndex(i))));
	}

	// Se muestra los informes de cada una de las facturas
	if (!m_strFacturaIni.IsEmpty()) // Se comprueba si al menos hay una.
	{
		CDlgInformes dlgInformes;
		dlgInformes.SetDatos(m_db, FACTURA);
		dlgInformes.SetFormula(m_strFacturaIni, m_strFacturaFin);
		dlgInformes.DoModal();
	}
}*/

/******************************************************************************************/
HRESULT CFacturaPedidos::FacturaPedido(CPedidos *Pedido)
{
	HRESULT hErr = S_OK;

	if (!m_db->BeginTrans())
		return -1;

	// Se buscan los albaranes de entrega y se guardan los elementos alquilados. Se marcan
	// los albaranes como facturados.
	hErr = BuscaArtiAlbaranEntrega(Pedido->m_NUMPEDIDO.Trim());

	// Se buscan los albaranes de recogida y se guardan los elementos alquilados. Se marcan
	// los albaranes como facturados.
	if (hErr == S_OK)
		hErr = BuscaArtiAlbaranRecogida(Pedido->m_NUMPEDIDO.Trim());

	// Se calcula los días y la cantidad de los artículos alquilados
	if (hErr == S_OK)
		hErr = PrepararArtiAlquilados(Pedido->m_NUMPEDIDO.Trim());

	// Se crea la factura
	if (hErr == S_OK)
		hErr = GuardaFactura(Pedido);

	if (hErr == S_OK)
	{
		m_db->CommitTrans();

		/*CString strMsg;
		strMsg.Format(IDC_CREADA_FACTURA, m_rsFactura.m_NUMFAC.Trim()); 
		AfxMessageBox(strMsg, MB_ICONINFORMATION);*/
	}
	else
		m_db->Rollback();

	return hErr;
}

/******************************************************************************************/
HRESULT CFacturaPedidos::BuscaArtiAlbaranEntrega(CString strPedido)
{
	HRESULT hErr = S_OK;

	CAlbaran rsAlbaran(m_db);
	CArtiAlbaran rsArtiAlbaran(m_db);
	CArtiPendiente rsArtiPendiente(m_db);
	CArtiEntrega artiEntrega;

	m_lArtiEntrega.RemoveAll();
	lstArtiVenta.RemoveAll();

	rsAlbaran.m_strFilter = "NUMPEDIDO LIKE '" + strPedido + "' AND TIPO = '" + ALB_ENTREGA + "' AND ESTADO = '" + NO_FACTURADO + "'";
	if (!rsAlbaran.Open(CRecordset::dynaset))
	{
		AfxMessageBox(IDC_ERROR_BD);
		return -1;
	}

	while (!rsAlbaran.IsEOF() && hErr == S_OK)
	{		
		// Se buscan los artículos del albarán de entrega que estén alquilados
		rsArtiAlbaran.m_strFilter = "NUMALB LIKE '" + rsAlbaran.m_NUMALB.Trim() + "'";
		if (!rsArtiAlbaran.Open(CRecordset::dynaset))
		{
			AfxMessageBox(IDC_ERROR_BD);
			return -1;
		}

		while (!rsArtiAlbaran.IsEOF())
		{
			if (rsArtiAlbaran.m_ALQUILER == ALQUILER) // Se guarda si es de alquiler
			{
				artiEntrega.m_strArti = rsArtiAlbaran.m_ARTI.Trim();
				artiEntrega.m_strNumAlb = rsArtiAlbaran.m_NUMALB.Trim();
				artiEntrega.m_dCanti = rsArtiAlbaran.m_CANTI;
				artiEntrega.m_strTipoAlq = rsArtiAlbaran.m_TIPOALQ.Trim();
				artiEntrega.m_fechaIniAlq = rsAlbaran.m_FECINIALQ;

				m_lArtiEntrega.AddTail(artiEntrega);
				//m_lArtiEntrega.SetAt(rsArtiAlbaran.m_ARTI.Trim(), artiEntrega);
			}

			// Se guarda el primer albarán donde aparece cada artículo de venta.
			// Si ya está en alguno, no se vuelve a incluir
			if (rsArtiAlbaran.m_ALQUILER == VENTA)
			{
				if ((lstArtiVenta.Find(rsArtiAlbaran.m_ARTI.Trim())) == NULL)
				{
					lstArtiVenta.AddTail(rsArtiAlbaran.m_ARTI.Trim());
					lstArtiVenta.AddTail(rsArtiAlbaran.m_NUMALB.Trim());
				}
			}

			rsArtiAlbaran.MoveNext();
		}

		rsArtiAlbaran.Close();

		rsAlbaran.m_ESTADO = FACTURADO;
		hErr = rsAlbaran.UpdateEstado();

		rsAlbaran.MoveNext();
	}

	rsAlbaran.Close();

	// Se busca también en la tabla de articulos pendientes por si hay alguno
	// del mes pasado que no ha sido devuelto
	if (hErr == S_OK)
	{
		rsArtiPendiente.m_strFilter = "NUMPEDIDO LIKE '" + strPedido + "' AND ESTADO = '" + NO_FACTURADO + "'";
		if (!rsArtiPendiente.Open(CRecordset::dynaset))
		{
			AfxMessageBox(IDC_ERROR_BD);
			return -1;
		}

		while (!rsArtiPendiente.IsEOF() && hErr == S_OK)
		{		
			artiEntrega.m_strArti = rsArtiPendiente.m_ARTI.Trim();
			artiEntrega.m_strNumAlb = rsArtiPendiente.m_NUMALB.Trim();
			artiEntrega.m_dCanti = rsArtiPendiente.m_CANTI;
			artiEntrega.m_strTipoAlq = rsArtiPendiente.m_TIPOALQ.Trim();
			artiEntrega.m_fechaIniAlq =rsArtiPendiente.m_FECINIALQ;

			m_lArtiEntrega.AddTail(artiEntrega);

			rsArtiPendiente.m_ESTADO = FACTURADO;
			hErr = rsArtiPendiente.UpdateEstado();

			rsArtiPendiente.MoveNext();
		}

		rsArtiPendiente.Close();
	}

	return hErr;
}

/******************************************************************************************/
HRESULT CFacturaPedidos::BuscaArtiAlbaranRecogida(CString strPedido)
{
	HRESULT hErr = S_OK;

	CAlbaran rsAlbaran(m_db);
	CArtiAlbaran rsArtiAlbaran(m_db);

	m_lArtiRecogida.RemoveAll();

	rsAlbaran.m_strFilter = "NUMPEDIDO LIKE '" + strPedido + "' AND TIPO = '" + ALB_RECOGIDA + "' AND ESTADO = '" + NO_FACTURADO + "'";
	if (!rsAlbaran.Open(CRecordset::dynaset))
	{
		AfxMessageBox(IDC_ERROR_BD);
		return -1;
	}

	while (!rsAlbaran.IsEOF() && hErr == S_OK)
	{		
		// Se buscan los artículos del albarán de recogida que estén alquilados
		rsArtiAlbaran.m_strFilter = "NUMALB LIKE '" + rsAlbaran.m_NUMALB.Trim() + "'";
		if (!rsArtiAlbaran.Open(CRecordset::dynaset))
		{
			AfxMessageBox(IDC_ERROR_BD);
			return -1;
		}

		while (!rsArtiAlbaran.IsEOF())
		{
			if (rsArtiAlbaran.m_ALQUILER == "S")
			{
				CArtiRecogida artiRecogida;

				artiRecogida.m_strArti = rsArtiAlbaran.m_ARTI.Trim();
				artiRecogida.m_dCanti = rsArtiAlbaran.m_CANTI;
				artiRecogida.m_fechaFinAlq = rsAlbaran.m_FECFINALQ;

				m_lArtiRecogida.AddTail(artiRecogida);
				//m_lArtiRecogida.SetAt(rsArtiAlbaran.m_ARTI.Trim(), artiRecogida);
			}

			rsArtiAlbaran.MoveNext();
		}

		rsArtiAlbaran.Close();

		rsAlbaran.m_ESTADO = FACTURADO;
		hErr = rsAlbaran.UpdateEstado();

		rsAlbaran.MoveNext();
	}

	rsAlbaran.Close();

	return hErr;
}

/******************************************************************************************/
HRESULT CFacturaPedidos::PrepararArtiAlquilados(CString strPedido)
{
	CArtiPendiente rsArtiPendiente(m_db);
	CArtiEntrega artiEntrega;
	CArtiRecogida artiRecogida;
	CArtiFacturado artiFacturado;
	BOOL bEncontrado;
	HRESULT hErr = S_OK;

	CString strArti;
	double dRestante;

	m_lArtiFacturado.RemoveAll();

	for (int i=0; i<m_lArtiRecogida.GetCount(); i++)
	{
		artiRecogida = m_lArtiRecogida.GetAt(m_lArtiRecogida.FindIndex(i));

		dRestante = 0;

		// Se busca en la lista de articulos de entrega para comprobar los días que ha 
		// estado alquilado. Si tengo artículos restantes vuelvo a buscar en la lista
		// de artículos entregados por si el mismo articulo estuviera en otro albarán
		do
		{
			// Si no es la primera vez, los artículos recogidos serán los restantes
			if (dRestante != 0)
				artiRecogida.m_dCanti = dRestante;

			bEncontrado = FALSE;
			for (int j=0; j<m_lArtiEntrega.GetCount() && bEncontrado == FALSE; j++)
			{
				artiEntrega = m_lArtiEntrega.GetAt(m_lArtiEntrega.FindIndex(j));
				if (artiRecogida.m_strArti == artiEntrega.m_strArti)
					bEncontrado = TRUE;
			}

			if (bEncontrado)
			{
				dRestante = artiRecogida.m_dCanti - artiEntrega.m_dCanti;

				if (dRestante >= 0)
					artiFacturado.m_dCanti = artiEntrega.m_dCanti;
				else
					artiFacturado.m_dCanti = artiRecogida.m_dCanti;
					//artiFacturado.m_dCanti = artiEntrega.m_dCanti - artiRecogida.m_dCanti;

				artiFacturado.m_strArti = artiEntrega.m_strArti;
				artiFacturado.m_strNumAlb = artiEntrega.m_strNumAlb;
				artiFacturado.m_fechaIniAlq = artiEntrega.m_fechaIniAlq;
				artiFacturado.m_fechaFinAlq = artiRecogida.m_fechaFinAlq;
				artiFacturado.m_iDiasAlquilado = CalculaDiasAlquiler(artiEntrega.m_fechaIniAlq, artiRecogida.m_fechaFinAlq, artiEntrega.m_strTipoAlq);

				m_lArtiFacturado.AddTail(artiFacturado);

				// Se el restante es mayor que 0 se elimina de la lista de entregados el 
				// elemento que preparamos para facturar
				// Si el restante es menor que 0 es porque de este articulo en este albarán
				// todavía no se ha recogido todo, así que se deja en la lista y se actualiza
				// la cantidad de unidades que quedan pendientes
				if (dRestante >= 0)
					m_lArtiEntrega.RemoveAt(m_lArtiEntrega.FindIndex(j-1));
				else
				{
					artiEntrega.m_dCanti -= artiRecogida.m_dCanti;
					m_lArtiEntrega.SetAt(m_lArtiEntrega.FindIndex(j-1), artiEntrega);
				}
			}
		} while (dRestante > 0 && m_lArtiEntrega.GetCount()>0);	
	}

	// Si queda algún artículo en la lista de entrega es porque quedan articulos pendientes
	// que se facturaran hasta la fecha fin de alquiler que se haya metido
	m_bPendientes = FALSE;
	if (m_lArtiEntrega.GetCount() > 0)
		m_bPendientes = TRUE;

	for (int i=0; i<m_lArtiEntrega.GetCount() && hErr == S_OK; i++)
	{
		artiEntrega = m_lArtiEntrega.GetAt(m_lArtiEntrega.FindIndex(i));

		// Será la fecha que me hayan pasado en el diálogo
		artiFacturado.m_fechaFinAlq = m_fechaFinAlq; 
		artiFacturado.m_iDiasAlquilado = CalculaDiasAlquiler(artiEntrega.m_fechaIniAlq, m_fechaFinAlq, artiEntrega.m_strTipoAlq);

		// Sólo se facturara y se marcara como pendiente y si al menos hau un día de alquiler
		if (artiFacturado.m_iDiasAlquilado > 0)
		{
			artiFacturado.m_strArti = artiEntrega.m_strArti;
			artiFacturado.m_dCanti = artiEntrega.m_dCanti;
			artiFacturado.m_strNumAlb = artiEntrega.m_strNumAlb;
			artiFacturado.m_fechaIniAlq = artiEntrega.m_fechaIniAlq;

			m_lArtiFacturado.AddTail(artiFacturado);		

			// Se incluye en la tabla de articulos pendientes para el mes que viene	
			rsArtiPendiente.m_NUMPEDIDO = strPedido;
			rsArtiPendiente.m_NUMALB = artiEntrega.m_strNumAlb;
			rsArtiPendiente.m_ARTI = artiEntrega.m_strArti;
			rsArtiPendiente.m_CANTI = artiEntrega.m_dCanti;
			rsArtiPendiente.m_FECINIALQ = CalculaDiaSiguiente(m_fechaFinAlq);;
			rsArtiPendiente.m_TIPOALQ = artiEntrega.m_strTipoAlq;
			rsArtiPendiente.m_ESTADO = NO_FACTURADO; 

			hErr = rsArtiPendiente.Insert();
		}
	}

	return hErr;
}

/******************************************************************************************/
int CFacturaPedidos::CalculaDiasAlquiler(CTime fechaIniAlq, CTime fechaFinAlq, CString strTipoAlq)
{
	int iDiasAlquiler = 0;

	if (fechaIniAlq > fechaFinAlq)
		return 0;

	if (strTipoAlq == MENSUAL)
		iDiasAlquiler = CalculaDiasMes(fechaIniAlq.GetMonth(), fechaIniAlq.GetYear());
	else
	{
		CTimeSpan fecha = fechaFinAlq - fechaIniAlq;
		iDiasAlquiler = (int) fecha.GetDays() + 1;

		if (strTipoAlq == DIA_LABORABLE)
		iDiasAlquiler -= CalculaFestivos(fechaIniAlq, fechaFinAlq);
	}
		
	return iDiasAlquiler;
}

/******************************************************************************************/
int CFacturaPedidos::CalculaDiasMes(int iMes, int iAgno)
{
	int iDiasMes = 0;

	// Si es febrero se calcula si es año bisiesto
	if (iMes == 2)
	{
		if (EsAgnoBisiesto(iAgno))
			iDiasMes = 29;
		else
			iDiasMes = 28;
	}
	else
	{	
		if ((iMes < 8 && iMes % 2 == 0) || (iMes > 8 && iMes % 2 != 0))
			iDiasMes = 30;
		else 
			iDiasMes = 31;
	}

	return iDiasMes;
}

/******************************************************************************************/
CTime CFacturaPedidos::CalculaDiaSiguiente(CTime fecha)
{
	CTimeSpan unDia(1, 0, 0, 0);
	CTime fechaSiguiente = fecha + unDia;

	return fechaSiguiente;

	/*int iDia = fecha.GetDay();
	int iMes = fecha.GetMonth();
	int iAgno = fecha.GetYear();

	int iDiasMes = CalculaDiasMes(iMes, iAgno);

	if (iDia < iDiasMes)
		iDia++;
	else
	{
		iDia = 1;

		// Se calcula el mes siguiente
		if (iMes == 12)
		{
			iMes = 1;
			iAgno++;
		}
		else
			iMes++;

	}
	
	CTime fechaSiguiente(iAgno, iMes, iDia, 0, 0, 0);

	return fechaSiguiente;*/
}

/******************************************************************************************/
BOOL CFacturaPedidos::EsAgnoBisiesto(int iAgno)
{
	BOOL bEsBisiesto = FALSE;

	if ((iAgno % 4 == 0) && (iAgno % 100 != 0 || iAgno % 400 == 0))
		bEsBisiesto = TRUE;

	return bEsBisiesto;
}

/******************************************************************************************/
int CFacturaPedidos::CalculaFestivos(CTime fechaIni, CTime fechaFin)
{
	int iDiasFiesta = 0;
	int iDiasFinSemana = 0;
	int iDiaSemanaIni = 0;
	int iDiaSemanaFin = 0;

	// Se calculan los días de fiesta y los fines de semana que hay entre ambas fechas

	// Se calculan los días de fin de semana comprendidos entre esas fechas
	iDiaSemanaIni = fechaIni.GetDayOfWeek();
	iDiaSemanaFin = fechaFin.GetDayOfWeek();

	// Si es domingo se cambia el valor de 1 a 8 para que al hacer las comparaciones
	// quede coherente
	// Lunes (2), Martes (3), Miércoles (4), Jueves (5) , Viernes (6),
	// Sábado (7), Domingo (1->8)

	if (iDiaSemanaIni == 1)
		iDiaSemanaIni = 8;
	if (iDiaSemanaFin == 1)
		iDiaSemanaFin = 8;

	CTimeSpan fecha = fechaFin - fechaIni;
	iDiasFinSemana = (int)fecha.GetDays() / 7; // Hacemos grupos de 7 (semanas)

	if (iDiaSemanaFin < iDiaSemanaIni)
		iDiasFinSemana++;

	iDiasFinSemana *= 2; // Se multiplica por 2 para contar el sábado y el domingo

	if (iDiaSemanaIni == 8) // Si el periodo empieza el domingo, se le resta un día
		iDiasFinSemana -= 1;

	if (iDiaSemanaFin == 7) // Si el periodo acaba en sábado se le suma un día más
		iDiasFinSemana += 1;

	if (iDiaSemanaFin == 8) // Si el periodo acaba en domingo se le suma 2 días más
		iDiasFinSemana += 2;

	// Se buscan los días de fiesta entre esas fechas
	CFestivos rsFestivos(m_db);

	CString strFechaIni = fechaIni.Format("%d/%m/%Y");
	CString strFechaFin = fechaFin.Format("%d/%m/%Y");

	rsFestivos.m_strFilter = "DIA >= '" + strFechaIni + "' AND DIA <= '" + strFechaFin + "'";
	if (!rsFestivos.Open(CRecordset::dynaset))
	{
		AfxMessageBox(IDC_ERROR_BD);
		return 0;
	}

	while (!rsFestivos.IsEOF())
		rsFestivos.MoveNext();

	iDiasFiesta = rsFestivos.GetRecordCount();
	rsFestivos.Close();

	return iDiasFinSemana + iDiasFiesta;
}

/******************************************************************************************/
HRESULT CFacturaPedidos::GuardaFactura(CPedidos *Pedido)
{
	HRESULT hErr = S_OK;

	CConta rsConta(m_db);
	CArtiFactura rsArtiFactura(m_db);
	CArtiFacturado artiFacturado;

	CString strNextNumFactura;

	// Si el pedido ya ha sido facturado, sólo se facturarían los alquileres pendientes.
	// Si no hay ninguno porque ya lo hemos facturado hasta el día de hoy, entonces no 
	// es necesario hacer factura
	if (Pedido->m_ESTADO.Trim() == FACTURADO ||
	   (Pedido->m_ESTADO.Trim() == ALQ_PENDIENTE && m_lArtiFacturado.GetCount() == 0))
		return -1; // Se devuelve -1 para que haga el rollback por si se ha cambiado algo

	// Comprobar si se debe generar factura o se debe incluir en una ya existente. 
	// Si es Factura por Obra, no se debe crear una nueva factura hasta que no cambie
	// la dirección de envío o el cliente (por si hay 2 clientes con las misma dirección de envío)
	if (m_iTipoFac == CONTRATO || (m_iTipoFac == OBRA && (Pedido->m_DIRENV.Trim() != m_OldDirEnv
		|| Pedido->m_CUENTA.Trim() != m_OldCliente)))
	{
		m_OldCliente = Pedido->m_CUENTA.Trim();
		m_OldDirEnv = Pedido->m_DIRENV.Trim();

		// Se crea la factura 
		RellenaFactura(Pedido);

		// Se coge el siguiente número de factura dependiento del contador del que se trate
		if (m_iContador == CONTADOR_A)
			hErr = rsConta.GetNextNumFacturaA(strNextNumFactura);
		if (m_iContador == CONTADOR_B)
			hErr = rsConta.GetNextNumFacturaB(strNextNumFactura);

		if (hErr == S_OK)
		{
			m_rsFactura.m_NUMFAC = strNextNumFactura.Trim();
			hErr = m_rsFactura.Insert();

			// Se inserta el cobro, sin el importe
			if (hErr == S_OK)
				hErr = GuardaCobros(&m_rsFactura, 0);

			// Se actualiza la variable del importe
			m_dTotalBruto = 0;

			if (hErr == S_OK)
			{
				m_strOldNumFactura = strNextNumFactura.Trim();

				if (m_strFacturaIni.IsEmpty())
					m_strFacturaIni = strNextNumFactura.Trim();
				m_strFacturaFin = strNextNumFactura.Trim();
			}
		}
	}
	else
		m_rsFactura.m_NUMFAC = m_strOldNumFactura;

	if (hErr == S_OK)
	{
		// Se crean los artículos de la factura
		// Se buscan los artículos del pedido a facturar
		CArtiVenta rsArtiVenta(m_db);
		rsArtiVenta.m_strFilter = "NUMPEDIDO LIKE '" + Pedido->m_NUMPEDIDO.Trim() + "'";
		if (!rsArtiVenta.Open(CRecordset::dynaset))
		{
			AfxMessageBox(IDC_ERROR_BD);
			return -1;
		}

		while (!rsArtiVenta.IsEOF() && hErr == S_OK)
		{
			LimpiaArtiFactura(&rsArtiFactura);

			// Se le asigna el número de factura
			rsArtiFactura.m_NUMFAC = m_rsFactura.m_NUMFAC;

			RellenaArtiFactura(&rsArtiFactura, &rsArtiVenta);

			// Si no es alquiler y el pedido no está facturado ni con alquileres pendientes, se crea
			// directamente el articulo en la factura, no hace falta hacer ninguna comprobación
			// con los albaranes de entrega y recogida. Si el pedido está en PENDIENTE  es
			// porque se han facturado Ventas, Alquileres del mes anterior Entregas.... pero
			// queda pediente algún alquiler
			if (rsArtiVenta.m_ALQUILER != ALQUILER && Pedido->m_ESTADO.Trim() == NO_FACTURADO)
			{			
				if (rsArtiVenta.m_ALQUILER == VENTA)
				{
					rsArtiFactura.m_CANTI = rsArtiVenta.m_ENVIADOS;

					// Se busca el número de albaran
					POSITION pos;
					if ((pos = lstArtiVenta.Find(rsArtiFactura.m_ARTI.Trim())) != NULL)
					{
						lstArtiVenta.GetNext(pos);
						rsArtiFactura.m_NUMALB = lstArtiVenta.GetAt(pos);
					}
				}

				hErr = rsArtiFactura.Insert();

				if (hErr == S_OK)
					m_dTotalBruto += rsArtiFactura.m_CANTI * rsArtiFactura.m_IMPOARTI * (1 - (rsArtiFactura.m_DTOARTI / 100));
			}
			else if (rsArtiVenta.m_ALQUILER == ALQUILER)
			{
				for(int i=0;i<m_lArtiFacturado.GetCount() && hErr == S_OK; i++)
				{
					artiFacturado = m_lArtiFacturado.GetAt(m_lArtiFacturado.FindIndex(i));
					if (artiFacturado.m_strArti == rsArtiFactura.m_ARTI)
					{
						rsArtiFactura.m_NUMALB = artiFacturado.m_strNumAlb;
						rsArtiFactura.m_CANTI = artiFacturado.m_dCanti;
						rsArtiFactura.m_NDIASALQ = artiFacturado.m_iDiasAlquilado;
						rsArtiFactura.m_FECINIALQ = artiFacturado.m_fechaIniAlq;
						rsArtiFactura.m_FECFINALQ = artiFacturado.m_fechaFinAlq;
						hErr = rsArtiFactura.Insert();

						if (hErr == S_OK)
							m_dTotalBruto += rsArtiFactura.m_CANTI * rsArtiFactura.m_IMPOARTI * (1 - (rsArtiFactura.m_DTOARTI / 100)) * rsArtiFactura.m_NDIASALQ;
					}
				}
			}

			rsArtiVenta.MoveNext();
		}
	}

	// Se actualiza el importe de la factura. Se hace aquí por si es una factura de varios
	// pedidos y se debe ir sumando lo de pedidos anteriores
	if (hErr == S_OK)
	{
		CCobros rsCobros(m_db);
		CString strIndex;

		if (m_rsFactura.m_NCOBROS == 0)
			m_rsFactura.m_NCOBROS = 1;

		// Se mete el importe para cada cobro de la factura por si hubiera varios
		for (int i=0; i<m_rsFactura.m_NCOBROS && hErr == S_OK; i++)
		{
			strIndex.Format("%d", i+1);
			rsCobros.m_NUMEFEC = m_rsFactura.m_NUMFAC.Trim() + "/" + strIndex + "/1";
			rsCobros.m_EUROS = CalculaValorNetoFactura()/m_rsFactura.m_NCOBROS;
			hErr = rsCobros.UpdateImporteCobro();
		}
	}

	// Si queda algo pendiente para el mes siguiente se le pone estado a Pendiente, si no,
	// se da por facturado.
	if (hErr == S_OK)
	{
		if (m_bPendientes)
			Pedido->m_ESTADO = ALQ_PENDIENTE;
		else
			Pedido->m_ESTADO = FACTURADO;

		hErr = Pedido->UpdateEstado();
	}

	
	return hErr;
}

/******************************************************************************************/
void CFacturaPedidos::RellenaFactura(CPedidos *Pedido)
{
	if (m_iTipoFac == CONTRATO)
		m_rsFactura.m_TIPO = POR_CONTRATO;
	else if (m_iTipoFac == OBRA)
		m_rsFactura.m_TIPO = POR_OBRA;

	m_rsFactura.m_NUMPEDIDO = Pedido->m_NUMPEDIDO.Trim();
	m_rsFactura.m_NUMALB = Pedido->m_NUMALB.Trim();
	m_rsFactura.m_CUENTA = Pedido->m_CUENTA.Trim();
	m_rsFactura.m_TARIFA = Pedido->m_TARIFA.Trim();
	m_rsFactura.m_DCTOS = Pedido->m_DCTOS;
	m_rsFactura.m_DCTOS2 = Pedido->m_DCTOS2;
	m_rsFactura.m_DCTOS3 = Pedido->m_DCTOS3;
	m_rsFactura.m_PP = Pedido->m_PP;
	m_rsFactura.m_IVA = Pedido->m_IVA;
	m_rsFactura.m_GRUFAC = Pedido->m_GRUFAC.Trim();
	m_rsFactura.m_DIRENV = Pedido->m_DIRENV.Trim();
	m_rsFactura.m_REPRE = Pedido->m_REPRE.Trim();
	m_rsFactura.m_SUBREP = Pedido->m_SUBREP.Trim();
	m_rsFactura.m_COMISION = Pedido->m_COMISION;
	m_rsFactura.m_COMISION2 = Pedido->m_COMISION2;
	m_rsFactura.m_FECHFAC = CTime::GetCurrentTime();
	//m_rsFactura.m_FECHALB = Pedido->;
	m_rsFactura.m_FECHPED = Pedido->m_FECHPED;
	m_rsFactura.m_CENTRO = Pedido->m_CENTRO.Trim();
	m_rsFactura.m_SREF	= Pedido->m_SREF.Trim();
	m_rsFactura.m_ATENCLI = Pedido->m_ATENCLI.Trim();
	m_rsFactura.m_TELEF1 = Pedido->m_TELEF1.Trim();
	m_rsFactura.m_TELEF2 = Pedido->m_TELEF2.Trim();
	//m_rsFactura.m_OBSFAC = ;
	m_rsFactura.m_FCOBRO =	Pedido->m_FCOBRO.Trim();
	m_rsFactura.m_NCOBROS = Pedido->m_NCOBROS;
	m_rsFactura.m_VTO1 = Pedido->m_VTO1;
	m_rsFactura.m_DVTO = Pedido->m_DVTO;
	m_rsFactura.m_DIA1 = Pedido->m_DIA1;
	m_rsFactura.m_DIA2 = Pedido->m_DIA2;
	m_rsFactura.m_DIA3 = Pedido->m_DIA3;
	m_rsFactura.m_RETENCOM = Pedido->m_RETENCOM;
	m_rsFactura.m_RETENFIS = Pedido->m_RETENFIS;
}

/******************************************************************************************/
void CFacturaPedidos::RellenaArtiFactura(CArtiFactura *rsArtiFactura, CArtiVenta *rsArtiVenta)
{	
	rsArtiFactura->m_NUMPED = rsArtiVenta->m_NUMPEDIDO.Trim();
	rsArtiFactura->m_ARTI = rsArtiVenta->m_ARTI.Trim();
	rsArtiFactura->m_DESARTI = rsArtiVenta->m_DESARTI.Trim();
	rsArtiFactura->m_PESO = rsArtiVenta->m_PESO;
	rsArtiFactura->m_ALQUILER = rsArtiVenta->m_ALQUILER.Trim();
	rsArtiFactura->m_TIPOALQ = rsArtiVenta->m_TIPOALQ.Trim();
	rsArtiFactura->m_CANTI = rsArtiVenta->m_CANTI;
	rsArtiFactura->m_IMPOARTI = rsArtiVenta->m_IMPOARTI;
	rsArtiFactura->m_DTOARTI = rsArtiVenta->m_DTOARTI;
	rsArtiFactura->m_IVARTI = rsArtiVenta->m_IVARTI;
	rsArtiFactura->m_DESARMEMO = rsArtiVenta->m_DESARMEMO.Trim();
}

/******************************************************************************************/
void CFacturaPedidos::LimpiaArtiFactura(CArtiFactura *rsArtiFactura)
{	
	rsArtiFactura->m_NUMFAC.Empty();
	rsArtiFactura->m_NUMALB.Empty();
	rsArtiFactura->m_NUMPED.Empty();
	rsArtiFactura->m_ARTI.Empty();
	rsArtiFactura->m_DESARTI.Empty();
	rsArtiFactura->m_PESO = 0;
	rsArtiFactura->m_ALQUILER.Empty();
	rsArtiFactura->m_TIPOALQ.Empty();
	rsArtiFactura->m_CANTI = 0.;
	rsArtiFactura->m_FECINIALQ = NULL;
	rsArtiFactura->m_FECFINALQ = NULL;
	rsArtiFactura->m_NDIASALQ = 0;
	rsArtiFactura->m_IMPOARTI = 0;
	rsArtiFactura->m_DTOARTI = 0;
	rsArtiFactura->m_IVARTI = 0;
	rsArtiFactura->m_DESARMEMO.Empty();
}

/******************************************************************************************/
HRESULT CFacturaPedidos::GuardaCobros(CFacturas *rsFactura, double dImporte)
{
	HRESULT hErr;	
	hErr = S_OK;

	CCobros rsCobros(m_db);

	if (rsFactura->m_NCOBROS == 0)
		rsFactura->m_NCOBROS = 1;

	// Se crean los diferentes vencimientos
	for (int i=0; i<rsFactura->m_NCOBROS && hErr == S_OK; i++)
	{				
		CString strIndex;
		strIndex.Format("%d", i+1);
		rsCobros.m_NUMEFEC = rsFactura->m_NUMFAC.Trim() + "/" + strIndex + "/1";

		rsCobros.m_NUMFAC = rsFactura->m_NUMFAC.Trim();
		rsCobros.m_FCOBRO = rsFactura->m_FCOBRO.Trim();
		rsCobros.m_CUENTA = rsFactura->m_CUENTA.Trim();
		rsCobros.m_FECHLIBRA = rsFactura->m_FECHFAC;
		rsCobros.m_ESTADO = COBRO_PENDIENTE;
		rsCobros.m_CENTRO = rsFactura->m_CENTRO.Trim();
		rsCobros.m_EUROS = dImporte / rsFactura->m_NCOBROS;

		// Si es la primera vez se utiliza el primer vencimiento, si no, los días
		// entre vencimientos
		if (i == 0)
		{
			CTimeSpan diasVTO1((LONG)rsFactura->m_VTO1, 0, 0, 0);
			rsCobros.m_FECHA = rsFactura->m_FECHFAC + diasVTO1;
		}
		else
		{
			CTimeSpan diasDVTO((LONG)rsFactura->m_DVTO, 0, 0, 0);
			rsCobros.m_FECHA = rsCobros.m_FECHA + diasDVTO;
		}

		hErr = rsCobros.Insert();
	}

	return hErr;
}

/******************************************************************************************/
double CFacturaPedidos::CalculaValorNetoFactura()
{
	double dDtoComercial, dProntoPago, dRetFiscal, dIVA, dTotalNeto;

	dDtoComercial = (m_dTotalBruto * m_rsFactura.m_DCTOS) / 100;
	dProntoPago = (m_dTotalBruto * m_rsFactura.m_PP) / 100;
	dRetFiscal = (m_dTotalBruto * m_rsFactura.m_RETENFIS) / 100;
	dIVA = (m_dTotalBruto * m_rsFactura.m_IVA) / 100;

	dTotalNeto = m_dTotalBruto - dDtoComercial - dProntoPago - dRetFiscal + dIVA;
	
	return dTotalNeto;
}
