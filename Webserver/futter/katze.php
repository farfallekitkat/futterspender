<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <link rel="stylesheet" type="text/css" href="styles/startseite.css">
    <link rel="stylesheet" type="text/css" href="styles/input.css">
    <link rel="stylesheet" type="text/css" href="styles/style.css">

</head>
<body>
    <?php
     //Datenbankverbindung
    $servername = "xxx.xxx.xxx.xxx"; 
    $username = "k84947_iot";
    $dbname = "k84947_iot";
	$dbpassword = "xxx";

    $conn = new mysqli($servername, $username,$dbpassword,$dbname);

    if($conn->connect_error) {
        die("Verbindung fehlgeschlagen: " . $conn -> connect_error);
    }

    if(isset($_POST['catsubmit'])) {
        $catvalue = $_POST['catname'];
        $maxAnzahl = $_POST['anzAusgabe'];
		$UID = $_POST['UID'];
        $sql = "Insert Into katze (CardUID, name, maxFutterausgabe) Values ('$UID','$catvalue', $maxAnzahl)";

        if ($conn->query($sql) == false) {
            echo "Fehler beim Erstellen des Eintrags: " . $conn->error; 
        }
    }


    ?>
    <form id = "catsubmit" method="post">
        <div class = "container2">
            <div class ="centered">
                <div class ="test">
                    <h1>Katzen Daten</h1>
                    <label>Katzenname</label>
                    <input type="text"  required class="search-box" name="catname">
                    <br>
                    <label>Anzahl extra Futterausgabe</label>
                    <input type="number" id="anzAusgabe" required class="search-box" name="anzAusgabe">
                    <br>
					<label>RFID UID</label>
                    <input type="text" id="UID" required class="search-box" name="UID">
                    <br>
                    <input type="submit" name="catsubmit" class="btn-hover color-11"  id="catsubmit"  value="Senden"> 
                    <!−− <input type="button" class="btn-hover color-11" value ="Einträge Anzeigen">
                    <input type="button" class="btn-hover color-11" value ="Zurück" onClick="document.location.href='index.php'">
                </div>
            </div>
        </div>
    </form>
</body>
</html>
