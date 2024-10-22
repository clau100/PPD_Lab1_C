$param1 = $args[0] # Nume fisier exe
$param2 = $args[1] # No of threads
$param3 = $args[2] # No of runs

# Executare exe in cmd mode
$suma = 0

for ($i = 0; $i -lt $param3; $i++) {
    Write-Output "Rulare" ($i + 1)

    # Execute the executable and capture all output
    $output = cmd /c .\$param1 $param2 2>&1

    # Print the entire output for debugging
    Write-Output $output

    # Assuming the last line of output is the execution time
    $executionTimeString = $output[$output.length - 1]

    # Convert the execution time to a number
    $executionTime = [double]::Parse($executionTimeString)

    # Add to the sum
    $suma += $executionTime
    Write-Output ""
}

$media = $suma / $param3 # Use $param3 instead of $i for average
Write-Output "Timp de executie mediu:" $media

# Creare fisier .csv
if (!(Test-Path outC.csv)) {
    New-Item outC.csv -ItemType File
    # Scrie date in csv
    Set-Content outC.csv 'Tip Matrice,Tip alocare,Nr threads,Timp executie'
}

# Append
Add-Content outC.csv ",,$($args[1]),$($media)"
