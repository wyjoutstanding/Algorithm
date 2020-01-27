:again
    pdata > data2.txt
    UVa1587_fc.exe < data2.txt > outfc.txt
    UVa1587.exe < data2.txt > out.txt
    fc outfc.txt out.txt
if not errorlevel 1 goto again