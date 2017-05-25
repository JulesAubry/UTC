<?php
	include("connexion.php");
?>

<!DOCTYPE html>
<html lang="fr">
  <head>
    <meta charset="utf-8">
    <title>Suppression Association Projet - Modele</title>
  </head>
  <body>
  	<a href="index.php">Index</a><br><br>
	<?php
	if(isset($_GET['id']) && isset($_GET['nom']) && isset($_GET['vers']) ){ 
		$id = $_GET['id'];
		$nom = $_GET['nom'];
		$vers= $_GET['vers'];

		$deleteUtilise = "DELETE FROM utilise WHERE nom_modele = $nom AND n_vers = '$vers' AND code = $id";
		$queryDeleteUtilise=pg_query($connexion, $deleteUtilise);    
		echo "Association supprimée";

	}

	?>
	</body>
  </html>
 
