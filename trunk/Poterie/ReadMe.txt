================================================================================
    BIBLIOTHÈQUE MICROSOFT FOUNDATION CLASS : Vue d'ensemble du projet Poterie
===============================================================================

L'Assistant Application a créé cette application Poterie pour  
vous.  Cette application décrit les principes de base de l'utilisation de  
Microsoft Foundation Classes et vous permet de créer votre application.

Ce fichier contient un résumé du contenu de chacun des fichiers qui 
constituent votre application Poterie.

Poterie.vcproj
    Il s'agit du fichier projet principal pour les projets VC++ générés à l'aide 
d'un Assistant Application. 
    Il contient les informations sur la version de Visual C++ qui a généré le 
fichier et  
    des informations sur les plates-formes, configurations et fonctionnalités du 
projet sélectionnées avec 
    l'Assistant Application.

Poterie.h
    Il s'agit du fichier d'en-tête principal de l'application.  Il contient 
d'autres 
    en-têtes de projet spécifiques (y compris Resource.h) et déclare la 
    classe d'application CPoterieApp.

Poterie.cpp
    Il s'agit du fichier source principal de l'application qui contient la 
    classe d'application CPoterieApp.

Poterie.rc
    Il s'agit de la liste de toutes les ressources Microsoft Windows que le 
    programme utilise.  Elle comprend les icônes, les bitmaps et les curseurs 
qui sont stockés 
    dans le sous-répertoire RES.  Ce fichier peut être modifié directement dans 
Microsoft 
    Visual C++. Vos ressources de projet sont dans 1036.

res\Poterie.ico
    Il s'agit d'un fichier icône, qui est utilisé comme icône de l'application.  
Cette 
    icône est incluse par le fichier de ressource principal Poterie.rc.

res\Poterie.rc2
    Ce fichier contient les ressources qui ne sont pas modifiées par Microsoft  
    Visual C++. Vous devez placer toutes les ressources non modifiables par 
    l'éditeur de ressources dans ce fichier.

/////////////////////////////////////////////////////////////////////////////

Pour la fenêtre frame principale :
    Le projet comprend une interface MFC standard.

MainFrm.h, MainFrm.cpp
    Ces fichiers contiennent la classe de frame CMainFrame 
dérivée de
    CMDIFrameWnd et qui contrôle toutes les fonctionnalités des frames MDI.

res\Toolbar.bmp
    Ce fichier bitmap sert à créer des images en mosaïque pour la barre 
d'outils.
    La barre d'outils et la barre d'état initiales sont construites dans la 
classe  
CMainFrame. Modifiez cette image de barre d'outils avec 
l'éditeur de ressources et 
    actualisez le tableau IDR_MAINFRAME TOOLBAR dans Poterie.rc 
pour ajouter 
    les boutons de barre d'outils.
/////////////////////////////////////////////////////////////////////////////

Pour la fenêtre frame enfant :

ChildFrm.h, ChildFrm.cpp
    Ces fichiers définissent et implémentent la classe CChildFrame 
    qui prend en charge les fenêtres enfants d'une application MDI.

/////////////////////////////////////////////////////////////////////////////

L'Assistant Application crée un type de document et une vue :

PoterieDoc.h, PoterieDoc.cpp - le document
    Ces fichiers contiennent votre classe CPoterieDoc.  Modifiez ces 
fichiers pour 
    ajouter les données de document spéciales et implémenter l'enregistrement et 
le 
    chargement des fichiers (via CPoterieDoc::Serialize).

PoterieView.h, PoterieView.cpp - la vue du document
    Ces fichiers contiennent votre classe CPoterieView.
    Les objets CPoterieView servent à afficher les objets CPoterieDoc.

res\PoterieDoc.ico
    Il s'agit d'un fichier icône, qui est utilisé comme icône des fenêtres 
enfants MDI 
    pour la classe CPoterieDoc.  Cette icône est incluse par le fichier 
de 
    ressources principal Poterie.rc.



/////////////////////////////////////////////////////////////////////////////

Prise en charge de l'aide :

hlp\Poterie.hhp
    Ce fichier est un fichier projet d'aide. Il contient les données requises 
    pour compiler les fichiers d'aide dans un fichier .chm.

hlp\Poterie.hhc
    Ce fichier répertorie le contenu du projet d'aide.

hlp\Poterie.hhk
    Ce fichier contient un index des rubriques d'aide.

hlp\afxcore.htm
    Ce fichier contient les rubriques d'aide standard relatives aux 
    objets de l'écran et aux commandes MFC standard. Ajoutez à ce fichier vos 
propres rubriques d'aide.

makehtmlhelp.bat
    Ce fichier est utilisé par le système de génération pour compiler les 
fichiers d'aide.

hlp\Images\*.gif
    Il s'agit de fichiers bitmap requis par le fichier des rubriques d'aide 
standard pour 
    les commandes standard de la bibliothèque Microsoft Foundation Class.


/////////////////////////////////////////////////////////////////////////////

Autres fonctionnalités :

Contrôles ActiveX
    L'application comprend la prise en charge des contrôles ActiveX.

/////////////////////////////////////////////////////////////////////////////

Autres fichiers standard :

StdAfx.h, StdAfx.cpp
    Ces fichiers sont utilisés pour générer un fichier d'en-tête précompilé 
(PCH) 
    nommé Poterie.pch et un fichier de type précompilé nommé 
Stdafx.obj.

Resource.h
    Il s'agit du ficher d'en-tête standard, qui définit les nouveaux ID de 
ressources.
    Microsoft Visual C++ lit et met à jour ce fichier.

Poterie.manifest
	Les fichiers manifestes d'application sont utilisés par Windows XP pour 
décrire les dépendances des applications  
	sur des versions spécifiques des assemblys côte à côte. Le chargeur 
utilise ces  
	informations pour charger l'assembly approprié à partir du cache de 
l'assembly ou directement  
	à partir de l'application. Le manifeste de l'application peut être inclus 
pour redistribution  
	comme fichier .manifest externe installé dans le même dossier que 
l'exécutable de l'application  
	ou être inclus dans l'exécutable sous la forme d'une ressource. 
/////////////////////////////////////////////////////////////////////////////

Autres remarques :

L'Assistant Application utilise "TODO:" pour indiquer les parties du code source 
où 
vous devrez ajouter ou modifier du code.

Si votre application utilise les MFC dans une DLL partagée vous devez redistribuer 
les DLL MFC. Si la langue de votre application n'est pas celle du système 
d'exploitation, vous devez également redistribuer le fichier des  ressources 
localisées MFC80XXX.DLL. Pour plus d'informations, consultez la section relative 
à la redistribution des applications Visual C++ dans la documentation MSDN.

/////////////////////////////////////////////////////////////////////////////
