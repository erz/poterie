/** Fichier permettant d'initialiser une console pour les cout/cerr/cin
*/

#include <windows.h>

#include <cstdio>
#include <iostream>

inline void InitializeConsoleStdIO()
{
    // si une console est rattachée au processus, alors il existe des fichiers
    // virtuel CONIN$ et CONOUT$ qui permettent respectivement de lire
    // et d'écrire depuis / dans cette console (voir la doc de CreateFile).

#if _MSC_VER >= 1400 // VC++ 8 
    { 
    // éviter le warning C4996: 'freopen' was declared deprecated 
    // This function or variable may be unsafe. Consider using freopen_s instead. 
    FILE *stream; 
    freopen_s( &stream, "CONIN$", "r", stdin ); 
    freopen_s( &stream, "CONOUT$", "w", stdout ); 
    freopen_s( &stream, "CONOUT$", "w", stderr ); 
    } 
#else 
    std::freopen( "CONIN$", "r", stdin ); 
    std::freopen( "CONOUT$", "w", stdout ); 
    std::freopen( "CONOUT$", "w", stderr ); 
#endif 

    // la ligne suivante synchronise les flux standards C++ (cin, cout, cerr...)
    std::ios_base::sync_with_stdio();    
}