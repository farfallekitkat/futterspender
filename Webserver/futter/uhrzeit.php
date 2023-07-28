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

    if(isset($_POST['uhrzeitsubmit'])) {
        $uhrzeit =$_POST['uhrzeit'];
        $sql = "Insert Into festeausgabe (uhrzeit) Values (TIME('$uhrzeit'))";

        if ($conn->query($sql) == FALSE) {
            echo "Fehler beim Erstellen des Eintrags: " . $conn->error; 
        }
    }

    ?>


    <form id = "catsubmit" method="post">
        <div class = "container2">
            <div class ="centered">
                <div class ="test">
                    <h1>Uhrzeit</h1>
                    <label>Uhrzeit</label>
                    <input type="time"  required class="search-box" id="uhrzeit" name="uhrzeit">
                    <br>
                    <input type="submit" name="uhrzeitsubmit" id="uhrzeitsubmit" value="Senden" class="btn-hover color-11"> 
                    <!−− <input type="button" class="btn-hover color-11" value ="Einträge Anzeigen">
                    <input type="button" class="btn-hover color-11" value ="Zurück" onClick="document.location.href='index.php'">
                </div>
            </div>
        </div>
    </form>
</body>
</html>
