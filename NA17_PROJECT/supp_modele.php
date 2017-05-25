<?php
	include("connexion.php");
?>

<!DOCTYPE html>
<html lang="fr">
  <head>
    <meta charset="utf-8">
    <title>Suppression modele</title>
  </head>
  <body>

		<a href="index.php">Index</a>
		<br><br><br>

		<?php 
			if(isset($_GET) && isset($_GET['nom']) && isset($_GET['vers'])){
				$nom = $_GET['nom'];
				$vers = $_GET['vers']; 

				$pasDeSkinNiExtension = 0;

				$selectSkin ="SELECT * FROM skin WHERE modele = $nom AND version = '$vers'";
				$querySelectSkin=pg_query($connexion, $selectSkin);
				while ($v_Result = pg_fetch_array($querySelectSkin, null, MYSQL_ASSOC)) {
 					$insertionSkinArchive = "INSERT INTO modele_scenari_archive(numero_archive, version, extension, skin) VALUES($nom, '$vers', NULL, '{$v_Result['n_skin']}')"; 
					$queryInsertionSkinArchive = pg_query($connexion, $insertionSkinArchive);
					$a = 1;
				}
				

				$selectExtension ="SELECT * FROM Extension WHERE modele = $nom AND version = '$vers'";
				$querySelectExtension=pg_query($connexion, $selectExtension);
				while ($v_Result2 = pg_fetch_array($querySelectExtension, null, MYSQL_ASSOC)) {
 					$insertionExtensionArchive = "INSERT INTO modele_scenari_archive(numero_archive, version, extension, skin) VALUES($nom, '$vers', '{$v_Result2['n_extension']}', NULL)"; 
					$queryInsertionExtensionArchive = pg_query($connexion, $insertionExtensionArchive);
					$a = 1;
				}
				
				if($a == 0) {
					$insertionArchive = "INSERT INTO modele_scenari_archive(numero_archive, version, extension, skin) VALUES($nom, '$vers', NULL, NULL)"; 
					$queryInsertionArchive = pg_query($connexion, $insertionArchive);

				}	

				$suppressionUtilise = "DELETE FROM utilise WHERE nom_modele = $nom AND n_vers = '$vers'";
				$querySuppressionUtilise = pg_query($connexion,$suppressionUtilise);

				$suppressionSkin = "DELETE FROM skin WHERE modele = $nom AND version = '$vers'";
				$querySuppressionSkin = pg_query($connexion,$suppressionSkin);

				$suppressionExtension = "DELETE FROM extension WHERE modele = $nom AND version = '$vers'";
				$querySuppressionExtension = pg_query($connexion,$suppressionExtension);

				$suppressionModele = "DELETE FROM modele_scenari WHERE nom_modele = $nom AND n_vers = '$vers'";
				$querySuppressionModele = pg_query($connexion,$suppressionModele);
				
				echo "Suppressions effectuées";
			}
				
		?>
  </body>
</html>

