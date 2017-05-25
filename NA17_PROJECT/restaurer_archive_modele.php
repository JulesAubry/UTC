<?php
	include("connexion.php");
?>

<!DOCTYPE html>
<html lang="fr">
  <head>
    <meta charset="utf-8">
    <title>Restaurer Archive</title>
  </head>
  <body>

		<a href="index.php">Index</a>
		</br></br></br>

		<?php 
			if(isset($_GET) && isset($_GET['nom']) && isset($_GET['vers']) ){
				$nom = $_GET['nom'];
				$vers = $_GET['vers'];
				
				$insertion = "INSERT INTO modele_scenari VALUES ($nom, '$vers')";
				$queryInsertion = pg_query($connexion,$insertion);
				
				$selectSkinArchive = "SELECT skin FROM modele_scenari_archive WHERE numero_archive = $nom AND version = '$vers'";
				$querySelectSkinArchive = pg_query($connexion, $selectSkinArchive);
				while ($v_Result = pg_fetch_array($querySelectSkinArchive, null, MYSQL_ASSOC)) {
					if($v_Result['skin'] != '') {
						$insertionSkin = "INSERT INTO skin VALUES('{$v_Result['skin']}', $nom, '$vers')"; 
						$queryInsertionSkin = pg_query($connexion, $insertionSkin);
					}
				}
				
				$selectExtensionArchive = "SELECT extension FROM modele_scenari_archive WHERE numero_archive = $nom AND version = '$vers'";
				$querySelectExtensionArchive = pg_query($connexion, $selectExtensionArchive);
				while ($v_Result2 = pg_fetch_array($querySelectExtensionArchive, null, MYSQL_ASSOC)) {
					if($v_Result2['extension'] != '') {
						$insertionExtension = "INSERT INTO extension VALUES('{$v_Result2['extension']}', $nom, '$vers')"; 
						$queryInsertionExtension = pg_query($connexion, $insertionExtension);
					}
				}
				
				$suppressionArchive = "DELETE FROM modele_scenari_archive WHERE numero_archive = $nom AND version = '$vers'";
				$querySuppressionArchive = pg_query($connexion, $suppressionArchive);
				
				echo "Restauration du modele $nom de version $vers effectuee";
			
			}
					
				
		?>
  </body>
</html>
