:: DECtoZSC - Autoconverter Script for full directories
:: By RACCOON for the MEMBRANE project
:: Released under the "I don't give a shit" lisence: I don't give a shit what you do with this, and make no promises about how well it runs.

:: This is supposed to take all .dec files in a directory and run them through the converter...
:: Argument: the directory of the .dec files

echo Converting Files In Directory: %1
echo on

forfiles /p %1  /m *.dec /c "cmd /c echo @file"
forfiles /p %1 /m *.dec /c "cmd /c java -jar %~dp0DECtoZSC-v1.1.jar @file"
forfiles /p %1  /m *.zsc /c "cmd /c echo @file"




