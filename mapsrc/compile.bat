
:: %%f is a variable - why isn't %%map valid?
for %%f in (*.map) do (
	echo Compiling %%~nf
	..\utils\bbsp.exe %%~nf.bsp
	:: hack - sleep so it can finish writing the file before starting the next process
	sleep 1
	..\utils\bvis.exe %%~nf.bsp
	:: hack - sleep so it can finish writing the file before starting the next process
	sleep 1
	..\utils\brad.exe %%~nf.bsp
	:: hack - sleep so it can finish writing the file before starting the next process
	sleep 1

	xcopy /y %%~nf.bsp ..\sandpit\maps
)

:: clean up the generated files
del *.bsp
del *.lbsp
del *.lin
del *.log
del *.p*
