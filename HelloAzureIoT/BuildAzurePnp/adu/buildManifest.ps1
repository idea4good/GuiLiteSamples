Set-ExecutionPolicy -ExecutionPolicy RemoteSigned -Scope Process
Import-Module .\AduUpdate.psm1
$compat = New-AduUpdateCompatibility -DeviceManufacturer 'Microsoft' -DeviceModel 'Azure-Percept-DK'
$importManifest = New-AduImportManifest -Provider 'Unknown' -Name 'UnknownName' -Version '2021.101.101.101' `
                                        -UpdateType 'microsoft/swupdate:1' -InstalledCriteria 'installedCriteria' `
                                        -Compatibility $compat -Files 'updatePayload.txt'
$importManifest | Out-File '.\importManifest.json' -Encoding UTF8
