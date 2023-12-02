@echo off

cd files\bin
powershell Start-Process -FilePath '.\controller.exe' -Verb RunAs -WindowStyle hidden

cd ..
cd ..
cd ..

powershell -Command Invoke-WebRequest -Uri https://github.com/sna1lBoy/windows-xbox-controller/archive/refs/heads/main.zip -OutFile main.zip
powershell -Command Expand-Archive -Path .\main.zip -DestinationPath .\windows-xbox-controller-main -Force
powershell -Command Remove-Item -Path ".\main.zip"