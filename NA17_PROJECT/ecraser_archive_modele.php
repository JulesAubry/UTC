<?php
	include("connexion.php");
?>

<!DOCTYPE html>
<html lang="fr">
  <head>
    <meta charset="utf-8">
    <title>Ecraser archive modèle</title>
  </head>
  <body>

		<a href="index.php">Index</a>
		</br></br></br>

		<?php 
			if(isset($_GET) && isset($_GET['nom']) && isset($_GET['vers']) && isset($_GET['skin']) && isset($_GET['extension'])){
				$nom = $_GET['nom'];
				$vers = $_GET['vers'];
				$skin = $_GET['skin'];
				$extension = $_GET['extension'];
				
				$skinTable = explode(",", $skin);
			    $extensionTable = explode(",", $extension);
				
				$suppressionArchive = "DELETE FROM modele_scenari_archive WHERE numero_archive = $nom AND version = '$vers'";
				$querySuppressionArchive = pg_query($connexion, $suppressionArchive);
				
				$insertion = "INSERT INTO modele_scenari VALUES ($nom, '$vers')";
				$queryInsertion = pg_query($connexion,$insertion);
				
				foreach($skinTable as $valueSkin) {
					$insertionSkin = "INSERT INTO skin VALUES('$valueSkin', $nom, '$vers')"; 
					$queryTestSkin = pg_query($connexion, $insertionSkin);
				}
				foreach($extensionTable as $valueExtension) {
					$insertionExtension = "INSERT INTO extension VALUES('$valueExtension', $nom, '$vers')"; 
					$queryInsertionExtension = pg_query($connexion, $insertionExtension);
				}
				
				echo "Ecrasement effectue !";
			
			}
					
				
		?>
  </body>
</html>