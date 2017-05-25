<?php
	include("connexion.php");
?>

<!DOCTYPE html>
<html lang="fr">
  <head>
    <meta charset="utf-8">
    <title>Ajout modele</title>
  </head>
  <body>

		<a href="index.php">Index</a>
		<br><br><br>

		<?php 
			if(isset($_POST) && isset($_POST['nom']) && isset($_POST['vers'])  && isset($_POST['skin'])  && isset($_POST['extension'])){
				$nom = $_POST['nom'];
				$vers = $_POST['vers'];
				$skin = $_POST['skin'];
				$skinTable = explode(",", $skin);
				$extension = $_POST['extension'];
				$extensionTable = explode(",", $extension);
				$var = 0;
				if($skinTable[0] != "") {	
					foreach($skinTable as $valueSkin) {
						$testSkin = "SELECT * FROM skin WHERE n_skin = '$valueSkin'"; 
						$queryTestSkin = pg_query($connexion, $testSkin);
						if (pg_num_rows($queryTestSkin) == 0) {
							 echo"Skin '".$valueSkin."' non connu </br>";
							$var = 1;
							//header("http://tuxa.sme.utc/~nf17a017/projet/modele.php");
						}
					}
				}
				
				if($extensionTable[0] != "") {	
					foreach($extensionTable as $valueExtension) {
						$testExtension = "SELECT * FROM extension WHERE n_extension = '$valueExtension'"; 
						$queryTestExtension = pg_query($connexion, $testExtension);
						if (pg_num_rows($queryTestExtension) == 0) {
							 echo"Extension '".$valueExtension."' non connue </br>";
							$var = 1;
							//header("http://tuxa.sme.utc/~nf17a017/projet/modele.php");
							}

					}
				}
				if($var == 0) {
				
					$testModele = "SELECT * FROM modele_scenari WHERE nom_modele = $nom"; 
					$queryTestModele = pg_query($connexion, $testModele);
					if (pg_num_rows($queryTestModele) == 1) {
						echo"nom_modele deja existant";
								//header("http://tuxa.sme.utc/~nf17a017/projet/modele.php");
					}
					else {						
						$testVers = "SELECT * FROM modele_scenari WHERE n_vers = '$vers'"; 
						$queryTestVers = pg_query($connexion, $testVers);
						if (pg_num_rows($queryTestVers) == 1) {
							echo"n_vers deja existant";
							//header("http://tuxa.sme.utc/~nf17a017/projet/modele.php");
						}
						else {
							$testArchive = "SELECT * FROM modele_scenari_archive WHERE numero_archive = $nom AND version = '$vers'";
							$queryTestArchive = pg_query($connexion,$testArchive);
							if(pg_num_rows($queryTestArchive) > 0) {
								echo "Il existe déjà une archive de ce modèle. Que voulez vous faire ? </br> <a href='ecraser_archive_modele.php?nom=$nom&vers=$vers&skin=$skin&extension=$extension'> L'écraser</a> &nbsp; &nbsp; &nbsp; <a href='restaurer_archive_modele.php?nom=$nom&vers=$vers'> Restaurer </a>";
							}
							else {							
								$insertion = "INSERT INTO modele_scenari VALUES ($nom, '$vers')";
								$queryInsertion = pg_query($connexion,$insertion);
								foreach($skinTable as $valueSkin) {
									$insertionSkin = "INSERT INTO skin VALUES('$valueSkin', $nom, '$vers')"; 
									$queryInsertionSkin = pg_query($connexion, $insertionSkin);
								}
								foreach($extensionTable as $valueExtension) {
									$insertionExtension = "INSERT INTO extension VALUES('$valueExtension', $nom, '$vers')"; 
									$queryInsertionExtension = pg_query($connexion, $insertionExtension);
								}
					
								echo "Modèle $nom de version $vers inséré. Insertions effectuées";
								}
							}
					}
				}	
		}	
					//header("http://tuxa.sme.utc/~nf17a017/projet");
				
		?>
  </body>
</html>

