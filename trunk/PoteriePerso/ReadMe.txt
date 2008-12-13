================================================================================
    BIBLIOTHÈQUE MICROSOFT FOUNDATION CLASS : Vue d'ensemble du projet PoteriePerso
===============================================================================

L'Assistant Application a créé cette application PoteriePerso pour  
vous.  Cette application décrit les principes de base de l'utilisation de  
Microsoft Foundation Classes et vous permet de créer votre application.

Ce fichier contient un résumé du contenu de chacun des fichiers qui 
constituent votre application PoteriePerso.

PoteriePerso.vcproj
    Il s'agit du fichier projet principal pour les projets VC++ générés à l'aide 
d'un Assistant Application. 
    Il contient les informations sur la version de Visual C++ qui a généré le 
fichier et  
    des informations sur les plates-formes, configurations et fonctionnalités du 
projet sélectionnées avec 
    l'Assistant Application.

PoteriePerso.h
    Il s'agit du fichier d'en-tête principal de l'application.  Il contient 
d'autres 
    en-têtes de projet spécifiques (y compris Resource.h) et déclare la 
    classe d'application CPoteriePersoApp.

PoteriePerso.cpp
    Il s'agit du fichier source principal de l'application qui contient la 
    classe d'application CPoteriePersoApp.

PoteriePerso.rc
    Il s'agit de la liste de toutes les ressources Microsoft Windows que le 
    programme utilise.  Elle comprend les icônes, les bitmaps et les curseurs 
qui sont stockés 
    dans le sous-répertoire RES.  Ce fichier peut être modifié directement dans 
Microsoft 
    Visual C++. Vos ressources de projet sont dans 1036.

res\PoteriePerso.ico
    Il s'agit d'un fichier icône, qui est utilisé comme icône de l'application.  
Cette 
    icône est incluse par le fichier de ressource principal PoteriePerso.rc.

res\PoteriePerso.rc2
    Ce fichier contient les ressources qui ne sont pas modifiées par Microsoft  
    Visual C++. Vous devez placer toutes les ressources non modifiables par 
    l'éditeur de ressources dans ce fichier.


/////////////////////////////////////////////////////////////////////////////

L'Assistant Application crée une classe de boîte de dialogue :

PoteriePersoDlg.h, PoteriePersoDlg.cpp – la boîte de dialogue
    Ces fichiers contiennent votre classe CPoteriePersoDlg.  Cette classe 
définit 
    le comportement de la boîte de dialogue principale de votre application.  Le 
modèle de boîte de dialogue se trouve 
    dans PoteriePerso.rc et peut être modifié dans Microsoft Visual 
C++.

/////////////////////////////////////////////////////////////////////////////

Prise en charge de l'aide :

hlp\PoteriePerso.hhp
    Ce fichier est un fichier projet d'aide. Il contient les données requises 
    pour compiler les fichiers d'aide dans un fichier .chm.

hlp\PoteriePerso.hhc
    Ce fichier répertorie le contenu du projet d'aide.

hlp\PoteriePerso.hhk
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
    nommé PoteriePerso.pch et un fichier de type précompilé nommé 
Stdafx.obj.

Resource.h
    Il s'agit du ficher d'en-tête standard, qui définit les nouveaux ID de 
ressources.
    Microsoft Visual C++ lit et met à jour ce fichier.

PoteriePerso.manifest
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
