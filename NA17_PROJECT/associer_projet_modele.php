<?php
	include("connexion.php");
?>

<!DOCTYPE html>
<html lang="fr">
  <head>
    <meta charset="utf-8">
    <title>Association projet - Modele</title>
  </head>
  <body>
  	<a href="index.php">Index</a><br><br>
	<?php
	if(isset($_GET['id'])){ 
		$id = $_GET['id'];
		echo "Associer le projet au modèle : <form method=\"post\" action=\"associer_projet_modele_reel.php\" > <select name=\"projet\">";
		$selectModele = "SELECT * FROM modele_scenari WHERE nom_modele NOT IN (SELECT nom_modele FROM utilise WHERE code = $id)";
		$querySelectModele=pg_query($connexion, $selectModele);        
		while ($v_Result = pg_fetch_array($querySelectModele, null, MYSQL_ASSOC)) {
				$nom = $v_Result['nom_modele'];
				$vers = $v_Result['n_vers'];
				echo "<option value=$nom,$vers,$id>$nom"." version : ".$vers."</option>";
			}
		echo "</select>
				<input type=\"submit\" value=\"ajouter\">
			</form>";
	

	}

	?>
	</body>
  </html>

