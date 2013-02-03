================================================================================
    BIBLIOTECA DE MICROSOFT FOUNDATION CLASS: Minerva Información general del proyecto
===============================================================================

El Asistente para aplicaciones ha creado esta Minerva aplicación para usted. Esta 
aplicación no sólo muestra los conceptos básicos para utilizar Microsoft Foundation Classes,
sino que también es un punto de partida para escribir su aplicación.

Este archivo contiene un resumen de lo que encontrará en cada uno de los archivos que
componen su Minerva aplicación.

Minerva.vcproj
    Este es el archivo de proyecto principal para proyectos de VC++ generados con un Asistente 
    para aplicaciones. Contiene información sobre la versión de Visual C++ que generó el archivo e 
    información acerca de las plataformas, las configuraciones y las características del proyecto
    seleccionadas con el Asistente para aplicaciones.

Minerva.h
    Este es el archivo de encabezado principal para la aplicación. Incluye otros
    encabezados específicos del proyecto (incluyendo Resource.h) y declara la
    clase de la aplicación CMinervaApp.

Minerva.cpp
    Este es el archivo de código fuente principal de la aplicación que contiene la
    clase de la aplicación CMinervaApp.

Minerva.rc
    Esta es una lista de todos los recursos de Microsoft Windows que utiliza
    el programa. Incluye los iconos, mapas de bits y cursores almacenados en el
    subdirectorio RES. Este archivo se puede editar directamente en Microsoft
    Visual C++. Los recursos del proyecto están en 3082.

res\Minerva.ico
    Este es un archivo de icono, que se utiliza como icono de la aplicación. El
    icono está incluido en el archivo de recursos principal Minerva.rc.

res\Minerva.rc2
    Este archivo contiene recursos no editados por Microsoft 
    Visual C++. Debe ubicar todos los recursos no editables por
    el editor de recursos en este archivo.

/////////////////////////////////////////////////////////////////////////////

El Asistente para aplicaciones crea una clase de diálogo:
MinervaDlg.h, MinervaDlg.cpp - cuadro de diálogo
    Estos archivos contienen la clase CMinervaDlg. Esta clase define
    el comportamiento del cuadro de diálogo principal de la aplicación. La plantilla del cuadro
    de diálogo está en Minerva.rc, que se puede editar en Microsoft Visual C++.
/////////////////////////////////////////////////////////////////////////////

Otras características:

Controles ActiveX
    La aplicación admite el uso de los controles ActiveX.
/////////////////////////////////////////////////////////////////////////////
Otros archivos estándar:

StdAfx.h, StdAfx.cpp
    Estos archivos se utilizan para compilar un archivo de encabezado precompilado (PCH)
    denominado Minerva.pch y un archivo de tipos precompilados denominado StdAfx.obj.

Resource.h
    Este es el archivo de encabezado estándar, que define nuevos identificadores de recursos.
    Microsoft Visual C++ lee y actualiza este archivo.

/////////////////////////////////////////////////////////////////////////////

Otras notas:

El Asistente para aplicaciones utiliza "ToDo:" para indicar las partes del código fuente que
debe agregar o personalizar.

Si su aplicación utiliza MFC en un archivo DLL compartido y la aplicación está en un
idioma distinto al idioma actual del sistema operativo, será necesario copiar 
los recursos MFC70XXX.DLL localizados correspondientes del CD-ROM de Microsoft
Visual C++ bajo el directorio Win\System en el directorio del sistema o 
system32 de su equipo y cambiar el nombre a MFCLOC.DLL. ("XXX" corresponde a la 
abreviatura del idioma. Por ejemplo, MFC70DEU.DLL contiene recursos traducidos
al alemán.) Si no realiza esta operación, algunos de los elementos de la interfaz de usuario de
su aplicación permanecerán en el idioma del sistema operativo.

/////////////////////////////////////////////////////////////////////////////
