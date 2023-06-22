<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Katzenfutterspender Website</title>
    <link rel="stylesheet" type="text/css" href="style.css">
</head>
<body>

<?php
    //Datenbankverbindung
    $servername = "127.0.0.1"; 
    $username = "root";
    $dbname = "Futterspender";

    $conn = new mysqli($servername, $username,"",$dbname);

    if($conn->connect_error) {
        die("Verbindung fehlgeschlagen: " . $conn -> connect_error);
    }

    echo "Verbindung zur Datenbank hergestellt";

    if(isset($_POST['catsubmit'])) {
        $catvalue = $_POST['catname'];
        $maxAnzahl = $_POST['anzAusgabe'];
        $sql = "Insert Into katze (name, maxFutterausgabe) Values ('$catvalue', $maxAnzahl)";

        if ($conn->query($sql) == TRUE) {
            echo "Neuer Eintrag erstellt"; 
        }else {
            echo "Fehler beim Erstellen des Eintrags: " . $conn->error; 
        }
    }

    if(isset($_POST['uhrzeitsubmit'])) {
        $uhrzeit =$_POST['uhrzeit'];
        $sql = "Insert Into festeausgabe (uhrzeit) Values (TIME('$uhrzeit'))";

        if ($conn->query($sql) == TRUE) {
            echo "Neuer Eintrag erstellt"; 
        }else {
            echo "Fehler beim Erstellen des Eintrags: " . $conn->error; 
        }
    }
?>

<form id = "catsubmit" method="post">
    <div id="container">
        <div id="left-div">
        <h2>Katzen Daten</h2>
        <label>Katzenname</label>
        <input type="text"  id="catname" name="catname">
        <br>
        <label>Anzahl extra Futterausgabe</label>
        <input type="number" id="anzAusgabe" name="anzAusgabe">
        <br>
        <input type="submit" name="catsubmit" id="catsubmit" value="Senden"> 

        </div>
        <div id="right-div">
        <h2>Allgemeine Futterzeiten</h2>
        <label>Uhrzeit zur Futterausgabe eingeben</label>
        <input type="time" placeholder="Uhrzeit eingeben" id="uhrzeit" name="uhrzeit">
        <br>
        <input type="submit" name="uhrzeitsubmit" id="uhrzeitsubmit" value="Senden"> 
        </div>
    </div>
</form>

    
</body>
</html>