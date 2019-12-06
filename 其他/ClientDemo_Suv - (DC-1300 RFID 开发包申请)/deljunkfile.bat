    @echo on
    echo ---del aps/idb/ncp/obj/tmp/pdb/ etc file-------------------------------------------------  
    del /F /S /Q *.sdf *.aps *.idb *.ncp *.obj *.pch *.sbr *.tmp *.pdb *.bsc *.ilk *.ncb *.opt *.manifest *.dep *.tlog *.log *.ipch 
    del .\debug\*.exe

    pause  