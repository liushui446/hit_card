@echo off
set avg=dlpc-swl-shell

if "%1"=="" (
echo ����б�:
dlpc-swl-shell devices 

echo ����ָ���ػ������÷���
echo �ǽ�dlpc-swl-shell���������ǰ���Ϲ����Ż�SN�š���ʹ��SDI����
echo sdi 1 runonce
echo sdi 0 runonce

ping 11.1.1.1 -n 1 -w 1000 > nul
goto :end
)else (
echo �л����:%1
set SWL_USB_IDX=%1

goto args
)


:args
set x=%2
if  not "%x%"==""  (
set avg=%avg% %x%
rem echo %avg%
shift
goto args
) 
echo %avg%
%avg%


:end

